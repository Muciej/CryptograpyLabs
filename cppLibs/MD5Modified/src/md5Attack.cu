#include <cstdint>
#include <curand_kernel.h>

#include <MD5Modified/deviceConstants.cuh>
#include <MD5Modified/md5MessageModification.cuh>

using std::uint32_t;

namespace MD5Modified
{
    using namespace Constants;

    __device__ void getWordDifference(const WordTable a, const WordTable b, WordTable& difference)
    {
        for(int i = 0; i < 4; i++)
        {
            difference[i] = a[i] - b[i];
        }
    }

    __device__ void getMessageDifference(const uint32_t* msgA, const uint32_t* msgB, uint32_t* difference)
    {
        for(int i = 0; i < 16; i++)
        {
            difference[i] = msgA[i] - msgB[i];
        }
    }

    __device__ bool checkDesiredDifference(const uint32_t* msgA, const uint32_t* msgB, const uint32_t* desiredDifference)
    {
        bool isGood = true;
        for(int i = 0; i < 16; i++)
        {
            if(desiredDifference[i] != msgA[i] - msgB[i])
            {
                isGood = false;
            }
        }
        return isGood;
    }

    __device__ std::uint32_t func(int it, std::uint32_t abcd[4])
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

    __device__ std::uint32_t rol(std::uint32_t r, std::uint8_t N)
    {
        return (r << N) | (r >> (32 - N));
    }

    __device__ std::uint32_t unrol(std::uint32_t r, std::uint8_t N)
    {
        return (r >> N) | (r << (32 - N));
    }

    __device__ void md5(const WordTable h0, const std::uint32_t* msg, WordTable h)
    {
        WordTable state;
        std::int16_t m, o, inputInd;
        std::uint32_t f;
        const std::uint8_t* rotn;

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

    __device__ void md5FirstPart(uint32_t* msg, WordTable h)
    {
        WordTable state;
        std::int16_t m, o, inputInd;
        std::uint32_t f;
        const std::uint8_t* rotn;

        for (int i = 0; i < 4; i++)
        {
            state[i] = h[i] = def_h0[i];			// init with default start vector
        }

        rotn = rots[0];
        m = M[0]; o = O[0];
        for (int q = 0; q < 16; q++)
        {
            inputInd = (m * q + o) % 16;
            f = state[1] + rol(state[0] + func(0, state) + constTable[q] + msg[inputInd], rotn[q % 4]);

            // MODIFICATION
            FirstPart::modifications[q](f, state);
            msg[inputInd] = unrol(f - state[1], rotn[q % 4]);

            state[0] = state[3];
            state[3] = state[2];
            state[2] = state[1];
            state[1] = f;
        }

        for (int mainIteration = 1; mainIteration < 4; mainIteration++)
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

    __device__ void md5SecondPart(const WordTable h0, std::uint32_t* msg, uint32_t* h)
    {
        uint32_t* state;
        std::int16_t m, o, inputInd;
        std::uint32_t f;
        const std::uint8_t* rotn;

        for (int i = 0; i < 4; i++)
        {
            state[i] = h[i] = h0[i];			// init with default start vector
        }

        rotn = rots[0];
        m = M[0]; o = O[0];
        for (int q = 0; q < 16; q++)
        {
            inputInd = (m * q + o) % 16;
            f = state[1] + rol(state[0] + func(0, state) + constTable[q] + msg[inputInd], rotn[q % 4]);

            // MODIFICATION
            SecondPart::modifications[q](f, state);
            msg[inputInd] = unrol(f - state[1], rotn[q % 4]);

            state[0] = state[3];
            state[3] = state[2];
            state[2] = state[1];
            state[1] = f;
        }

        for (int mainIteration = 1; mainIteration < 4; mainIteration++)
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

    __global__ void attackFirstPart(uint32_t* msg0, uint32_t* msg0Prime, uint32_t* result, uint32_t* resultPrime, int* isDifferentialFound)
    {
        // initialize CUDA random generator
        const uint32_t idx = threadIdx.x + blockIdx.x * blockDim.x;

        curandState generator{};
        curand_init(idx, idx, 0, &generator);

        // init variables
        uint32_t msg0Local[16];
        uint32_t msg0PrimeLocal[16];

        // calculate MD5 with message modification for round one
        while(*isDifferentialFound <= 0)
        {
            // random message selection
            for(auto& word : msg0Local)
            {
                word = curand(&generator);
            }

            md5FirstPart(msg0Local, result);

            for(int i = 0; i < 16; i++)
            {
                msg0PrimeLocal[i] = msg0Local[i] + Constants::deltaM0[i];
            }

            if(checkDesiredDifference(resultPrime, result, Constants::deltaH1))
            {
                atomicAdd(isDifferentialFound, 1);
            }
        }

        for(int i = 0; i < 16; i++)
        {
            msg0[i] = msg0Local[i];
            msg0Prime[i] = msg0PrimeLocal[i];
        }
    }

    __global__ void attackSecondPart(uint32_t* msg1, uint32_t* msg1Prime, const uint32_t* IV, const uint32_t* IVPrime, int* isCollisionFound)
    {
        // initialize CUDA random generator
        const uint32_t idx = threadIdx.x + blockIdx.x * blockDim.x;

        curandState generator{};
        curand_init(idx, idx, 0, &generator);

        // init variables
        uint32_t msg1Local[16];
        uint32_t msg1PrimeLocal[16];
        uint32_t result[4];
        uint32_t resultPrime[4];

        // calculate MD5 with message modification for round one
        while(*isCollisionFound <= 0)
        {
            // random message selection
            for(auto& word : msg1Local)
            {
                word = curand(&generator);
            }

            md5SecondPart(IV, msg1Local, result);

            for(int i = 0; i < 16; i++)
            {
                msg1PrimeLocal[i] = msg1Local[i] + Constants::deltaM1[i];
            }

            md5(IVPrime, msg1PrimeLocal, resultPrime);

            bool areEqual = true;
            for (int i = 0; i < 4; i++) {
                if (result[i] != resultPrime[i]) {
                    areEqual = false;
                }
            }

            if(areEqual)
            {
                atomicAdd(isCollisionFound, 1);
            }
        }

        for(int i = 0; i < 16; i++)
        {
            msg1[i] = msg1Local[i];
            msg1Prime[i] = msg1PrimeLocal[i];
        }
    }

    void fullAttack(uint32_t* msg0, uint32_t* msg0Prime, uint32_t* msg1, uint32_t* msg1Prime)
    {
        uint32_t* result;
        uint32_t* resultPrime;
        int* isCollisionFound;
        int* isDifferentialFound;

        // allocate CUDA memory
        cudaMallocManaged(&result, 4 * sizeof(uint32_t));
        cudaMallocManaged(&resultPrime, 4 * sizeof(uint32_t));
        cudaMallocManaged(&isCollisionFound, sizeof(int));
        cudaMallocManaged(&isDifferentialFound, sizeof(int));

        // run attack in a loop
        while(*isCollisionFound <= 0)
        {
            *isDifferentialFound = 0;
            attackFirstPart<<<32, 256>>>(msg0, msg0Prime, msg1, msg1Prime, isDifferentialFound);
            attackSecondPart<<<32, 256>>>(msg1, msg1Prime, result, resultPrime, isCollisionFound);
        }
    }

} // namespace MD5Modified