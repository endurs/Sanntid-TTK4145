// Compile with `gcc foo.c -Wall -std=gnu99 -lpthread`, or use the makefile
// The executable will be named `foo` if you use the makefile, or `a.out` if you use gcc directly

#include <pthread.h>
#include <stdio.h>

int i = 0;
//add mutex to protect i
pthread_mutex_t ilock;

// Note the return type: void*
void* incrementingThreadFunction(){
    // TODO: increment i 1_000_000 times
    for (int j = 0; j < 1000069; j++){
        //ilock mutex
        pthread_mutex_lock(&ilock);
        i++;
        pthread_mutex_unlock(&ilock);
    }
    return NULL;
}

void* decrementingThreadFunction(){
    // TODO: decrement i 1_000_000 times
    for (int j = 0; j < 1000000; j++){
        pthread_mutex_lock(&ilock);
        i--;
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
