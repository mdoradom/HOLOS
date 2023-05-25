#include <stdio.h>
#include "SDL.h"
#include <iostream>
#include <vector>

constexpr int N = 10000000;
int globalVar = 0;

using namespace std;

int TestThread(void* data) {
	for (int i = 0; i < N; i++) {
		globalVar++; // Critical region
	}
	return N;
}

int main(int argc, char* argv[]) {
	SDL_Thread* thread;
	int threadReturnValue;

	cout << "Simple SDL_CreateThread test:\n" << endl;

	int numThreads;
	printf("Enter the number of threads to create: ");
	scanf_s("%d", &numThreads);

	vector<SDL_Thread*> threads(numThreads);

	for (int i = 0; i < numThreads; i++) {
		threads[i] = SDL_CreateThread(TestThread, "TestThread", (void*)NULL);
		if (threads[i] == NULL) {
			printf("SDL_CreateThread failed: %s\n", SDL_GetError());
			return -1;
		}
	}

	for (int i = 0; i < numThreads; i++) {
		SDL_WaitThread(threads[i], &threadReturnValue);
		printf("Thread %d returned value: %d\n", i + 1, threadReturnValue);
	}

	printf("ID: Thread counter : %d\n", globalVar);

	return 0;
}
