#include<iostream>
#include<thread>
#include<semaphore>
#include<unistd.h>
using namespace std;

counting_semaphore<3> sem(3); // Initialize the semaphore with a count of 3 if count = 1, it will be a binary semaphore

void worker(int id) {
    cout << "Worker " << id << " is waiting to enter the critical section." << endl;
    sem.acquire(); // Wait (decrement the semaphore)
    cout << "Worker " << id << " has entered the critical section." << endl;
    sleep(2); // Simulate work by sleeping for 2 seconds
    cout << "Worker " << id << " is leaving the critical section." << endl;
    sem.release(); // Signal (increment the semaphore)
}

int main() {
    thread workers[10];
    
    // Create 10 worker threads
    for (int i = 0; i < 10; ++i) {
        workers[i] = thread(worker, i + 1);
    }
    
    // Wait for all worker threads to finish
    for (int i = 0; i < 10; ++i) {
        workers[i].join();
    }
    
    return 0;
}