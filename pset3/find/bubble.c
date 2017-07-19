#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //int arraySize = 6;
    int array[] = {5, 2, 1, 3, 6, 4};
    
    int length = array / array[0];
    printf("%i", length);
    for(int i = 0; i<6; i++)
    {
        printf("%i\n", array[i]);
    }
}