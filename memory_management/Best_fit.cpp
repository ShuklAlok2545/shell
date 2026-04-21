#include<iostream>
#include<vector>
using namespace std;    

class BestFit {
    private:
        vector<int> memory;

    public:
        BestFit(int size) : memory(size, 0) {}

        bool allocate(int process_size) {
            int best_index = -1;
            int best_size = INT_MAX;

            for (size_t i = 0; i < memory.size(); i++) {
                if(memory[i] == 0)
                {
                    int j = i;
                    while(j < memory.size() && memory[j] == 0)
                    {
                        j++;
                    }
                    int block_size = j - i;
                    if(block_size >= process_size && block_size < best_size) {
                        best_index = i;
                        best_size = block_size;
                    }
                    i = j; // Skip to the end of the current block
                }
            }

            if (best_index != -1) {
                for (int k = best_index; k < best_index + process_size; k++) {
                    memory[k] = 1; // Mark as allocated
                }
                return true;
            }
            return false; // Not enough space found
        }

        void deallocate(int start_index, int process_size) {
            for (int i = 0; i < process_size; i++) {
                memory[start_index + i] = 0; // Mark as free
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
    BestFit memory_manager(10); // Create a memory manager with 10 units of memory

    memory_manager.allocate(3); // Allocate 3 units
    memory_manager.display(); // Display memory state

    memory_manager.allocate(4); // Allocate 4 units
    memory_manager.display(); // Display memory state

    memory_manager.deallocate(0, 3); // Deallocate the first 3 units
    memory_manager.display(); // Display memory state

    return 0;
}