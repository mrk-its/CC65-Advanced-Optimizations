#include <atari.h>
#include "benchmark.h"

#define SCREEN_SIZE_X 40
#define SCREEN_SIZE_Y 24
#define NO_ENEMIES 30
#define NO_ENTITIES (NO_ENEMIES+1)
#define PLAYER_INDEX (NO_ENEMIES)

#define _countof(array) (sizeof(array) / sizeof(array[0]))
#define MAX_LOOKUP_VALUE 100
#define FIRST_DIGIT_CHAR 0x10

#define ENTITY_DEAD 0
#define ENTITY_PLAYER 1
#define ENTITY_ENEMY 2
typedef char e_entity_type;

// +1 for player
typedef struct s_entity {
    char x[NO_ENTITIES];
    char y[NO_ENTITIES];
    char hp[NO_ENTITIES];
    e_entity_type type[NO_ENTITIES];
} s_entity;

typedef struct s_player {
    char attack;
} s_player;


typedef struct s_game_state {
    s_entity entities;
    s_player player;
} s_game_state;

// Lookup tables
char get_entity_tile[] = {
    'x', 'p', 'e'
};

s_game_state game_state;

char div_10_lookup[MAX_LOOKUP_VALUE];
char mod_10_lookup[MAX_LOOKUP_VALUE];
char *screen_line_lookup[SCREEN_SIZE_Y];

void place_enemy(char index, char x, char y)
{
    game_state.entities.x[index] = x;
    game_state.entities.y[index] = y;
}

void set_entities()
{
    char index;
    // set entities
    for (index = 0; index < NO_ENEMIES; index++)
    {
        place_enemy(index, (index*5) % SCREEN_SIZE_X, index / 2 + 9);
        game_state.entities.hp[index] = 99;
        game_state.entities.type[index] = ENTITY_ENEMY;
    };
    // set player
    game_state.entities.hp[PLAYER_INDEX] = 99;
    game_state.entities.x[PLAYER_INDEX] = SCREEN_SIZE_X/2;
    game_state.entities.type[PLAYER_INDEX] = ENTITY_PLAYER;
};

void draw_entity(char index)
{
    char *draw_ptr = screen_line_lookup[game_state.entities.y[index]] + game_state.entities.x[index];
    char hp = game_state.entities.hp[index];
    *draw_ptr = get_entity_tile[game_state.entities.type[index]];
    *(++draw_ptr) = div_10_lookup[hp];
    *(++draw_ptr) = mod_10_lookup[hp];
};

void damage_enemy(char index)
{
    // damage
    if (game_state.entities.hp[index] > 0)
        game_state.entities.hp[index]--;
}

void one_frame()
{
    char index;
    // draw enemies
    for (index = 0; index < NO_ENEMIES; index++)
    {
        damage_enemy(index);
        draw_entity(index);
    };

    // draw player
    draw_entity(PLAYER_INDEX);
}

void init_lookup_tables()
{
    char *screen_ptr = (char *)SAVMSC;
    char index1;
    // init screen lookup
    for (index1 = 0; index1 < SCREEN_SIZE_Y; ++index1)
        screen_line_lookup[index1] = screen_ptr + index1 * SCREEN_SIZE_X;

    for (index1 = 0; index1 < MAX_LOOKUP_VALUE; ++index1)
    {
        div_10_lookup[index1] = index1/10 + FIRST_DIGIT_CHAR;
        mod_10_lookup[index1] = index1%10 + FIRST_DIGIT_CHAR;
    }
}

void main(void)
{
    char times;

    init_lookup_tables();
    set_entities();

    start_benchmark();
    for (times = 0; times < 100; ++times)
        one_frame();
    end_benchmark();
}
