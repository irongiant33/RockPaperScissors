#include "../include/functions.h"

/**
 * Accepts one character of user input and checks to make sure it falls within
 * the range of available bots.
 * 
 * Inputs:
 *        - None
 * Returns: 
 *        - 0 to (NUM_BOTS - 1) corresponding to the bot number selected
 *        - exits on error and prints to screen
 * 
 */
int validate_input(int max_val)
{
    bool in_range = false;
    int return_val = 0;
    int ascii_val = '1';
    while(!in_range)
    {
        char user_input;
        scanf(" %c", &user_input);
        if(user_input == EOF)
        {
            printf("Bad user input. Exiting\n");
            exit(0);
        }
        for(int i = ascii_val; i < (ascii_val + max_val); i++)
        {
            if(i == user_input)
            {
                in_range = true;
                break;
            }
        }
        if(!in_range)
        {
            printf("User input out of range. Try Again.\n");
        }
        return_val = user_input - ascii_val;
    }
    return return_val;
}

/**
 * Frees the stats_t struct.
 * 
 * Inputs:
 *       - stats_t struct
 * Returns:
 *       - None
 * 
 */
void free_stats(stats_t * stats)
{
    free(stats->user_selection);
    free(stats->bot_selection);
    free(stats->user_choice);
    free(stats->bot_choice);
    free(stats);
    stats = NULL;
    return;
}

/**
 * Allocates memory for the the stats_t struct.
 * 
 * Inputs:
 *       - None
 * Returns:
 *       - a pointer to the stats_t struct
 * 
 */
stats_t * initialize_stats(int bot_id)
{
    stats_t * stats = calloc(1, sizeof(stats_t));
    stats->bot_wins = 0;
    stats->user_wins = 0;
    stats->num_ties = 0;
    stats->game_num = 0;
    stats->bot_id = bot_id;
    stats->bot_selection = calloc(1, sizeof(char));
    stats->bot_selection = NULL;
    stats->user_selection = calloc(1, sizeof(char));
    stats->user_selection = NULL;
    stats->user_choice = calloc(NUM_GAMES, sizeof(int));
    memset(stats->user_choice, -1, NUM_GAMES * sizeof(int));
    stats->bot_choice = calloc(NUM_GAMES, sizeof(int));
    memset(stats->bot_choice, -1, NUM_GAMES * sizeof(int));
    return stats;
}

stats_t * play_human_bot()
{
    //prompt for opponent
    int bot_id = NUM_BOTS;
    display_title(OPPONENT, bot_id);
    bot_id = validate_input(NUM_BOTS);
    bot_func_ptr bot = choose_bot(bot_id);

    stats_t * game_stats = initialize_stats(bot_id);
    game_stats->user_id = NUM_BOTS; //the human player
    while(game_stats->game_num < NUM_GAMES)
    {
        //display selection menu to user
        display_in_game(game_stats);

        //obtain bot's selection
        if(game_stats->bot_selection == NULL)
        {
            game_stats->bot_selection = calloc(MAX_WORD_LENGTH , sizeof(char));
        }
        game_stats->bot_choice[game_stats->game_num] = game_stats->game_num == 0 ? (*bot)(-1) : (*bot)(game_stats->user_choice[game_stats->game_num - 1]);
        display_selection(game_stats->bot_choice[game_stats->game_num], game_stats->bot_selection);

        //obtain user's selection
        if(game_stats->user_selection == NULL)
        {
            game_stats->user_selection = calloc(MAX_WORD_LENGTH, sizeof(char));
        }
        game_stats->user_choice[game_stats->game_num] = validate_input(NUM_CHOICES);
        display_selection(game_stats->user_choice[game_stats->game_num], game_stats->user_selection);

        //update stats
        int result = game_stats->user_choice[game_stats->game_num] - game_stats->bot_choice[game_stats->game_num];
        game_stats->game_num++;
        if(result == -2 || result == 1)
        {
            game_stats->user_wins++;
        }
        else if(result == -1 || result == 2)
        {
            game_stats->bot_wins++;
        }
        else
        {
            game_stats->num_ties++;
        }
    }
    return game_stats;
}

stats_t * play_bot_bot()
{
    //prompt for first bot
    int bot_id = NUM_BOTS;
    int bot_index = 0;
    bot_func_ptr * bot = calloc(2, sizeof(bot_func_ptr));
    display_title(FIRST_BOT, bot_id);
    int first_bot_id = validate_input(NUM_BOTS);
    bot[bot_index] = choose_bot(first_bot_id);
    bot_index++;

    //prompt for second bot
    display_title(OPPONENT, first_bot_id);
    bot_id = validate_input(NUM_BOTS);
    bot[bot_index] = choose_bot(bot_id);

    stats_t * game_stats = initialize_stats(bot_id);
    game_stats->user_id = first_bot_id; //user is aka the first bot
    while(game_stats->game_num < NUM_GAMES)
    {
        //obtain second bot's selection
        if(game_stats->bot_selection == NULL)
        {
            game_stats->bot_selection = calloc(MAX_WORD_LENGTH , sizeof(char));
        }
        game_stats->bot_choice[game_stats->game_num] = game_stats->game_num == 0 ? (*bot[1])(-1) : (*bot[1])(game_stats->user_choice[game_stats->game_num - 1]);
        display_selection(game_stats->bot_choice[game_stats->game_num], game_stats->bot_selection);

        //obtain first bot's selection (user)
        if(game_stats->user_selection == NULL)
        {
            game_stats->user_selection = calloc(MAX_WORD_LENGTH, sizeof(char));
        }
        game_stats->user_choice[game_stats->game_num] = game_stats->game_num == 0 ? (*bot[0])(-1) : (*bot[0])(game_stats->bot_choice[game_stats->game_num - 1]);
        display_selection(game_stats->user_choice[game_stats->game_num], game_stats->user_selection);

        //update stats
        int result = game_stats->user_choice[game_stats->game_num] - game_stats->bot_choice[game_stats->game_num];
        game_stats->game_num++;
        if(result == -2 || result == 1)
        {
            game_stats->user_wins++;
        }
        else if(result == -1 || result == 2)
        {
            game_stats->bot_wins++;
        }
        else
        {
            game_stats->num_ties++;
        }
    }
    return game_stats;
}

stats_t * play_seq_bot()
{
    printf("happy");
    stats_t * game_stats = initialize_stats(1);
    return game_stats;
}

int main()
{
    bool still_playing = true;
    while(still_playing)
    {
        //main variables
        int bot_id = NUM_BOTS;
        bot_func_ptr * bot = calloc(2, sizeof(bot_func_ptr));

        //prompt for game mode
        display_title(STARTUP, bot_id);
        int game_mode = validate_input(NUM_GAME_MODES);
        stats_t * game_stats;
        switch (game_mode)
        {
        case HUMAN_BOT:
            game_stats = play_human_bot();
            break;
        case BOT_BOT:
            game_stats = play_bot_bot();
            break;
        case SEQ_BOT:
            game_stats = play_seq_bot();
            break;
        }

        //display final game statistics and ask to play another round
        display_in_game(game_stats);
        int user_input = validate_input(2);
        if(user_input == 1)
        {
            still_playing = false;
            system("clear");
        }

        //free all memory
        free_stats(game_stats);
        free_bayes();
        free(bot);
    }
}