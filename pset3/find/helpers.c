/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"
/**
 * Returns true if value is in array of n values, else false.
 */
 
//Binary search 
bool search(int value, int values[], int n)
{
    // Checks if n is positive
    if ( n<0)
    {
        return false;
    }
    
    int low = 0;
    int high = n-1;
    
    
    while(high >= low)
    {
        int midpoint = (high + low) / 2;
        
        if(values[midpoint] == value)
        {
            return true;
        }
        if(values[midpoint] > value)
        {
            high = midpoint - 1;
        }
        if(values[midpoint] < value)
        {
            low = midpoint + 1;
        }
    }
    
    return false;
}
    


/**
 * Sorts array of n values.
 */
//Bubble sort 
void sort(int values[], int n)
{
    int swapCount = -1;
    
    while(swapCount != 0)
    {
        swapCount = 0;
        for(int i = 0; i<n-1; i++)
        {
            if(values[i] > values[i+1])
            {   
                int temp = values[i];
                values[i] = values[i+1];
                values[i+1] = temp;
                swapCount++;
            }
        }
    }
    return;
}
