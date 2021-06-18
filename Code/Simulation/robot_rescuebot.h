#ifndef RESCUEBOT_H
#define RESCUEBOT_H

#include <stdio.h>

#define North 1
#define South 3
#define West 4
#define East 2
#define Toggle 5

int minSteps(char *world, int iniPos, int width, int target_index);
int get_pos(char *world, char toAquire);
int move(char *world);

#endif // RESCUEBOT_H