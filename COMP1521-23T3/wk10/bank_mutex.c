// Increments the value of a global bank balance concurrently using threads

#include <stdio.h>
#include <pthread.h>
#include <time.h>

int bank_balance = 0;

// This is a mutex - a global lock on certain data structures / code segments.
// The point of a mutex to prevent concurrency issues with multiple threads messing with each other.
pthread_mutex_t bank_mutex = PTHREAD_MUTEX_INITIALIZER;

// Deposit an amount provided in '*data' to the bank account $1 at a time
void *deposit(void *data) {
    // Get the amount to deposit from the argument
    int amount = *(int *) data;

    for (int i = 0; i < amount; i++) {
        // Sleep for 1 nanosecond - simulate transaction time
        nanosleep(&(struct timespec){.tv_nsec = 1}, NULL);

        // Get exclusive access to the bank balance by locking the global mutex.
        // Only one thread can hold this lock at a time, so only one thread can execute the following code.
        pthread_mutex_lock(&bank_mutex);

        ////////////////////////////////////////////////////////////////////////////////////////////////
        // This is what we call a critical section - only one thread should be here at a time

        // Increment bank balance
        bank_balance++;

        // End of critical section
        ////////////////////////////////////////////////////////////////////////////////////////////////

        // Release exclusive access to the bank balance by unlocking the global mutex.
        // Once we have unlocked the mutex, another thread can take it and execute the previous code.
        pthread_mutex_unlock(&bank_mutex);
    }

    return NULL;
}


int main(void) {
    // Create a thread to deposit $5000 into the bank account
    pthread_t thread1;
    int amount1 = 5000;
    pthread_create(&thread1, NULL, deposit, &amount1);

    // Create a thread to deposit $10000 into the bank account
    pthread_t thread2;
    int amount2 = 10000;
    pthread_create(&thread2, NULL, deposit, &amount2);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Should print $15000
    printf("Final bank balance: $%d\n", bank_balance);
    
    return 0;
}