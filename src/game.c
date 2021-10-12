#include "game.h"

typedef struct tile Tile;
typedef struct cursor Cursor;

int gameLoop(void){
	
	initscr();
	start_color();
	cbreak();
	
	int ch = '0';
	
	WINDOW* win = newwin(20, 41, (stdscr->_maxy/2) - 10, (stdscr->_maxx/2) - 20);
	refresh();
	box(win, 0,0);
	
	printCenter(win, 2, "Welcome to Minesweeper");
	printCenter(win, 3, "Press any key to continue");
	wrefresh(win);
	wgetch(win);
	
	while(ch != 'n' && ch != 'N'){
		sweeperLoop(win);
		wclear(win);
		box(win, 0,0);
		printCenter(win, 2, "Would you like to play again? [y/n]");
		wmove(win, 3, 20);
		ch = wgetch(win);
	}
	
	endwin();
	return 0;
}

int sweeperLoop(WINDOW* win){
	
	int runGame = 1;
	Cursor curse;
	curse.x = 3;
	curse.y = 4;
	Tile** grid = (Tile**)malloc(10*sizeof(Tile*));
	for(int i = 0; i < 10; ++i)
		grid[i] = (Tile*)malloc(10*sizeof(Tile));
	
	initGrid(grid);
	setGrid(grid);
	wclear(win);
	box(win,0,0);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	displayGrid(win, grid);
	setCursor(win, curse);
	keypad(win, true);
	printCenter(win, 1, "Minesweeper");
	mvwprintw(win, 4, 1, "[SPACE] ~ Uncover tile");
	mvwprintw(win, 5, 1, "[F] ~ Flag tile for mine");
	mvwprintw(win, 6, 1, "[G] ~ Question tile for mine");
	mvwprintw(win, 7, 1, "[Q] ~ Quit the game");
	setCursor(win, curse);
	wrefresh(win);
	
	while(runGame){
		int ch = wgetch(win);
		switch(ch){
			case(KEY_LEFT):
				if(curse.x <= 0) break;
				curse.x -= 1;
				break;
			case(KEY_RIGHT):
				if(curse.x >= 9) break;
				curse.x += 1;
				break;
			case(KEY_UP):
				if(curse.y <= 0) break;
				curse.y -= 1;
				break;
			case(KEY_DOWN):
				if(curse.y >= 9) break;
				curse.y += 1;
				break;
			case(' '):
				if(checkIfMine(grid[curse.x][curse.y])){
					grid[curse.x][curse.y].flag = -2;
					runGame = 0;
					printCenter(win, 2, "Game Over");
					printCenter(win, 3, "Press any key to continue");
					uncoverGrid(grid);
					displayGrid(win, grid);
					wmove(win, 8,20);
					wrefresh(win);
					wgetch(win);
				}
				uncoverTile(grid, curse);
				break;
			case('f'):
				flagTile(grid, curse);
				break;
			case('g'):
				questionTile(grid, curse);
				break;
			case('q'):
				runGame = 0;
				break;
			default:
				break;
		}
		
		if(runGame == 0) break;
		
		setCursor(win, curse);
		displayGrid(win, grid);
		setCursor(win, curse);
		wrefresh(win);
		if(checkWin(grid)){
			runGame = 0;
			printCenter(win, 2, "You Win!");
			printCenter(win, 3, "Press any key to continue");
			uncoverGrid(grid);
			displayGrid(win, grid);
			wmove(win,8,20);
			wrefresh(win);
			wgetch(win);
		}
	}
	
	return 0;
}