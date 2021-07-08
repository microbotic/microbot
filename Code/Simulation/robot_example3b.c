#include <stdio.h>
#include "robot_example3b.h"

// IMPLEMENT THIS FUNCTION
// ALLOWED RETURN VALUES:
// 1: North, 2: East, 3: South, 4: West, 5: Toggle watern/land mode
int current_id = -1;
int c = 0;

int move(char *world, int map_id) {
    if(map_id != current_id) {
        c = 0;
        current_id = map_id;
    }
    printf("Current map: %d \n" ,current_id);
    c = c+1;
    if(c > 3) {
        return 3;
    } else {
        return 1;
    }
}