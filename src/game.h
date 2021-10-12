#ifndef GAME
#define GAME

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "functions.h"

struct tile{
	int mine;
	int flag;
	
};

struct cursor{
	int x;
	int y;
};

int gameLoop(void);
int sweeperLoop(WINDOW* win);

#endif
