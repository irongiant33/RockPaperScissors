#ifndef BOTS_H
#define BOTS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "play.h"

#define NUM_BOTS 4

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

bot_func_ptr choose_bot(int bot_index);
int random_bot(int prev_user_choice);
int low_confidence_bot(int prev_user_choice);
int high_confidence_bot(int prev_user_choice);
int random_weight_bot(int prev_user_choice);
int confidence_bot(int confidence, int prev_user_choice);
int weighting_bot(int confidence, int prev_user_choice);
bayes_t * allocate_bayes(int confidence);
void free_bayes();
void display_params();

#endif