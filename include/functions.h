#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structs.h"

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
void display_title();
void display_instructions(int bot_index);
void display_in_game(stats_t * stats);
void display_selection(int selection, char * string_selection);

#endif