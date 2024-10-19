cmake_minimum_required(VERSION 3.20)

add_library(MD5Downloaded STATIC
    src/md5.cpp
)

target_include_directories(MD5Downloaded PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(MD5Downloaded PUBLIC
    compiler_flags
)

