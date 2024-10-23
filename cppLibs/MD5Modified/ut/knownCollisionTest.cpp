#include <gtest/gtest.h>
#include <MD5Modified/md5.hpp>
#include "helpers.hpp"

namespace
{

using namespace testHelpers;

namespace FirstPair
{

const uint32_t IV[4] = {
    0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};

const uint32_t msg_0[16] = {
    0x02dd31d1, 0xc4eee6c5, 0x069a3d69, 0x5cf9af98,
    0x87b5ca2f, 0xab7e4612, 0x3e580440, 0x897ffbb8,
    0x0634ad55, 0x02b3f409, 0x8388e483, 0x5a417125,
    0xe8255108, 0x9fc9cdf7, 0xf2bd1dd9, 0x5b3c3780};
const uint32_t msg_1[16] = {
    0xd11d0b96, 0x9c7b41dc, 0xf497d8e4, 0xd555655a,
    0xc79a7335, 0x0cfdebf0, 0x66f12930, 0x8fb109d1,
    0x797f2775, 0xeb5cd530, 0xbaade822, 0x5c15cc79,
    0xddcb74ed, 0x6dd3c55f, 0xd80a9bb1, 0xe3a7cc35};
const uint32_t msg_0_prime[16] = {
    0x02dd31d1, 0xc4eee6c5, 0x069a3d69, 0x5cf9af98,
    0x07b5ca2f, 0xab7e4612, 0x3e580440, 0x897ffbb8,
    0x0634ad55, 0x02b3f409, 0x8388e483, 0x5a41f125,
    0xe8255108, 0x9fc9cdf7, 0x72bd1dd9, 0x5b3c3780};
const uint32_t msg_1_prime[16] = {
    0xd11d0b96, 0x9c7b41dc, 0xf497d8e4, 0xd555655a,
    0x479a7335, 0x0cfdebf0, 0x66f12930, 0x8fb109d1,
    0x797f2775, 0xeb5cd530, 0xbaade822, 0x5c154c79,
    0xddcb74ed, 0x6dd3c55f, 0x580a9bb1, 0xe3a7cc35};

const uint32_t expected_hash[4] = {
    0x9603161f, 0xa30f9dbf, 0x9f65ffbc, 0xf41fc7ef
};

} // namespace FirstPair

namespace SecondPair
{
const uint32_t IV[4] = {
	0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476
};

const uint32_t msg_0[16] = {
    0x02dd31d1, 0xc4eee6c5, 0x069a3d69, 0x5cf9af98,
    0x87b5ca2f, 0xab7e4612, 0x3e580440, 0x897ffbb8,
    0x0634ad55, 0x02b3f409, 0x8388e483, 0x5a417125,
    0xe8255108, 0x9fc9cdf7, 0xf2bd1dd9, 0x5b3c3780,
};
const uint32_t msg_1[16] = {
    0x313e82d8, 0x5b8f3456, 0xd4ac6dae, 0xc619c936, 
    0xb4e253dd, 0xfd03da87, 0x06633902, 0xa0cd48d2,
    0x42339fe9, 0xe87e570f, 0x70b654ce, 0x1e0da880, 
    0xbc2198c6, 0x9383a8b6, 0x2b65f996, 0x702af76f
};
const uint32_t msg_0_prime[16] = {
    0x02dd31d1, 0xc4eee6c5, 0x069a3d69, 0x5cf9af98, 
    0x07b5ca2f, 0xab7e4612, 0x3e580440, 0x897ffbb8,
    0x0634ad55, 0x02b3f409, 0x8388e483, 0x5a41f125, 
    0xe8255108, 0x9fc9cdf7, 0x72bd1dd9, 0x5b3c3780
};
const uint32_t msg_1_prime[16] = {
    0x313e82d8, 0x5b8f3456, 0xd4ac6dae, 0xc619c936, 
    0x34e253dd, 0xfd03da87, 0x06633902, 0xa0cd48d2,
    0x42339fe9, 0xe87e570f, 0x70b654ce, 0x1e0d2880, 
    0xbc2198c6, 0x9383a8b6, 0xab65f996, 0x702af76f
};

const uint32_t expected_hash[4] = {
     0x8d5e7019, 0x61804e08, 0x715d6b58, 0x6324c015
};

}   // namespace secondPair

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

	EXPECT_TRUE(compareWords(H0, H1));
    EXPECT_TRUE(compareWords(H0, FirstPair::expected_hash));
	printWord(H0);
	printWord(H1);
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

	EXPECT_TRUE(compareWords(H0, H1));
    EXPECT_TRUE(compareWords(H0, SecondPair::expected_hash));
	printWord(H0);
	printWord(H1);
}

} // namespace
