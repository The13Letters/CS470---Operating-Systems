//Name: Alex Solomon
//Date: 3/4/2026
//Assignment: CS470 Quiz 8.T In Class


//Include Statements
#include <stdio.h>
#include <stdlib.h>

//Constants
#define PAGE_SIZE 1024
#define NUM_FRAMES 16

//Main Function
int main(void) 
{
    //local variables
    const int number_pages = 4;
    int page_table[] = {5, 2, 9, 1};
    int n;

    //Prompt for N
    printf("Enter number of logical addresses (N):\n");
    if (scanf("%d", &n) != 1 || n < 0) 
    {
        fprintf(stderr, "Invalid N\n");
        return EXIT_FAILURE;
    }

    //Prompt for addresses
    printf("Enter logical address(es), one per line:\n");
    for (int i = 0; i < n; i++) 
    {
        long logical;
        if (scanf("%ld", &logical) != 1) 
        {
            fprintf(stderr, "Invalid Logical Input\n");
            return EXIT_FAILURE;
        }

        //Handle negative address edge case
        if (logical < 0) 
        {
            printf("Logical: %ld | INVALID (negative address)\n", logical);
            continue;
        }

        //Compute page and offset
        long page = logical / PAGE_SIZE;
        long offset = logical % PAGE_SIZE;

        //Check if page is valid (0 to 3)
        if (page >= number_pages) 
        {
            printf("Logical: %ld | INVALID (page out of range)\n", logical);
        } 
        else 
        {
            //Look up the frame and compute the physical address
            int frame = page_table[page];
            long physical = (long)frame * PAGE_SIZE + offset;
            
            //Print the exact expected format
            printf("Logical: %ld | Page: %ld | Offset: %ld | Frame: %d | Physical: %ld\n", logical, page, offset, frame, physical);
        }
    }

    return EXIT_SUCCESS;
}