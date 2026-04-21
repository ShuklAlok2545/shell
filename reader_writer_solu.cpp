#include <iostream>
#include <thread>
#include <semaphore>
#include <unistd.h>


using namespace std;

// Binary semaphore (acts like mtx) for protecting readerCount
counting_semaphore<1> mtx(1);

// Semaphore for writers (ensures exclusive access)
counting_semaphore<1> writerSem(1);

int readerCount = 0;

void reader(int id) {
    while (true) {
        // Entry section
        mtx.acquire();
        readerCount++;
        if (readerCount == 1) {
            writerSem.acquire(); // First reader blocks writers
        }
        mtx.release();

        // Critical section (Reading)
        cout << "Reader " << id << " is reading..." << endl;
        sleep(1);

        // Exit section
        mtx.acquire();
        readerCount--;
        if (readerCount == 0) {
            writerSem.release(); // Last reader allows writers
        }
        mtx.release();

        sleep(1);
    }
}

void writer(int id) {
    while (true) {
        cout << "Writer " << id << " is waiting..." << endl;

        writerSem.acquire(); // Exclusive access

        // Critical section (Writing)
        cout << "Writer " << id << " is writing..." << endl;
        sleep(2);

        writerSem.release();

        sleep(1);
    }
}

int main() {
    thread readers[5];
    thread writers[2];

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        readers[i] = thread(reader, i + 1);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        writers[i] = thread(writer, i + 1);
    }

    // Join threads (runs infinitely)
    for (int i = 0; i < 5; i++) {
        readers[i].join();
    }

    for (int i = 0; i < 2; i++) {
        writers[i].join();
    }

    return 0;
}