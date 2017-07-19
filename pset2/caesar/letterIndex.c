#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Letter: ");
    char plaintext = get_char();
    int letterIndex = plaintext - 'A';
    printf("\nIndex of %c is %i\n", plaintext, letterIndex);
}