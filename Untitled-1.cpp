#include <iostream>
#include <map>
#include <vector>
using namespace std;

class QuickFitAllocator {
private:
    map<int, vector<int>> freeLists; // Free lists segregated by size

public:
    // Initialize free lists with predefined sizes
    QuickFitAllocator() {
        freeLists[2] = {};  // 2 MB blocks
        freeLists[4] = {};  // 4 MB blocks
        freeLists[8] = {};  // 8 MB blocks
    }

    // Add free blocks to a list
    void addFreeBlock(int blockSize, int count) {
        if (freeLists.find(blockSize) != freeLists.end()) {
            for (int i = 0; i < count; ++i) {
                freeLists[blockSize].push_back(blockSize); // Simulate memory blocks
            }
            cout << count << " blocks of size " << blockSize << " MB added to free list.\n";
        } else {
            cout << "Invalid block size: " << blockSize << " MB.\n";
        }
    }

    // Allocate a block of memory
    int allocate(int requestSize) {
        if (freeLists.find(requestSize) != freeLists.end() && !freeLists[requestSize].empty()) {
            int block = freeLists[requestSize].back(); // Allocate the last block
            freeLists[requestSize].pop_back();        // Remove it from the list
            cout << "Allocated block of size " << requestSize << " MB.\n";
            return block;
        } else {
            cout << "Allocation failed for size " << requestSize << " MB.\n";
            return -1; // Allocation failed
        }
    }

    // Deallocate a block of memory
    void deallocate(int blockSize) {
        if (freeLists.find(blockSize) != freeLists.end()) {
            freeLists[blockSize].push_back(blockSize); // Return the block to its free list
            cout << "Deallocated block of size " << blockSize << " MB.\n";
        } else {
            cout << "Invalid block size: " << blockSize << " MB.\n";
        }
    }

    // Display the free lists
    void displayFreeLists() {
        cout << "\nCurrent Free Lists:\n";
        for (const auto &entry : freeLists) {
            cout << "Size " << entry.first << " MB: " << entry.second.size() << " blocks available.\n";
        }
    }
};

int main() {
    QuickFitAllocator allocator;

    // Add three 2MB partitions
    allocator.addFreeBlock(2, 3);

    // Add three 4MB partitions
    allocator.addFreeBlock(4, 3);

    // Add three 8MB partitions
    allocator.addFreeBlock(8, 3);

    int choice, size;

    while (true) {
        cout << "\n1. Allocate Memory\n2. Deallocate Memory\n3. Display Free Lists\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter memory size to allocate (2, 4, or 8 MB): ";
            cin >> size;
            allocator.allocate(size);
            break;

        case 2:
            cout << "Enter memory size to deallocate (2, 4, or 8 MB): ";
            cin >> size;
            allocator.deallocate(size);
            break;

        case 3:
            allocator.displayFreeLists();
            break;

        case 4:
            cout << "Exiting...\n";
            return 0;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}