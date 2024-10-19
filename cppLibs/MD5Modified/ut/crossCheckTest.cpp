#include <gtest/gtest.h>
#include <MD5Downloaded/md5.hpp>
#include <string>

TEST(MD5DownloadedTest, basicHash)
{
    const std::string msg = "TestMsg";
    const auto hash = MD5Downloaded::GetMD5String(msg);
    EXPECT_EQ(hash, "5109e515f8e9a33c0d43f4c3d8901359");
}

