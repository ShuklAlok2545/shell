#include<iostream>
#include<vector>
using namespace std;

class NextFit{
    private:
        vector<int> memory;
        int last_allocated_index;

    public:
        NextFit(int size) : memory(size, 0), last_allocated_index(0) {}

        bool allocate(int process_size) {
            int n = memory.size();
            int count = 0;
            for(int i = last_allocated_index; count < n; i = (i + 1) % n){
                if(memory[i] == 0) {
                    count++;
                    if(count == process_size) {
                        for(int j = 0; j < process_size; j++) {
                            memory[(i - j + n) % n] = 1; // Mark as allocated
                        }
                        last_allocated_index = (i + 1) % n; // Update last allocated index
                        return true;
                    }
                }
                else {
                    count = 0; // Reset count if we hit an allocated block
                }
            }
            return false; // Not enough space found
        }

        void deallocate(int start_index, int process_size) {
            for (int i = 0; i < process_size; i++) {
                memory[(start_index + i) % memory.size()] = 0; // Mark as free
            }
        }

        void display() {
            for (size_t i = 0; i < memory.size(); i++) {
                cout << memory[i] << " ";
            }
            cout << endl;
        }
};

int main() {
    NextFit memory_manager(10); // Create a memory manager with 10 units of memory

    memory_manager.allocate(3); // Allocate 3 units
    memory_manager.display(); // Display memory state

    memory_manager.allocate(4); // Allocate 4 units
    memory_manager.display(); // Display memory state

    memory_manager.deallocate(0, 3); // Deallocate the first 3 units
    memory_manager.display(); // Display memory state

    return 0;
}

// The Worst Fit memory management algorithm allocates the largest available block of memory to a process. This implementation 
//uses a vector to represent memory, where 0 indicates free memory and 1 indicates allocated memory. 
//The allocate function searches for the largest block of free memory that can accommodate the requested process size, 
//while the deallocate function frees the specified block of memory. The display function shows the current state of memory.