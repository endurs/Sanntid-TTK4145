// Compile with `gcc foo.c -Wall -std=gnu99 -lpthread`, or use the makefile
// The executable will be named `foo` if you use the makefile, or `a.out` if you use gcc directly

#include <pthread.h>
#include <stdio.h>

int i = 0;
pthread_mutex_t ilock;

void* incrementingThreadFunction(){
    for (int j = 0; j < 169; j++){
        //ilock mutex
        pthread_mutex_lock(&ilock);
        i++;
        printf("i: %d\n", i);
        pthread_mutex_unlock(&ilock);

        //waste time calculating pi 100000 times
        double pi = 0;
        for (int k = 0; k < 1000; k++){
            pi += 4.0 * (1 - (k % 2) * 2) / (2 * k + 1);
        }
        
    }
    return NULL;
}

void* decrementingThreadFunction(){
    for (int j = 0; j < 100; j++){
        pthread_mutex_lock(&ilock);
        i--;
        printf("i: %d\n", i);
        pthread_mutex_unlock(&ilock);

        //waste time calculating pi 100000 times
        double pi = 0;
        for (int k = 0; k < 1000; k++){
            pi += 4.0 * (1 - (k % 2) * 2) / (2 * k + 1);
        }
        pthread_mutex_unlock(&ilock);
    }
    return NULL;
}


int main(){
    //init mutex
    pthread_mutex_init(&ilock, NULL);

    pthread_t incrementingThread, decrementingThread;
    pthread_create(&incrementingThread, NULL, incrementingThreadFunction, NULL);
    pthread_create(&decrementingThread, NULL, decrementingThreadFunction, NULL);
    

    pthread_join(incrementingThread, NULL);
    pthread_join(decrementingThread, NULL);

    //kill mutex because thats apparently good practice
    pthread_mutex_destroy(&ilock);

    
    printf("The magic number is: %d\n", i);
    if(i == 69){
        printf("Nice\n");
    }
    return 0;
}
