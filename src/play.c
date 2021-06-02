#include "../include/functions.h"

char sequence_dir[] = "../sequences/";

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
        char user_input[MAX_USER_IN];
        int scan_results = scanf(" %s", user_input);
        if(scan_results == EOF)
        {
            printf("Bad user input. Exiting\n");
            exit(0);
        }
        for(int i = ascii_val; i < (ascii_val + max_val); i++)
        {
            if(i == user_input[0])
            {
                in_range = true;
                break;
            }
        }
        if(!in_range)
        {
            printf("User input out of range. Try Again.\n");
        }
        return_val = user_input[0] - ascii_val;
    }
    return return_val;
}

void handle_settings(settings_t * settings)
{
    display_settings();
    //change number of games?
    printf("\nNumber of games to play (current: %d, max: %d) ==> ", settings->num_games, MAX_NUM_GAMES);
    int new_num_games;
    int scan_results = scanf(" %d", &new_num_games);
    if(scan_results == EOF)
    {
        printf("Bad user input. Exiting\n");
        exit(0);
    }
    if(new_num_games > 0 && new_num_games <= MAX_NUM_GAMES)
    {
        printf("Updated number of games from %d to %d\n", settings->num_games, new_num_games);
        settings->num_games = new_num_games;
    }
    else
    {
        printf("Bad user input. Number of games unchanged.\n");
    }

    //change logging?
    char old_logging = (settings->logging) ? 'y' : 'n';
    printf("\nLog Results? y/n (current: %c) ==> ", old_logging);
    char new_logging[MAX_USER_IN];
    scan_results = scanf(" %s", new_logging);
    if(scan_results == EOF)
    {
        printf("Bad user input. Exiting\n");
        exit(0);
    }
    if(new_logging[0] == 'y' || new_logging[0] == 'n')
    {
        printf("Updated logging status from %c to %c\n", old_logging, new_logging[0]);
        settings->logging = (new_logging[0] == 'y') ? true : false;
    }
    else
    {
        printf("logging status unchanged.\n");
    }
    printf("\nPress any key and enter to exit.");
    scanf(" %s", new_logging);
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
stats_t * initialize_stats(settings_t settings)
{
    stats_t * stats = calloc(1, sizeof(stats_t));
    stats->bot_wins = 0;
    stats->user_wins = 0;
    stats->num_ties = 0;
    stats->game_num = 0;
    stats->bot_id = -1;
    stats->settings = settings;
    stats->bot_selection = calloc(1, sizeof(char));
    stats->bot_selection = NULL;
    stats->user_selection = calloc(1, sizeof(char));
    stats->user_selection = NULL;
    stats->user_choice = calloc(stats->settings.num_games, sizeof(int));
    memset(stats->user_choice, -1, stats->settings.num_games * sizeof(int));
    stats->bot_choice = calloc(stats->settings.num_games, sizeof(int));
    memset(stats->bot_choice, -1, stats->settings.num_games * sizeof(int));
    return stats;
}

/**
 * written with the help of https://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm
 */
void write_to_file(stats_t * game_stats)
{
    FILE * fp;
    time_t rawtime;
    struct tm *info;
    char outfilename[MAX_USER_IN];
    time(&rawtime);
    info = localtime( &rawtime );
    strftime(outfilename, MAX_USER_IN,"../results/testresults_%d%b%y_%H%M%S", info);
    fp = fopen(outfilename, "w");
    fprintf(fp, "num games, user id, bot id, num user wins, num bot wins, num ties\n");
    fprintf(fp, "%d, %d, %d, %d, %d, %d\n", game_stats->settings.num_games, game_stats->user_id, game_stats->bot_id, game_stats->user_wins, game_stats->bot_wins, game_stats->num_ties);
    fprintf(fp, "\ngame num, user choice, bot choice\n");
    for(int i = 1; i < game_stats->settings.num_games + 1; i++)
    {
        fprintf(fp, "%d, %d, %d\n", i, game_stats->user_choice[i-1], game_stats->bot_choice[i-1]);
    }
    fclose(fp);
}

void validate_sequence(stats_t * game_stats)
{
    //get a proper filename from the user
    FILE *fp;
    bool valid_input = false;
    while(!valid_input)
    {
        char * filename = calloc(NUM_GAMES + sizeof(sequence_dir), sizeof(char));
        char * user_input = calloc(NUM_GAMES, sizeof(char));
        scanf("%s", user_input);
        int sequence_dir_len = sizeof(sequence_dir);
        filename = strncat(filename, sequence_dir, sequence_dir_len);
        filename = strncat(filename, user_input, NUM_GAMES);
        fp = fopen(filename, "r");
        if(fp == NULL)
        {
            printf("\ninvalid filename. enter again: ");
        }
        else
        {
            valid_input = true;
        }
        free(filename);
        free(user_input);
    }

    //log all of the correct game entries within the file
    int game_num = 0;
    while(game_num < game_stats->settings.num_games)
    {
        int entry = fgetc(fp);
        if(entry == EOF){break;}
        switch (entry)
        {
        case 'r':
            game_stats->user_choice[game_num] = ROCK;
            game_num++;
            break;
        case 'R':
            game_stats->user_choice[game_num] = ROCK;
            game_num++;
            break;
        case 'p':
            game_stats->user_choice[game_num] = PAPER;
            game_num++;
            break;
        case 'P':
            game_stats->user_choice[game_num] = PAPER;
            game_num++;
            break;
        case 's':
            game_stats->user_choice[game_num] = SCISSORS;
            game_num++;
            break;
        case 'S':
            game_stats->user_choice[game_num] = SCISSORS;
            game_num++;
            break;
        }
    }
    
    //check to make sure the file wasn't empty or filled with junk characters
    if(game_num == 0)
    {
        game_stats->user_choice[game_num] = ROCK;
        game_num++;
    }

    //fill in the rest of the games if only a partial sequence was completed.
    int counter = 0;
    int num_entered_games = game_num;
    while(game_num < game_stats->settings.num_games)
    {
        game_stats->user_choice[game_num] = game_stats->user_choice[counter % num_entered_games];
        game_num++;
        counter++;
    }
    fclose(fp);
}

void play_human_bot(stats_t * game_stats)
{
    //prompt for opponent
    int bot_id = NUM_BOTS;
    display_title(OPPONENT, bot_id);
    bot_id = validate_input(NUM_BOTS);
    bot_func_ptr bot = choose_bot(bot_id);

    game_stats->bot_id = bot_id;
    game_stats->user_id = NUM_BOTS; //the human player
    set_seed();
    while(game_stats->game_num < game_stats->settings.num_games)
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
}

void play_bot_bot(stats_t * game_stats)
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

    game_stats->bot_id = bot_id;
    game_stats->user_id = first_bot_id; //user is aka the first bot
    set_seed();
    while(game_stats->game_num < game_stats->settings.num_games)
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
}

void play_seq_bot(stats_t * game_stats)
{
    //prompt for opponent
    int bot_id = NUM_BOTS + 1; //sequence ID
    display_title(OPPONENT, bot_id);
    bot_id = validate_input(NUM_BOTS);
    bot_func_ptr bot = choose_bot(bot_id);

    //initialize stats
    game_stats->bot_id = bot_id;
    game_stats->user_id = NUM_BOTS + 1; //the sequence
    set_seed();

    //prompt for sequence
    display_sequence(game_stats);
    validate_sequence(game_stats);

    while(game_stats->game_num < game_stats->settings.num_games)
    {
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
}

int main()
{
    bool still_playing = true;
    bool is_settings = true;
    settings_t * settings = calloc(1, sizeof(settings));
    settings->num_games = NUM_GAMES;
    settings->logging = LOGGING;
    while(still_playing)
    {
        //main variables
        int bot_id = NUM_BOTS;
        bot_func_ptr * bot = calloc(2, sizeof(bot_func_ptr));

        //main menu
        while(is_settings)
        {
            display_title(MENU, bot_id);
            int menu_option = validate_input(NUM_MENU_OPTIONS);
            if(menu_option == SETTINGS)
            {
                handle_settings(settings);
            }
            else if(menu_option == PLAY)
            {
                is_settings = false;
            }
        }

        //prompt for game mode
        display_title(STARTUP, bot_id);
        int game_mode = validate_input(NUM_GAME_MODES);
        stats_t * game_stats = initialize_stats(*settings);
        switch (game_mode)
        {
        case HUMAN_BOT:
            play_human_bot(game_stats);
            break;
        case BOT_BOT:
            play_bot_bot(game_stats);
            break;
        case SEQ_BOT:
            play_seq_bot(game_stats);
            break;
        case MENU:
            free_stats(game_stats);
            free(bot);
            is_settings = true;
            continue;
        }
        //write output to file
        if(settings->logging)
        {
            write_to_file(game_stats);
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