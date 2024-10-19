enable_testing()

set(SOURCES
    crossCheckTest.cpp
)

add_executable(MD5ModifiedTest ${SOURCES})

target_link_libraries( MD5ModifiedTest PRIVATE
    GTest::gtest_main
    MD5Downloaded
)
