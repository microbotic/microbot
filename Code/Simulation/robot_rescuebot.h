#ifndef RESCUEBOT_H
#define RESCUEBOT_H

#include <stdio.h>

#define North 1
#define South 3
#define West 4
#define East 2
#define Toggle 5
#define MaxSteps 201

// Function declaration
//int minSteps(char *world, int initial_position_x, int initial_position_y, int width);
int minSteps(char *world, int initial_position, int width);
int move(char *world);

#endif // RESCUEBOT_H