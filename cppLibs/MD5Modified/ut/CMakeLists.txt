enable_testing()

set(SOURCES
    helpers.cpp
    crossCheckTest.cpp
    knownCollisionTest.cpp
)

add_executable(MD5ModifiedTest ${SOURCES})

target_link_libraries(MD5ModifiedTest PRIVATE
    GTest::gtest_main
    MD5Modified
    MD5Downloaded
)
