// Increments the value of a global bank balance concurrently using threads

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdatomic.h>      // Need to include stdatomic.h for atomic types


// We make bank_balance an 'atomic int' so operations on it are atomic *where possible*
atomic_int bank_balance = 0;

// Deposit an amount provided in '*data' to the bank account $1 at a time
void *deposit(void *data) {
    // Get the amount to deposit from the argument
    int amount = *(int *) data;

    for (int i = 0; i < amount; i++) {
        // Sleep for 1 nanosecond - simulate transaction time
        nanosleep(&(struct timespec){.tv_nsec = 1}, NULL);

        // Now that bank balance is an atomic int, this occurs atomically for free
        bank_balance++;

        // NOTE: 'bank_balance = bank_balance + 1'  !!IS NOT ATOMIC!!
        // This is because this is interpreted as: 1) Get bank_balance, 2) Add 1, 3) Store in bank_balance
        // 'bank_balance++' and 'bank_balance += 1' are atomic as they are interpreted as: 1) Increment bank_balance by 1
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
}