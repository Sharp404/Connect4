# Connect4 in C 
> by Sharp - 1st Year of Master's in Computer Security

## Project Context

This project is part of a C course in my first year of Master's in Computer Security. The objective of the project is to implement the game Connect Four in the C programming language.

## Description

This program is a command-line implementation of the famous game Connect Four, also known as "Puissance 4" in French. Connect Four was first sold under the Connect Four trademark in 1974 by Milton Bradley, and it has been held by Hasbro since 1984.

The objective of the game is to align a sequence of four tokens of the same color on a 6x7 grid. Each player has 21 tokens of their chosen color (represented as 'X' or 'O' in this program). On each turn, the players take turns placing a token in a column of their choice. The token then slides down to the lowest available position in that column. The first player to achieve a consecutive alignment of at least four pieces, horizontally, vertically, or diagonally, wins the game. If all the boxes in the grid are filled and no player has won, the game is declared a draw.

## Program Structure & Architecture

```bash
.
└─── connect4
    ├─── src
           ├─── check.c
           ├─── connect4.c
           ├─── connect4.h
           ├─── grid.c
           └─── grid.h
    ├─── BUILD.md
    └─── README.md
```
- check.c: Contains functions for performing various checks related to the grid and the tokens.
- connect4.c: Implements the game logic for Connect Four.
- connect4.h: Header file for the Connect Four game logic.
- grid.c: Manages the game board, including grid initialization, updates, and display.
- grid.h: Header file for the game board management.
    
## Choices made

In this project, I made the following design choices:

- The code is divided into multiple files to improve modularity and ease of review.
- Small functions are used to enhance code readability and maintainability.
- A total of 17 functions, including the main function, have been implemented.

## How to play ?

To play the game, follow these steps:

1. Compile and execute the program.
2. Choose between yourself and your opponent to determine who will be "X" and who will be "O".
3. By default, Player 1 has the "X" tokens.
4. Player 1 starts the game by entering a number between 1 and 7 corresponding to the column where they want to place their token. Press the enter key to confirm the choice.
5. The game begins, and the game grid will update accordingly.
6. Player 2 takes their turn by entering a number to place their token in a column.
7. Continue taking turns until a player wins or the game ends in a draw.
8. Once the game is finished, the filled grid will display the moves made by both players.
9. If you want to start another game, simply type ./connect4 again.

Enjoy the game and have fun testing your skills and strategy!
