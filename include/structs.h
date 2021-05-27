#ifndef STRUCTS_H
#define STRUCTS_H

#include "define.h"

typedef int (*bot_func_ptr)(int);

typedef struct bayes
{
    //total number of observations
    int num_observations;

    //ROW and COL ordered: rock (r), paper (p), scissors (s)
    //ROW conditional on COL. ex: conditionals[2][0] => P(s1 | r2)
    //                            given that rock was picked this turn, the number
    //                            of times that scissors preceeded rock
    int conditionals[NUM_CHOICES][NUM_CHOICES];

    //ordered: rock (r), paper (p), scissors (s)
    //ex: priors[1] = P(p)
    //    the number of times paper was picked
    int priors[NUM_CHOICES];
} bayes_t;

typedef struct stats
{
    int game_num;
    int bot_wins;
    int user_wins;
    int num_ties;
    int bot_id;
    int user_id;
    char * user_selection;
    char * bot_selection;
    int * user_choice;
    int * bot_choice;
} stats_t;

#endif