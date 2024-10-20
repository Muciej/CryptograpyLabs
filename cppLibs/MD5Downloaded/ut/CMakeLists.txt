enable_testing()

set(SOURCES
    basicTest.cpp
)

add_executable(MD5DownloadedTest ${SOURCES})

target_link_libraries(MD5DownloadedTest PRIVATE
    GTest::gtest_main
    MD5Downloaded
)