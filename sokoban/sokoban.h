#ifndef GAME_H
#define GAME_H

/* map size */
#define ROW	10
#define COL	10
#define MAX_NAME	20
#define INMAP(r, c)	(0<=r && r<ROW && 0<=c && c<COL )

/* to save storage */
#define BLANK	(1 << 0)
#define TARGET	(1 << 1)
#define WALL	(1 << 2)
#define BOX	(1 << 3)
#define MAN	(1 << 4)

#define SET(n, bit)	((n) |= bit)
#define UNSET(n, bit)	((n) &= ~bit)
#define ISSET(n, bit)	((n) & bit)

#define ERR	-1

#define DRAW_BLANK	" "
#define DRAW_TARGET	"\033[32m*\033[0m"
#define DRAW_WALL	"\033[7m#\033[0m"
#define DRAW_BOX	"\033[7mX\033[0m"
#define DRAW_BOXTARGET	"\033[42mX\033[0m"
#define DRAW_MAN	"@"
#define HIDE_CURSOR	"\033[?25l"
#define SHOW_CURSOR	"\033[?25h"

int open_map(char *filename);	/* open map file */
void get_man();
void draw_map();
void move(int r_offset, int c_offset);
int  judge();
#endif
