// Increments the value of a global bank balance concurrently using threads

#include <stdio.h>
#include <pthread.h>
#include <time.h>

int bank_balance = 0;

// Deposit an amount provided in '*data' to the bank account $1 at a time
void *deposit(void *data) {
    // Arguments are passed to thread functions as pointers.
    // It is a 'void *' because we want to be able to pass any type.
    //      - A void pointer is a generic pointer, it can point to any type.

    // We have to type cast data before we can dereference it.
    // Without a cast, C has no idea what type 'data' points to so assumes it is 'void' (no type)
    // Effectively '(int *) data' means treat data like it points to an integer. Then we can dereference as normal.
    int amount = *(int *) data;

    for (int i = 0; i < amount; i++) {
        // Sleep for 1 nanosecond - simulate transaction time
        nanosleep(&(struct timespec){.tv_nsec = 1}, NULL);

        // Increment bank balance
        bank_balance++;
        // !!THIS IS NOT ATOMIC!!
        // Breaking this down into assembly:
        //  lw      $t0, bank_balance
        //  addi    $t0, $t0, 1
        //  sw      $t0, bank_balance
        // Notice that this takes 3 instructions to complete!
        //
        // Say we have two threads reach this at the same time, taking turns executing instructions:
        // Thread 1                         Thread 2
        //  lw       $t0, bank_balance                                      $t0 = 0
        //                                   lw     $t0, bank_balance       $t0 = 0
        // --> Both threads have just loaded the same value
        //  addi    $t0, $t0, 1                                             $t0 = 1
        //                                   addi    $t0, $t0, 1            $t0 = 1
        //  sw      $t0, bank_balance
        //                                   sw      $t0, bank_balance
        // --> Both threads have just stored the same value - we lost an increment!
        //
        // This is what we call a 'race condition', where two threads 'race' to access one shared variable.
    }

    // Ususally we return NULL from a thread function.
    // We can however return something in a similar way to how we pass arguments to threads - pointers.
    // We can return a pointer to some return value for the thread, although this is rarely used.
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