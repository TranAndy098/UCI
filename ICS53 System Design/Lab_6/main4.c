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
pthread_cond_t bufferFull;
pthread_cond_t bufferEmpty;

int consumer_delay = 0;
int producer_delay = 0;

void *producer(int number, int amount, int delay);
void *consumer(int number, int delay);


int main(int argc, char const *argv[])
{   
    if (argc < 6) {
        printf("Not all arguements given, only %d given and not 5\n", argc-1);
        return 0;
    }
    p = atoi(argv[1]);
    c = atoi(argv[2]);
    i = atoi(argv[3]);
    b = atoi(argv[4]);
    d = atoi(argv[5]);
    printf("p = %d\n", p);
    printf("c = %d\n", c);
    printf("i = %d\n", i);
    printf("b = %d\n", b);
    printf("d = %d\n", d);
    if (d == 0) {
        consumer_delay = .5;
    }
    if (d == 1) {
        producer_delay = .5;
    }
    
    if (c >= p * i) {
        printf("More consumers than producers * items, c(%d) >= p(%d) * i(%d)\n", c, p, i);
        return 0;
    }

    buffer = (int*)malloc(b * sizeof(int));
    producers = (pthread_t*)malloc(p * sizeof(pthread_t));
    consumers = (pthread_t*)malloc(c * sizeof(pthread_t));
    pthread_mutex_init(&mutexBuffer, NULL);
    pthread_cond_init(&bufferFull, NULL);
    pthread_cond_init(&bufferEmpty, NULL);

    goal_count = p * i;

    int total_threads = 0;
    int goal_threads = p + c;

    int curr_producers = 0;
    int curr_consumers = 0;

    while (total_threads < goal_threads) {
        if (curr_producers < p) {
            printf("Producer Creates %d\n", curr_producers);
            pthread_create(&producers[curr_producers], NULL, producer(curr_producers, i, producer_delay), NULL);
            pthread_join(producers[curr_producers], NULL);
            curr_producers++;
        }

        if (curr_consumers < c) {
            printf("Consumer Creates %d\n", curr_consumers);
            pthread_create(&consumers[curr_consumers], NULL, consumer(curr_consumers, consumer_delay), NULL);
            pthread_join(consumers[curr_consumers], NULL);
            curr_consumers++;
        }
    }
    
    
    for (int t = 0; t < p; t++) {
        pthread_join(producers[t], NULL);
        printf("Producer Joined %d\n", t);
    }
    for (int t = 0; t < c; t++) {
        pthread_join(consumers[t], NULL);
        printf("Consumer Joined %d\n", t);
    }

    pthread_mutex_destroy(&mutexBuffer);
    pthread_cond_destroy(&bufferFull);
    pthread_cond_destroy(&bufferEmpty);
    return 0;
}

void *producer(int number, int amount, int delay){
    for (int ti = 0; ti < amount; ti++){

        pthread_mutex_lock(&mutexBuffer);
        while (count >= b)
        {
            pthread_cond_wait(&bufferEmpty, &mutexBuffer);
        }
        printf("producer_%d produced item %d\n", number, ti + (number * amount));
        buffer[count] = ti + (number * amount);
        total_count++;
        count++;
        pthread_cond_broadcast(&bufferFull);
        pthread_mutex_unlock(&mutexBuffer);
        sleep(d);
    }
    // need to add mutex and add items to buf and have it switch between the different producers
    return NULL;
}

void *consumer(int number, int delay){
    while (total_count != goal_count){
        
        
        pthread_mutex_lock(&mutexBuffer);
        while (count <= 0)
        {
            pthread_cond_wait(&bufferFull, &mutexBuffer);
        }
        
        count--;
        printf("consumer_%d consumed item %d\n", number, buffer[count]);
        for (int cc = 0; cc < count; cc++) {
            buffer[cc] = buffer[cc+1];
        }
        
        pthread_cond_broadcast(&bufferEmpty);
        pthread_mutex_unlock(&mutexBuffer);
        sleep(d);
        
    }
    
    
    // need to add mutex and remove items from buff and switch between the different consumers
    return NULL;
}

