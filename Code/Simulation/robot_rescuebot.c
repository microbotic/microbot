#include "robot_rescuebot.h"

// IMPLEMET THIS FUNCTION
// ALLOWED RETURN VALUES:
// 1: North, 2: East, 3: South, 4: West, 5: Toggle watern/land mode

int current_mode = 0;
int actual_map = 0;

int newCellValue(char *world, int *steps, int curret, int newPos, int actualEnergy)
{
    if(world[newPos] == 'T' || world[newPos] == 't')
        return actualEnergy + 1;
    if(world[newPos] == '*')
        return actualEnergy + 4;
    return ((world[newPos] !=  (world[curret])) ? actualEnergy + 4 : actualEnergy + 1);
}

int minEnergy(char *world, int initial_position, int width, int target_index)
{
    int totalEnergy = 1;     //counter for the steps to go to the target
    int steps[200];
    for (int i = 0; i < 200; i++)   //Clear the steps counter
        steps[i] = 0;
    steps[initial_position] = ((world[initial_position] == '~' && current_mode == 0) || 
        ((world[initial_position] == 'O' && current_mode == 1) || world[initial_position] == '*')  ? 4 : 1);
    int targetFound = 0;
    while(targetFound == 0)
    {
        if(steps[target_index] != 0){
            return steps[target_index];
        }
        for(int i = 0; i < 200; i++)
        {
            if(steps[i] == totalEnergy)
            {
                if((world[i - width] != '#') && (steps[i - width] == 0))
                    steps[i - width] = newCellValue(world, steps, i, i - width, totalEnergy);
                if((world[i + width] != '#') && (steps[i + width] == 0))
                    steps[i + width] = newCellValue(world, steps, i, i + width, totalEnergy);    
                if((world[i + 1] != '#') && (steps[i + 1] == 0))
                    steps[i + 1] = newCellValue(world, steps, i, i + 1, totalEnergy);
                if((world[i - 1] != '#') && (steps[i - 1] == 0))
                    steps[i - 1] = newCellValue(world, steps, i, i - 1, totalEnergy);
            }
        }
        totalEnergy ++;
    }
    return totalEnergy;
}

int get_pos(char *world, char toAquire)
{
    for (int i = 0; i < 200; ++i)
        if (world[i] == toAquire)
            return i;
    return -1;
}

int move(char *world, int worldNumber) {
    if(actual_map != worldNumber)
    {
        current_mode = 0;
        actual_map = worldNumber;
    }
    int robot_index, width, target_index = -1;
    int bestRoute = 0;
    width = get_pos(world, '\n') + 1;
    robot_index = get_pos(world, 'R');
    target_index = get_pos(world, 'T');
    if(target_index == -1)
        target_index = get_pos(world, 't');
    if(target_index == -1)
        target_index = get_pos(world, 'X');
    //get min steps in every direction
    int ifUp = ((world[robot_index - width] == '#') ? 1000 : minEnergy(world, robot_index - width, width, target_index));
    int ifDown = ((world[robot_index + width] == '#') ? 1000 : minEnergy(world, robot_index + width, width, target_index));
    int ifLeft = ((world[robot_index - 1] == '#') ? 1000 : minEnergy(world, robot_index - 1, width, target_index)); 
    int ifRight = ((world[robot_index + 1] == '#') ? 1000 : minEnergy(world, robot_index + 1, width, target_index));
    if((ifUp <= ifDown) && (ifUp <= ifLeft) && (ifUp <= ifRight))
        bestRoute = North;
    else if((ifDown <= ifLeft) && (ifDown <= ifRight))
        bestRoute = South;
    else if(ifLeft <= ifRight)
        bestRoute = West;
    else
        bestRoute = East;

    //decide if robot has to toggle
    if(((bestRoute == North)
        &&(((world[robot_index - width] == '~') && (current_mode == 0)) || ((world[robot_index - width] == 'O') && (current_mode == 1)))) ||
        ((bestRoute == South)
        && (((world[robot_index + width] == '~') && (current_mode == 0)) || ((world[robot_index + width] == 'O') && (current_mode == 1)))) ||
        ((bestRoute == West)
        &&(((world[robot_index - 1] == '~') && (current_mode == 0)) || ((world[robot_index - 1] == 'O') && (current_mode == 1)))) ||
        ((bestRoute == East)
        && (((world[robot_index + 1] == '~') && (current_mode == 0)) || ((world[robot_index + 1] == 'O') && (current_mode == 1)))))
        {
            current_mode = (current_mode == 0 ? 1 : 0);
            return Toggle;
        }
    if(bestRoute == North && world[robot_index - width] == '*')
        return DestroyNort;
    if(bestRoute == South && world[robot_index + width] == '*')
        return DestroySouth;
    if(bestRoute == West && world[robot_index - 1] == '*')
        return DestroyWest;
    if(bestRoute == East && world[robot_index + 1] == '*')
        return DestroyEast;
    return bestRoute; // REPLACE THE RETURN VALUE WITH YOUR CALCULATED RETURN VALUE
}