add_executable(fetchd
    main.cpp
)

target_include_directories(fetchd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(fetchd PRIVATE utils)
