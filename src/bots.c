#include "../include/functions.h"

//global variable to track probability parameters through the game. 
//should be freed after each game.
bayes_t * params = NULL;
int prev_choice_buffer[2] = {-1, -1};


bayes_t * allocate_bayes(int confidence)
{
    bayes_t * params = calloc(1, sizeof(bayes_t));
    params->num_observations = confidence * NUM_CHOICES * NUM_CHOICES;
    for(int i = 0; i < NUM_CHOICES; i++)
    {
        for(int j = 0; j < NUM_CHOICES; j++)
        {
            params->conditionals[i][j] = confidence;
        }
        params->priors[i] = confidence * NUM_CHOICES;
    }
    return params;
}

void free_bayes()
{
    free(params);
    params = NULL;
}

void update_params(int prev_user_choice)
{
    prev_choice_buffer[0] = prev_choice_buffer[1];
    prev_choice_buffer[1] = prev_user_choice;
    if(prev_choice_buffer[0] == -1)
    {
        //I chose not to consider the first game as an observation since we need
        //to wait to have 2 user input values to know how to update the conditionals
        return;
    }
    params->conditionals[prev_choice_buffer[0]][prev_choice_buffer[1]]++;
    params->priors[prev_user_choice]++;
    params->num_observations++;
    return;
}

/**
 * Displays the global variable "params" for debugging purposes.
 * 
 */
void display_params()
{
    printf("\n\n");
    printf("Num Observations: %d\n", params->num_observations);
    printf("%5s %3s %3s %7s\n", "R2", "P2", "S2", "Priors");
    printf("%2s%3d %3d %3d %7d\n", "R1", params->conditionals[0][0], params->conditionals[0][1], params->conditionals[0][2], params->priors[0]);
    printf("%2s%3d %3d %3d %7d\n", "P1", params->conditionals[1][0], params->conditionals[1][1], params->conditionals[1][2], params->priors[1]);
    printf("%2s%3d %3d %3d %7d\n", "S1", params->conditionals[2][0], params->conditionals[2][1], params->conditionals[0][2], params->priors[2]);
    printf("\n\n");
}

bot_func_ptr choose_bot(int bot_id)
{
    bot_func_ptr bot = NULL;
    switch (bot_id)
    {
    case 0:
        bot = &random_bot;
        break;
    case 1:
        bot = &low_confidence_bot;
        break;
    case 2:
        bot = &high_confidence_bot;
        break;
    case 3:
        bot = &random_weight_bot;
        break;
    }
    return bot;
}

/**
 * Picks rock, paper, scissors at random and returns it. The most difficult
 * opponent.
 * 
 * Input:
 *      - stats_t *: it is unused and is here just to avoid declaring multiple typedefs for bot functions
 * 
 */
int random_bot(int prev_user_choice)
{
    time_t t;
    srand((unsigned) time(&t));
    int selection = rand() % NUM_CHOICES;
    return selection;
}

/**
 * A bot that uses conditional probabilities with LOWER prior confidence that
 * your choices are actually random. It will take FEWER non-random selections
 * to influence the probabilities that determine which selection is made. The bot
 * will select the item which beats the item with the highest probability of you
 * choosing it conditioned on your last choice.
 * 
 * This is only first-order prediction, so it is fairly easy to predict when it
 * is going to change guesses. Final selections are NOT weighted.
 * 
 */
int low_confidence_bot(int prev_user_choice)
{
    int confidence = 1; //think about this as the number of games that have already been observed
    return confidence_bot(confidence, prev_user_choice);
}

/**
 * A bot that uses conditional probabilities with HIGHER prior confidence that
 * your choices are actually random. It will take MORE non-random selections
 * to influence the probabilities that determine which selection is made. The bot
 * will select the item which beats the item with the highest probability of you
 * choosing it conditioned on your last choice.
 * 
 * This is only first-order prediction, so it is fairly easy to predict when it
 * is going to change guesses. Final selections are NOT weighted.
 * 
 */
int high_confidence_bot(int prev_user_choice)
{
    int confidence = 10; //think about this as the number of games that have already been observed
    return confidence_bot(confidence, prev_user_choice);
}

/**
 * A bot that uses conditional probabilities with LOWER prior confidence that
 * your choices are actually random. It will take FEWER non-random selections
 * to influence the probabilities that determine which selection is made. The bot
 * will select the item which beats the item with the highest probability of you
 * choosing it conditioned on your last choice.
 * 
 * This is only first-order prediction, so it is fairly easy to predict when it
 * is going to change guesses. Final selections ARE weighted.
 * 
 */
int random_weight_bot(int prev_user_choice)
{
    int confidence = 1; //think about this as the number of games that have already been observed
    return weighting_bot(confidence, prev_user_choice);
}

int confidence_bot(int confidence, int prev_user_choice)
{
    float likelihoods[NUM_CHOICES];
    if(prev_user_choice == -1)
    {
        params = allocate_bayes(confidence);
        return random_bot(prev_user_choice);
    }
    if(DEBUG){display_params();}
    int max_index = -1;
    float max_val = -1;
    for(int i = 0; i < NUM_CHOICES; i++)
    {
        float division_factor = (1.0 / params->num_observations) * (1.0 / (NUM_CHOICES * params->num_observations));
        likelihoods[i] = params->conditionals[prev_user_choice][i] * params->priors[i] * division_factor;
        if(likelihoods[i] > max_val)
        {
            max_val = likelihoods[i];
            max_index = i;
        }
        if(DEBUG){printf("%d) %.3f\n", i, likelihoods[i]);}
    }
    update_params(prev_user_choice);

    //return the option that beats what is most likely
    if(DEBUG){printf("max index: %d\n", max_index);}
    return (max_index + 1) % NUM_CHOICES;
}

int weighting_bot(int confidence, int prev_user_choice)
{
    float likelihoods[NUM_CHOICES];
    if(prev_user_choice == -1)
    {
        params = allocate_bayes(confidence);
        return random_bot(prev_user_choice);
    }
    if(DEBUG){display_params();}
    float normalization = 0.0;
    for(int i = 0; i < NUM_CHOICES; i++)
    {
        float division_factor = (1.0 / params->num_observations) * (1.0 / (NUM_CHOICES * params->num_observations));
        likelihoods[i] = params->conditionals[prev_user_choice][i] * params->priors[i] * division_factor;
        if(DEBUG){printf("%d) %.3f\n", i, likelihoods[i]);}
        normalization += likelihoods[i];
    }
    update_params(prev_user_choice);

    //return an option selected by weights
    time_t t;
    srand((unsigned) time(&t));
    float rand_val = (float) rand() / RAND_MAX;
    float offset = 0.0;
    for(int i = 0; i < NUM_CHOICES; i++)
    {
        float val = likelihoods[i] / normalization + offset;
        if(rand_val < val)
        {
            return (i + 1) % NUM_CHOICES;
        }
        offset += likelihoods[i] / normalization;
    }
}