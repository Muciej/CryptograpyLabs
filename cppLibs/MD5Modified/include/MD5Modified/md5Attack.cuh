#pragma once

#include <cstdint>

using std::uint32_t;

namespace MD5Modified
{

    // __global__ void attackFirstPart(uint32_t* msg0, uint32_t* msg0Prime, uint32_t* result, uint32_t* resultPrime, int* isDifferentialFound);
    // __global__ void attackSecondPart(uint32_t* msg1, uint32_t* msg1Prime, const uint32_t* IV, const uint32_t* IVPrime, int* isCollisionFound);
    void fullAttack(uint32_t* msg0, uint32_t* msg0Prime, uint32_t* msg1, uint32_t* msg1Prime);

} // namespace MD5Modified