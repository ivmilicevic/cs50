#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    //check for proper usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./whodunit infile outfile\n");
        return 1;
    }
    
    //store filenames for later use
    char *inputFileName = argv[1];
    char *outputFileName = argv[2];
    
    //open input file using fread
    FILE *inputFile = fopen(inputFileName, "r");
    
    //check for error with opening input file
    if( inputFile == NULL)
    {
        fprintf(stderr, "Couldn't open %s.\n", inputFileName);
        return 2;
    }
    
    //open output file
    FILE *outputFile = fopen(outputFileName, "w");
    
    //check for errors with output file
    if(outputFile == NULL)
    {
        fclose(inputFile);
        fprintf(stderr, "Couldn't create %s.\n", outputFileName);
    }
    
    //create buffer for input file bitmap info and file headers
    BITMAPFILEHEADER bmpFileHeader;
    BITMAPINFOHEADER bmpInfoHeader;
    
    //reads 14 bytes (because BITMAPFILEHEADER has size of 14 bytes) 1 time from inputFile and stores it into memory at place bmpFileHeader
    fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, inputFile);
    
    //reads 40 bytes (because BITMAPINFOHEADER has size of 40 bytes) 1 time from inputFile and stores it into memory at place bmpInfoHeader
    fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, inputFile);
    
    //checks is input file valid 24bit uncompressed BMP 4.0
    if (bmpFileHeader.bfType != 0x4d42 || bmpFileHeader.bfOffBits != 54 || bmpInfoHeader.biSize !=40 || bmpInfoHeader.biBitCount != 24 || bmpInfoHeader.biCompression != 0)
    {
        fclose(outputFile);
        fclose(inputFile);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    //write bitmap file header from memory at location &bmpFileHeader to output file
    fwrite(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, outputFile);
    
    //write bitmap info header from memory at location &bmpInfoHeader to output file
    fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, outputFile);
    
    //determine padding for each line
    int padding = (4 - (bmpInfoHeader.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //iterate over scanlines
    //abs returns absolute value
    for (int i = 0, biHeight = abs(bmpInfoHeader.biHeight); i < biHeight; i++)
    {
        //iterate over each pixel
        for(int j = 0; j < bmpInfoHeader.biWidth; j++)
        {
            RGBTRIPLE triple;
            
            //read RGB triple from input file, and store it in memory at location &triple
            fread(&triple, sizeof(RGBTRIPLE), 1, inputFile);
            
            //check is pixel pure white
            if(triple.rgbtRed == 0xff && triple.rgbtBlue == 0xff && triple.rgbtGreen == 0xff)
            {
                triple.rgbtRed = 0x40;
                triple.rgbtBlue = 0x40;
                triple.rgbtGreen = 0x40;
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outputFile);
            }
            
            else if(triple.rgbtRed == 0xff && triple.rgbtBlue == 0x00 && triple.rgbtGreen == 0x00)
            {
                triple.rgbtRed = 0x00;
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outputFile);
            }
            
            else
            {
                //write rgb triple to output file
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outputFile);
            }
        }
        
        //skip over padding
        fseek(inputFile, padding, SEEK_CUR);
        
        //write padding to output file
        for(int k = 0; k < padding; k++)
        {
            fputc(0x00, outputFile);
        }
    }
    
    //close input and output files
    fclose(inputFile);
    fclose(outputFile);
    
    //finish
    return 0;
}