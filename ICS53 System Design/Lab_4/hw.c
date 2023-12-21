// Andy Quoc Anh Dinh Tran 57422363


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>


// functions
int find_best_fit(int block_size); // find best fitting block
int allocate(int header, int block_size); // using postion and block size will implement header and return address of first index 
void block_list(); // prints all blocks information
void free_block(int pointer); // free block
void coalesce_block(int header1, int header2); // coalesced blocks
void truncate_block(int pointer, int old_size, int new_size);
void get_more_block(int pointer, int old_size, int new_size);
void get_new_block(int pointer, int old_size, int new_size);
void write_to_mem(int pointer, char *word);
void print_mem(int pointer, int amount);
void print_dec_to_hex(int decimal);
bool allocation_check(int pointer, int size);
bool pointer_check(int pointer);
void print_test();


// variables
char input[100]; // instantiate input string
int heap[127]; // heap with 127 addresses
int heap_size = 127;
int bits = 8;
char hex[16] = "0123456789ABCDEF";


int main(int argc, char const *argv[])
{   
    heap[0] = 254; // decimal representation of 11111100 -> 1111110 and 0 -> size 1111110 (126) and 0 (freed)

    for (int i = 1; i < heap_size; i++) 
    {
        heap[i] = 0;
    }

    char *token; // to handle requests
    bool quit = false; // to keep shell running until quit is inputted
    char whitespace[100];
    int block_size = 0;
    int block_pointer = -1;
    int best_free_block = -1;
    int amount = 0;

    // while loop runs until "quit" is the input
    while (!quit) 
    {
        // testing to see the layout of the heap and its details
        // print_test();
        
        // get input, strip ending newline from terminal and then get first token of input while spliting at spaces
        // get input, strip ending newline from terminal and then get first token of input while spliting at spaces
        printf(">");
        fgets(input, 100, stdin);
        strcpy(whitespace, input);
        best_free_block = -1;
        block_pointer = -1;
        amount = 0;

        // if input is empty, ask for input again
        if (strcmp(input, "\n")==0) 
        { 
            // printf("empty command\n"); 
            continue;
        }

        token = strtok(whitespace, "     ");
        if (strcmp(token, "\n")==0) 
        { 
            // printf("empty command\n"); 
            continue;
        }

        // start to split up input into components
        token = strtok(input, "\n");
        token = strtok(token, "     ");

        // changing working directory
        if (strcmp(token, "quit")==0) 
        {
            quit = true;
        }

        else if (strcmp(token, "malloc")==0) 
        {
            token = strtok(NULL, "     ");
            block_size = atoi(token) + 1;
            best_free_block = find_best_fit(block_size);
            
            if (block_size <= 0) {
                // printf("Size is not valid\n");
            }
            else if (best_free_block == -1) {
                // printf("Size is too large for a single block\n");
            }
            else {
                int new_pointer = allocate(best_free_block, block_size);
                if (new_pointer != -1) {
                    printf("%d\n", new_pointer);
                }
            }
    
        }

        else if (strcmp(token, "free")==0) 
        {
            token = strtok(NULL, "     ");
            block_pointer = atoi(token);
            
            if (pointer_check(block_pointer)) {
                free_block(block_pointer);
            }
            else {
                // printf("Pointer is not to start of block\n");
            }
        }

        else if (strcmp(token, "realloc")==0) 
        {
            token = strtok(NULL, "     ");
            block_pointer = atoi(token);

            if (pointer_check(block_pointer)) {
                
                token = strtok(NULL, "     ");
                block_size = atoi(token) + 1;
                int old_size = heap[block_pointer-1] / 2;
                int allocated = heap[block_pointer-1] % 2;
                
                if (!allocated) {
                    // printf("Reallocating freed block has undefined behavior\n");
                }
                else if (block_size <= 1) {
                    // printf("Size is not valid\n");
                }
                else if (block_size < old_size-1) {
                    truncate_block(block_pointer, old_size, block_size);
                    printf("%d\n", block_pointer);
                }
                else if ((block_size > old_size) || (block_size == old_size-1)) {
                    int curr_header = block_pointer - 1;
                    int next_header = curr_header + old_size;
                    int allocated = heap[next_header] % 2;
                    int next_size = heap[next_header] / 2;
                    int diff = block_size - old_size;

                    if ((!allocated) && ((next_size > diff+1) || (next_size == diff))) {
                        get_more_block(block_pointer, old_size, block_size);
                        printf("%d\n", block_pointer);
                    }
                    else {
                        get_new_block(block_pointer, old_size, block_size);
                    }
                }
                else {
                    // printf("Size is the same no change was made\n");
                }
            }
            else {
                // printf("Pointer is not to start of block\n");
            }

        }

        else if (strcmp(token, "writemem")==0)
        {
            token = strtok(NULL, "     ");
            block_pointer = atoi(token);
            token = strtok(NULL, "     ");
            amount = 0;

            while (token[amount] != '\0') {
                amount++;
            }

            /*
            if (allocation_check(block_pointer, amount)) {
                
                write_to_mem(block_pointer, token);
            }
            else {
                printf("Pointer and size is not allocated so no write\n");
            }
            */

            // if uncomment above, comment out below
            write_to_mem(block_pointer, token);
        }

        else if (strcmp(token, "printmem")==0)
        {
            token = strtok(NULL, "     ");
            block_pointer = atoi(token);
            token = strtok(NULL, "     ");
            amount = atoi(token);

            /*
            if (allocation_check(block_pointer, amount)) {
                
                print_mem(block_pointer, amount);
            }
            else {
                printf("Pointer and its amount is not allocated so no print\n");
            }
            */

            // if uncomment above, comment out below
            print_mem(block_pointer, amount);
        }

        else if (strcmp(token, "blocklist")==0)
        {
            block_list();
        }

        else {
            // printf("Invalid Command\n");
        }
    }
    return 0;
}


// using the size will find the header of the best fit free block
int find_best_fit(int block_size) 
{
    int best_fit = -1;
    int best_diff = 126;
    int curr_header = 0;
    int curr_diff = 0;
    int allocated;
    int curr_size;

    while (curr_header < 127) 
    {
        allocated = heap[curr_header] % 2; // allocation status is last bit
        curr_size = heap[curr_header] / 2; // size is first 7 bits

        if ((!allocated) && ((block_size <= curr_size-2) || (block_size == curr_size))) { // if block is free and big enough
            curr_diff = curr_size - block_size;
            if (curr_diff < best_diff) { // if better fit then save it
                best_diff = curr_diff;
                best_fit = curr_header;
            }
        }
        curr_header += curr_size;
    }
    return best_fit;
}


// using header and block, intialize block and change information in header
int allocate(int header, int block_size)
{
    int old_size = heap[header] / 2; // gathers old size of free space
    heap[header] = (block_size * 2) + 1; // changes header to hold current block size and allocated
        int pointer = header + 1; // pointer to first address

        // for (int i = 1; i < block_size; i++) {
        //     heap[header + i] = 0;
        // }

        if (old_size > block_size) {
            int next_header = block_size + header; // next header is the amount of free space used plus 1 for new header
            int diff = old_size - block_size;
            heap[next_header] = diff * 2; // new header updated with new free space
            coalesce_block(next_header, next_header+diff); // coalesce just freed block with the next one if possible
        }
        return pointer;
}


// print block information
void block_list()
{
    int curr_header = 0;
    int allocated;
    int curr_size;

    while (curr_header < 126) 
    {
        allocated = heap[curr_header] % 2; // allocation status is last bit
        curr_size = heap[curr_header] / 2; // size is first 7 bits

        if (allocated) {
            printf("%d, %d, allocated\n", curr_header + 1, curr_size-1);
        }
        else {
            printf("%d, %d, free\n", curr_header + 1, curr_size-1);
        }
        
        if (curr_size == 0) {
            curr_header += 1;
        }else {
            curr_header += curr_size;
        }
    }
}


// using pointer will free the block
void free_block(int pointer)
{
    int header = pointer - 1; // header is right before pointer
    int allocated = heap[header] % 2; // allocation status is last bit

    if (allocated) {
        int curr_size = heap[header] / 2; // size is first 7 bits
        
        // for (int i = 0; i < curr_size; i++) {
        //     heap[header + i] = 0; // emptying addresses
        // }

        int next_header = header + curr_size; // next header after the freed one
        heap[header] = curr_size * 2; // storing size of block
        coalesce_block(header, next_header); // coalesce just freed block with the next one if possible
    }
    else {
        // printf("Already Freed\n");
    }
}


// takes two headers and if they both free will combine
void coalesce_block(int header1, int header2) // headers
{
    if (header2 < 127) {
        int curr_size1 = heap[header1] / 2; // get size of recently freed block
        int allocated2 = heap[header2] % 2; // get allocation status 
        int curr_size2 = heap[header2] / 2; // get size of second block

        if (!allocated2) {
            heap[header2] = 0; // the second header is no longer needed and now an empty address
            heap[header1] = (curr_size1 + curr_size2) * 2; // the front header will have the total size of the two free blocks + old header address
            int next_header = header1 + (heap[header1]/2);
            coalesce_block(header1,next_header);
        }
    }
}


// the block is getting smaller so needs to split
void truncate_block(int pointer, int old_size, int new_size)
{

    int header = pointer - 1;

    // for (int i = new_size; i < old_size; i ++){// freeing the truncated blocks
    //     heap[header + i] = 0;
    // }
    
    heap[header] = (new_size * 2) + 1; // change current header to have new size
    int next_header = header + old_size; // next header before this one split
    int second_size = old_size - new_size; // size of second block created, -1 for header
    heap[header + new_size] = second_size * 2; // changing header of split with size
    coalesce_block(header + new_size, next_header); // coalesce of newly freed block and the one after
}


// the next block is free so will use its space
void get_more_block(int pointer, int old_size, int new_size)
{
    int curr_header = pointer -1;
    int next_header = curr_header + old_size; // get the next header's information
    int diff = new_size - old_size; // get the amount of space needed
    int next_size = heap[next_header] / 2;

    // if the next block size + 1 (for header) is equal amount needed then can just use the next block
    if (next_size == diff) {
        heap[curr_header] = (new_size * 2) + 1; // changing header details with new size
        
        // for (int i = old_size; i < new_size; i++) { // initialize the new space
        //     heap[curr_header + i] = 0;
        // }
    }
    // else will use only use a part of it 
    else {
        next_header += diff; // next header will shift over the difference of sizes
        next_size -= diff; // the next block size will reduce
        
        // for (int i = old_size; i < new_size; i++) { // initialize the new space
        //     heap[curr_header + i] = 0;
        // }
        heap[curr_header] = (new_size * 2) + 1; // changing header details with new size
        heap[next_header] = next_size * 2;
        coalesce_block(next_header, next_header + next_size); // coalesce just in case
    }
}


// the next block is allocated so must find best fit freed block
void get_new_block(int pointer, int old_size, int new_size) 
{
    int new_header = find_best_fit(new_size); // using the new size, will find the header 

    if (new_header == -1) {
        //printf("No block big enough for %d\n", new_size);
    }
    else {
        int new_pointer = allocate(new_header, new_size); // allocate the new block for this old block
        printf("%d\n", new_pointer);
        int small_size = 0;
        if (old_size < new_size) {
            small_size = old_size;
        }
        else {
            small_size = new_size;
        }
        for (int i = 0; i < small_size-1; i++) { // move data from old block to new block
            heap[new_pointer+i] = heap[pointer+i];
        }
        free_block(pointer); // free old block
    }
}


// will write character at a time into heap starting at pointer
void write_to_mem(int pointer, char *word)
{
    int i = 0;
    int j = 0;

    while (word[i] != '\0') {
        j = (int) word[i];
        j = j % 256; // represents only taking least significant 8 bits
        heap[pointer + i] = j;
        i++;
    }
}


// starting at pointer, will print amount of data as hexadecimal
void print_mem(int pointer, int amount) 
{
    for (int i = 0; i < amount; i++) {
        print_dec_to_hex(heap[pointer+i]);
        printf(" ");
    }
    printf("\n");
}


// recursive function to print decimal as hexadecimal
void print_dec_to_hex(int decimal)
{
    int remainder = decimal % 16;
    int div = decimal / 16;

    if (div > 0) {
        print_dec_to_hex(div);
    }
    printf("%c", hex[remainder]);
}


// checks if pointer is allocated and if size is within bounds starting at pointer, but currently not used
bool allocation_check(int pointer, int size) 
{
    int curr_header = 0;
    int next_header = 0;
    int allocated;
    int curr_size;

    while (curr_header < 127) 
    {
        allocated = heap[curr_header] % 2; // allocation status is last bit
        curr_size = heap[curr_header] / 2; // size is first 7 bits
        next_header = curr_header + curr_size;

        if (pointer < next_header) {
            if (pointer == curr_header) {
                return false;
            }
            else if (curr_header + size > next_header) {
                return false;
            }
            else if (allocated) {
                return true;
            } 
            else {
                return false;
            }
        }
        curr_header = next_header;
    }
    return false;
}


// checks if pointer is the first address of block
bool pointer_check(int pointer)
{
    int curr_header = 0;
    int next_header = 0;
    int curr_size;

    while (curr_header < 127) 
    {
        curr_size = heap[curr_header] / 2; // size is first 7 bits
        next_header = curr_header + curr_size;

        if (pointer < next_header) {
            if (pointer == curr_header + 1) {
                return true;
            }
            return false;
        }
        curr_header = next_header;
    }
    return false;
}


// prints out heap and its details and data
void print_test()
{
    printf("__________HEAP__________\n");
    int curr_header = 0;
    int allocated;
    int curr_size;

    while (curr_header < 127) 
    {
        allocated = heap[curr_header] % 2; // allocation status is last bit
        curr_size = heap[curr_header] / 2; // size is first 7 bits
        printf("Header at address %d with size %d ", curr_header, curr_size);
        
        if (allocated) {
            printf("allocated consisting of:\n");
        }
        else {
            printf("freed consisting of:\n");
        }

        for (int i = 0; i < curr_size; i++) {
            printf("%d ", heap[curr_header+i]);
            if (i % 8 == 7) {
                printf("\n");
            }
        }
        curr_header += curr_size;
        printf("\n");
    }
    printf("________________________\n");
}

