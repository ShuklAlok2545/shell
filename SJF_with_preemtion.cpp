#include<bits/stdc++.h>
using namespace std;

// This program implements the SJF-with-preemption scheduling algorithm.
struct Process {
    int id; // Process ID
    int arrivalTime; // Time at which the process arrives
    int burstTime; // Time required by the process to complete
    int remainingTime; // Time remaining for the process to complete
};

vector<int>completion_order; // Vector to store the order of process completion
int avgwaitingTime = 0; // Variable to accumulate total waiting time for average calculation
void SJF(vector<Process>& processes) {
    // Sort processes based on their arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int currentTime = 0; // Current time in the scheduling process
    cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;

    while (!processes.empty()) {
        int idx = -1; // Index of the process with the shortest remaining time
        for (size_t j = 0; j < processes.size(); j++) {
            if (processes[j].arrivalTime <= currentTime) { // Check if the process has arrived
                if (idx == -1 || processes[j].remainingTime < processes[idx].remainingTime) { // Find the process with the shortest remaining time
                    idx = j;
                }
            }
        }
        if (idx == -1) { // If no process has arrived, move to the next time unit
            currentTime++;
        } else {
            processes[idx].remainingTime--; // Decrease remaining time by 1 unit

            if (processes[idx].remainingTime == 0) { // If the process is completed
                completion_order.push_back(processes[idx].id); // Add process ID to completion order
                int completionTime = currentTime + 1; // Calculate completion time
                int turnaroundTime = completionTime - processes[idx].arrivalTime; // Calculate turnaround time
                int waitingTime = turnaroundTime - processes[idx].burstTime; // Calculate waiting time
                avgwaitingTime += waitingTime; // Accumulate waiting time for average calculation

                cout << processes[idx].id << "\t\t" << processes[idx].arrivalTime << "\t\t" << processes[idx].burstTime << "\t\t" 
                     << completionTime << "\t\t" << turnaroundTime << "\t\t" << waitingTime << endl;

                processes.erase(processes.begin() + idx); // Remove the completed process from the list
            }
            currentTime++; // Move to the next time unit after processing
        }
    }
}


int main() {
    int n; // Number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n); // Vector to store processes

    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].id = i + 1; // Assign process ID
        processes[i].remainingTime = processes[i].burstTime; // Initialize remaining time
    }
    SJF(processes); // Call the SJF function
    for(int id: completion_order){
        cout<<"Process "<<id<<" completed."<<endl;
    }
    
    cout << "Average Waiting Time: " << (double)avgwaitingTime / n << endl; // Calculate and display average waiting time
    return 0;
}

// This program implements the Shortest Job First (SJF) scheduling algorithm with preemption. It calculates the average 
//waiting time for a set of processes based on their arrival times and burst times. The program uses a vector to store the
//processes and sorts them based on their arrival times. It then simulates the scheduling process, updating the remaining  
//time for each process and calculating completion, turnaround, and waiting times accordingly. Finally, it displays the results 
//in a tabular format and calculates the average waiting time.