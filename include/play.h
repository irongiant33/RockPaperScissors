#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define NUM_BOTS 3
#define NUM_CHOICES 3
#define ANY_NUMBER 10
#define MAX_WORD_LENGTH 9
#define NUM_GAMES 100
#define ROCK 0
#define PAPER 1
#define SCISSORS 2

#define DEBUG false

typedef struct stats
{
    int game_num;
    int bot_wins;
    int user_wins;
    int num_ties;
    int bot_id; 
    char * user_selection;
    char * bot_selection;
    int * user_choice;
    int * bot_choice;
} stats_t;

