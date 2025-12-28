#pragma once
#include <iostream>
#include <cstring>


// Helper functions

inline const char* simplifyFile(const char* path) {
    const char* file = std::strrchr(path, '/'); // get last / position
    return file ? file + 1 : path; // read file name from the next position of / or return the original var
}


// Verbose logs that show file, line and function from where they're called

#ifndef NDEBUG
    #define DEBUG_LOG_V(msg) \
        do { \
        const char* file = simplifyFile(__FILE__); \
        std::cout << "[DEBUG] " \
                  << file << ":" << __LINE__ \
                  << " (" << __func__ << ") " \
                  << msg << '\n'; \
    } while (0)
#else
    #define DEBUG_LOG_V(msg) do {} while (0)
#endif

#define INFO_LOG_V(msg) \
    do { \
        const char* file = simplifyFile(__FILE__); \
        std::cout << "[INFO] " \
                  << file << ":" << __LINE__ \
                  << " (" << __func__ << ") " \
                  << msg << '\n'; \
    } while (0)

#define ERROR_LOG_V(msg) \
    do { \
        const char* file = simplifyFile(__FILE__); \
        std::cerr << "[ERROR] " \
                  << file << ":" << __LINE__ \
                  << " (" << __func__ << ") " \
                  << msg << '\n'; \
    } while (0)


// Simple logs that only show the message

#ifndef NDEBUG
    #define DEBUG_LOG(msg) \
        do { std::cout << "[DEBUG] " << msg << '\n'; } while (0)
#else
    #define DEBUG_LOG(msg) do {} while (0)
#endif

#define INFO_LOG(msg) \
    do { std::cout << "[INFO] " << msg << '\n'; } while (0)

#define ERROR_LOG(msg) \
    do { std::cerr << "[ERROR] " << msg << '\n'; } while (0)


// User outputs which don't even have the brackets prefix

#define USER_INFO(msg) \
    do { std::cout << msg << '\n'; } while (0)