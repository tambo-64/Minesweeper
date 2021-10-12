#ifndef FUNCTIONS
#define FUNCTIONS

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "game.h"

typedef struct tile Tile;
typedef struct cursor Cursor;

void printCenter(WINDOW* win, int row, char* str);
int checkWin(Tile** grid);
int checkIfMine(Tile t);
int checkIfFlagged(Tile t);
void flagTile(Tile** grid, Cursor curse);
void questionTile(Tile** grid, Cursor curse);
void initGrid(Tile** grid);
void setGrid(Tile** grid);
void displayGrid(WINDOW* win, Tile** grid);
void setCursor(WINDOW* win, Cursor curse);
int uncoverTile(Tile** grid, Cursor curse);
int uncoverTileTwo(Tile** grid, int x, int y);
void uncoverGrid(Tile** grid);

#endif
