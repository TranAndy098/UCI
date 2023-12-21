#include <stdio.h>
#include <unistd.h>

int main() {
    unsigned int i = 0;
    while(i < 30)
    {
        printf("Counter: %d\n", i);
        i++;
        sleep(1);
    }
    return 0;
}