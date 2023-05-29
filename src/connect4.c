#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "connect4.h"
#include "grid.h"

#define WRITE 1
#define READ 0             

//Check if the player move is valid or not
static bool check_move(struct Grid *g, int player_move)
{   
    if (player_move > 7 || player_move <= 0)
    {
        printf("\nThis move is not valid !\n");
        return false;
    }
    if (g->grid[player_move-1] != ' ')
    {
        printf("\nNo more move possible.\nThe column is full !\n");
        return false;
    }
    return true;
}


//Gets player movements and returns the game grid edit if so
static int get_move(struct Grid *g, char *player_move)
{
    bool result;
    int player_input;
    char *buff = NULL;
    sleep(1);
    do 
    {
        printf("Player %c : Enter the column number where you want to put your token [between 1 & 7]: ", *player_move); 
        buff = readline("");

        if (buff == NULL)
        {
            return -1; // -1 = error
        }

        player_input = atoi(buff);
        result = check_move(g, player_input);
        
    } while (!result);
    
    for (int i = HEIGHT-1; i >= 0 ; i--) //row
    {
        if (g->grid[i * WIDTH + (player_input-1)]  == ' ') 
        {
            g->grid[i * WIDTH + (player_input-1)] = *player_move;   
            break;
        }
    }

    //Determines player turn
    if (*player_move == 'O')
    {
        *player_move = 'X';
    }
    else 
    {
        *player_move = 'O';
    }
    return result;
}


//Parent function : send an input and write the grid in the pipe
static int send_input(struct Grid *g)
{
    const int buffer_size = WIDTH*HEIGHT;
    if (write(g->pipefd[WRITE], g->grid, buffer_size) == -1)
    {
        printf("Error writing !\n");
        return -1; // -1 = error
    }
    return 0; // 0 = false
}


//Function that retrieves all the other functions needed for the main
static int connect4(void)  
{
    struct Grid *g = init_grid();
    
    if (g == NULL)
    {
        return -1; // -1 = error
    }

    int lc = launch_child(g); //wait le child avant de quitter

    if (lc != 0)
    {
        free(g->grid);
        free(g);
        return lc;
    }
    
    char player_move = 'X'; // by default Player 1 is 'X'

    while (check_win(g) != 1)
    {
        
        if (send_input(g) != 0 || get_move(g, &player_move) == 0)
        {
            close(g->pipefd[WRITE]);
            free(g->grid);
            free(g);
            return 1; // 1 = true
        }
    }
    close(g->pipefd[WRITE]);
    free(g->grid);
    free(g);
    return 0; // 0 = false
}


//main function
int main(void)
{
   return connect4();
}