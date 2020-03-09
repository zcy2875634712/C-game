#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MaxRow	100
#define MaxCol	100
#define NOTHING 0
#define MINE	1
#define InMap(x , y , r ,c)	(x >= 0 && x < r && y >= 0 && y < c)
#define SELECT	"\033[7m"
#define HIDE_CURSOR	"\033[?25l"
#define SHOW_CURSOR	"\033[?25h"
#define CANCEL	"\033[0m"
#define INITX 3
#define INITY 3
typedef enum Status
{
	OPENED,
	CLOSED,
	MARKED
} STAT;

typedef struct Element
{
	STAT stat;
	int mine;
	int number;
} ELEM;

ELEM map [MaxRow][MaxCol];

void InitMap(int number , int row , int col)
{
	int i , j , randx , randy;
	for(i = 0; i < row; i++)
		for(j = 0; j < col; j++)
	 	{
			map [i][j].stat = CLOSED;
			map [i][j].mine = NOTHING;
			map [i][j].number = 0; 
		}

	for(i = 0; i < number; i++)
	{
		srand(time(NULL));
		do
		{
			randx = rand() % row;
			randy = rand() % col;
		}while(map [randx][randy].mine == MINE);
		map [randx][randy].mine = MINE;
	}
}

void DrawMap(int x , int y , int row , int col , int over)
{
	int i , j;
	STAT s;
	printf(HIDE_CURSOR);
	for(i = 0; i < row; i++)
	{
		for(j = 0; j < col; j++)
		{
			if(i == x && j == y)
				printf(SELECT);
			s = map [i][j].stat;
			if(s == CLOSED)
			{	if(over == 0)
					putchar('#');
				else
				{
					if(map [i][j].mine == MINE)
						putchar('!');
					else
						putchar(' ');
				}

			}
			if(s == MARKED)
				putchar('*');
			if(s == OPENED)
			{
				if(map [i][j].number == 0)
					putchar(' ');
				else
					printf("%d" , map [i][j].number);
			}
			printf(CANCEL);
		}
		putchar('\n');
	}
	printf("key wsad to move,key o to open,key m to mark,key q to quit.\n");
}
int AroundMines(int x , int y , int row , int col)
{
	int offsetx , offsety , around = 0;
	for(offsetx = -1; offsetx <= 1; offsetx++)
		for(offsety = -1 ; offsety <= 1; offsety++)
		{
			if(offsetx == 0 && offsety == 0)
				continue;
			if(InMap(x + offsetx , y + offsety , row , col))
			{
				if(map [x + offsetx][y + offsety].mine == MINE)
					around++;		
			}
		}
	return around;
}

void Expand(int x , int y , int row , int col)
{
	STAT s;
	int around;
	s = map [x][y].stat;
	if(s == MARKED || s == OPENED || map [x][y].mine == MINE)
		return;
	around = AroundMines(x , y , row , col);
	map [x][y].stat = OPENED;
	map [x][y].number = around;
	if(around != 0)
		return;

	if(InMap(x - 1 , y , row , col))
		Expand(x - 1 , y , row , col);
	if(InMap(x + 1 , y , row , col))
		Expand(x + 1 , y , row , col);
	if(InMap(x , y - 1 , row , col))
		Expand(x , y - 1 , row , col);
	if(InMap(x , y + 1 , row , col))
		Expand(x , y + 1 , row , col);
}

int Open(int x , int y , int row , int col)
{
	int over = 0;
	if(map [x][y].stat == CLOSED)
	{
		if(map [x][y].mine == NOTHING)
			Expand(x , y , row , col);
		else
			over = 1;
	}
	return over;
}
void Mark(int x , int y)
{
	if(map [x][y].stat == CLOSED)
		map [x][y].stat = MARKED;
	else
	{
		if(map [x][y].stat == MARKED)
			map [x][y].stat = CLOSED;
	}
}
int Win(int row, int col)
{
	int win = 1 ,  i ,  j;
	for(i = 0; i < row; i++)
		for(j = 0; j < col; j++)
		{
			if(map [i][j].mine == MINE && map [i][j].stat != MARKED)
				win = 0;
		}	
	return win;
}
int main()
{
	int x , y , over = 0 , quit = 0 , row , col , mines;
	char input;
	x = INITX;
	y = INITY;
	printf("please enter some data:\n");
	printf("row column mines\n");
	scanf("%d%d%d" , &row , &col , &mines);
	InitMap(mines , row , col);
	while(!quit)
	{
		system("clear");
		DrawMap(x , y , row , col ,over);
		if(Win(row , col))
		{
			printf("----GAME WIN----\n");
			break;
		}
		if(over)
		{
			printf("----GAMEOVER----\n");
			break;
		}
		input = getchar();
		switch(input)
		{
			case 'w':
			case 'W':
				if(x > 0)
					x--;
				break;
			case 's':
			case 'S':
				if(x < row - 1)
					x++;
				break;
			case 'a':
			case 'A':
				if(y > 0)
					y--;
				break;
			case 'd':
			case 'D':
				if(y < col -1)
					y++;
				break;
			case 'o':
			case 'O':
				over = Open(x , y , row , col);
				break;
			case 'm':
			case 'M':
				Mark(x , y);
				break;
			case 'q':
			case 'Q':
				quit = 1;
				break;	
		}
	}
	printf(SHOW_CURSOR);
}
