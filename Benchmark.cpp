#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <immintrin.h>	// header for SIMD
#include <tbb/concurrent_vector.h>	// header for permanently valid pointer vector container
#include <tbb/cache_aligned_allocator.h>	// header for memory allign-64bit
#include <tbb/parallel_sort.h>	// header for parallel sort	
#include <tbb/parallel_for.h>	// header for parallel in for loop
#include <tbb/task_arena.h> // header for task arena
#include <benchmark/benchmark.h>	// header for C++ program benchmark				
#include <random>	// header for random inting point number
#include <float.h>
#include <span>
#include <map>
#include <set>
#include <algorithm>

constexpr int MAX_NUM = 1 << 25;
#define BENCHMARK_TEST(x) BENCHMARK(x)->Arg(2)

using std::cout;
using std::span;
using std::vector;
using std::string;
using tbb::concurrent_vector;
using tbb::cache_aligned_allocator;
using tbb::parallel_for;
using tbb::parallel_sort;
using std::map;
using std::set;


#define parallel_sort_benchmark
#define normal_sort
#define SIMD_Only_Test
#define SIMD_MulThread_Test
#define Non_SIMD_MulThread

#ifdef  parallel_sort_benchmark

void Parallel_sort(vector<int> &arr) {
		parallel_sort(arr.begin(), arr.end());
}


void BM_Parallel_sort(benchmark::State& state) {
	std::vector<int> arr;
	arr.reserve(MAX_NUM);


	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(INT_MIN, INT_MAX);
	
	for (unsigned i = 0; i < MAX_NUM; ++i) {
			arr.push_back( distrib(gen));
	}

	for (auto _ : state){
			Parallel_sort(arr);
	}
}

BENCHMARK(BM_Parallel_sort); 
BENCHMARK(BM_Parallel_sort)->ThreadPerCpu();

#endif

#ifdef normal_sort

void Normal_sort(vector<int> &arr) {
		std::sort(arr.begin(), arr.end());
}

void BM_Normal_sort(benchmark::State& state) {

	std::vector<int> arr;
	arr.reserve(MAX_NUM);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(INT_MIN, INT_MAX);
	
	for (unsigned i = 0; i < MAX_NUM; ++i) {
			arr.push_back( distrib(gen));
	}

	for (auto _ : state){
			Normal_sort(arr);
	}
}


BENCHMARK(BM_Normal_sort); 
BENCHMARK(BM_Normal_sort)->ThreadPerCpu();

#endif


#ifdef Non_SIMD_MulThread

void non_SIMD_MulThread(vector<float, cache_aligned_allocator<float>> &arr1,
				vector<float, cache_aligned_allocator<float>> &arr2,
				vector<float, cache_aligned_allocator<float>> &arr3,
				vector<float, cache_aligned_allocator<float>> &arr4,
				vector<float, cache_aligned_allocator<float>> &result) {
				
		auto Begin1 = arr1.begin(), Begin2 = arr2.begin(),
			 Begin3 = arr3.begin(), Begin4 = arr4.begin();
		auto End = arr1.end();
		auto r_addr = result.begin();

		while (Begin1 != End) {
				float tmp1 = *Begin1 / (*Begin2);	
				float tmp2 = *Begin3 / (*Begin4);
				float result = tmp1 * tmp2;

				*r_addr = result;
				
				Begin1 = Begin1 + 1, Begin2 = Begin2 + 1;
				Begin3 = Begin3 + 1, Begin4 = Begin4 + 1;
				r_addr = r_addr + 1;
		}
}

void BM_non_SIMD_MulThread(benchmark::State & state) {

	constexpr unsigned MAX = 1 << 20;

	vector<float, cache_aligned_allocator<float>> arr1, arr2, arr3, arr4;
	vector<float, cache_aligned_allocator<float>> result;

	arr1.reserve(MAX);
	arr2.reserve(MAX);
	arr3.reserve(MAX);	
	arr4.reserve(MAX);	
	result.reserve(MAX);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> distrib(FLT_MIN, FLT_MAX);

	for (unsigned i = 0; i < MAX; ++i) {
			arr1.push_back(distrib(gen));
			arr2.push_back(distrib(gen));
			arr3.push_back(distrib(gen));
			arr4.push_back(distrib(gen));
	}

	for (auto _ : state) {
			non_SIMD_MulThread(arr1, arr2, arr3, arr4, result);
	}
}

BENCHMARK(BM_non_SIMD_MulThread);
BENCHMARK(BM_non_SIMD_MulThread)->ThreadPerCpu();

#endif


#ifdef SIMD_Only_Test

void SIMD_Only(vector<float, cache_aligned_allocator<float>> &arr1,
				vector<float, cache_aligned_allocator<float>> &arr2,
				vector<float, cache_aligned_allocator<float>> &arr3,
				vector<float, cache_aligned_allocator<float>> &arr4,
				vector<float, cache_aligned_allocator<float>> &result) {
		__m256 m1, m2, m3, m4;
		__m256 r1;

		auto Begin1 = arr1.begin(), Begin2 = arr2.begin(),
			 Begin3 = arr3.begin(), Begin4 = arr4.begin();
		auto End = arr1.end();
		auto r_addr = result.begin();

		while (Begin1 != End) {
				m1 = _mm256_load_ps(&*Begin1);
				m2 = _mm256_load_ps(&*Begin2);
				m3 = _mm256_load_ps(&*Begin3);
				m4 = _mm256_load_ps(&*Begin4);

				__m256 tmp1, tmp2;
				tmp1 = _mm256_div_ps(m1, m2);
				tmp2 = _mm256_div_ps(m3, m4);
				r1 = _mm256_mul_ps(tmp1, tmp2);	

				_mm256_store_ps(&*r_addr, r1);

				Begin1 = Begin1 + 8, Begin2 = Begin2 + 8;
				Begin3 = Begin3 + 8, Begin4 = Begin4 + 8;
				r_addr = r_addr + 8;
		}
}

void BM_SIMD_Only(benchmark::State& state){
	constexpr unsigned MAX = 1 << 20;

	vector<float, cache_aligned_allocator<float>> arr1, arr2, arr3, arr4;
	vector<float, cache_aligned_allocator<float>> result;

	arr1.reserve(MAX);
	arr2.reserve(MAX);
	arr3.reserve(MAX);	
	arr4.reserve(MAX);	
	result.reserve(MAX);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> distrib(FLT_MIN, FLT_MAX);

	for (unsigned i = 0; i < MAX; ++i) {
			arr1.push_back(distrib(gen));
			arr2.push_back(distrib(gen));
			arr3.push_back(distrib(gen));
			arr4.push_back(distrib(gen));
	}

	for (auto _ : state) {
			SIMD_Only(arr1, arr2, arr3, arr4, result);
	}
}

BENCHMARK(BM_SIMD_Only);
BENCHMARK(BM_SIMD_Only)->ThreadPerCpu();

#endif


#ifdef SIMD_MulThread_Test


void SIMD_MulThread(span<float> arr1, span<float> arr2, span<float> arr3, 
				span<float> arr4, span<float> result) {

		__m256 m1, m2, m3, m4;
		__m256 r1;
                                                          
	  	auto Begin1 = arr1.begin(), Begin2 = arr2.begin(),
        	 Begin3 = arr3.begin(), Begin4 = arr4.begin();
        auto End = arr1.end();
        auto r_addr = result.begin();
                                                          
        while (Begin1 != End) {
        		m1 = _mm256_load_ps(&*Begin1);
        		m2 = _mm256_load_ps(&*Begin2);
        		m3 = _mm256_load_ps(&*Begin3);
        		m4 = _mm256_load_ps(&*Begin4);
                                                          
        		__m256 tmp1, tmp2;
        		tmp1 = _mm256_div_ps(m1, m2);
        		tmp2 = _mm256_div_ps(m3, m4);
        		r1 = _mm256_mul_ps(tmp1, tmp2);	
                                                          
        		_mm256_store_ps(&*r_addr, r1);
                                                          
        		Begin1 = Begin1 + 8, Begin2 = Begin2 + 8;
        		Begin3 = Begin3 + 8, Begin4 = Begin4 + 8;
				r_addr = r_addr + 8;
		}
}


void BM_SIMD_MulThread(benchmark::State &state) {
		
		constexpr unsigned length = 1 << 8;
		tbb::task_arena Arena(2);


		constexpr unsigned MAX = 1 << 20;

		vector<float, cache_aligned_allocator<float>> arr1, arr2, arr3, arr4;
		vector<float, cache_aligned_allocator<float>> result;

		arr1.reserve(MAX);
		arr2.reserve(MAX);
		arr3.reserve(MAX);	
		arr4.reserve(MAX);	
		result.reserve(MAX);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::normal_distribution<> distrib(FLT_MIN, FLT_MAX);

		for (unsigned i = 0; i < MAX; ++i) {
			arr1.push_back(distrib(gen));
			arr2.push_back(distrib(gen));
			arr3.push_back(distrib(gen));
			arr4.push_back(distrib(gen));
		}

		for (auto _ : state) {
		Arena.execute([&]() {
						parallel_for(unsigned(0), unsigned(arr1.size()), length, [&](unsigned i) {
							unsigned step = i + length;
							SIMD_MulThread(span<float>(arr1.begin() + i, arr1.begin() + step),
											span<float>(arr2.begin() + i, arr2.begin() + step),
											span<float>(arr3.begin() + i, arr3.begin() + step),
											span<float>(arr4.begin() + i, arr4.begin() + step),
											span<float>(result.begin() + i, result.begin() + step));
						});});
		}
}

BENCHMARK(BM_SIMD_MulThread);
BENCHMARK(BM_SIMD_MulThread)->ThreadPerCpu();
BENCHMARK_MAIN();

#endif
