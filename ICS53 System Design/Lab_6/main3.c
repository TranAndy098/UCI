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
pthread_t producers;
pthread_t consumers;
pthread_mutex_t mutexBuffer;
pthread_cond_t bufferFull;
pthread_cond_t bufferEmpty;

int consumer_delay = 0;
int producer_delay = 0;

void *producer(void* arg);
void *consumer(void* arg);


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
    // sleep(time) = sleep 500ms is sleep .5s
    if (c >= p * i) {
        printf("More consumers than producers * items, c(%d) >= p(%d) * i(%d)\n", c, p, i);
        return 0;
    }

    buffer = (int*)malloc(b * sizeof(int));
    pthread_mutex_init(&mutexBuffer, NULL);
    pthread_cond_init(&bufferFull, NULL);
    pthread_cond_init(&bufferEmpty, NULL);

    goal_count = p * i;
    
    pthread_create(&producers, NULL, producer, NULL);
    
    pthread_create(&consumers, NULL, consumer, NULL);
    
    pthread_join(producers, NULL);
    
    pthread_join(consumers, NULL);
    

    pthread_mutex_destroy(&mutexBuffer);
    pthread_cond_destroy(&bufferFull);
    pthread_cond_destroy(&bufferEmpty);
    return 0;
}

void *producer(void* arg){
    int round = 0;
    while (total_count != goal_count)
    {   
                for (int ti = 0; ti < p; ti++){

            
                
            

                    pthread_mutex_lock(&mutexBuffer);
                    while (count >= b)
                        {
                            pthread_cond_wait(&bufferEmpty, &mutexBuffer);
                        }
                    printf("producer_%d produced item %d\n", ti, round + (ti * i));
                    buffer[count] = round + (ti * i);
                    total_count++;
                    count++;
                    pthread_mutex_unlock(&mutexBuffer);
                    
                    pthread_cond_broadcast(&bufferFull);
                }
                if (total_count == goal_count) {
                    break;
                }
            sleep(producer_delay);
            round++;
            }
    
    // need to add mutex and add items to buf and have it switch between the different producers
    printf("producers done\n");
    return NULL;
}

void *consumer(void* arg){
    while (total_count != goal_count)
    {
        
            for (int ti = 0; ti < c; ti++){
            
                
            
            
                pthread_mutex_lock(&mutexBuffer);
                while (count <= 0)
                {
                    pthread_cond_wait(&bufferFull, &mutexBuffer);
                }
                count--;
                printf("consumer_%d consumed item %d\n", ti, buffer[0]);
                for (int cc = 0; cc < count; cc++) {
                    buffer[cc] = buffer[cc+1];
                }
                
                
                pthread_mutex_unlock(&mutexBuffer);
                
                pthread_cond_broadcast(&bufferEmpty);
                if (total_count == goal_count) {
                    break;
                }
            }
        sleep(consumer_delay);
        
        
    }
    printf("consumers done\n");
    
    
    // need to add mutex and remove items from buff and switch between the different consumers
    return NULL;
}

