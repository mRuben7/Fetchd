#include "main.h"
#include "log.h"

#include <atomic>
#include <csignal>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstring>

// Global flag used by main loop
static std::atomic<bool> isRunning{true};

// Signal handler
void handle_signal(int signal) {
    DEBUG_LOG("Received signal: " << signal);
    isRunning = false;
}

int create_listener_socket(const char* path) {
    int fd = socket(AF_UNIX, SOCK_STREAM, 0); // creates a file descriptor to handle a kernel object
    if (fd < 0) {
        perror("socket"); // prints info from errno
        return -1;
    }

    sockaddr_un addr{};
    addr.sun_family = AF_UNIX; //set Address Family UNIX
    std::strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);

    // Remove old socket file if it exists
    unlink(path);

    if (bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        perror("bind");
        close(fd);
        return -1;
    }

    if (listen(fd, 5) < 0) {
        perror("listen");
        close(fd);
        return -1;
    }

    return fd;
}

int main() {
    // Register signal handlers
    std::signal(SIGINT, handle_signal);   // Ctrl+C
    std::signal(SIGTERM, handle_signal);  // kill

    USER_INFO("fetchd: daemon started");

    const char* socket_path = "/tmp/fetchd.sock";
    int server_fd = create_listener_socket(socket_path);
    if (server_fd < 0) {
        return 1;
    }

    USER_INFO("fetchd: listening on " << socket_path);

    while (isRunning) {
        INFO_LOG("fetchd: running");
        int client_fd = accept(server_fd, nullptr, nullptr);

        if (client_fd < 0) {
            if (!isRunning) break; // interrupted by signal
            perror("accept");
            continue;
        }

        char buffer[128]{};
        ssize_t n = read(client_fd, buffer, sizeof(buffer) - 1);

        if (n > 0) {
            std::cout << "fetchd: received command: " << buffer;

            if (std::strncmp(buffer, "STOP", 4) == 0) {
                isRunning = false;
            }
        }

        close(client_fd);
    }

    close(server_fd);
    unlink(socket_path);

    USER_INFO("fetchd: daemon stopping");
    return 0;
}
