#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    
    float changeOwedFloat;
    int coinsUsed = 0;
    do
    {
        printf("O hai! How much change is owed?\n");
        changeOwedFloat = get_float();
    }
    while(changeOwedFloat<0);
    int centsOwed = round(changeOwedFloat * 100);
    while(centsOwed>=25)
    {
        coinsUsed++;
        centsOwed -= 25;
    }
    while(centsOwed>=10)
    {
        coinsUsed++;
        centsOwed -=10;
    }
    while(centsOwed>=5)
    {
        coinsUsed++;
        centsOwed -=5;
    }
    while(centsOwed>=1)
    {
        coinsUsed++;
        centsOwed -=1;
    }
    printf("%i\n",coinsUsed);
    
    
}