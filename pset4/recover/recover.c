#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//define data type BYTE as unsigned integer(8 bits, 1 byte)
typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    //check for correct usage
    if(argc != 2)
    {
        fprintf(stderr, "Usage is ./recover card.raw\n");
        return 1;
    }
    
    //open raw file
    FILE *rawFile = fopen(argv[1], "r");
    if(rawFile == NULL)
    {
        fprintf(stderr, "Raw file couldn't be opened\n");
        return 2;
    }
    
    
    BYTE bufferArray[512];
    
    
    int blocksRead = 1, recoveryStarted = 0, fileIndex = 0;
    char filename[10];
    sprintf(filename, "%03i.jpg", fileIndex);
    FILE *currentImg;
    
    blocksRead = fread(bufferArray, 512, 1, rawFile);
    
    while(blocksRead)
    {
        
        
        //if start of new jpeg is found
        if(bufferArray[0] == 0xff && bufferArray[1] == 0xd8 && bufferArray[2] == 0xff && (bufferArray[3] & 0xf0) == 0xe0)
        {
            if(recoveryStarted == 0)
            {
                //change recoveryStarted
                recoveryStarted = 1;
                
                //first jpeg file found, create first file and write buffer to it
                
                currentImg = fopen(filename, "w");
                fwrite(bufferArray, 512, 1, currentImg);
            }
            
            else if(recoveryStarted == 1)
            {
                //close previous file
                fclose(currentImg);
                
                //create new file with appropriate filename
                fileIndex++;
                sprintf(filename, "%03i.jpg", fileIndex);
                currentImg = fopen(filename, "w");
                
                //write to new file
                fwrite(bufferArray, 512, 1, currentImg);
            }
        }
        
        else
        {
            //if we found jpeg before write bufferArray to output file
            if(recoveryStarted == 1)
            {
                fwrite(bufferArray, 512, 1, currentImg);
            }
            //if not discard buffer and return to start of the loop
        }
        
        blocksRead = fread(bufferArray, 512, 1, rawFile);
        
    }
    fclose(currentImg);
    
    
}