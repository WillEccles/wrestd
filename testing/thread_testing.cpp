#include <iostream>
#include <cstdio>
#include <string>
#include "wrethreading.h"
#include <vector>
#include <chrono>

using namespace wrestd::threading;
using namespace std::chrono;

void benchmark_singlethread(std::size_t datapoints) {
	std::vector<int> vec(datapoints);
	for (std::size_t i = 0; i < datapoints; i++) {
		vec[i] = i%3;
	}

	std::cout << "Using " << datapoints << " pieces of sample data for single-threaded test...\n";

	auto start = steady_clock::now();
	for (std::size_t i = 0; i < datapoints; i++) {
		vec[i] = (vec[i] * 2) % 4;
	}
	auto end = steady_clock::now();
	std::printf("Finished single-thread benchmark in %.5g seconds.\n", duration_cast<duration<double>>(end - start).count() * (double)seconds::period::num / (double)seconds::period::den);
}

void benchmark_multithread(std::size_t datapoints) {
	std::vector<int> vec(datapoints);
	for (std::size_t i = 0; i < datapoints; i++)
	{
		vec[i] = i % 3;
	}
	std::size_t tcount = std::thread::hardware_concurrency();

	std::cout << "Using " << datapoints << " pieces of sample data and " << tcount << " threads for a multi-threaded test...\n";

	auto start = steady_clock::now();
	parallel_foreach<int>(vec, tcount, [](int val, std::size_t t) -> int {
		return (val * 2) % 4;
	});
	auto end = steady_clock::now();
	std::printf("Finished multi-thread benchmark in %.5g seconds.\n", duration_cast<duration<double>>(end - start).count() * (double)seconds::period::num / (double)seconds::period::den);

}

int main(void) {
	int count = 1'000'000'000;
	std::cout << "This will take " << (sizeof(int) * count)/1000/1000 << "MB of memory, twice.\n";
	benchmark_singlethread(count);
	benchmark_multithread(count);

	return 0;
}