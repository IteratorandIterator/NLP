cmake_minimum_required(VERSION 3.12)

project(TEST LANGUAGES CXX)

set(CMAKE_CXX_COMPILER "/usr/local/clang/bin/clang++")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-mavx2)
#add_library(benchmark SHARED ${/usr/local/benchmark/lib})
#add_library(TBB SHARED ${/usr/local/tbb/lib})

add_executable(Benchmark)
target_sources(Benchmark PUBLIC Benchmark.cpp)
find_package(benchmark REQUIRED)
find_package(TBB REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(Benchmark PUBLIC Threads::Threads)
target_link_libraries(Benchmark PUBLIC benchmark::benchmark)
target_link_libraries(Benchmark PUBLIC TBB::tbb)
