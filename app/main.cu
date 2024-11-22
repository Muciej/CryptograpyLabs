#include <iostream>
#include <MD5Modified/md5Attack.cuh>
#include <MD5Modified/md5Utils.hpp>
#include <MD5Modified/data.hpp>

void fullMain()
{
	uint32_t* msg0;
	uint32_t* msg0Prime;
	uint32_t* msg1;
	uint32_t* msg1Prime;

    cudaMallocManaged(&msg0, 16 * sizeof(uint32_t));
    cudaMallocManaged(&msg0Prime, 16 * sizeof(uint32_t));
    cudaMallocManaged(&msg1, 16 * sizeof(uint32_t));
    cudaMallocManaged(&msg1Prime, 16 * sizeof(uint32_t));

    MD5Modified::fullAttack(msg0, msg0Prime, msg1, msg1Prime);

    MD5Modified::utils::printMessage(msg0);
    MD5Modified::utils::printMessage(msg0Prime);
    MD5Modified::utils::printMessage(msg1);
    MD5Modified::utils::printMessage(msg1Prime);
}

void onlyEx3()
{
	uint32_t* msg0;
	uint32_t* msg0Prime;
	uint32_t* msg1;
	uint32_t* msg1Prime;

    cudaMallocManaged(&msg0, 16 * sizeof(uint32_t));
    cudaMallocManaged(&msg0Prime, 16 * sizeof(uint32_t));
    cudaMallocManaged(&msg1, 16 * sizeof(uint32_t));
    cudaMallocManaged(&msg1Prime, 16 * sizeof(uint32_t));

	for (uint16_t i = 0; i < 16; i++) {
		msg0[i] = FirstPair::msg_0[i];
		msg0Prime[i] = FirstPair::msg_0_prime[i];
	}

    MD5Modified::onlySecondPart(msg0, msg0Prime, msg1, msg1Prime);

    MD5Modified::utils::printMessage(msg1);
    MD5Modified::utils::printMessage(msg1Prime);
}

int main()
{
    // fullMain();
    onlyEx3();

    return 0;
}