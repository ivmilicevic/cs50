#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int board[3][3] = { {1,2,3}, {4,5,6}, {7,8,0} };
    int counter = 1;
 
    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            if(board[i][j] == counter || board[i][j] == 0)
            {
                counter++;
            }
        }
        printf("\n");
    }
    printf("%i", counter);
}