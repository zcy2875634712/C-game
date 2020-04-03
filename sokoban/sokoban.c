#include <stdio.h>
#include <stdlib.h>
#include "sokoban.h"
#include "../getch/getch.h"


char map[ROW][COL];
int man_r, man_c;

int open_map(char *filename)
{
	FILE *fp;
	if ((fp = fopen(filename, "rb")) == NULL)
		return ERR;
	fread(*map, sizeof(char), ROW*COL, fp);
	fclose(fp);
	return 0;
}

void get_man()
{
	int i, j;
	for (i = 0; i < ROW; i++)
		for(j = 0; j < COL; j++) {
			if(ISSET(map[i][j], MAN)) {
				man_r = i;
				man_c = j;
				UNSET(map[i][j], MAN);
			}
		}
}

void draw_map()
{
	int i, j;

	printf(HIDE_CURSOR);
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			if (i == man_r && j == man_c) {
				printf(DRAW_MAN);
			} else {
				if (ISSET(map[i][j], BOX)) {
					if (ISSET(map[i][j], BLANK))
						printf(DRAW_BOX);
					if (ISSET(map[i][j], TARGET))
						printf(DRAW_BOXTARGET);
				} else {
					if (ISSET(map[i][j], BLANK))
						printf(DRAW_BLANK);
					if (ISSET(map[i][j], TARGET))
						printf(DRAW_TARGET);
					if (ISSET(map[i][j], WALL))
						printf(DRAW_WALL);
				}
			}
		}
		putchar('\n');
	}
}

void move(int r_offset, int c_offset)
{
	int next_r, next_c, after_r, after_c;
	
	next_r = man_r + r_offset;
	next_c = man_c + c_offset;
	after_r = man_r + r_offset * 2;
	after_c = man_c + c_offset * 2;

	if(INMAP(next_r, next_c)) {
		if (ISSET(map[next_r][next_c], BOX)) {
			if (INMAP(after_r, after_c)) {
				if (!ISSET(map[after_r][after_c], WALL)
				&& !ISSET(map[after_r][after_c], BOX)) {
				
					SET(map[after_r][after_c], BOX);
					UNSET(map[next_r][next_c], BOX);
					man_r = next_r;
					man_c = next_c;
				}					
			}
		} else {
			if (!ISSET(map[next_r][next_c], WALL)) {
			man_r = next_r;
			man_c = next_c;
			}
		}
	}
}

int judge()
{
	int win = 1, i, j;

	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++) {
			if (ISSET(map[i][j], TARGET)
			&& !ISSET(map[i][j], BOX))
				win = 0;
		}

	return win;
}

int main()
{
	char filename[MAX_NAME];
	char opt;
	int quit = 0;

	printf("\nPlease enter the map file: ");
	scanf("%s", filename);
	if(open_map(filename) == ERR) {
		printf("Failed to open map file! \n");
		exit(0);
	}

	get_man();

	for (; ;) {
		system("clear");
		draw_map();
		if (quit || judge()) {
			break;
		}
		opt = getch();
		switch (opt) {
		case 'w':
		case 'W':
			move(-1, 0);
			break;
		case 's':
		case 'S':
			move(1, 0);
			break;
		case 'a':
		case 'A':
			move(0, -1);
			break;
		case 'd':
		case 'D':
			move(0, 1);
			break;
		case 'q':
		case 'Q':
			quit = 1;
			break;
		}
	}

	printf(SHOW_CURSOR);
}
