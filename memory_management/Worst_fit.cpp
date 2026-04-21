#include<iostream>
#include<vector>
using namespace std;

class WorstFit {
private:
    vector<int> memory;

public:
    WorstFit(int size) : memory(size, 0) {}

    bool allocate(int process_size) {
        int n = memory.size();

        int max_block_size = 0;
        int max_block_start = -1;

        int i = 0;
        while (i < n) {
            if (memory[i] == 0) {
                int start = i;
                int count = 0;

                while (i < n && memory[i] == 0) {
                    count++;
                    i++;
                }

                if (count > max_block_size) {
                    max_block_size = count;
                    max_block_start = start;
                }
            } else {
                i++;
            }
        }

        if (max_block_size >= process_size) {
            for (int j = 0; j < process_size; j++) {
                memory[max_block_start + j] = 1;
            }
            return true;
        }

        return false;
    }

    void deallocate(int start, int size) {
        for (int i = 0; i < size; i++) {
            memory[start + i] = 0;
        }
    }

    void display() {
        for (int x : memory) cout << x << " ";
        cout << endl;
    }
};

int main() {
    WorstFit mem(10);

    mem.allocate(3);
    mem.display();

    mem.allocate(2);
    mem.display();

    mem.deallocate(0,3);
    mem.display();

    mem.allocate(4); // goes to largest free block
    mem.display();

    return 0;
}