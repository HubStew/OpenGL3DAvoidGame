#ifndef STONE_H
#define STONE_H

#include <stdio.h>
#include <stdlib.h>
#include <ctime>

int rockPos[4];
int rockPos2[4];

int preRoad = 0;
int nextRoad = 0;

int stoneArray[4][4] = { {0, 0, 0, 0},
						 {0, 0, 1, 1}, 
						 {0, 1, 0, 1}, 
						 {0, 1, 1, 0} };

/* 돌의 경우의수를 지정해주는 함수 */
void makeRock()
{
	srand((int)time(NULL));

	if (nextRoad == 1 || nextRoad == 3)
	{
		preRoad = 2;
		for(int i = 1; i < 4; i++)
			rockPos[i] = stoneArray[i][preRoad];
	} else
	{
		preRoad = (int)((rand() % 9)%2 + 1);
		if (preRoad == 2)
			preRoad++;

		for(int i = 1; i < 4; i++)
			rockPos[i] = stoneArray[i][preRoad];
	}

}

void makeRock2()
{
	srand((int)time(NULL));


	if (preRoad == 1 || preRoad == 3)
	{
		nextRoad = 2;
		for(int i = 1; i < 4; i++)
			rockPos2[i] = stoneArray[i][nextRoad];
	} else
	{
		nextRoad = (int)((rand() % 9)%2 + 1);
		if (nextRoad == 2)
			nextRoad++;

		for(int i = 1; i < 4; i++)
			rockPos2[i] = stoneArray[i][nextRoad];
	}


}


#endif