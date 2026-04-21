#include<iostream>
using namespace std;
#define MAX 100

class FirstFit {
    int memory[MAX];
    int size;
public:
    FirstFit(int s) : size(s) {
        for (int i = 0; i < size; i++) {
            memory[i] = 0; // Initialize memory to 0 (free)
        }
    }   
    
    void allocate(int processSize) {
        for (int i = 0; i < size; i++) {
            if (memory[i] == 0) { // Check for free memory
                int j;
                for (j = i; j < i + processSize && j < size; j++) {
                    if (memory[j] != 0) { // Not enough space
                        break;
                    }
                }
                if (j == i + processSize) { // Found a suitable block
                    for (int k = i; k < j; k++) {
                        memory[k] = 1; // Mark memory as allocated
                    }
                    cout << "Allocated " << processSize << " units of memory." << endl;
                    return;
                }
            }
        }
        cout << "Not enough memory to allocate " << processSize << " units." << endl;
    }
    void deallocate(int start, int processSize) {
        for (int i = start; i < start + processSize && i < size; i++) {
            memory[i] = 0; // Mark memory as free
        }
        cout << "Deallocated " << processSize << " units of memory starting from index " << start << "." << endl;
    }
    void display() {
        cout << "Memory: ";
        for (int i = 0; i < size; i++) {        
            cout << memory[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    FirstFit ff(20); // Create a memory of size 20
    ff.display();
    
    ff.allocate(5); // Allocate 5 units of memory
    ff.display();
    
    ff.allocate(3); // Allocate 3 units of memory
    ff.display();
    
    ff.deallocate(0, 5); // Deallocate the first 5 units of memory
    ff.display();
    
    ff.allocate(4); // Allocate 4 units of memory
    ff.display();
    
    return 0;
}