#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// gcc p1.c -o p1 -lm
// ./p1

void coordinates_pairs(int amount) 
    {
        srand ( time(NULL)); // setup rand
        int x, y, dist; // instantiate x, y, dist

        for (int i = 0; i < amount; i++){
            x = rand() % 10; // x is modded by 10 to get int in [0, 9]
            y = rand() % 10; // y is modded by 10 to get int in [0, 9]
            dist = (int) round(sqrt(pow(x,2) + pow(y,2))); // dist is rounded integer of squareroot of x^2 and y^2

            printf("(%d, %d): %d ",x ,y, dist); // print coordinates and distance from origin (0, 0)
            for (int j = 0; j < dist; j++){
                printf("*"); // print "*" for distance length
            }
            printf("\n");
        }
    }

int main(int argc, char const *argv[])
    {
        // 10 is just to indicate 10 coordinate pairs
        coordinates_pairs(10);
        return 0;
    }
