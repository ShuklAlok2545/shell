#include<bits/stdc++.h>
using namespace std;

// structure to represent a process in the Shortest Job First (SJF) scheduling algorithm
struct Process {
    int id; // Process ID
    int arrivalTime; // Time at which the process arrives
    int burstTime; // Time required by the process to complete
};

int avgwaitingTime = 0; // Variable to accumulate total waiting time for average calculation

void SJF(vector<Process>& processes) {
    // Sort processes based on their arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });
    int currentTime = 0; // Current time in the scheduling process
    cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl; 
    for (size_t i = 0; i < processes.size(); i++) {
        int idx = -1; // Index of the process with the shortest burst time
        for (size_t j = 0; j < processes.size(); j++) {
            if (processes[j].arrivalTime <= currentTime) { // Check if the process has arrived
                if (idx == -1 || processes[j].burstTime < processes[idx].burstTime) { // Find the process with the shortest burst time
                    idx = j;
                }
            }
        }
        if (idx == -1) { // If no process has arrived, move to the next time unit
            currentTime++;
        } else {
            int completionTime = currentTime + processes[idx].burstTime; // Calculate completion time
            int turnaroundTime = completionTime - processes[idx].arrivalTime; // Calculate turnaround time
            int waitingTime = turnaroundTime - processes[idx].burstTime; // Calculate waiting time
            avgwaitingTime += waitingTime; // Accumulate waiting time for average calculation

            cout << processes[idx].id << "\t\t" << processes[idx].arrivalTime << "\t\t" << processes[idx].burstTime << "\t\t" 
                 << completionTime << "\t\t" << turnaroundTime << "\t\t" << waitingTime << endl;

            currentTime = completionTime; // Move to the next time slot after completing the current process
            processes.erase(processes.begin() + idx); // Remove the completed process from the list
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
    }

    SJF(processes); // Call the SJF function

    cout << "Average Waiting Time: " << (double)avgwaitingTime / n << endl; // Calculate and display average waiting time

    return 0;
}

//summary 
// This program implements the Shortest Job First (SJF) scheduling algorithm. It defines a Process structure to
// represent each process with its ID, arrival time, and burst time. The SJF function sorts the processes based on their arrival time
//and then selects the process with the shortest burst time that has arrived at the current time. It calculates the completion time,
// turnaround time, and waiting time for each process and accumulates the total waiting time to compute the average waiting time at
// the end. The main function prompts the user to input the number of processes and their respective arrival and burst times before calling the SJF function.