#include "../include/bots.h"

char bot_names[NUM_BOTS][20] = {"Random Randy", "Doubtful Doug", "Competitive Charlie", "Weighing Walter"};

/**
 * Prints title screen
 * kudos to this ascii art generator: https://patorjk.com/software/taag/#p=display&c=echo&f=Big&t=Rock%20Paper%20Scissors%0A%0A
 * 
 * Inputs:
 *        - None
 * Returns: 
 *        - None
 * 
 */
void display_title()
{
    system("clear");
    system("echo \"  _____            _      _____                         _____      _                        \"");
    system("echo \" |  __ \\          | |    |  __ \\                       / ____|    (_)                       \"");
    system("echo \" | |__) |___   ___| | __ | |__) |_ _ _ __   ___ _ __  | (___   ___ _ ___ ___  ___  _ __ ___ \"");
    system("echo \" |  _  // _ \\ / __| |/ / |  ___/ _\\` | '_ \\ / _ \\ '__|  \\___ \\ / __| / __/ __|/ _ \\| '__/ __|\"");
    system("echo \" | | \\ \\ (_) | (__|   <  | |  | (_| | |_) |  __/ |     ____) | (__| \\__ \\__ \\ (_) | |  \\__ \\ \"");
    system("echo \" |_|  \\_\\___/ \\___|_|\\_\\ |_|   \\__,_| .__/ \\___|_|    |_____/ \\___|_|___/___/\\___/|_|  |___/\"");
    system("echo \"                                    | |                                                     \"");
    system("echo \"                                    |_|                                                     \"");
    printf("\n\n Choose the bot you wish to play against:\n");
    for(int i = 1; i <= NUM_BOTS; i++)
    {
        printf("\t %d) %s\n", i, bot_names[i - 1]);
    }
    printf("\nEnter a value [1-%d]: ", NUM_BOTS);
}

/**
 * Prints instructions before the game starts
 * 
 * Inputs:
 *        - None
 * Returns: 
 *        - None
 * 
 */
void display_instructions(int bot_index)
{
    system("clear");
    printf("***************************************************************\n");
    printf("*                                                             *\n");
    printf("*               Human vs. %-20s                *\n", bot_names[bot_index]);
    printf("*                                                             *\n");
    printf("***************************************************************\n");
    printf("\n\n Your goal is to beat the bot. You win if you are victorious in \n");
    printf("34 games out of 100. The more games over 33 in which you are \n");
    printf("victorious (consistently), the more superior your intellect over the bot.\n\n");
    printf("A perfectly random game should average out to 33.3 wins for each\n");
    printf("competitor, as well as 33.3 ties (in the long run). If you come up\n");
    printf("with fewer than 33 wins (consistently), you are too predictable.");
    printf("\n\nPress any number key and enter to continue.\n");
}

/**
 * Prints game stats and user selection options.
 * 
 * Inputs:
 *        - None
 * Returns: 
 *        - None
 * 
 */
void display_in_game(stats_t * stats)
{
    system("clear");
    printf("***************************************************************\n");
    printf("*                                                             *\n");
    printf("*                     Game: %3d                               *\n", stats->game_num);
    printf("*                 Bot Wins: %3d                               *\n", stats->bot_wins);
    printf("*               Human Wins: %3d                               *\n", stats->user_wins);
    printf("*                     Ties: %3d                               *\n", stats->num_ties);
    if(stats->bot_selection != NULL)
    {
        printf("*   Previous Bot Selection: %8s                          *\n", stats->bot_selection);
    }
    if(stats->user_selection != NULL)
    {
        printf("* Previous Human Selection: %8s                          *\n", stats->user_selection);
    }
    printf("*                                                             *\n");
    printf("***************************************************************\n");
    if(stats->game_num < NUM_GAMES)
    {
        printf("\n\nThe bot has made its selection. What do you choose?\n");
        printf("\t 1) Rock\n\t 2) Paper\n\t 3) Scissors\n\n");
        printf("Choice: ");
    }
    else
    {
        printf("Would you like to play again:\n\t 1) Yes\n\t 2) No\n");
        printf("Choice: ");
    }
}

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
    stats->game_num = 1;
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

void assign_selection(int selection, char * string_selection)
{
    switch(selection)
    {
    case ROCK: ;
        char rock[MAX_WORD_LENGTH] = "    Rock";
        memcpy(string_selection, rock, MAX_WORD_LENGTH);
        break;
    case PAPER: ;
        char paper[MAX_WORD_LENGTH] = "   Paper";
        memcpy(string_selection, paper, MAX_WORD_LENGTH);
        break;
    case SCISSORS: ;
        char scissors[MAX_WORD_LENGTH] = "Scissors";
        memcpy(string_selection, scissors, MAX_WORD_LENGTH);
        break;
    }
    return;
}

int main()
{
    bool still_playing = true;
    while(still_playing)
    {
        display_title();
        int bot_id = validate_input(NUM_BOTS);
        bot_func_ptr bot = choose_bot(bot_id);
        bool in_game = true;
        display_instructions(bot_id);
        validate_input(ANY_NUMBER);
        stats_t * game_stats = initialize_stats(bot_id);
        while(game_stats->game_num < NUM_GAMES)
        {
            //display selection menu to user
            display_in_game(game_stats);

            //obtain bot's selection
            if(game_stats->bot_selection == NULL)
            {
                game_stats->bot_selection = calloc(MAX_WORD_LENGTH , sizeof(char));
            }
            game_stats->bot_choice[game_stats->game_num - 1] = game_stats->game_num == 1 ? (*bot)(-1) : (*bot)(game_stats->user_choice[game_stats->game_num - 2]);
            assign_selection(game_stats->bot_choice[game_stats->game_num - 1], game_stats->bot_selection);

            //obtain user's selection
            if(game_stats->user_selection == NULL)
            {
                game_stats->user_selection = calloc(MAX_WORD_LENGTH, sizeof(char));
            }
            game_stats->user_choice[game_stats->game_num - 1] = validate_input(NUM_CHOICES);
            assign_selection(game_stats->user_choice[game_stats->game_num - 1], game_stats->user_selection);

            //update stats
            int result = game_stats->user_choice[game_stats->game_num - 1] - game_stats->bot_choice[game_stats->game_num - 1];
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
        display_in_game(game_stats);
        int user_input = validate_input(2);
        if(user_input == 1)
        {
            still_playing = false;
        }
        //write stats to a file

        //free all memory
        free_stats(game_stats);
        free_bayes();
    }
}