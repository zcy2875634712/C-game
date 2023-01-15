getch.o: getch/getch.c getch/getch.h
	gcc -c getch/getch.c -o getch.o
Sokoban: getch.o sokoban/sokoban.c sokoban/sokoban.h 
	gcc getch.o sokoban/sokoban.c sokoban/sokoban.h  -o Sokoban
Minesweeper: getch.o minesweeper/minesweeper.c
	gcc getch.o minesweeper/minesweeper.c -o Minesweeper
