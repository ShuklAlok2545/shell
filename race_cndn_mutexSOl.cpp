//solution:->
// To fix the race condition, we can use a mutex to ensure that only one thread can access the sharedCounter variable at a time.
#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

mutex mtx; // Declare a mutex
int sharedCounter = 0; // Shared variable that will be accessed by multiple threads

void incrementCounter() {
    for (int i = 0; i < 100000; i++) {
        mtx.lock(); // Acquire the mutex
        sharedCounter++; // Increment the shared counter
        mtx.unlock(); // Release the mutex
    }
}

int main() {
    thread thread1(incrementCounter); // Create first thread to increment the counter
    thread thread2(incrementCounter); // Create second thread to increment the counter

    thread1.join(); // Wait for thread1 to finish
    thread2.join(); // Wait for thread2 to finish

    cout<<"Expected value of sharedCounter: 200000"<<endl; // Output the expected value of the shared counter
    cout << "Final value of sharedCounter: " << sharedCounter << endl; // Output the final value of the shared counter
    return 0;
}



//why not using just a bool variable to lock and unlock instead of mutex?
//achieving mutual exclusion using a simple bool variable can lead to several issues, such as busy waiting and race conditions
//progress of one thread can be interrupted by another thread before it can update the bool variable, leading to both threads
// thinking they have access to the critical section, which can cause unpredictable behavior and data corruption.
// Using a bool variable to implement locking can lead to issues such as busy waiting, where a thread continuously checks the 
//variable in a loop, consuming CPU resources unnecessarily.
// Additionally, without proper atomic operations, there can be race conditions when multiple threads try to access and modify
// the bool variable simultaneously, leading to unpredictable behavior.
// Mutexes provide a more robust and efficient way to handle synchronization between threads, ensuring that only one thread
// can access the critical section of code that modifies the shared variable at any given time, without the drawbacks associated with using a simple bool variable for locking.


//peterson's solution is a software-based solution to the critical section problem that uses two boolean variables 
//and a turn variable to ensure mutual exclusion between two threads. It allows both threads to access the critical
// section without busy waiting, and it guarantees that one thread will not starve the other. However, it is not suitable 
//for more than two threads and can be complex to implement correctly, which is why mutexes are generally preferred for 
//synchronization in modern programming.