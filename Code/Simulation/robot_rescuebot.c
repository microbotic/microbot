#include "robot_rescuebot.h"

// IMPLEMET THIS FUNCTION
// ALLOWED RETURN VALUES:
// 1: North, 2: East, 3: South, 4: West, 5: Toggle watern/land mode

int current_mode = 0; 

int minSteps(char *world, int initial_position, int width)
{
    int newSteps;
    int newToggle = 0;
    int totalSteps = 1;     //counter for the steps to go to the target
    int steps[200];
    //Clear the steps counter
    for (int i = 0; i < 200; i++)
    {
        steps[i] = 0;
    }
    steps[initial_position] = 1;  //mark the initial step as 1 (one steps total from the robot to the target)
    newSteps = 1;
    int targetFound = 0;
    while((newSteps != 0) && (targetFound == 0))
    {
        newSteps = 0;   //initialize new steps (if there are no new steps no makes sence to try again)
        for(int i = 0; i < 200; i++)
        {
            int actualpos = 0;
            if(steps[i] == totalSteps)
            {
                actualpos = i;
                if((world[actualpos - width] == 'T') || (world[actualpos + width] == 'T') ||
                    (world[actualpos + 1] == 'T') || (world[actualpos - 1] == 'T'))
                {
                    targetFound = 1;
                    break;
                }
                //count steps to go to different positions
                if((world[actualpos - width] != '#') && (steps[actualpos - width] == 0))
                {
                    steps[actualpos - width] = totalSteps + 1;
                    newSteps++;
                }
                if((world[actualpos + width] != '#') && (steps[actualpos + width] == 0))
                {
                    steps[actualpos + width] = totalSteps + 1;
                    newSteps++;
                }
                if((world[actualpos + 1] != '#') && (steps[actualpos + 1] == 0))
                {
                    steps[actualpos + 1] = totalSteps + 1;
                    newSteps++;
                }
                if((world[actualpos - 1] != '#') && (steps[actualpos - 1] == 0))
                {
                    steps[actualpos - 1] = totalSteps + 1;
                    newSteps++;
                }
            }
        }
        if (newSteps != 0)
        {
            totalSteps++;
        }
    }
    return totalSteps;
}

int move(char *world) {
    int robot_index, target_index, robot_index_x, robot_index_y, target_index_x, target_index_y, width;
    
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
    
    //robot next to the target *** TARGET FOUND - SINGLE MOVE ***
    if(world[robot_index - width] == 'T')
        return North;
    if(world[robot_index + width] == 'T')
        return South;
    if(world[robot_index - 1] == 'T')
        return West;
    if(world[robot_index + 1] == 'T')
        return East;
  
    //analize surrounding
    int isFreeToMove[4];
    int upIsFree, downIsFree, leftIsFree, rightIsFree;
    upIsFree = (world[robot_index - width] == '#' ? 0 : 1);
    downIsFree = (world[robot_index + width] == '#' ? 0 : 1);
    leftIsFree = (world[robot_index - 1] == '#' ? 0 : 1);
    rightIsFree = (world[robot_index + 1] == '#' ? 0 : 1);

    int ifUp = 201;
    int ifDown = 201;
    int ifLeft = 201; 
    int ifRight = 201;;
    
    //IF UP IS FREE -------------------------------------------------------

    if(upIsFree == 1)
        ifUp = minSteps(world, robot_index - width, width);
    if(downIsFree == 1)
        ifDown = minSteps(world, robot_index + width, width);
    if(leftIsFree)
        ifLeft = minSteps(world, robot_index - 1, width);
    if(rightIsFree)
        ifRight = minSteps(world, robot_index + 1, width);
      
    int bestRoute = 0;
    if((ifUp <= ifDown) && (ifUp <= ifLeft) && (ifUp <= ifRight))
        bestRoute = North;
    else if((ifDown <= ifLeft) && (ifDown <= ifRight))
        bestRoute = South;
    else if(ifLeft <= ifRight)
        bestRoute = West;
    else
        bestRoute = East;


    //decide if robot has to toggle
    //NORTH
    if(bestRoute == North)
    {
        if ((world[robot_index - width] == '~') && (current_mode == 0))
        {
            current_mode = 1;
            return Toggle;
        }
        if ((world[robot_index - width] == 'O') && (current_mode == 1))
        {
            current_mode = 0;
            return Toggle;
        }    
    }
    //SOUTH
    if(bestRoute == South)
    {
        if ((world[robot_index + width] == '~') && (current_mode == 0))
        {
            current_mode = 1;
            return Toggle;
        }
        if ((world[robot_index + width] == 'O') && (current_mode == 1))
        {
            current_mode = 0;
            return Toggle;
        }    
    }
    //WEST
    if(bestRoute == West)
    {
        if ((world[robot_index - 1] == '~') && (current_mode == 0))
        {
            current_mode = 1;
            return Toggle;
        }
        if ((world[robot_index - 1] == 'O') && (current_mode == 1))
        {
            current_mode = 0;
            return Toggle;
        }    
    }
    //EAST
    if(bestRoute == East)
    {
        if ((world[robot_index + 1] == '~') && (current_mode == 0))
        {
            current_mode = 1;
            return Toggle;
        }
        if ((world[robot_index + 1] == 'O') && (current_mode == 1))
        {
            current_mode = 0;
            return Toggle;
        }    
    }
    return bestRoute; // REPLACE THE RETURN VALUE WITH YOUR CALCULATED RETURN VALUE
}