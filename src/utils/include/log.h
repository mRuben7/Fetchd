#pragma once
#include <iostream>

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

#define USER_INFO(msg) \
    do { std::cout << msg << '\n'; } while (0)