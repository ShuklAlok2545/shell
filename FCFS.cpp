#include<bits/stdc++.h>
using namespace std;

// This program implements the First-Come, First-Served (FCFS) scheduling algorithm.
struct Process {
    int id; // Process ID
    int arrivalTime; // Time at which the process arrives
    int burstTime; // Time required by the process to complete
};

int avgwaitingTime = 0;
void FCFS(vector<Process>& processes) {
    // Sort processes based on their arrival time
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int currentTime = 0; // Current time in the scheduling process
    cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;

    for (const auto& process : processes) {
        if (currentTime < process.arrivalTime) {
            currentTime = process.arrivalTime; // If the CPU is idle, move to the arrival time of the next process
        }
        int completionTime = currentTime + process.burstTime; // Calculate completion time
        int turnaroundTime = completionTime - process.arrivalTime; // Calculate turnaround time
        int waitingTime = turnaroundTime - process.burstTime; // Calculate waiting time
        avgwaitingTime += waitingTime; // Accumulate waiting time for average calculation


        cout << process.id << "\t\t" << process.arrivalTime << "\t\t" << process.burstTime << "\t\t" 
             << completionTime << "\t\t" << turnaroundTime << "\t\t" << waitingTime << endl;

        currentTime = completionTime; // Move to the next time slot after completing the current process
    }
}

int main() {
    int n; // Number of processes
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
        processes[i].id = i + 1; // Assign process ID
    }

    FCFS(processes); // Call the FCFS scheduling function
    cout << "Average Waiting Time: " << (double)avgwaitingTime / n << endl; // Calculate and display average waiting time

    return 0;
}