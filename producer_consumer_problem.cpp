#include<iostream>
#include<thread>
#include<semaphore>
#include<unistd.h>
using namespace std;


//solution to producer consumer problem using counting semaphore in c++14
// Define a counting semaphore with a maximum count of 5
counting_semaphore<5> sem(5); // Initialize the semaphore with a count of 5

void producer(int id) {
    while (true) {
        cout << "Producer " << id << " is producing an item." << endl<<endl;
        sleep(1); // Simulate time taken to produce an item
        sem.release(); // Signal that an item has been produced
        cout << "Producer " << id << " has produced an item." << endl<<endl;
    }
}

void consumer(int id) {
    while (true) {
        cout << "Consumer " << id << " is waiting to consume an item." << endl<<endl;
        sem.acquire(); // Wait for an item to be produced
        cout << "Consumer " << id << " has consumed an item." << endl<<endl;
        sleep(1); // Simulate time taken to consume an item
    }
}


int main() {
    thread producers[3];
    thread consumers[3];
    
    // Create 3 producer threads
    for (int i = 0; i < 3; ++i) {
        producers[i] = thread(producer, i + 1);
    }
    
    // Create 3 consumer threads
    for (int i = 0; i < 3; ++i) {
        consumers[i] = thread(consumer, i + 1);
    }
    
    // Wait for all producer threads to finish (in this case, they run indefinitely)
    for (int i = 0; i < 3; ++i) {
        producers[i].join();
    }
    
    // Wait for all consumer threads to finish (in this case, they run indefinitely)
    for (int i = 0; i < 3; ++i) {
        consumers[i].join();
    }
    
    return 0;
}