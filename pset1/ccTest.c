#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long long number = 378282246310005;
    int last = number % 1;
    printf("%i", last);
}