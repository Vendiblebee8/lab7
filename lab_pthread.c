#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // Compile with "-lpthread"

int total = 0; // to record total number of messages from the two threads
pthread_t t1, t2;

void * thread_work(void * arg) {
    long self_counter = 0; // to record how many times printed by the current thread

    return (void *)self_counter;
}

int main(int argc, char * argv[]) {
    long t1_c = 0, t2_c = 0; // to record numbers of times printed by T1 and T2

    if (argc < 3) {
        printf("There must be 2 arguements following the binary!\n");
        return 0;
    }

    total = atoi(argv[1]); 
    
    pthread_create(&t1, NULL, thread_work, argv + 2);
    pthread_create(&t2, NULL, thread_work, argv + 2);
    pthread_join(t1, (void *)&t1_c);
    pthread_join(t2, (void *)&t2_c);
    
    printf("In main thread: T1 printed %ld times. T2 printed %ld times.\n", t1_c, t2_c);
    
    return 0;
}


