#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>

#undef main

int main() {
    SDL_RWops* file = SDL_RWFromFile("MYSTRING.txt", "w + ");

    if (file != NULL) {

        const char* str = "Hello World";
        size_t len = SDL_strlen(str);

        if (SDL_RWwrite(file, str, 1, len) != len) {

            printf("Couldn't fully write string\n");

        } else {

            printf("Wrote %d 1-byte blocks\n", len);

        }

        /* Seek to 0 bytes from the end of the file */
        Sint64 length = SDL_RWseek(file, 0, RW_SEEK_END);

        /* Seek to 0 bytes from the start of the file */
        SDL_RWseek(file, 0, RW_SEEK_SET);
        char* buf = (char*)malloc(length + 1);
        Sint64 nb_read = SDL_RWread(file, buf, 1, length);
        buf[nb_read] = '\0';

        printf("Read % d bytes[% s]", nb_read, buf);
        SDL_RWclose(file);
    }

    return 0;
}