#include <gtest/gtest.h>
#include <MD5Modified/md5.hpp>
#include <MD5Modified/md5Utils.hpp>
#include "helpers.hpp"
#include "data.hpp"

namespace
{

using namespace testHelpers;

TEST(CollisionTest, FirstKnownCollision)
{
	uint32_t h0[4];
	uint32_t h1[4];
	uint32_t H0[4];
	uint32_t H1[4];

	MD5Modified::MD5HashNonPadded(FirstPair::IV, FirstPair::msg_0, h0);
	MD5Modified::MD5HashNonPadded(h0, FirstPair::msg_1, H0);

	MD5Modified::MD5HashNonPadded(FirstPair::IV, FirstPair::msg_0_prime, h1);
	MD5Modified::MD5HashNonPadded(h1, FirstPair::msg_1_prime, H1);

	EXPECT_TRUE(MD5Modified::utils::compareWords(H0, H1));
    EXPECT_TRUE(MD5Modified::utils::compareWords(H0, FirstPair::expected_hash));
	MD5Modified::utils::printWord(H0);
	MD5Modified::utils::printWord(H1);
}

TEST(CollisionTest, SecondKnownCollision)
{
	uint32_t h0[4];
	uint32_t h1[4];
	uint32_t H0[4];
	uint32_t H1[4];

	MD5Modified::MD5HashNonPadded(SecondPair::IV, SecondPair::msg_0, h0);
	MD5Modified::MD5HashNonPadded(h0, SecondPair::msg_1, H0);

	MD5Modified::MD5HashNonPadded(SecondPair::IV, SecondPair::msg_0_prime, h1);
	MD5Modified::MD5HashNonPadded(h1, SecondPair::msg_1_prime, H1);

	EXPECT_TRUE(MD5Modified::utils::compareWords(H0, H1));
    EXPECT_TRUE(MD5Modified::utils::compareWords(H0, SecondPair::expected_hash));
	MD5Modified::utils::printWord(H0);
	MD5Modified::utils::printWord(H1);
}

} // namespace
