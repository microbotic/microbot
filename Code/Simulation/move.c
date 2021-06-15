// THIS IS THE FUNCTION YOU IMPLEMENT
int move(char *world)
{
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
            width = i + 1;
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
    for (int i = 0; i < 200; ++i)
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
    if (world[(robot_index_y - 1) * width + robot_index_x] == 'T')
        return North;
    if (world[(robot_index_y + 1) * width + robot_index_x] == 'T')
        return South;
    if (world[robot_index_y * width + robot_index_x - 1] == 'T')
        return West;
    if (world[robot_index_y * width + robot_index_x + 1] == 'T')
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
    int ifRight = 201;
    ;

    //IF UP IS FREE -------------------------------------------------------

    if (upIsFree == 1)
    {
        int newSteps;
        int totalSteps = 1; //counter for the steps to go to the target

        //Clear the steps counter
        for (int i = 0; i < 200; i++)
        {
            steps[i] = 0;
        }
        steps[(robot_index_y - 1) * width + robot_index_x] = 1; //mark the initial step as 1 (one steps total from the robot to the target)

        newSteps = 1;
        int targetFound = 0;
        while ((newSteps != 0) && (targetFound == 0))
        {
            newSteps = 0; //initialize new steps (if there are no new steps no makes sence to try again)
            for (int i = 0; i < 200; i++)
            {
                int actualx = 0;
                int acutaly = 0;
                if (steps[i] == totalSteps)
                {
                    acutaly = i / width;
                    actualx = i % width;
                    if ((world[(acutaly - 1) * width + actualx] == 'T') || (world[(acutaly + 1) * width + actualx] == 'T') ||
                        (world[acutaly * width + actualx + 1] == 'T') || (world[acutaly * width + actualx - 1] == 'T'))
                    {
                        targetFound = 1;
                        break;
                    }
                    //count steps to go to different positions
                    if ((world[(acutaly - 1) * width + actualx] != '#') && (steps[(acutaly - 1) * width + actualx] == 0))
                    {
                        steps[(acutaly - 1) * width + actualx] = totalSteps + 1;
                        newSteps++;
                    }
                    if ((world[(acutaly + 1) * width + actualx] != '#') && (steps[(acutaly + 1) * width + actualx] == 0))
                    {
                        steps[(acutaly + 1) * width + actualx] = totalSteps + 1;
                        newSteps++;
                    }
                    if ((world[acutaly * width + actualx + 1] != '#') && (steps[acutaly * width + actualx + 1] == 0))
                    {
                        steps[acutaly * width + actualx + 1] = totalSteps + 1;
                        newSteps++;
                    }
                    if ((world[acutaly * width + actualx - 1] != '#') && (steps[acutaly * width + actualx - 1] == 0))
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

    if (downIsFree == 1)
    {
        int newSteps;
        int totalSteps = 1; //counter for the steps to go to the target

        //Clear the steps counter
        for (int i = 0; i < 200; i++)
        {
            steps[i] = 0;
        }
        steps[(robot_index_y + 1) * width + robot_index_x] = 1; //mark the initial step as 1 (one steps total from the robot to the target)
        newSteps = 1;
        int targetFound = 0;
        while ((newSteps != 0) && (targetFound == 0))
        {
            newSteps = 0; //initialize new steps (if there are no new steps no makes sence to try again).
            for (int i = 0; i < 200; i++)
            {
                int actualx = 0;
                int acutaly = 0;
                if (steps[i] == totalSteps)
                {
                    acutaly = i / width;
                    actualx = i % width;
                    if ((world[(acutaly - 1) * width + actualx] == 'T') || (world[(acutaly + 1) * width + actualx] == 'T') ||
                        (world[acutaly * width + actualx + 1] == 'T') || (world[acutaly * width + actualx - 1] == 'T'))
                    {
                        targetFound = 1;
                        break;
                    }
                    //count steps to go to different positions
                    if ((world[(acutaly - 1) * width + actualx] != '#') && (steps[(acutaly - 1) * width + actualx] == 0))
                    {
                        steps[(acutaly - 1) * width + actualx] = totalSteps + 1;
                        newSteps++;
                    }
                    if ((world[(acutaly + 1) * width + actualx] != '#') && (steps[(acutaly + 1) * width + actualx] == 0))
                    {
                        steps[(acutaly + 1) * width + actualx] = totalSteps + 1;
                        newSteps++;
                    }
                    if ((world[acutaly * width + actualx + 1] != '#') && (steps[acutaly * width + actualx + 1] == 0))
                    {
                        steps[acutaly * width + actualx + 1] = totalSteps + 1;
                        newSteps++;
                    }
                    if ((world[acutaly * width + actualx - 1] != '#') && (steps[acutaly * width + actualx - 1] == 0))
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

    if (leftIsFree == 1)
    {
        int newSteps;
        int totalSteps = 1; //counter for the steps to go to the target

        //Clear the steps counter
        for (int i = 0; i < 200; i++)
        {
            steps[i] = 0;
        }
        steps[robot_index_y * width + robot_index_x - 1] = 1; //mark the initial step as 1 (one steps total from the robot to the target)
        newSteps = 1;
        int targetFound = 0;
        while ((newSteps != 0) && (targetFound == 0))
        {
            newSteps = 0; //initialize new steps (if there are no new steps no makes sence to try again)
            for (int i = 0; i < 200; i++)
            {
                int actualx = 0;
                int acutaly = 0;
                if (steps[i] == totalSteps)
                {
                    acutaly = i / width;
                    actualx = i % width;
                    if ((world[(acutaly - 1) * width + actualx] == 'T') || (world[(acutaly + 1) * width + actualx] == 'T') ||
                        (world[acutaly * width + actualx + 1] == 'T') || (world[acutaly * width + actualx - 1] == 'T'))
                    {
                        targetFound = 1;
                        break;
                    }
                    //count steps to go to different positions
                    if ((world[(acutaly - 1) * width + actualx] != '#') && (steps[(acutaly - 1) * width + actualx] == 0))
                    {
                        steps[(acutaly - 1) * width + actualx] = totalSteps + 1;
                        newSteps++;
                    }
                    if ((world[(acutaly + 1) * width + actualx] != '#') && (steps[(acutaly + 1) * width + actualx] == 0))
                    {
                        steps[(acutaly + 1) * width + actualx] = totalSteps + 1;
                        newSteps++;
                    }
                    if ((world[acutaly * width + actualx + 1] != '#') && (steps[acutaly * width + actualx + 1] == 0))
                    {
                        steps[acutaly * width + actualx + 1] = totalSteps + 1;
                        newSteps++;
                    }
                    if ((world[acutaly * width + actualx - 1] != '#') && (steps[acutaly * width + actualx - 1] == 0))
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

    if (rightIsFree == 1)
    {
        int newSteps;
        int totalSteps = 1; //counter for the steps to go to the target

        //Clear the steps counter
        for (int i = 0; i < 200; i++)
        {
            steps[i] = 0;
        }
        steps[robot_index_y * width + robot_index_x + 1] = 1; //mark the initial step as 1 (one steps total from the robot to the target)
        newSteps = 1;
        int targetFound = 0;
        while ((newSteps != 0) && (targetFound == 0))
        {
            newSteps = 0; //initialize new steps (if there are no new steps no makes sence to try again)
            for (int i = 0; i < 200; i++)
            {
                int actualx = 0;
                int acutaly = 0;
                if (steps[i] == totalSteps)
                {
                    acutaly = i / width;
                    actualx = i % width;
                    if ((world[(acutaly - 1) * width + actualx] == 'T') || (world[(acutaly + 1) * width + actualx] == 'T') ||
                        (world[acutaly * width + actualx + 1] == 'T') || (world[acutaly * width + actualx - 1] == 'T'))
                    {
                        targetFound = 1;
                        break;
                    }
                    //count steps to go to different positions
                    if ((world[(acutaly - 1) * width + actualx] != '#') && (steps[(acutaly - 1) * width + actualx] == 0))
                    {
                        steps[(acutaly - 1) * width + actualx] = totalSteps + 1;
                        newSteps++;
                    }
                    if ((world[(acutaly + 1) * width + actualx] != '#') && (steps[(acutaly + 1) * width + actualx] == 0))
                    {
                        steps[(acutaly + 1) * width + actualx] = totalSteps + 1;
                        newSteps++;
                    }
                    if ((world[acutaly * width + actualx + 1] != '#') && (steps[acutaly * width + actualx + 1] == 0))
                    {
                        steps[acutaly * width + actualx + 1] = totalSteps + 1;
                        newSteps++;
                    }
                    if ((world[acutaly * width + actualx - 1] != '#') && (steps[acutaly * width + actualx - 1] == 0))
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
    if ((ifUp <= ifDown) && (ifUp <= ifLeft) && (ifUp <= ifRight))
        bestRoute = North;
    else if ((ifDown <= ifLeft) && (ifDown <= ifRight))
        bestRoute = South;
    else if (ifLeft <= ifRight)
        bestRoute = West;
    else
        bestRoute = East;

    return bestRoute;
}