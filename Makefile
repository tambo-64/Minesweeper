minesweeper: src/main.c src/functions.c src/game.c src/functions.h src/game.h
	gcc -o minesweeper src/main.c src/functions.c src/game.c -g -Wall -I. -lncurses
