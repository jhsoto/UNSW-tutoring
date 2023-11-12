# Week 10 Summary
We've made it! The last week of 1521 :)  
This week we'll be scratching the surface of **threads** and **concurrency.**

This is very much an extension topic, so you only really have to worry about the topics this week if you are aiming for a really high mark!

## Concurrency and Parallelism
So far when writing code, we've been writing and running our code such that it executes neatly top to the bottom as a single unit.  
When we did MIPS we got to look at the individual instructions that the CPU would execute in order to run our programs.  
Importantly, we saw that **the CPU could only execute one instruction at a time,** and we assumed that our program would just run start to finish without stopping.

This has a pretty obvious issue though, if a computer can only do one thing at time, *how can our computer run multiple programs simultaneously?*  
There are two main approaches to addressing this problem: **concurrency and parallelism.**

### Concurrency
If we have multiple tasks we want our CPU to do be doing, one approach would be to **split up each task and swap between them.**  
This is **conurrency.**

The CPU is still only every executing one task at a time, it is just swapping between multiple regularly, so it *appears* that multiple tasks are running at once.

#### Swapping Tasks - Context Switch
In operating system terminology, the swap between tasks is called a **context switch.**  
The exact semantics of a context switch are beyond the scope of this course, so check out the operating systems course for more details :)

### Parallelism
Another approach is utilise **more CPUs to perform multiple tasks** (or even multiple parts of the same task!) **at the same time.**  
This is **parallelism.**

There is no swapping back and forth required this time, since there are multiple CPUs that can all execute instructions simultaneously.

### The Difference
Just to emphasise the difference here, **concurrency** is when *multiple tasks are swapped between on one CPU,* like Task 1 and Task 2 on the image below.  
**Parallelism** is when *multiples tasks are executed simulataneously on multiple CPUs,* like Task 1 and Task 3 on the image below.

![concurrency & parallelism](https://jenkov.com/images/java-concurrency/concurrency-vs-parallelism-3.png)
(credit: https://jenkov.com/images/java-concurrency/concurrency-vs-parallelism-3.png)

## Threads
**Threads** are a *unit of execution.*  
In more simple terms, a thread is a single task, executing instructions linearly from start to finish.

This might sound a bit like a *process,* but there is a slight difference.  
A process is actually **a collection of threads** that work together to run some program.  
Each process can have multiple *threads of execution,* or multiple subtasks which it swaps between.

Processes store some shared information that all threads need, like file descriptors and memory, but threads are **mostly independent.**  
Most importantly, **threads have their own set of registers.**

Creating and running threads forms the basis of both concurrency and parallelism.

### Using Threads in C
We can create a thread in C using the **`pthread_create()`** function.  
This function takes 4 arguments:

1) `pthread_t *thread`: A pointer to a **thread handle** that indentifies the thread we are going to create.  
`pthread_create()` will fill in this handle for us, like `stat` or `posix_spawn` with the process ID.  

2) `pthread_attr_t *attr`: Fancy configuration options, we just leave it as **NULL** usually.

3) `void *(*start_rountine) (void *)`: The **function our thread should run.**  
Once created, the thread will start execution from here.  
The type is scary, it is a function pointer after all. What you want to do is a pass the *name of a function* that has a signature like: `void *run_thread(void *data);`

4) `void *arg`: An **argument (must be pointer)** that is given to the function the thread runs.  
Can be left as **NULL** if you don't want to pass an argument.

Overall, a call to `pthread_create()` will look something like:
```
// The function our thread will execute
void *my_thread_function(void *data) {
    ...
}

int main(void) {
    ...
    // Thread handle
    pthread_t thread;
    // Thread creation
    pthread_create(&thread, NULL, my_thread_function, NULL);
    ...
}
```

> **NOTE:** When compiling programs that use threads, you **must include `-pthread` as a compile option!**  
> For example, if compiling `thread.c` (which uses threads) using `dcc`, you would type something like: `dcc -pthread thread.c -o thread`

#### Joining Threads
The last thing you need to do with threads is wait for them to finish, also called '**joining**' since the thread *rejoins the thread that originally made it.*  
If you don't wait for a thread to finish, **as soon as the program ends all threads stop too!**  
If your main thread relies on the other threads finishing first, make sure you wait for them.  
This is what you'll want to do 99% of the time you use threads.

The function for this is called `pthread_join()` and is quite simple.  
It takes a thread handle that `pthread_create()` made and a pointer to a place to put a return value or NULL if you don't want the return value.

A typical call will look something like this:
```
pthread_t thread;
// Create a thread and get the handle for it
pthread_create(&thread, ...);
...
// Wait for the thread to finish and ignore the return value
pthread_join(thread, NULL);
```

#### Argument Passing
A bit more on passing arguments to threads, because it is a little difficult.

The starting function for a thread (and pthread create) both take a **`void *`** argument.  
If you haven't come across this type before, it is called a **void pointer** and is a bit like a **generic pointer type.**  
C knows it is a pointer, but *doesn't know what type it points to.*  
If we try to *deference a void pointer,* C will complain because it assumes it points to nothing (void)!

What we can do is **type cast** the void pointer into another type of pointer, effectively *telling C what type the pointer actually points to.*  
For example, to cast `void *data` into an `int` pointer, we would write: `int *int_ptr = (int *)data;`  
Now we can deference our casted pointer and C will be happy :)

Continuing from the above example of calling `pthread_create()`, if we wanted to pass the number `10` as an argument, we would do this:
```
void *my_thread_function(void *data) {
    // We need to type cast the void pointer into an int pointer
    int *int_ptr = (int *)data;
    // Now we can dereference to get our data back!
    int thread_data = *int_ptr;

    // If we print thread_data it should be 10
    printf("%d", thread_data);

    ...
}

int main(void) {
    ...
    pthread_t thread;

    // The data we are passing to the thread
    int main_data = 10;
    // We give pthread_create() a pointer to our data
    pthread_create(&thread, NULL, my_thread_function, &main_data);
    ...
}
```

## Concurrency / Synchronisation Issuses
When we starting introducing threads and concurrent execution into our programs, we run into a whole category of new bugs which are really annoying to find and fix.  
Most of these issues have to do with **shared state** of some form, such as *a global variable* or *files* where multiple threads need to communicate or access the same data.  

Parts of a program which access this shared state are called **critical sections** and are the source of most concurrency bugs...

### Race Conditions
The most common concurrency bug is the **race condition,** where two threads try to access some shared data 'at the same time' (not literally the same time as we are only working with concurrency here).

For example, lets say we have two threads both trying to increment a global counter using the simple line of code: `global_counter++`  
What happens if two threads try to execute this line of code 'at the same time'?  
It might seem okay, since this is only one line of code, what could go wrong??

Remember that `global_coutner` is a *global variable.*  
If we go back to MIPS for a second, we would translate `global_counter++` like so:
```
lw      $t0, global_counter
addi    $t0, $t0, 1
sw      $t0, global_counter
```
Now we see that the simple increment code **actually takes three instructions to complete!**  
Let's say we have two threads who are both up to executing this increment, and they take turns running instructions.  
The flow of execution will look something like this:
```
Thread 1                        Thread 2
lw       $t0, global_counter                                    $t0 = 0
                                lw     $t0, global_counter      $t0 = 0
--> Both threads have just loaded the same value
addi    $t0, $t0, 1                                             $t0 = 1
                                addi    $t0, $t0, 1             $t0 = 1
sw      $t0, global_counter                                     global_counter = 1
                                sw      $t0, global_counter     global_counter = 1
--> Both threads just stored the same value!!
```
As we can see, what just happened is that *two threads tried to increment the counter,* **but the counter only increased by 1!**

There are two solutions to this problem we'll look at in this course...

#### Mutual Exclusion
**Mutual exclusion** involves putting a 'lock' around the critical sections of our code so that **only thread can execute the section at a time.**  
In the above example, it's a bit like putting our global variable in a safe and locking it, then only giving out the key to the safe to one thread at a time.  
If a second thread tries to unlock the safe while the first thread is still using the global variable, it won't be able to get the key and thus has to wait for the first thread to finish before it can use the global variable.

These locks and keys are often implemented by a **mutex.**  
You can create a mutex in C by creating a global variable of the type `pthread_mutex_t` and initialising it to the value `PTHREAD_MUTEX_INITIALIZER`.  
Then, you can call `pthread_mutex_lock` and `pthread_mutex_unlock` to 'lock' (get exclusive access) and 'unlock' (allow another thread to get exclusive access) the mutex.

For an example of this in action, check out the `bank_mutex.c` example.

#### Atomics
**Atomics** are a way to try to execute as many operations *atomically* as possible.  
To execute an operation 'atomically' (aka an *atomic operation*), it must **not be able to be broken down into smaller steps.**

As we saw, `global_counter++` is not atomic, but if we include `stdatomic.h` and make the global counter an `atomic_int` type instead of a regular `int`, the compiler will try everything it can **to make all operations on that variable atomic.**  
It won't always work, some operations simply can't be made atomic, but incrementing a global variable is an operation that it can make atomic!

If incrementing our counter is now atomic, that means there is **no possible race condition on it anymore** since it can't be interrupted part way though (the whole issue to begin with)!

Check out `bank_atomics.c` to see atomics in action :)

> **NOTE:** Sometimes, what operations are and aren't atomic are a bit strange...  
> For instance, although `global_counter++` and `global_counter += 1` are atomic, **`global_counter = global_counter + 1` is NOT atomic!**  
> In this case, this is because the first two methods of incrementing our counter are seen as exactly that, incrementing a variable.  
> The non-atomic version is seen as *loading a variable, incrementing it and storing the reuslt to a (potentially different!) variable,* which cannot be made atomic in all cases, so it ends up being non-atomic.  
> **Be very careful with atomics!!**

### Deadlocks
Deadlocks are an issue that can occur when using the mutex locks we introduced earlier.  
That's right the solution to one problem made more problems...

A **deadlock** occurs when **two threads get stuck waiting for each other to release a lock the other thread is holding onto.**  
It's probably easiest to see this in an example so here's a timeline for a deadlock:
```
First, what both threads are trying to do:
There are two global locks (mutexes): lock A and lock B
Thread 1        Thread 2
---------------------------
lock(A)         lock(B)
lock(B)         lock(A)
unlock(B)       unlock(A)
unlock(A)       unlock(B)


Now, a potential timeline of execution.
Both threads start from the first lock and take turns executing.

Thread 1                    Thread 2
-----------------------------------------------------
Acquires lock A
                            Acquires lock B
Tries to acquire lock B
Fails, waits for the lock
                            Tries to acquire lock A
                            Fails, waits for the lock
-> Both threads are now waiting for each other to release the locks!
```
To put it into words, thread 1 has lock A and is waiting for lock B.  
Thread 2 has lock B and is waiting for lock A.  
For thread 1 to progress, thread 2 need to release lock B.  
But for thread 2 to release lock B, it first needs thread 1 to release lock A.  
But for thread 1 to release lock A, it first needs thread 2 to release lock B...  
**Both threads are stuck waiting forever!**  
Thread 1 and thread 2 are in *deadlock.*

The solution to deadlock is really simple: **make sure all threads acquire all locks in the same order.**  
If every thread agrees to acquire lock A before lock B, there is no possible way for a thread to have lock B AND want lock A, preventing the circular waiting that created the deadlock.

To fix the above example, thread 2 should be changed to acquire the locks in the same order as thread 1:
```
Thread 1        Thread 2
---------------------------
lock(A)         lock(A)
lock(B)         lock(B)
unlock(B)       unlock(B)
unlock(A)       unlock(A)
```

## The End
And that's a wrap on COMP1521!  
Hope you all enjoyed at least one thing from this course and learnt something too :)  
I hope you enjoyed these summaries and the tutorials!

For a lot of you this will be the deepest into computers you dare venture, and that is perfectly okay, to all of you getting off the wild ride that is low-level computing at this point, I wish you the best of luck!  
Study hard, I know this is a tough course for many, but you'll make it through!!!

To those of you who haven't quite had their low-level fill yet, you may be asking...

## What Next?
Did you enjoy any specific parts of 1521?  
If so, I can suggest a few follow-up courses / electives that might interest you :)

### COMP3231 or COMP3891 - Operating Systems
If you enjoyed learning about **files, syscalls, concurrency/threads** or just miss seeing MIPS in lectures, **operating systems** is a great elective to look into.  
You go much deeper into how all the subsystems that make up an operating system work and even get to code up parts of an OS yourself!  

### COMP3222 & COMP3211 - Digital Circuits and Systems & Computer Architecture
If you enjoyed the topic on **bits** and/or want a deeper look at **how computer hardware works** after doing some MIPS, these are the courses for you!  
If you are an electrical engineering student you already have to do ELEC2141 which is an equivalent course to COMP3222.  
These courses look a lot at hardware - digital circuits - and how you can go from a simple switch (a transistor) to a CPU.  
If that sounds interesting to you, check them out!


# Goodbye :)