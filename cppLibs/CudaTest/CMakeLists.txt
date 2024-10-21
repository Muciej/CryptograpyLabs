cmake_minimum_required(VERSION 3.20)

set(CUDA_TEST_TARGET_NAME CudaTest)

add_library(${CUDA_TEST_TARGET_NAME} STATIC
    test.cu
)

target_include_directories(${CUDA_TEST_TARGET_NAME} PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${CUDA_TEST_TARGET_NAME} PUBLIC
    compiler_flags
)

set_target_properties(${CUDA_TEST_TARGET_NAME}
    PROPERTIES CUDA_SEPARABLE_COMPILATION ON
)

set_target_properties(${CUDA_TEST_TARGET_NAME}
    PROPERTIES POSITION_INDEPENDENT_CODE ON
)

