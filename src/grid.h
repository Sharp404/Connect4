#ifndef GRID_HEADER_H
#define GRID_HEADER_H

#include <sys/types.h>

#define HEIGHT 6
#define WIDTH 7         


//Put the structure of the grid here :
struct Grid 
{
    pid_t child_pid;
    char *grid;
    int pipefd[2];
};

//Put all the functions of the grid here :
struct Grid *init_grid();
int launch_child(struct Grid *g);
void print_grid(struct Grid *g);

#endif //GRID_HEADER_H
