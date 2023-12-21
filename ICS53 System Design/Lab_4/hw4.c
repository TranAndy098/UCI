/*
 * Nicholas Pavini
 * 53254367
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// constants
#define HEAP_SIZE 127
#define MAX_LINE 1024

//function prototypes
void initializeHeap();
void mallocH(int);
int findFF(int);
int findBF(int);
void freeH(int);
void swap(int*, int*);
void parallelBubbleSort(int[], int[], int);
void blocklist();
void writemem(int, char*);
void printmem(int, int);

int firstFit = 1; // start off as firstfit
uint8_t heap[HEAP_SIZE]; // heap of 8 bits per entry since we are storing single chars or a header/footer

int main(int argc, char **argv) {
    initializeHeap();

    // set to bestFit is arg provided
    if (argc == 2 && strcmp(argv[1], "BestFit") == 0)
        firstFit = 0;

    // initialize space for commands
    char cmd[MAX_LINE];
    char *cmdBuff = cmd;

    // main loop
    int quitting = 0;
    do {
        printf(">");

        // get command and remove newline as needed
        size_t buffersize = MAX_LINE;
        size_t charsRead = getline(&cmdBuff, &buffersize, stdin);

        // if nothing read just redo the loop
        if (charsRead == 0 || (charsRead == 1 && cmd[0] == '\n'))
            continue;

        // make sure null is at the end
        if (cmd[charsRead-1] == '\n')
            cmd[charsRead-1] = '\0';

        // get operation
        char *op = strtok(cmd, " \t");

        // allocate block of memory
        if (strcmp(op, "malloc") == 0) {
            int size = atoi(strtok(NULL, " \t"));
            mallocH(size);
        }
        // free block of memory
        else if (strcmp(op, "free") == 0) {
            int index = atoi(strtok(NULL, " \t"));
            freeH(index);
        }
        // print information about all blocks in heap
        else if (strcmp(op, "blocklist") == 0) {
            blocklist();
        }
        // write string to memory
        else if (strcmp(op, "writemem") == 0) {
            int index = atoi(strtok(NULL, " \t"));
            char *str = strtok(NULL, " \t");
            writemem(index, str);
        }
        // print memory segment in decimal
        else if (strcmp(op, "printmem") == 0) {
            int index = atoi(strtok(NULL, " \t"));
            int size = atoi(strtok(NULL, " \t"));
            printmem(index, size);
        }
        else {
            quitting = 1;
        }

    } while (!quitting);

    return 0;
}

void initializeHeap() {
    heap[0] = HEAP_SIZE * 2; // 11111110 -> free block of size HEAP_SIZE including header and footer
    heap[HEAP_SIZE-1] = heap[0];

    for (int i = 1; i < HEAP_SIZE - 1; ++i)
        heap[i] = 0;
}

// loop through and find a block with enough space to allocate,, return its index
int findFF(int size) {
    int i = 0;
    while (i < HEAP_SIZE) {
        if (heap[i] % 2 == 0 && heap[i] / 2 - 2 >= size) {
            return i;
        }
        i += heap[i] / 2;
    }

    return -1;
}

// find smallest block with enough space
int findBF(int size) {
    int bestFit = -1;
    
    int i = 0;
    while (i < HEAP_SIZE) {
        if (heap[i] % 2 == 0 && heap[i] / 2 - 2 >= size) {
            if (bestFit == -1)
                bestFit = i;
            else
                bestFit = heap[i] / 2 < heap[bestFit] / 2 ? i : bestFit; // if the current space is smaller than the best fit, lets use i
        }
        i += heap[i] / 2;
    }

    return bestFit;
}

// find an appropriate block and allocate the space
void mallocH(int size) {
    int block = firstFit ? findFF(size) : findBF(size);

    if (block >= 0) {
        int blockSize = heap[block] / 2;

        // if the newly split block would only be 3 long including header/footer, we dont split
        if (blockSize - size - 2 < 3)
            size = blockSize - 2;

        heap[block] = (size + 2) * 2 + 1; // update header
        heap[block + size + 1] = heap[block]; // add/update footer

        // if there is a next block and we didnt perfectly fill, left create a new header, and update the footer of the block
        if (size != blockSize - 2) {
            heap[block + size + 2] = (blockSize - size - 2) * 2;
            heap[block + blockSize - 1] = heap[block + size + 2];
        }

        printf("%d\n", block+1);
    }
}

// set a block to unallocated
void freeH(int index) {
    --index; // set index to the header of the block
    int headerIndex, footerIndex;

    // if we are at the start of the heap or the prev block is not free, we keep the same header index, else we extend left to the free blocks header
    if (index == 0 || heap[index-1] % 2 == 1)
        headerIndex = index;
    else
        headerIndex = index - heap[index-1] / 2;

    // if we are on the last block of the heap or the next block is not free, we keep the same footer, else we extend right to the free blocks footer
    int nextBlock = index + heap[index] / 2;
    if (nextBlock == HEAP_SIZE || heap[nextBlock] % 2 == 1)
        footerIndex = index + heap[index] / 2 - 1;
    else
        footerIndex = index + heap[index] / 2 + heap[nextBlock] / 2 - 1;

    // set header and footer to be the correct size and unallocated
    heap[headerIndex] = (footerIndex - headerIndex + 1) * 2;
    heap[footerIndex] = heap[headerIndex];
}

// helper funtion since we swap 4 elements and want cleaner code
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// we will use this to sort by block size (descending order), and keep the block start indexes in the correct locations
void parallelBubbleSort(int arr1[], int arr2[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr1[j] < arr1[j + 1]) {
                swap(&arr1[j], &arr1[j + 1]);
                swap(&arr2[j], &arr2[j + 1]);
            }
        }
    }
}

void blocklist() {
    // start at first header and get total number of blocks
    int i = 0, numBlocks = 0;
    while (i < HEAP_SIZE) {
        ++numBlocks;
        i += heap[i] / 2;
    }

    // allocate arrays for block sizes and there start positions
    int blocks[numBlocks];
    int blockStarts[numBlocks];

    // get the block sizes and when they start
    i = 0;
    int currBlock = 0;
    while (currBlock < numBlocks) {
        blocks[currBlock] = heap[i] / 2;
        blockStarts[currBlock] = i;
        i += heap[i] / 2;
        ++currBlock;
    }

    // parallel sort the arrays and then print
    currBlock = 0;
    parallelBubbleSort(blocks, blockStarts, numBlocks);
    while (currBlock < numBlocks) {
        printf("%d-%d-%s\n", blocks[currBlock] - 2, blockStarts[currBlock] + 1, heap[blockStarts[currBlock]] % 2 == 0 ? "free" : "allocated");
        ++currBlock;
    }
}

// write some sequence of chars to an address
void writemem(int index, char *str) {
    while (*str != '\0') {
        heap[index] = *str;
        ++index; ++str;
    }
}

// print size chars starting at index
void printmem(int index, int size) {
    if (size > 0) {
        int i = index;
        while (i < index + size - 1) {
            printf("%d-", heap[i]);
            ++i;
        }
        printf("%d\n", heap[i]);
    }
}
