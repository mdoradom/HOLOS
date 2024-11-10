#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>

#undef main

#define MAX_INTS 10

int main() {
    SDL_RWops* file = SDL_RWFromFile("MYINTS.txt", "w + ");

    if (file != NULL) {

        const int* ints[MAX_INTS];
        size_t len = sizeof(ints);

        for (int i = 0; i < 10; i++) {

            printf("Enter an integer: ");
            scanf("%d", &ints[i]);
        
        }

        if (SDL_RWwrite(file, ints, 1, len) != len) {

            printf("Couldn't fully write ints\n");

        }
        else {

            printf("Wrote %d 1-byte blocks\n", len);

        }

        /* Seek to 0 bytes from the end of the file */
        Sint64 length = SDL_RWseek(file, 0, RW_SEEK_END);

        /* Seek to 0 bytes from the start of the file */
        SDL_RWseek(file, 0, RW_SEEK_SET);
        int* buf = (int*)malloc(length + 1);
        Sint64 nb_read = SDL_RWread(file, buf, 1, length);
        buf[nb_read] = '\0';

        printf("Read %lld bytes [", nb_read);
        for (int i = 0; i < MAX_INTS; i++) {
            printf("%d ", buf[i]);
        }
        printf("]\n");

        SDL_RWclose(file);
    }

    return 0;
}