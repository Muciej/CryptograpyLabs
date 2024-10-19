cmake_minimum_required(VERSION 3.20)

set(CUDA_TEST_TARGET_NAME CudaTest)

add_executable(${CUDA_TEST_TARGET_NAME} test.cu)

target_link_libraries(${CUDA_TEST_TARGET_NAME} PUBLIC
    compiler_flags
)

set_target_properties(${CUDA_TEST_TARGET_NAME}
    PROPERTIES CUDA_SEPARABLE_COMPILATION ON
)

set_target_properties(${CUDA_TEST_TARGET_NAME}
    PROPERTIES POSITION_INDEPENDENT_CODE ON
)

