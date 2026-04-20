#include<iostream>
#include<thread>
#include<unistd.h>
using namespace std;

// This program demonstrates concurrent execution of two tasks using threads in C++14.

void taskA(){// Simulate some work in task A
    for(int i=0;i<5;i++){
        std::cout<<"Task A is running..."<<std::endl;
        sleep(1);
    }
}

void taskB(){// Simulate some work in task B
    for(int i=0;i<5;i++){
        std::cout<<"Task B is running..."<<std::endl;
        sleep(1);
    }
}

int main(){
    thread threadA(taskA);
    thread threadB(taskB);

    threadA.join(); // Wait for threadA to finish
    threadB.join(); // Wait for threadB to finish

    cout<<"Both tasks completed."<<endl;
    return 0;
}