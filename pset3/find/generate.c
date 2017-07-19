/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // Program will run when only n is supplied or both n and seed are supplied
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // converts first argument from string to int, so it can be used as number
    int n = atoi(argv[1]);

    // If seed is supplied it will use that value to seed drand48(), by first converting it to long int. If seed is not supplied it will automatically seed drand48() with current system time in seconds
    if (argc == 3)
    {
        srand48( (long) atoi(argv[2]) );
    }
    else
    {
        srand48((long) time(NULL));
    }

    // Prints out n pseudo-random numbers by calling function drand48. Function returns number between 0 and 1, so it needs to be multiplied by maximum value of number that we want.
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
