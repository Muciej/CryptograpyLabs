#pragma once

#include <cstdint>

using std::uint32_t;

namespace MD5Modified::MessageModification
{
	__device__ static void overwriteBytes(uint32_t& modified, const uint32_t& abcd, const uint32_t& mask)
	{
		modified = ((modified) & ~(mask)) | ((abcd) & (mask));
	}
}

namespace MD5Modified::SecondPart
{

__device__ static void a_1(uint32_t& modified, const uint32_t*) {
	modified &= 0b11110101111111111111011111011111;
	modified |= 0b10000100001000000000000000000000;
}

__device__ static void d_1(uint32_t& modified, const uint32_t* abcd) {
	MessageModification::overwriteBytes(modified, abcd[1], 0b01110000000111110001000011000000);
	modified &= 0b11111101110111110111111111011001;
	modified |= 0b10001100000000000000100000000000;
}

__device__ static void c_1(uint32_t& modified, const uint32_t* abcd) {
	MessageModification::overwriteBytes(modified, abcd[1], 0b00000000000000000000000000011000);
	modified &= 0b10111111110111111110111101111111;
	modified |= 0b10111110000111110000100101100110;
}

__device__ static void b_1(uint32_t& modified, const uint32_t* abcd) {
	MessageModification::overwriteBytes(modified, abcd[1], 0b00000000000000000000011000000001);
	modified &= 0b10111011110001001110011000010001;
	modified |= 0b10111010000001000000000000010000;
}

__device__ static void a_2(uint32_t& modified, const uint32_t*) {
	modified &= 0b01001011111011111110111001010000;
	modified |= 0b01001000001011110000111001010000;
}

__device__ static void d_2(uint32_t& modified, const uint32_t*) {
	modified &= 0b01100101111011101110110001010110;
	modified |= 0b00000100001000100000110001010110;
}

__device__ static void c_2(uint32_t& modified, const uint32_t* abcd) {
	MessageModification::overwriteBytes(modified, abcd[1], 0b00000001100000001000000000000000);
	modified &= 0b11110111110011011111111000111111;
	modified |= 0b10010110000000010001111000000001;
}

__device__ static void b_2(uint32_t& modified, const uint32_t* abcd) {
	MessageModification::overwriteBytes(modified, abcd[1], 0b00000000000000000000000000000010);
	modified &= 0b11100100011111101111111111111110;
	modified |= 0b10000100001100101000001111000000;
}

__device__ static void a_3(uint32_t& modified, const uint32_t* abcd) {
	MessageModification::overwriteBytes(modified, abcd[1], 0b00000000000000000001000000000000);
	modified &= 0b11111100011111010111110111111101;
	modified |= 0b10011100000000010000000111000001;
}

__device__ static void d_3(uint32_t& modified, const uint32_t*) {
	modified &= 0b11111111111110111110111111111100;
	modified |= 0b10000111100000111000001111000000;
}

__device__ static void c_3(uint32_t& modified, const uint32_t* abcd) {
	MessageModification::overwriteBytes(modified, abcd[1], 0b00000000000010000110000000000000);
	modified &= 0b11111111111111011110111111111111;
	modified |= 0b10000000000001011000001111000011;
}

__device__ static void b_3(uint32_t& modified, const uint32_t* abcd) {
	MessageModification::overwriteBytes(modified, abcd[1], 0b01111111000000000000000000000000);
	modified &= 0b11111111111110000001111111111111;
	modified |= 0b10000000000010000001000010000000;
}

__device__ static void a_4(uint32_t& modified, const uint32_t*) {
	modified &= 0b00111111111111111111111101111111;
	modified |= 0b00111111000011111110000000001000;
}

__device__ static void d_4(uint32_t& modified, const uint32_t*) {
	modified &= 0b01000000111110111111111111111111;
	modified |= 0b01000000000010111110000010001000;
}

__device__ static void c_4(uint32_t& modified, const uint32_t*) {
	modified &= 0b01111101111111110111111111110111;
	modified |= 0b01111101000000000000000000000000;
}

__device__ __device__ static void b_4(uint32_t& modified, const uint32_t*) {
	modified &= 0b01111111111111111111111111111111;
	modified |= 0b00100000000000000000000000000000;
}

typedef void (*Modification)(uint32_t&, const uint32_t* abcd);
__device__ const Modification modifications[16] = { &a_1, &d_1, &c_1, &b_1, &a_2, &d_2, &c_2, &b_2, &a_3, &d_3, &c_3, &b_3, &a_4, &d_4, &c_4, &b_4 };

} // namespace MD5Modified::SecondPart

namespace MD5Modified::FirstPart
{

__device__ static void a_1(uint32_t&, const uint32_t*) {
}

__device__ static void d_1(uint32_t&, const uint32_t*) {
}

__device__ static void c_1(uint32_t& modified, const uint32_t*) {
	modified &= 0b11111111111101111111011110111111;
}

__device__ static void b_1(uint32_t& modified, const uint32_t* abcd) {
	MessageModification::overwriteBytes(modified, abcd[1], 0b00000000011101111111011110000000);
	modified &= 0b11111111011111111111111110111111;
	modified |= 0b10000000000010000000100000000000;
}

__device__ static void a_2(uint32_t& modified, const uint32_t*) {
	modified &= 0b11111101010000000000000000111111;
	modified |= 0b10001000010000000000000000100101;
}

__device__ static void d_2(uint32_t& modified, const uint32_t* abcd) {
	MessageModification::overwriteBytes(modified, abcd[1], 0b01110101000000000000000000011010);
	modified &= 0b01110111011111111011110001011011;
	modified |= 0b00000010011111111011110001000001;
}

__device__ static void c_2(uint32_t& modified, const uint32_t*) {
	modified &= 0b00000011111111101111100000100000;
	modified |= 0b00000011111111101111100000100000;
}

__device__ static void b_2(uint32_t& modified, const uint32_t*) {
	modified &= 0b00000001111100010101010101000000;
	modified |= 0b00000001100100010000010101000000;
}

__device__ static void a_3(uint32_t& modified, const uint32_t* abcd) {
	MessageModification::overwriteBytes(modified, abcd[1], 0b00000000000000000001000000000000);
	modified &= 0b11111011111100000111111100111101;
	modified |= 0b11111011000100000010111100111101;
}

__device__ static void d_3(uint32_t& modified, const uint32_t*) {
	modified &= 0b01111111011111111101111001111100;
	modified |= 0b01000000000111111001000001000000;
}

__device__ static void c_3(uint32_t& modified, const uint32_t* abcd) {
	MessageModification::overwriteBytes(modified, abcd[1], 0b00000000000000000100000000000000);
	modified &= 0b00111111111100011100111011111110;
	modified |= 0b00000000000000011000000011000010;
}

__device__ static void b_3(uint32_t& modified, const uint32_t* abcd) {
	MessageModification::overwriteBytes(modified, abcd[1], 0b00000011000000000000000000000000);
	modified &= 0b00111111111110000001111101111111;
	modified |= 0b00000000000010000001000100000000;
}

__device__ static void a_4(uint32_t& modified, const uint32_t*) {
	modified &= 0b01111101111111111111111001111111;
	modified |= 0b01000001000011111110000000001000;
}

__device__ static void d_4(uint32_t& modified, const uint32_t*) {
	modified &= 0b01011100111110111111111111111111;
	modified |= 0b00000000000010111110000110001000;
}

__device__ static void c_4(uint32_t& modified, const uint32_t*) {
	modified &= 0b01111101111111111111111111110111;
	modified |= 0b00100001000000001000000000000000;
}

__device__ static void b_4(uint32_t& modified, const uint32_t*) {
	modified &= 0b01111111111111111111111111111111;
	modified |= 0b00100000000000000000000000000000;
}

typedef void (*Modification)(uint32_t&, const uint32_t* abcd);
__device__ const Modification modifications[16] = { &a_1, &d_1, &c_1, &b_1, &a_2, &d_2, &c_2, &b_2, &a_3, &d_3, &c_3, &b_3, &a_4, &d_4, &c_4, &b_4 };

} // namespace MD5Modified::FirstPart