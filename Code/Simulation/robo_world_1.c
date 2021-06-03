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
    //robot position in x and y coordinates
    robot_index_y = robot_index / width;
    robot_index_x = robot_index % width;

    //Target position in x and y coordinates 
    target_index_y = target_index / width;
    target_index_x = target_index % width;

    //Distance between robot and target
    int xDistance = target_index_x - robot_index_x;
    int yDistance = target_index_y - robot_index_y;
    
    //robot next to the target *** TARGET FOUND - SINGLE MOVE ***
    if(world[(robot_index_y - 1) * width + robot_index_x] == 'T')
        return North;
    if(world[(robot_index_y + 1) * width + robot_index_x] == 'T')
        return South;
    if(world[robot_index_y * width + robot_index_x - 1] == 'T')
        return West;
    if(world[robot_index_y * width + robot_index_x + 1] == 'T')
        return East;
    

    int moveWest;

    int steps[200];

    //analize surrounding
    int isFreeToMove[4];
    int upIsFree, downIsFree, leftIsFree, rightIsFree;
    upIsFree = (world[(robot_index_y - 1) * width + robot_index_x] == '#' ? 0 : 1);
    downIsFree = (world[(robot_index_y + 1) * width + robot_index_x] == '#' ? 0 : 1);
    leftIsFree = (world[robot_index_y * width + robot_index_x - 1] == '#' ? 0 : 1);
    rightIsFree = (world[robot_index_y * width + robot_index_x + 1] == '#' ? 0 : 1);

    int ifUp = 201;
    int ifDown = 201;
    int ifLeft = 201; 
    int ifRight = 201;;
    
    //IF UP IS FREE -------------------------------------------------------

    if(upIsFree == 1)
    {
        int newSteps;
        int totalSteps = 1;     //counter for the steps to go to the target

        //Clear the steps counter
        for (int i = 0; i < 200; i++)
        {
            steps[i] = 0;
        }
        steps[(robot_index_y - 1) * width + robot_index_x] = 1;  //mark the initial step as 1 (one steps total from the robot to the target)

        newSteps = 1;
        int targetFound = 0;
        while((newSteps != 0) && (targetFound == 0))
        {
            newSteps = 0;   //initialize new steps (if there are no new steps no makes sence to try again)
            for(int i = 0; i < 200; i++)
            {
                int actualx = 0;
                int acutaly = 0;
                if(steps[i] == totalSteps)
                {
                    acutaly = i / width;
                    actualx = i % width;
                    if((world[(acutaly - 1) * width + actualx] == 'T') || (world[(acutaly + 1) * width + actualx] == 'T') ||
                        (world[acutaly * width + actualx + 1] == 'T') || (world[acutaly * width + actualx - 1] == 'T'))
                    {
                        targetFound = 1;
                        break;
                    }
                    //count steps to go to different positions
                    if((world[(acutaly - 1) * width + actualx] != '#') && (steps[(acutaly - 1) * width + actualx] == 0))
                    {
                        steps[(acutaly - 1) * width + actualx] = totalSteps + 1;
                        newSteps++;
                    }
                    if((world[(acutaly + 1) * width + actualx] != '#') && (steps[(acutaly + 1) * width + actualx] == 0))
                    {
                        steps[(acutaly + 1) * width + actualx] = totalSteps + 1;
                        newSteps++;
                    }
                    if((world[acutaly * width + actualx + 1] != '#') && (steps[acutaly * width + actualx + 1] == 0))
                    {
                        steps[acutaly * width + actualx + 1] = totalSteps + 1;
                        newSteps++;
                    }
                    if((world[acutaly * width + actualx - 1] != '#') && (steps[acutaly * width + actualx - 1] == 0))
                    {
                        steps[acutaly * width + actualx - 1] = totalSteps + 1;
                        newSteps++;
                    }
                }
            }
            if (newSteps != 0)
               {
                totalSteps++;
            }
        }
        ifUp = totalSteps;
    }


    // IF DOWN IS FREE

    if(downIsFree == 1)
    {
        int newSteps;
        int totalSteps = 1;     //counter for the steps to go to the target

        //Clear the steps counter
        for (int i = 0; i < 200; i++)
        {
            steps[i] = 0;
        }
        steps[(robot_index_y + 1) * width + robot_index_x] = 1;  //mark the initial step as 1 (one steps total from the robot to the target)
        newSteps = 1;
        int targetFound = 0;
        while((newSteps != 0) && (targetFound == 0))
        {
            newSteps = 0;   //initialize new steps (if there are no new steps no makes sence to try again)
            for(int i = 0; i < 200; i++)
            {
                int actualx = 0;
                int acutaly = 0;
                if(steps[i] == totalSteps)
                {
                    acutaly = i / width;
                    actualx = i % width;
                    if((world[(acutaly - 1) * width + actualx] == 'T') || (world[(acutaly + 1) * width + actualx] == 'T') ||
                        (world[acutaly * width + actualx + 1] == 'T') || (world[acutaly * width + actualx - 1] == 'T'))
                    {
                        targetFound = 1;
                        break;
                    }
                    //count steps to go to different positions
                    if((world[(acutaly - 1) * width + actualx] != '#') && (steps[(acutaly - 1) * width + actualx] == 0))
                    {
                        steps[(acutaly - 1) * width + actualx] = totalSteps + 1;
                        newSteps++;
                    }
                    if((world[(acutaly + 1) * width + actualx] != '#') && (steps[(acutaly + 1) * width + actualx] == 0))
                    {
                        steps[(acutaly + 1) * width + actualx] = totalSteps + 1;
                        newSteps++;
                    }
                    if((world[acutaly * width + actualx + 1] != '#') && (steps[acutaly * width + actualx + 1] == 0))
                    {
                        steps[acutaly * width + actualx + 1] = totalSteps + 1;
                        newSteps++;
                    }
                    if((world[acutaly * width + actualx - 1] != '#') && (steps[acutaly * width + actualx - 1] == 0))
                    {
                        steps[acutaly * width + actualx - 1] = totalSteps + 1;
                        newSteps++;
                    }
                }
            }
            if (newSteps != 0)
               {
                totalSteps++;
            }
        }
        ifDown = totalSteps;
    }

    //----------GOING LEFT

    if(leftIsFree == 1)
    {
        int newSteps;
        int totalSteps = 1;     //counter for the steps to go to the target

        //Clear the steps counter
        for (int i = 0; i < 200; i++)
        {
            steps[i] = 0;
        }
        steps[robot_index_y * width + robot_index_x - 1] = 1;  //mark the initial step as 1 (one steps total from the robot to the target)
        newSteps = 1;
        int targetFound = 0;
        while((newSteps != 0) && (targetFound == 0))
        {
            newSteps = 0;   //initialize new steps (if there are no new steps no makes sence to try again)
            for(int i = 0; i < 200; i++)
            {
                int actualx = 0;
                int acutaly = 0;
                if(steps[i] == totalSteps)
                {
                    acutaly = i / width;
                    actualx = i % width;
                    if((world[(acutaly - 1) * width + actualx] == 'T') || (world[(acutaly + 1) * width + actualx] == 'T') ||
                        (world[acutaly * width + actualx + 1] == 'T') || (world[acutaly * width + actualx - 1] == 'T'))
                    {
                        targetFound = 1;
                        break;
                    }
                    //count steps to go to different positions
                    if((world[(acutaly - 1) * width + actualx] != '#') && (steps[(acutaly - 1) * width + actualx] == 0))
                    {
                        steps[(acutaly - 1) * width + actualx] = totalSteps + 1;
                        newSteps++;
                    }
                    if((world[(acutaly + 1) * width + actualx] != '#') && (steps[(acutaly + 1) * width + actualx] == 0))
                    {
                        steps[(acutaly + 1) * width + actualx] = totalSteps + 1;
                        newSteps++;
                    }
                    if((world[acutaly * width + actualx + 1] != '#') && (steps[acutaly * width + actualx + 1] == 0))
                    {
                        steps[acutaly * width + actualx + 1] = totalSteps + 1;
                        newSteps++;
                    }
                    if((world[acutaly * width + actualx - 1] != '#') && (steps[acutaly * width + actualx - 1] == 0))
                    {
                        steps[acutaly * width + actualx - 1] = totalSteps + 1;
                        newSteps++;
                    }
                }
            }
            if (newSteps != 0)
               {
                totalSteps++;
            }
        }
        ifLeft = totalSteps;
    }

    // IF GOING RIGHT ------------------------------------

    if(rightIsFree == 1)
    {
        int newSteps;
        int totalSteps = 1;     //counter for the steps to go to the target

        //Clear the steps counter
        for (int i = 0; i < 200; i++)
        {
            steps[i] = 0;
        }
        steps[robot_index_y * width + robot_index_x + 1] = 1;  //mark the initial step as 1 (one steps total from the robot to the target)
        newSteps = 1;
        int targetFound = 0;
        while((newSteps != 0) && (targetFound == 0))
        {
            newSteps = 0;   //initialize new steps (if there are no new steps no makes sence to try again)
            for(int i = 0; i < 200; i++)
            {
                int actualx = 0;
                int acutaly = 0;
                if(steps[i] == totalSteps)
                {
                    acutaly = i / width;
                    actualx = i % width;
                    if((world[(acutaly - 1) * width + actualx] == 'T') || (world[(acutaly + 1) * width + actualx] == 'T') ||
                        (world[acutaly * width + actualx + 1] == 'T') || (world[acutaly * width + actualx - 1] == 'T'))
                    {
                        targetFound = 1;
                        break;
                    }
                    //count steps to go to different positions
                    if((world[(acutaly - 1) * width + actualx] != '#') && (steps[(acutaly - 1) * width + actualx] == 0))
                    {
                        steps[(acutaly - 1) * width + actualx] = totalSteps + 1;
                        newSteps++;
                    }
                    if((world[(acutaly + 1) * width + actualx] != '#') && (steps[(acutaly + 1) * width + actualx] == 0))
                    {
                        steps[(acutaly + 1) * width + actualx] = totalSteps + 1;
                        newSteps++;
                    }
                    if((world[acutaly * width + actualx + 1] != '#') && (steps[acutaly * width + actualx + 1] == 0))
                    {
                        steps[acutaly * width + actualx + 1] = totalSteps + 1;
                        newSteps++;
                    }
                    if((world[acutaly * width + actualx - 1] != '#') && (steps[acutaly * width + actualx - 1] == 0))
                    {
                        steps[acutaly * width + actualx - 1] = totalSteps + 1;
                        newSteps++;
                    }
                }
            }
            if (newSteps != 0)
               {
                totalSteps++;
            }
        }
        ifRight = totalSteps;
    }

      
    int bestRoute = 0;
    if((ifUp <= ifDown) && (ifUp <= ifLeft) && (ifUp <= ifRight))
        bestRoute = North;
    else if((ifDown <= ifLeft) && (ifDown <= ifRight))
        bestRoute = South;
    else if(ifLeft <= ifRight)
        bestRoute = West;
    else
        bestRoute = East;
  
    return bestRoute; // REPLACE THE RETURN VALUE WITH YOUR CALCULATED RETURN VALUE
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
        '#','T','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
        '#','O','R','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','#','\n',
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