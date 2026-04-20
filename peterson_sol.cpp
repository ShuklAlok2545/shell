#include <iostream>
#include <thread>
using namespace std;

// Peterson's solution for two threads

volatile bool flag[2] = {false, false}; // Flags to indicate if a thread
int turn; // Variable to indicate which thread's turn it is

void peterson(int threadID) {
    int other = 1 - threadID; // Get the ID of the other thread
    flag[threadID] = true; // Indicate that this thread wants to enter the critical section
    turn = other; // Set the turn to the other thread

    // Wait until the other thread is not interested or it's this thread's turn
    while (flag[other] && turn == other) {
        // Busy wait
    }

    // Critical section
    cout << "Thread " << threadID << " is in the critical section." << endl;

    flag[threadID] = false; // Indicate that this thread is leaving the critical section
}

int main() {
    thread t1(peterson, 0); // Create first thread
    thread t2(peterson, 1); // Create second thread

    t1.join(); // Wait for thread 1 to finish
    t2.join(); // Wait for thread 2 to finish

    return 0;
}