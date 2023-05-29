#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "grid.h"

#define WRITE 1
#define READ 0       


//Initialize the game grid with empty cells
struct Grid *init_grid()
{
   struct Grid *g = malloc(sizeof(struct Grid));
   g->grid = malloc(sizeof(char)*(WIDTH*HEIGHT));

   if (g == NULL)                
   {
      return g;
   }
   
   if (g->grid == NULL)          
   {
      free(g);
      return NULL;
   }

   for(int i = 0; i < WIDTH*HEIGHT ; i++)
   {
      g->grid[i] = ' ';
   }
   
   if (pipe(g->pipefd) == -1)
   {
      printf("Error : pipe\n");
      return NULL;
   }

   g->child_pid = 0;
   return g;
}


//Print the grid of the connect4
void print_grid(struct Grid *g)
{
   printf("  1   2   3   4   5   6   7"); 
   for (int i = 0; i < HEIGHT; i++) //row
   {
      printf("\n+---+---+---+---+---+---+---+\n|");
      for(int j = 0; j < WIDTH; j++) //col
      {
         printf(" %c |", g->grid[i * WIDTH + j]); //print the stdout char at the X/Y coordonate
      }
   }
   printf("\n+---+---+---+---+---+---+---+\n");
   printf("  1   2   3   4   5   6   7\n");  
}


//Reset the grid on the screen to prepare a new play
static void reset_screen()        
{
   system("clear");
}


//Child function that read, wait an input and return the status of the program - if there is an error or not
static int wait_input(struct Grid *g) 
{
   const int buffer_size = WIDTH*HEIGHT;
   int res = read(g->pipefd[READ], g->grid, buffer_size);

   while (res == 0)
   {
      sleep(15); //Modify the sleep if the game is too slow
      res = read(g->pipefd[READ], g->grid, buffer_size);
   }
   if(res == -1)
   {
      printf("Error reading !\n");
      return -1; // -1 = error
   }
   return 0; // 0 = false
}


//Child Function that print the grid and close the child pipe in reading and free them
static int print_child(struct Grid *g)
{
   close(g->pipefd[1]);
   while (1)
   {
      if(wait_input(g) == -1)
      {
         close(g->pipefd[READ]); 
         free(g->grid); 
         free(g); 
         return -1; // -1 = error
      }
      reset_screen();
      print_grid(g);
   }
   print_grid(g);
   close(g->pipefd[READ]);
   free(g->grid); 
   free(g); 
   return 0; // 0 = false
}
    

//Parent Function that create a fork and exit the print_child if it's value is 0 then close the pipe in reading
int launch_child(struct Grid *g)
{
   g->child_pid = fork();

   if (g->child_pid < 0)
   {
      printf("Error fork !\n");
      return -1; // -1 = error
   }

   if(g->child_pid == 0)
   {
      exit(print_child(g));
   }
   close(g->pipefd[READ]);
   return 0; // 0 = false
}