#include <stdio.h>
#include "SDL.h"
#include <iostream>
#include <vector>

constexpr int N = 10000000;
int globalVar = 0;
SDL_mutex* mutex = NULL;

int TestThread(void* data)
{
    int i;

    for (i = 0; i < N; i++) {
        SDL_LockMutex(mutex); // Lock the mutex before accessing the critical region
        globalVar++; // Critical region
        SDL_UnlockMutex(mutex); // Unlock the mutex after accessing the critical region
    }

    return i;
}

int main(int argc, char* argv[])
{
    std::cout << "Simple SDL_CreateThread test:\n" << std::endl;

    int numThreads;
    std::cout << "Enter the number of threads to create: ";
    std::cin >> numThreads;

    std::vector<SDL_Thread*> threads(numThreads);
    mutex = SDL_CreateMutex(); // Create a mutex

    for (int i = 0; i < numThreads; i++) {
        threads[i] = SDL_CreateThread(TestThread, "TestThread", (void*)NULL);
        if (threads[i] == NULL) {
            printf("SDL_CreateThread failed: %s\n", SDL_GetError());
            return -1;
        }
    }

    int threadReturnValue;
    for (int i = 0; i < numThreads; i++) {
        SDL_WaitThread(threads[i], &threadReturnValue);
        printf("Thread %d returned value: %d\n", i + 1, threadReturnValue);
    }

    SDL_DestroyMutex(mutex); // Destroy the mutex

    printf("ID: Thread counter : %d\n", globalVar);

    return 0;
}
