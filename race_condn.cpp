#include<iostream>
#include<thread>
#include<chrono>
#include<vector>
#include<algorithm>
using namespace std;

// This program demonstrates a race condition when multiple threads access and modify a shared variable without proper synchronization.

int sharedCounter = 0; // Shared variable that will be accessed by multiple threads
void incrementCounter() {
    for (int i = 0; i < 100000; i++) {
        sharedCounter++; // Increment the shared counter
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



//how this is happening:->

//Both threads are incrementing the sharedCounter variable simultaneously without any synchronization
// mechanism (like mutexes). This can lead to a race condition where both threads read the same value of sharedCounter, 
//increment it, and write it back, resulting in lost updates and an incorrect final value.
// The expected value is 200000 (100000 increments from each thread), but due to the race condition, the final value may
// be less than 200000, demonstrating the issue. 

// count = count + 1; is not an atomic operation. It involves reading the value of count, incrementing it, and writing it back.
// If two threads execute this operation simultaneously, they might both read the same value of count, increment it,
// and write it back, resulting in only one increment being recorded instead of two. This
//temp = count + 1; if context switch happens after this line, both threads will have the same value of temp, and when they write it back to count,
//count = temp;

