#include <stdio.h>
#include <stdlib.h>
#include "sokoban.h"

int main()
{
	int i, j, num;
	FILE *fw;
	char map[ROW][COL];
	char element[7];
	char filename[MAX_NAME];
	
	SET(element[0], BLANK);
	SET(element[1], WALL);
	SET(element[2], TARGET);

	//box on blank
	SET(element[3], BLANK);
	SET(element[3], BOX);

	//box on target
	SET(element[4], TARGET);
	SET(element[4], BOX);

	//man on blank
	SET(element[5], BLANK);
	SET(element[5], MAN);

	//man on target
	SET(element[6], TARGET);
	SET(element[6], MAN);

	printf("0--blank\n1--wall\n2--target\n3--box on blank\n4--box on target\n5--man on blank\n6--man on target\n");

	for (i = 0; i < ROW; i++) {
		for(j = 0; j < COL; j++) {
			scanf("%1d", &num);
			map[i][j] = element[num];
		}
	}
	
	printf("enter map file name: ");
	scanf("%s", filename);

	fw = fopen(filename, "wb+");
	fwrite(*map, sizeof(char), ROW * COL, fw);
	fclose(fw);
}
