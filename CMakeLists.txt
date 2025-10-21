cmake_minimum_required(VERSION 3.15)
project(tablr VERSION 0.0.0 LANGUAGES C CXX)

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
    enable_language(CUDA)
    target_compile_definitions(tablr PUBLIC TABLR_CUDA_ENABLED)
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
