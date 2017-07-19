#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    
    if(argc != 2)
    {
        printf("Incorrect usage. Please provide keyword in format ./vigenere KEYWORd\n");
        return 1;
    }
    
    string keyword = argv[1];
    int keywordLength = strlen(keyword);
    
    for(int i = 0; i< keywordLength ; i++)
    {
        if( (isalpha(keyword[i]) == false) )
        {
            printf("Incorrect usage. Please provide keyword in format ./vigenere KEYWORD\n");
            return 1;
        }
    }
    
    
    printf("plaintext: ");
    string plaintext = get_string();
    int plaintextLength = strlen(plaintext);
    
    printf("ciphertext:");
    int x = 0;
    for(int i = 0; i  < plaintextLength; i++)
    {
        
        if(isalpha(plaintext[i]) && isupper(plaintext[i]))
        {
            
            int k = x % keywordLength;
            int plaintextLetterIndex = plaintext[i] - 'A';
            int keywordLetterIndex = 0;
            if (isupper(keyword[k]))
            {
                keywordLetterIndex = keyword[k] - 'A';
            }
            else if (islower(keyword[k]))
            {
                keywordLetterIndex = keyword[k] - 'a';
            }
            
            int cipherText = ((plaintextLetterIndex + keywordLetterIndex) % 26);
            int asciiValue = cipherText + 'A';
            //printf("Letter %c (index %i), encrypted with letter %c(index %i) has value of %i (ascii %c) \n",plaintext[i], plaintextLetterIndex, keyword[k], keywordLetterIndex, cipherText, asciiValue);
            printf("%c", asciiValue);
            x++;
            
        }
        
        else if (isalpha(plaintext[i]) && islower(plaintext[i]))
        {
            int k = x % keywordLength;
            int plaintextLetterIndex = plaintext[i] - 'a';
            int keywordLetterIndex = 0;
            if(isupper(keyword[k]))
            {
                keywordLetterIndex = keyword[k] - 'A';
            }
            else if (islower(keyword[k]))
            {
                keywordLetterIndex = keyword[k] - 'a';
            }
            int cipherText = ((plaintextLetterIndex + keywordLetterIndex) % 26);
            int asciiValue = cipherText + 'a';
            //printf("Letter %c (index %i), encrypted with letter %c(index %i) has value of %i (ascii %c) \n",plaintext[i], plaintextLetterIndex, keyword[k], keywordLetterIndex, cipherText, asciiValue);
            printf("%c", asciiValue);
            x++;
        }
        else
        {
            //printf("Letter %c is not letter \n", plaintext[i]);
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}