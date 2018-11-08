#include <cstdio>
#include <thread>
#include "queue.h"
#include <chrono>

int main(void) {
	wrestd::collections::concurrent_queue<int> mycqueue;
	bool filled = false;

	std::thread t1([&] {
		for (int i = 0; i < 5; i++) {
			std::printf("Enqueued: %d\n", i);
			mycqueue.enqueue(i);
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		filled = true;
	});

	int myval;
	mycqueue.await_dequeue([&](int v) {
		myval = v;
		std::printf("Dequeued: %d\n", myval);
	});

	while (!filled) {}

	mycqueue.stop_waiting();

	mycqueue.print();

	t1.join();

	return 0;
}