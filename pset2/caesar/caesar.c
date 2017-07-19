#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    
    int k = atoi(argv[1]);
    
    printf("plaintext: ");
    string plaintext = get_string();
    
    printf("ciphertext:");
    
    for(int i = 0, stringLength = strlen(plaintext); i < stringLength; i++)
    {
        if(isalpha(plaintext[i]) && isupper(plaintext[i]))
        {
            int letterIndex = plaintext[i] - 'A';
            int ciphertext = (letterIndex + k) % 26;
            char asciiValue = ciphertext + 'A';
            printf("%c", asciiValue);
            //printf("Ciphered value of %c with key %i is %i, in ASCII %c\n", plaintext[i], k, ciphertext, asciiValue);
        }
        
        else if (isalpha(plaintext[i]) && islower(plaintext[i]))
        {
            int letterIndex = plaintext[i] - 'a';
            int ciphertext = (letterIndex + k) % 26;
            char asciiValue = ciphertext + 'a';
            printf("%c", asciiValue);
            //printf("Ciphered value of %c with key %i is %i, in ASCII %c\n", plaintext[i], k, ciphertext, asciiValue);
        }
        
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    
    printf("\n");
}
