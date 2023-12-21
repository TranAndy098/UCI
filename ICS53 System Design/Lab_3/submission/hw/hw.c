#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>
#include <fcntl.h>

#include <stdbool.h>

void read_memory(int page_number, int offset);
bool page_fault(int page_number);
void virtual_to_main(int page_number, int main_place);
int main_replacement();
void update_usage(int page_number);
int replace_check(int page_number);
void not_in_main(int page_number);
void main_to_virtual(int page_number, int main_place);
void write_memory(int page_number, int offset, int value);
void new_usage(int page_number);


const int vm_size = 128;
const int vm_pages = 16;
const int mm_size = 32;
const int mm_pages = 4;
const int pg_table_size = 16;
const int page_size = 8;

struct page {
    int valid_bit;
    int dirty_bit;
    int page_number;
    int main_placement;
};

typedef struct page page;

page page_table[16];
int main_memory[32];
int main_memory_table[4];
int main_memory_usage[4];
int virtual_memory[128];



bool lru = false;


char input[100]; // instantiate input string

int main(int argc, char const *argv[])
{   

    if (argc > 1) {
        if (strcmp(argv[1], "LRU")==0) {
            // printf("Is doing LRU\n");
            lru = true;
        }
        else if (strcmp(argv[1], "FIFO")==0) {
            // printf("Is doing FIFO\n");
        }
    }
    else {
        // printf("Defaulting to FIFO\n");
    }

    // initalize all memory locations to -1
    for (int i = 0; i < vm_size; i++){
        virtual_memory[i] = -1;
    }

    for (int i = 0; i < mm_size; i++){
        main_memory[i] = -1;
    }

    for (int i = 0; i < mm_pages; i++){
        main_memory_table[i] = -1;
    }

    for (int i = 0; i < mm_pages; i++){
        main_memory_usage[i] = -1;
    }

    //initalize all valid bits to 0
    for (int i = 0; i < pg_table_size; i++){
        page_table[i].valid_bit = 0;
        page_table[i].dirty_bit = 0;
        page_table[i].page_number = i;
        page_table[i].main_placement = i;
    }


    char *token; // to handle requests
    bool quit = false; // to keep shell running until quit is inputted
    char whitespace[100];

    int addr = -1;
    int page_number = -1;
    int offset = -1;
    int value = -1;


    // while loop runs until "quit" is the input
    while (!quit) 
    {
        // get input, strip ending newline from terminal and then get first token of input while spliting at spaces
        // get input, strip ending newline from terminal and then get first token of input while spliting at spaces
        printf("> ");
        fgets(input, 100, stdin);
        strcpy(whitespace, input);

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
        else if (strcmp(token, "showmain")==0) 
        {
            token = strtok(NULL, "     ");
            page_number = atoi(token);
            
            if ((-1 < page_number) && (page_number <= 3)) {
                int start_point = 8 * page_number;
                for (int i = 0; i < page_size; i ++) {
                    printf("%d: %d\n", start_point + i, main_memory[start_point+i]);
                }
            }
            else {
                printf("Main memory %d is invalid\n", page_number);
            }
            
            
        }
        else if (strcmp(token, "showptable")==0) 
        {
            // token = strtok(NULL, "     ");

            for (int i = 0; i < vm_pages; i ++) {
                printf("%d:%d:%d:%d\n", i, page_table[i].valid_bit,page_table[i].dirty_bit,page_table[i].main_placement);
            }
    
            
        }
        else if (strcmp(token, "read")==0) 
        {

            token = strtok(NULL, "     ");
            addr = atoi(token);
            if ((addr < 0) || (128 < addr)){
                printf("%d address is invalid\n", addr);
            }
            else {
                page_number = addr / page_size;
                offset = addr % page_size;
                read_memory(page_number, offset);
            }

        } 
        else if (strcmp(token, "write")==0) 
        {

            token = strtok(NULL, "     ");
            addr = atoi(token);
            if ((addr < 0) || (128 < addr)){
                printf("%d address is invalid\n", addr);
            }
            else {
                page_number = addr / page_size;
                offset = addr % page_size;
                token = strtok(NULL, "     ");
                value = atoi(token);
                write_memory(page_number, offset, value);
            }

        }
        else {
            printf("Invalid Command\n");
        }

    }
    return 0;
}

void write_memory(int page_number, int offset, int value) {
    // printf("Writing Memory\n");
    if (page_fault(page_number)) {
        not_in_main(page_number); 
    }
    page_table[page_number].dirty_bit = 1;
    int main_place = page_table[page_number].main_placement;
    main_memory[(main_place * 8) + offset] = value;
    // printf("Writing %d in main memory adreess %d\n", value, (main_place * 8) + offset);
    update_usage(page_number);
}


void read_memory(int page_number, int offset) {
    // printf("Reading Memory\n");
    if (!page_fault(page_number)) {
        // printf("reading from main memory adreess %d\n", (page_table[page_number].main_placement * 8) + offset);
        printf("%d\n", main_memory[(page_table[page_number].main_placement * 8) + offset]);
    }
    else {
        printf("%d\n", virtual_memory[(page_number * 8) + offset]);
        not_in_main(page_number);
    }
    update_usage(page_number);
}

bool page_fault(int page_number) {
    // printf("Page Fault Check\n");
    if (page_table[page_number].valid_bit == 1) {
        return false;
    }
    printf("A Page Fault Has Occurred\n");
    return true;
}

void not_in_main(int page_number) {
    int main_place = replace_check(page_number);
        if (main_place == -1) {
            int old_page = main_replacement();
            main_place = page_table[old_page].main_placement;

            main_to_virtual(old_page, main_place);
            page_table[old_page].main_placement = old_page;
            
            
        }
        new_usage(page_number);

        virtual_to_main(page_number, main_place);



}

void main_to_virtual(int page_number, int main_place) {
    // printf("Moving main to virtual\n");

    int virtual_start = page_number * 8;
    int main_start = main_place * 8;

    for (int i = 0; i < page_size; i++) {
        virtual_memory[virtual_start + i] = main_memory[main_start + i];
    }
    page_table[page_number].valid_bit = 0;
    page_table[page_number].dirty_bit = 0;
}


void virtual_to_main(int page_number, int main_place) {
    // printf("Moving virtual to main\n");

    int virtual_start = page_number * 8;
    int main_start = main_place * 8;

    for (int i = 0; i < page_size; i++) {
        main_memory[main_start + i] = virtual_memory[virtual_start + i];
    }
    
    page_table[page_number].valid_bit = 1;
    page_table[page_number].dirty_bit = 0;
    page_table[page_number].main_placement = main_place;
    main_memory_table[main_place] = page_number;
}

int replace_check(int page_number) {
    // printf("Replace Check\n");

    for (int i = 0; i < mm_pages; i++) {
        if (main_memory_table[i] == -1) {
            // printf("Open spot %d\n", i);
            return i;
        }
    }
    return -1;

}

int main_replacement() {
    // printf("Finding Page Number to replace\n");
    if (lru) {
        int least_used = -1;
        int amount = -1;
        for (int i = 0; i < mm_pages; i++) {
            if (main_memory_usage[i] > amount) {
                least_used = i;
                amount = main_memory_usage[i];
            }
        }
        int return_page = -1;
        for (int i = 0; i < pg_table_size; i++) {
            if ((page_table[i].valid_bit == 1) && (page_table[i].main_placement == least_used)) {
                // printf("Replacing page %d\n", i);
                return_page = i;
                break;
            }
        }
        return return_page;
    }
    else {
        // printf("Replacing page %d\n", main_memory_usage[0]);
        return main_memory_usage[0];
    }
    

}

void update_usage(int page_number) {
    if (lru) {
        // printf("Update LRU Usage\n");
        int main_place = page_table[page_number].main_placement;
        for (int i = 0; i < mm_pages; i++) {
            if (i == main_place) {
                main_memory_usage[i] = 1;
            }
            else if (main_memory_usage[i] > -1){
                main_memory_usage[i] += 1;
            }
        }
    }
    
}
void new_usage(int page_number) {
    if (!lru) {
        // printf("New FIFO Usage\n");
        if ( main_memory_usage[3] != -1) {
            for (int i = 0; i < mm_pages-1; i++) {
                main_memory_usage[i] = main_memory_usage[i+1];
            }
            main_memory_usage[3] = -1; 
        }
        
        for (int i = 0; i < mm_pages; i++) {
            if (main_memory_usage[i] == -1) {
                main_memory_usage[i] = page_number;
                break;
            }
        }
    }
    
}