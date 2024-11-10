#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <vector>

using namespace std;

// Screen size
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

constexpr auto MAXR = 2500; // Number of rectangles
SDL_Rect r[MAXR];

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

bool quit = false;
int frames = 0; // Number of Drawn frames

// move: Move a rectangle in a random direction
void move(SDL_Rect* r) {
	int dir = rand() % 4;
	if (dir == 0) {
		r->x += 10;
		r->x = r->x % SCREEN_WIDTH;
	}
	else if (dir == 1) {
		r->y += 10;
		r->y = r->y % SCREEN_HEIGHT;

	}
	else if (dir == 2) {
		r->x -= 10;
		r->x = r->x % SCREEN_WIDTH;

	}
	else if (dir == 3) {
		r->y -= 10;
		r->y = r->y % SCREEN_HEIGHT;

	}
}

// Move rectangles from 'start' to 'end' in a random way
// Update the result and increase number of frames drawn.
void updateRect(int start, int end) {
	for (int i = start; i < end; i++) {
		SDL_FillRect(screenSurface, &r[i], SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
		move(&r[i]);
		SDL_FillRect(screenSurface, &r[i], SDL_MapRGB(screenSurface->format, rand() % 0xFF, rand() % 0xFF, 0xFF));
	}
	SDL_UpdateWindowSurface(window);
	frames++;
}

// updateRectThread: Function to be executed by each thread
void updateRectThread(int start, int end) {
	while (!quit) {
		updateRect(start, end);
	}
}

// Initialize SDL
int initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize SDL_Error = %s\n", SDL_GetError());
		return(-1);
	}

	window = SDL_CreateWindow("SDL prova", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("SDL could not create Window SDL_Error = %s\n", SDL_GetError());
		return(-1);
	}

	screenSurface = SDL_GetWindowSurface(window);
	return 0;
}

int main(int argc, char** argv) {
	if (initSDL() < 0) {
		printf("ERROR: Unable to init SDL");
		return (-1);
	}

	printf("Starting\n");

	// Draw background
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(window);

	// Init rectangles
	for (int i = 0; i < MAXR; i++) {
		r[i].x = rand() % SCREEN_WIDTH;
		r[i].y = rand() % SCREEN_HEIGHT;
		r[i].h = 10;
		r[i].w = 10;
	}

	int numThreads;
	printf("Enter the number of threads to create: ");
	scanf("%d", &numThreads);

	vector<thread> threads;
	int chunkSize = MAXR / numThreads;
	int start = 0;
	int end = start + chunkSize;

	// Create threads
	for (int i = 0; i < numThreads; i++) {
		threads.push_back(thread(updateRectThread, start, end));
		start = end;
		end += chunkSize;
	}

	// Start game loop
	SDL_Event e;
	Uint32 startTicks, nowTicks;
	startTicks = SDL_GetTicks();

	while (quit == false) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;
		}

		updateRect(0, MAXR); // Update Rectangles

		nowTicks = SDL_GetTicks();
		if ((nowTicks - startTicks) > 1000) {
			startTicks = nowTicks;
			printf("frames/s = %d\n", frames);
			frames = 0;
		}
	}

	// Wait for threads to finish
	for (int i = 0; i < numThreads; i++) {
		threads[i].join();
	}

	return 0;
}
