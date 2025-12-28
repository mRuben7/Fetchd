#include "main.h"

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
    std::cout << "Received signal: " << signal << '\n';
    isRunning = false;
}

int main() {
    // Register signal handlers
    std::signal(SIGINT, handle_signal);   // Ctrl+C
    std::signal(SIGTERM, handle_signal);  // kill

    std::cout << "fetchd: daemon started\n";

    while (isRunning) {
        std::cout << "fetchd: running\n";
        std::raise(SIGTERM);
    }

    std::cout << "fetchd: daemon stopping\n";
    return 0;
}
