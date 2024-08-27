#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Two mutexes
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* thread1_func(void* arg) {
    // Lock the mutexes in a consistent order (e.g., mutex1 first, then mutex2)
    pthread_mutex_lock(&mutex1);
    printf("Thread 1: locked mutex1\n");

    // Simulate some work
    sleep(1);

    pthread_mutex_lock(&mutex2);
    printf("Thread 1: locked mutex2\n");

    // Critical section (work with both mutexes locked)
    printf("Thread 1: working in critical section\n");

    // Unlock both mutexes
    pthread_mutex_unlock(&mutex2);
    printf("Thread 1: unlocked mutex2\n");
    pthread_mutex_unlock(&mutex1);
    printf("Thread 1: unlocked mutex1\n");

    return NULL;
}

void* thread2_func(void* arg) {
    // Lock the mutexes in the same order (mutex1 first, then mutex2)
    pthread_mutex_lock(&mutex2);
    printf("Thread 2: locked mutex2\n");

    // Simulate some work
    sleep(1);

    pthread_mutex_lock(&mutex1);
    printf("Thread 2: locked mutex1\n");

    // Critical section (work with both mutexes locked)
    printf("Thread 2: working in critical section\n");

    // Unlock both mutexes
    pthread_mutex_unlock(&mutex1);
    printf("Thread 2: unlocked mutex1\n");
    pthread_mutex_unlock(&mutex2);
    printf("Thread 2: unlocked mutex2\n");

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Create two threads
    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
