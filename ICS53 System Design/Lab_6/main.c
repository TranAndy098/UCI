// Andy Quoc Anh Dinh Tran 57422363

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

int p;
int c;
int i;
int b;
int d;

int* buffer;
int count = 0;
int total_count = 0;
int goal_count = 0;

pthread_t* producers;
pthread_t* consumers;

pthread_mutex_t mutexBuffer;
pthread_cond_t notEmpty;
pthread_cond_t notFull;

double consumer_delay = 0;
double producer_delay = 0;

void *producer(void *args);
void *consumer(void *args);

typedef struct {
    int id;
} thread_id;


int main(int argc, char const *argv[])
{   
    if (argc < 6) {
        printf("Not all arguements given, only %d given and not 5\n", argc-1);
        return 0;
    }

    // populate the variables with the correct arguements
    p = atoi(argv[1]);
    c = atoi(argv[2]);
    i = atoi(argv[3]);
    b = atoi(argv[4]);
    d = atoi(argv[5]);

    // if d == 0, consumer has half second delay before and after consuming
    if (d == 0) {
        consumer_delay = .5;
    }
    // if d == 1, producer has half second delay before and after producing
    if (d == 1) {
        producer_delay = .5;
    }
    
    // checking to satisfy c < p * i
    if (c >= p * i) {
        printf("More consumers than producers * items, c(%d) >= p(%d) * i(%d)\n", c, p, i);
        return 0;
    }

    // initialize dynamic buffer, producer array, consumer array
    buffer = (int*)malloc(b * sizeof(int));
    producers = (pthread_t*)malloc(p * sizeof(pthread_t));
    consumers = (pthread_t*)malloc(c * sizeof(pthread_t));

    // initialize mutex, and two thread conditions
    pthread_mutex_init(&mutexBuffer, NULL);
    pthread_cond_init(&notEmpty, NULL);
    pthread_cond_init(&notFull, NULL);

    // total amount of items
    goal_count = p * i;

    // locks mutex to ensure all producers and consumers are created with mutual exclusion
    pthread_mutex_lock(&mutexBuffer);

    // creating producer threads
    for (int t = 0; t < p; t++) {
        thread_id *args = malloc(sizeof *args);
        args->id = t;
        pthread_create(&producers[t], NULL, producer, args);
    }

    // creating consumer threads
    for (int t = 0; t < c; t++) {
        thread_id *args = malloc(sizeof *args);
        args->id = t;
        pthread_create(&consumers[t], NULL, consumer, args);
    }

    // unlocks mutex so producers and consumers can start 
    pthread_mutex_unlock(&mutexBuffer);

    // join producer threads back to main thread
    for (int t = 0; t < p; t++) {
        pthread_join(producers[t], NULL);
    }

    // join consumer threads back to main thread
    for (int t = 0; t < c; t++) {
        pthread_join(consumers[t], NULL);
    }

    // destroy mutex, and two thread conditions
    pthread_mutex_destroy(&mutexBuffer);
    pthread_cond_destroy(&notEmpty);
    pthread_cond_destroy(&notFull);

    return 0;
}

void *producer(void* arg)
{
    // create struct from args to get producer id
    thread_id *args = arg;

    // each producer will create i amount of items
    for (int ti = 0; ti < i; ti++)
    {
        // sleep before production
        sleep(producer_delay);

        // locks mutex to avoid data race
        pthread_mutex_lock(&mutexBuffer);

        // will wait if buffer is full
        while (count >= b)
        {
            pthread_cond_wait(&notFull, &mutexBuffer);
        }

        printf("producer_%d produced item %d\n", args->id, ti + (args->id * i));

        // update buffer with item and update count
        buffer[count] =  ti + (args->id * i);
        count++;

        // unlocks mutex for another thread to be able to run
        pthread_mutex_unlock(&mutexBuffer);

        // sends signal to say that the buffer is not empty
        pthread_cond_signal(&notEmpty);

        // sleep after production
        sleep(producer_delay);
    }
    free(args);
    return NULL;
}

void *consumer(void* arg)
{
    // create struct from args to get consumer id
    thread_id *args = arg;

    // run until all items have been consumed all together by all consumers
    while (total_count != goal_count)
    {
        // sleep before consumption
        sleep(consumer_delay);

        // locks mutex to avoid data race
        pthread_mutex_lock(&mutexBuffer);

        // will wait if buffer is empty
        while ((count <= 0) && (total_count != goal_count))
        {
            pthread_cond_wait(&notEmpty, &mutexBuffer);
        }

        // if all items are consumed, unlock mutex and send signal to all other consumers waiting
        if (total_count == goal_count) {
            pthread_mutex_unlock(&mutexBuffer);
            pthread_cond_broadcast(&notEmpty);
            break;
        }


        printf("consumer_%d consumed item %d\n", args->id, buffer[0]);

        // update buffer, queue method simulate circular buffer
        count--;
        for (int cc = 0; cc < count; cc++) {
            buffer[cc] = buffer[cc+1];
        }

        // increment items consumed counter
        total_count++;
        
        // unlocks mutex for another thread to be able to run
        pthread_mutex_unlock(&mutexBuffer);
        
        // sends signal to say that the buffer is not full
        pthread_cond_signal(&notFull);

        // if all items are consumed, unlock mutex and send signal to all other consumers waiting
        if (total_count == goal_count) {
            pthread_cond_broadcast(&notEmpty);
            break;
        }

        // sleep after consumption
        sleep(consumer_delay);
    }

    free(args);
    return NULL;
}

