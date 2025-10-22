cmake_minimum_required(VERSION 3.15)
project(tablr VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

option(TABLR_BUILD_TESTS "Build tests" OFF)
option(TABLR_BUILD_EXAMPLES "Build examples" OFF)
option(TABLR_CUDA_SUPPORT "Enable CUDA support" OFF)
option(TABLR_XPU_SUPPORT "Enable Intel XPU support" OFF)
option(TABLR_NPU_SUPPORT "Enable NPU support" OFF)
option(TABLR_TPU_SUPPORT "Enable TPU support" OFF)

file(GLOB TABLR_CORE_SOURCES "src/core/*.c")
file(GLOB TABLR_IO_SOURCES "src/io/*.c")
file(GLOB TABLR_OPS_SOURCES "src/ops/*.c")
file(GLOB TABLR_DEVICE_SOURCES "src/device/*.c")
file(GLOB_RECURSE TABLR_HEADERS "include/tablr/*.h")

set(TABLR_SOURCES 
    ${TABLR_CORE_SOURCES}
    ${TABLR_IO_SOURCES}
    ${TABLR_OPS_SOURCES}
    ${TABLR_DEVICE_SOURCES}
)

add_library(tablr STATIC ${TABLR_SOURCES})
target_include_directories(tablr PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(TABLR_CUDA_SUPPORT)
    include(CheckLanguage)
    check_language(CUDA)
    if(CMAKE_CUDA_COMPILER)
        enable_language(CUDA)
        find_package(CUDAToolkit REQUIRED)
        target_sources(tablr PRIVATE "src/device/cuda_ops.cu")
        target_compile_definitions(tablr PUBLIC TABLR_CUDA_ENABLED)
        target_link_libraries(tablr PUBLIC CUDA::cudart)
        set_target_properties(tablr PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
        message(STATUS "CUDA support enabled")
    else()
        message(WARNING "CUDA compiler not found. Building without CUDA support.")
        set(TABLR_CUDA_SUPPORT OFF)
    endif()
endif()

if(TABLR_XPU_SUPPORT)
    target_sources(tablr PRIVATE "src/device/xpu_ops.cpp")
    target_compile_definitions(tablr PUBLIC TABLR_XPU_ENABLED)
    target_link_libraries(tablr PUBLIC sycl)
endif()

if(TABLR_NPU_SUPPORT)
    target_sources(tablr PRIVATE "src/device/npu_ops.c")
    target_compile_definitions(tablr PUBLIC TABLR_NPU_ENABLED)
endif()

if(TABLR_TPU_SUPPORT)
    target_sources(tablr PRIVATE "src/device/tpu_ops.c")
    target_compile_definitions(tablr PUBLIC TABLR_TPU_ENABLED)
endif()

if(TABLR_BUILD_TESTS AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")
    enable_testing()
    add_subdirectory(tests)
endif()

if(TABLR_BUILD_EXAMPLES AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/examples")
    add_subdirectory(examples)
endif()

install(TARGETS tablr EXPORT tablrTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)
