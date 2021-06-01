/*
A very simple text based simulation of a rescue scenario. Wall, robot and target only.

Copyright 2021 Kristian Rother (kristian.rother@hshl.de)

Redistribution and use in source and binary forms, with or without modification, are permitted provided
that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions
and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions
and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to
endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <stdlib.h>

// THIS IS THE FUNCTION YOU IMPLEMENT
int move(char *world) {
    int robot_index, target_index, robot_index_x, robot_index_y, target_index_x, target_index_y, width;
    int North = 1;
    int South = 3;
    int West = 4;
    int East = 2;
    //int nextMove = 1;
    for (int i = 0; i < 200; ++i)
    {
        if (world[i] == '\n')
        {
            width = i+1;
            break;
        }
    }
    for (int i = 0; i < 200; ++i)
    {
        if (world[i] == 'R') 
        {
            robot_index = i;
            break;
        }
    }
    for(int i = 0; i < 200; ++i)
    {
        if (world[i] == 'T') 
        {
            target_index = i;
            break;
        }
    }
    printf("\nwidth = %d\n", width);
    //robot position in x and y coordinates
    robot_index_y = robot_index / width;
    robot_index_x = robot_index % width;

    //Target position in x and y coordinates 
    target_index_y = target_index / width;
    target_index_x = target_index % width;
    printf("robot position: %d - %d\n", robot_index_x, robot_index_y);
    printf("target position: %d - %d\n", target_index_x, target_index_y);
    int xDistance = target_index_x - robot_index_x;
    int yDistance = target_index_y - robot_index_y;
    printf("Distance: %d - %d\n", xDistance, yDistance);
    //robot next to the target *** TARGET FOUND - SINGLE MOVE ***
    if(robot_index_x - 1 == target_index_x)
        return West;
    if(robot_index_x + 1 == target_index_x)
        return East;
    if(robot_index_y - 1 == target_index_y)
        return North;
    if(robot_index_y + 1 == target_index_y)
        return South;


    //nalize surrounding
    int isFreeToMove[8];
    for (int i = 0; i < 8; i++)
        isFreeToMove[i] = -1;

    //watch up
    for (int i = 0; i < 3; i++)
        isFreeToMove[i] = (world[(robot_index_y - 1)*width + (robot_index_x - 1 + i)] == '#' ? 0 : 1);
   
    //watch down
    for (int i = 0; i < 3; i++)
        isFreeToMove[i + 5] = (world[(robot_index_y + 1)*width + (robot_index_x - 1 + i)] == '#' ? 0 : 1);

    //watch left
    isFreeToMove[3] = (world[(robot_index_y)*width + (robot_index_x - 1)] == '#' ? 0 : 1);
    
    //watch right
    isFreeToMove[4] = (world[(robot_index_y)*width + (robot_index_x + 1)] == '#' ? 0 : 1);

    printf("\n");
    for(int i = 0; i < 8; i++)
        printf(" %d ", isFreeToMove[i]);

    printf("\n");
    
    //Check the shortest distance between X and Y
    //If the robot is in the same column with the target
    if(xDistance == 0)
    {
        if(yDistance > 0)
        {
            //try to move south
            if(isFreeToMove[6] == 1)
            {
                return South;
            }
        }
        else if (yDistance < 0)
        {
            //try to move north
            if(isFreeToMove[1])
            {
                return North;
            }
        }
    }

    //If the robot is in the same row with the target
    else if (yDistance == 0)
    {
        if(xDistance > 0)
        {
            //try to move East
            if(isFreeToMove[4] == 1)
            {
                return East;
            }
        }
        else if (xDistance < 0)
        {
            //try to move West
            if(isFreeToMove[3] == 1)
            {
                return West;
            }
        }
    }

    /*else if(abs(xDistance) < abs(yDistance))
    {
        if(xDistance > 0)
        {
            //robot will try to move East
            if(isFreeToMove[4])
                return East;
        }
        else
        {
            //robot will try to move Weast
            if(isFreeToMove[3])
                return West;
        }
    }
    else
    {
        if(yDistance > 0)
        {
            //robot will try to move South
            if(isFreeToMove[6])
                return South;
        }
        else
        {
            //robot will try to move North
            return North;
        }
    }*/
    return 1; // REPLACE THE RETURN VALUE WITH YOUR CALCULATED RETURN VALUE
}

// Return target index
int update_world(int movement, char *world, int robot_index, int width) {
    int target_index = 0;
    // NORTH
    if(movement == 1) {
        target_index = robot_index-(width+1); // +1 for the newline
    }
    // SOUTH
    else if(movement == 3) {
        target_index = robot_index+(width+1); // +1 for the newline
    }
    // EAST
    else if(movement == 2) {
        target_index = robot_index+1;
    }
    // WEST
    else if(movement == 4) {
        target_index = robot_index-1;
    }
    
    // ACTION
    if(world[target_index] == 'O') {
        world[target_index] = 'R';
        world[robot_index] = 'O';
        return target_index;
    }
    else if(world[target_index] == '#') {
        printf("%s", world);
        printf("%c", '\n');
        printf("FAILURE, crashed into a wall!");
        exit(1);
    }
     else if(world[target_index] == 'T') {
        world[target_index] = 'R';
        world[robot_index] = 'O';
        printf("%s", world);
        printf("%c", '\n');
        printf("SUCCESS, target found!");
        exit(0);
    }
}

int main() {
    const int MAX_STEPS = 200;
    int step = 1;
    
    int movement;
    int width = 20; // excluding newlines

    // The world
    char world[200] = {
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','R','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','#','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','T','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','\n',
    };

    // Initialize target and robot positions
    // Assumes only one target, one robot
    unsigned int elements = sizeof(world)/sizeof(world[0]);

    // Initialize the index of the robot and the target.
    // Assumes exactly one robot and one target
    int robot_index;
    int target_index;

    for(int i = 0; i < elements; ++i) {
    if (world[i] == 'R') {
            robot_index = i;
            break;
        }
    }
    for(int i = 0; i < elements; ++i) {
    if (world[i] == 'T') {
            target_index = i;
            break;
        }
    }

    // Print the initial world
    printf("Starting position: %c", '\n');
    // Debug output
    // printf("Robot index: %i / target index: %i %c", robot_index, target_index, '\n');
    printf("%s", world);
    printf("%c", '\n');
    
    while(step <= MAX_STEPS) {
        printf("After step number %i: %c", step, '\n');

        movement = move(world);
        robot_index = update_world(movement, world, robot_index, width);
        printf("%s", world);
        printf("%c", '\n');
        step = step+1;
    }
    if(step >= MAX_STEPS) {
        printf("FAILURE, maximum number of steps exceeded.");
    }
    
}