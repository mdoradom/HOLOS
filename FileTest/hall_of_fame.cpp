#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>

struct Player {
    char name[50];
    int score;
};

int compare_players(const void* a, const void* b) {
    const struct Player* player1 = (const struct Player*)a;
    const struct Player* player2 = (const struct Player*)b;
    return player2->score - player1->score;
}

void save_players(const struct Player* players, int num_players) {
    SDL_RWops* file = SDL_RWFromFile("FAME.TXT", "wb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < num_players; i++) {
        const int name_length = strlen(players[i].name);
        SDL_RWwrite(file, &name_length, sizeof(int), 1);
        SDL_RWwrite(file, players[i].name, sizeof(char), name_length);
        SDL_RWwrite(file, &players[i].score, sizeof(int), 1);
    }

    SDL_RWclose(file);
}

void load_players(struct Player* players, int* num_players) {
    SDL_RWops* file = SDL_RWFromFile("FAME.TXT", "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int name_length;
    int score;
    int i = 0;

    while (SDL_RWread(file, &name_length, sizeof(int), 1) > 0) {
        SDL_RWread(file, players[i].name, sizeof(char), name_length);
        players[i].name[name_length] = '\0';
        SDL_RWread(file, &score, sizeof(int), 1);
        players[i].score = score;
        i++;
    }

    *num_players = i;

    SDL_RWclose(file);
}

void print_players(const struct Player* players, int num_players) {
    printf("Name\t\tScore\n");
    printf("-------------------------\n");
    for (int i = 0; i < num_players; i++) {
        printf("%-15s\t%d\n", players[i].name, players[i].score);
    }
}

int main(int argc, char* argv[]) {
    struct Player players[100];
    int num_players = 0;

    load_players(players, &num_players);
    print_players(players, num_players);

    char name[50];
    int score;

    printf("Enter a name: ");
    scanf_s("%s", name, sizeof(name));

    printf("Enter a score: ");
    scanf_s("%d", &score);

    struct Player new_player;
    strncpy_s(new_player.name, sizeof(new_player.name), name, _TRUNCATE);
    new_player.score = score;

    players[num_players] = new_player;
    num_players++;

    qsort(players, num_players, sizeof(struct Player), compare_players);

    save_players(players, num_players);

    printf("Hall of Fame updated:\n");
    print_players(players, num_players);

    return 0;
}
