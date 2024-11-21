cmake_minimum_required(VERSION 3.20)

add_library(MD5Modified STATIC
    src/md5.cpp
    src/md5Utils.cpp
    src/md5MessageModification.cpp
)

target_include_directories(MD5Modified PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(MD5Modified PUBLIC
    compiler_flags
)

add_subdirectory(ut)
