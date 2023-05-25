#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>

int main() {
    SDL_RWops* file = SDL_RWFromFile("MYINTS.txt", "r");
    if (file != NULL) {
        const Sint64 length = SDL_RWseek(file, 0, RW_SEEK_END);
        SDL_RWseek(file, 0, RW_SEEK_SET);

        char* buf = (char*)malloc(length + 1);

        const Sint64 nb_read = SDL_RWread(file, buf, 1, length);
        buf[nb_read] = '\0';

        for (int i = 0; i < nb_read; i++) {
            printf("%c", buf[i]);
        }
        printf("\n");

        SDL_RWclose(file);
        free(buf);
    }
    else {
        printf("Error opening file.\n");
    }

    return 0;
}
