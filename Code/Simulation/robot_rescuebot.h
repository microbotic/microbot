#ifndef RESCUEBOT_H
#define RESCUEBOT_H

#include <stdio.h>

#define North 1
#define South 3
#define West 4
#define East 2
#define Toggle 5
#define DestroyNort 6
#define DestroyEast 7
#define DestroySouth 8
#define DestroyWest 9

int newCellValue(char *world, int *steps, int curret, int newPos, int actualEnergy);
int minEnergy(char *world, int iniPos, int width, int target_index);
int get_pos(char *world, char toAquire);
int move(char *world, int worldNumber);

#endif // RESCUEBOT_H

//gcc robot_rescuebot.c robo_world_4.c