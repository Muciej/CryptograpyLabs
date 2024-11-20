#include <gtest/gtest.h>
#include <MD5Modified/md5Utils.hpp>
#include <MD5Modified/constants.hpp>
#include "helpers.hpp"
#include "data.hpp"

namespace
{

using namespace MD5Modified;

TEST(MD5Utils, messageDifferenceFunctionKnownPairs)
{
    std::uint32_t difference[16];
    utils::getMessageDifference(FirstPair::msg_0_prime, FirstPair::msg_0, difference);

    EXPECT_TRUE(utils::compareMessages(difference, Constants::deltaM0));

    utils::getMessageDifference(FirstPair::msg_1_prime, FirstPair::msg_1, difference);

    EXPECT_TRUE(utils::compareMessages(difference, Constants::deltaM1));

    utils::getMessageDifference(SecondPair::msg_0_prime, SecondPair::msg_0, difference);

    EXPECT_TRUE(utils::compareMessages(difference, Constants::deltaM0));

    utils::getMessageDifference(SecondPair::msg_1_prime, SecondPair::msg_1, difference);

    EXPECT_TRUE(utils::compareMessages(difference, Constants::deltaM0));
    // utils::printMessage(difference);
    // utils::printMessage(Constants::deltaM1);
}

}