#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int total = 0;
int global_count = 0;
pthread_t t1, t2;
pthread_mutex_t lock;

void print_string(const char* str, int is_reverse, long tid) {
    pthread_mutex_lock(&lock);
    global_count++;
    printf("%d: In thread %ld (TID=%ld): ", global_count, (tid == t1 ? 1 : 2), tid);
    if (is_reverse) {
        for (int i = strlen(str) - 1; i >= 0; i--) {
            putchar(str[i]);
        }
    } else {
        printf("%s", str);
    }
    putchar('\n');
    pthread_mutex_unlock(&lock);
}

void *thread_work(void *arg) {
    char* str = (char*)arg;
    long tid = (long)pthread_self();
    int is_reverse = (tid == t2);
    long self_counter = 0;

    int half_total = total / 2;

    for (int i = 0; i < half_total; ++i) {
        print_string(str, is_reverse, tid);
        self_counter++;
    }

    return (void *)self_counter;
}

int main(int argc, char *argv[]) {
    long t1_c = 0, t2_c = 0;

    if (argc < 3) {
        printf("There must be 2 arguments following the binary!\n");
        return 0;
    }

    total = atoi(argv[1]);
    pthread_mutex_init(&lock, NULL);
    
    char str[100] = "";
    for (int i = 2; i < argc; i++) {
        strcat(str, argv[i]);
        strcat(str, " ");  
    }

    pthread_create(&t1, NULL, thread_work, str);
    pthread_create(&t2, NULL, thread_work, str);
    pthread_join(t1, (void **)&t1_c);
    pthread_join(t2, (void **)&t2_c);
    
    printf("In main thread: T1 printed %ld times. T2 printed %ld times.\n", t1_c, t2_c);
    pthread_mutex_destroy(&lock);

    return 0;
}
