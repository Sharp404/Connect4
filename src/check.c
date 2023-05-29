#include <stdio.h>
#include <stdbool.h>

#include "grid.h"


//Check if there is at least 4 token in an ascending diagonal (/)
static int check_diagonal_ascending(struct Grid *g, char player_move, int i, int j) 
{
    if ((j + 3 > WIDTH) || (i + 3 > HEIGHT))
    {
        return 0; // O = false
    }

    for (int k = 0; k <= 3; k++) 
    {        
        if (g->grid[(i + k) * WIDTH + (j + k)] != player_move)
        {
            return 0; // O = false
        }
    }
    return 1; // 1 = true
}


//Check if there is at least 4 token in an descending diagonal (\)
static int check_diagonal_descending(struct Grid *g, char player_move, int i, int j) 
{
    if ((j - 3 < 0) || (i + 3 > HEIGHT))
    {
        return 0; // O = false
    }

    for (int k = 0; k <= 3; k++) 
    {
        if (g->grid[(i + k) * WIDTH + (j - k)] != player_move)
        {
            return 0; // O = false
        }
    }
    return 1; // 1 = true
}


//Check if the grid is full
static int check_full(struct Grid *g)
{
    for (int i = 0; i < HEIGHT; i++) //row
    {
        for(int j = 0; j < WIDTH; j++) //col
        {
            if (g->grid[i * WIDTH + j] == ' ')
            {
                return 0; // O = false
            }
        }
    }
    print_grid(g);  
    printf("\nThe grid is full !\nNo more move possible.\nTied match !\n");
    return 1; // 1 = true
}


//Check if there is at least 4 token in the same line 
static int check_horizontal(struct Grid *g, char player_move, int i, int j) 
{
    if (j + 3 > WIDTH)
    {
        return 0; // O = false
    }

    for (int k = 0; k <= 3; k++) 
    {
        if (g->grid[i * WIDTH + j + k] != player_move)
        {
            return 0; // O = false
        }
    }
    return 1; // 1 = true
}


//Check if there is at least 4 token in the same column 
static int check_vertical(struct Grid *g, char player_move, int i, int j)
{
    if (i + 3 > HEIGHT)
    {
        return 0; // 0 = false
    }

    for (int k = 0; k <= 3; k++) 
    {
        if (g->grid[(i+k) * WIDTH + j] != player_move)
        {
            return 0; // O = false
        }
    }
    return 1; // 1 = true
}


//Check if there is a winner, and if there is one who are they
int check_win(struct Grid *g)
{
    for (int i = 0; i < HEIGHT; i++) //row
    {
        for(int j = 0; j < WIDTH; j++) //col
        {
            char player_move = g->grid[i * WIDTH + j];

            if(player_move != ' ')
            {
                if ((check_horizontal(g, player_move, i, j) == 1) || (check_vertical(g, player_move, i, j) == 1))
                {
                    printf("Player '%c' won this game !\n", player_move); 
                    print_grid(g);         
                    return (1); // 1 = true
                }
                if ((check_diagonal_ascending(g, player_move, i, j)) || (check_diagonal_descending(g, player_move, i, j) == 1))   
                {
                    printf("Player '%c' won this game with a diagonal move !\n", player_move);
                    print_grid(g);           
                    return (1); // 1 = true
                }
            }
        }
    }
    return check_full(g); 
}