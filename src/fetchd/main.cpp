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

int main() {
    // Register signal handlers
    std::signal(SIGINT, handle_signal);   // Ctrl+C
    std::signal(SIGTERM, handle_signal);  // kill

    USER_INFO("fetchd: daemon started");

    while (isRunning) {
        std::cout << "fetchd: running\n";
        std::raise(SIGTERM);
    }

    USER_INFO("fetchd: daemon stopping");
    return 0;
}
