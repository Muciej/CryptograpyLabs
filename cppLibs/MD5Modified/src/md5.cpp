#include <MD5Modified/md5.hpp>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdint>

namespace MD5Modified
{


const std::int16_t M[] = { 1, 5, 3, 7 };		// to calculate input visiting sequence
const std::int16_t O[] = { 0, 1, 5, 0 };		// input_ind = m * it + q
const std::int16_t rot0[] = { 7, 12, 17, 22 };
const std::int16_t rot1[] = { 5, 9, 14, 20 };
const std::int16_t rot2[] = { 4, 11, 16, 23 };
const std::int16_t rot3[] = { 6, 10, 15, 21 };
const std::int16_t *rots[] = { rot0, rot1, rot2, rot3 };
const WordTable def_h0 = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };

const std::uint32_t constTable[] =
{
	3614090360, 3905402710, 606105819, 3250441966, 
	4118548399, 1200080426, 2821735955, 4249261313, 
	1770035416, 2336552879, 4294925233, 2304563134, 
	1804603682, 4254626195, 2792965006, 1236535329, 
	4129170786, 3225465664, 643717713, 3921069994, 
	3593408605, 38016083, 3634488961, 3889429448, 
	568446438, 3275163606, 4107603335, 1163531501, 
	2850285829, 4243563512, 1735328473, 2368359562, 
	4294588738, 2272392833, 1839030562, 4259657740, 
	2763975236, 1272893353, 4139469664, 3200236656, 
	681279174, 3936430074, 3572445317, 76029189, 
	3654602809, 3873151461, 530742520, 3299628645, 
	4096336452, 1126891415, 2878612391, 4237533241, 
	1700485571, 2399980690, 4293915773, 2240044497, 
	1873313359, 4264355552, 2734768916, 1309151649, 
	4149444226, 3174756917, 718787259, 3951481745
};

constexpr std::uint32_t func(int it, std::uint32_t abcd[4])
{
	switch (it)
	{
	case 0:
		return (abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]);
		break;
	case 1:
		return (abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]);
		break;
	case 2:
		return  abcd[1] ^ abcd[2] ^ abcd[3];
		break;
	case 3:
		return abcd[2] ^ (abcd[1] | ~abcd[3]);
		break;
	}
	return 0;
}

constexpr std::uint32_t rol(std::uint32_t r, std::int16_t N)
{
	std::uint32_t  mask1 = (1 << N) - 1;
	return ((r >> (32 - N)) & mask1) | ((r << N) & ~mask1);
}

void MD5HashNonPadded(const WordTable h0, const std::uint32_t* msg, WordTable h)
{
	WordTable state;
	std::int16_t m, o, inputInd;
	std::uint32_t f;
	const std::int16_t* rotn;

	for (int i = 0; i < 4; i++)
	{
		state[i] = h[i] = h0[i];			// init with start vector
	}
	for (int mainIteration = 0; mainIteration < 4; mainIteration++)
	{
		rotn = rots[mainIteration];
		m = M[mainIteration]; o = O[mainIteration];
		for (int q = 0; q < 16; q++)
		{
			inputInd = (m * q + o) % 16;
			f = state[1] + rol(state[0] + func(mainIteration, state) + constTable[q + 16 * mainIteration] + msg[inputInd], rotn[q % 4]);

			state[0] = state[3];
			state[3] = state[2];
			state[2] = state[1];
			state[1] = f;
		}
	}
	for (int i = 0; i<4; i++)
	{
		h[i] += state[i];				// init state + state after iterations
	}
}

} // namespace MD5Modified
