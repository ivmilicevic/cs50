#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (void)
{
    string name = get_string();
    if(name[0] != ' ')
        {
            printf("%c", toupper(name[0]));
        }
        
    for(int i=0, stringLength = strlen(name); i<stringLength; i++)
    {
        if(name[i-1] == ' ' && name[i] != ' ')
        {
            printf("%c", toupper(name[i]));
        }
    
    }
    printf("\n");
    
}