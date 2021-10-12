#include "functions.h"
#include <string.h>

void printCenter(WINDOW* win, int row, char* str){
	int center = win->_maxx / 2;
	int half_length = strlen(str) / 2;
	int adjusted = center - half_length;
	mvwprintw(win, row, adjusted, str);
	wrefresh(win);
}

int checkWin(Tile** grid){
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			if(checkIfMine(grid[j][i])){ //there is a mine
				if(grid[j][i].flag != 9)
					return 0;
			}
			else{ // there is NOT a mine
				if(grid[j][i].flag >= 9 && grid[j][i].flag < 0)
					return 0;
			}
		}
	}
	
	return 1;
}

int checkIfMine(Tile t){
	return t.mine == 1;
}

int checkIfFlagged(Tile t){
	return t.flag != -1;
}

void flagTile(Tile** grid, Cursor curse){
	if(grid[curse.x][curse.y].flag == -1 || grid[curse.x][curse.y].flag == 10)
		grid[curse.x][curse.y].flag = 9;
	else if(grid[curse.x][curse.y].flag == 9)
		grid[curse.x][curse.y].flag = -1;
}

void questionTile(Tile** grid, Cursor curse){
	if(grid[curse.x][curse.y].flag == -1 || grid[curse.x][curse.y].flag == 9)
		grid[curse.x][curse.y].flag = 10;
	else if(grid[curse.x][curse.y].flag == 10)
		grid[curse.x][curse.y].flag = -1;
}

typedef struct tile Tile;

void initGrid(Tile** grid){
	
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			grid[i][j].mine = 0;
			grid[i][j].flag = -1;
		}
	}	
}

void setGrid(Tile** grid){
	srand((unsigned)time(0));
	int x,y;
	for(int i = 0; i < 15; ++i){
		x = rand() % 10;
		y = rand() % 10;
		while(checkIfMine(grid[x][y])){
			x = rand() % 10;
			y = rand() % 10;
		}
		grid[x][y].mine = 1;
	}
	
}

void displayGrid(WINDOW* win, Tile** grid){
	//j = x && i = y
	for(int i = 0; i < 10; ++i){
		wmove(win,9+i,1);
		for(int j = 0; j < 10; ++j){
			switch(grid[j][i].flag){
				case(-2):
					wprintw(win, "<*>");
					break;
				case(-1):
					//if(checkIfMine(grid[j][i])){ wprintw(win, "<*>"); break;}
					wprintw(win, "<->");
					break;
				case(0):
					wprintw(win, "   ");
					break;
				case(9):
					wprintw(win, "<!>");
					break;
				case(10):
					wprintw(win, "<?>");
					break;
				default:
					//if(checkIfMine(grid[j][i])){ wprintw(win, "<*>"); break;}
					wprintw(win, "<%d>", grid[j][i].flag);
					break;
				
				if(checkIfMine(grid[j][i])){ wprintw(win, "<*>"); break;}
				
			}
			/*switch(checkIfMine(grid[j][i])){
				case(1):
					wprintw(win, "<!>");
					break;
				case(0):
					wprintw(win, "<->");
					break;
			}*/
			if(j < 9) wprintw(win, " ");
		}}
}

void setCursor(WINDOW* win, Cursor curse){
	wmove(win, curse.y + 9, (curse.x*4) + 2); 
}

int uncoverTile(Tile** grid, Cursor curse){
	if(grid[curse.x][curse.y].flag != -1) return grid[curse.x][curse.y].flag;
	if(checkIfMine(grid[curse.x][curse.y])){
		grid[curse.x][curse.y].flag = -2;
		return -2;
	}
	int count = 0;
	for(int i = -1; i < 2; ++i){
		for(int j = -1; j < 2; ++j){
			if(j == 0 && i == 0) continue;
			if(curse.x+j < 0 || curse.x+j > 9 || curse.y+i < 0 || curse.y+i > 9) continue;
			count += checkIfMine(grid[curse.x+j][curse.y+i]);
		}}
	grid[curse.x][curse.y].flag = count;
	
	if(grid[curse.x][curse.y].flag == 0){
		for(int i = -1; i < 2; ++i){
			for(int j = -1; j < 2; ++j){
				if(curse.x+j < 0 || curse.x+j > 9 || curse.y+i < 0 || curse.y+i > 9) continue;
				if(j == 0 && i == 0) continue;
				uncoverTileTwo(grid,curse.x+j,curse.y+i);
		}}
	}
	
	return count;
}

int uncoverTileTwo(Tile** grid, int x, int y){
	if(grid[x][y].flag != -1) return grid[x][y].flag;
	if(checkIfMine(grid[x][y])){
		grid[x][y].flag = -2;
		return -2;
	}
	int count = 0;
	for(int i = -1; i < 2; ++i){
		for(int j = -1; j < 2; ++j){
			if(x+j < 0 || x+j > 9 || y+i < 0 || y+i > 9) continue;
			if(j == 0 && i == 0) continue;
			count += checkIfMine(grid[x+j][y+i]);
		}}
	grid[x][y].flag = count;
	
	if(grid[x][y].flag == 0){
		for(int i = -1; i < 2; ++i){
			for(int j = -1; j < 2; ++j){
				if(x+j < 0 || x+j > 9 || y+i < 0 || y+i > 9) continue;
				if(j == 0 && i == 0) continue;
				uncoverTileTwo(grid,x+j,y+i);
		}}
	}
	
	return count;
}

void uncoverGrid(Tile** grid){
	for(int i = 0; i < 10; ++i){
		for(int j = 0; j < 10; ++j){
			if(checkIfFlagged(grid[j][i])) continue;
			if(checkIfMine(grid[j][i])){
				grid[j][i].flag = -2;
				continue;
			}
			uncoverTileTwo(grid, j, i);
		}
	}
}