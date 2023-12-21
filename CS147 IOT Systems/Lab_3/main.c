#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char const *argv[])
{   

    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    int last_sec = timeinfo->tm_sec;
    int current = 0;
    int d_days = 31;
    int n_days = 30;
    int days;

    while(1) {
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        last_sec = timeinfo->tm_sec;

        if (timeinfo->tm_mon == 10) {
            n_days = 30 - timeinfo->tm_mday;
        }
        else if (timeinfo->tm_mon == 11) {
            d_days = 31 - timeinfo->tm_mday;
            n_days = 0;
        }
        days = d_days + n_days;
        

        if (current != last_sec) {
            //printf ( "%s\n", asctime (timeinfo) );
            printf ( "Days:%d Hours:%d Minutes:%d Seconds:%d\n", days, 23-timeinfo->tm_hour, 59-timeinfo->tm_min, 60-timeinfo->tm_sec );
        }
        current = last_sec;
        //break;
    }
    //printf ( "%s\n", asctime (timeinfo) );
    
    return 0;
}