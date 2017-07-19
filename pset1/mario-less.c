#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int pyramidHeight;
    do {
        printf("Height: ");
        pyramidHeight = get_int();
    }
    while(pyramidHeight>23 || pyramidHeight<0);
    int numberOfColumns = pyramidHeight + 1;
    
    for(int currentRow = 1; currentRow<=pyramidHeight; currentRow++)
    {
        int numberOfSpaces = numberOfColumns - (currentRow +1);
        int numberOfHashes = currentRow + 1;
        
        for (int spaces = 0; spaces<numberOfSpaces; spaces++)
        {
           printf(" ");
        }
        
        for (int hashes = 0; hashes<numberOfHashes; hashes++)
        {
            printf("#");
        }
        printf("\n");
        
    }
}