#include "../include/functions.h"

char bot_names[NUM_BOTS][BOT_NAME_LENGTH] = {"Random Randy", "Doubtful Doug", "Competitive Charlie", "Weighing Walter"};

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

void display_selection(int selection, char * string_selection)
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