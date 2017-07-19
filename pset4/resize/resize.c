/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n inputFile outputFile\n");
        return 1;
    }
    int resizeFactor = atoi(argv[1]);
    if(resizeFactor < 0 || resizeFactor > 100)
    {
        fprintf(stderr, "n must be positive and less than or equal to 100.\n");
    }

    // remember filenames
    char *inputFileName = argv[2];
    char *outputFileName = argv[3];

    // open input file 
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", inputFileName);
        return 2;
    }

    // open output file
    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL)
    {
        fclose(inputFile);
        fprintf(stderr, "Could not create %s.\n", outputFileName);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bmpFileHeader;
    fread(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, inputFile);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bmpInfoHeader;
    fread(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, inputFile);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bmpFileHeader.bfType != 0x4d42 || bmpFileHeader.bfOffBits != 54 || bmpInfoHeader.biSize != 40 || 
        bmpInfoHeader.biBitCount != 24 || bmpInfoHeader.biCompression != 0)
    {
        fclose(outputFile);
        fclose(inputFile);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    if(resizeFactor > 1)
    {
        //stores input file width and height for later use
        int inputBiWidth = bmpInfoHeader.biWidth;
        int inputBiHeight = abs(bmpInfoHeader.biHeight);
        int inputPadding = (4 - (inputBiWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        
        //updates output file headers and calculates padding
        bmpInfoHeader.biWidth = bmpInfoHeader.biWidth * resizeFactor;
        bmpInfoHeader.biHeight = bmpInfoHeader.biHeight * resizeFactor;
        int outputPadding = (4 - (bmpInfoHeader.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        bmpInfoHeader.biSizeImage = ((sizeof(RGBTRIPLE) * bmpInfoHeader.biWidth) + outputPadding) * abs(bmpInfoHeader.biHeight);
        bmpFileHeader.bfSize = bmpInfoHeader.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        
        //writes updated bmp file and info headers into output file
        fwrite(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, outputFile);
        fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, outputFile);
        
        //create array for storing resized horizontaly of type RGBTRIPLE that holds biWidth values
        RGBTRIPLE array[bmpInfoHeader.biWidth];
        
        //iterate over input file scanlines(height)
        for (int currentLine = 0; currentLine < inputBiHeight; currentLine++)
        {
            
            int arrayCursor = 0;
            //iterate over pixels in current line(width)
            for(int currentPixel = 0; currentPixel<inputBiWidth; currentPixel++)
            {
                //read current pixel
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, inputFile);
                
                //write every pixel in line to array resizeFactor times and update array cursor position over time.
                for(int b = 0; b < resizeFactor; b++)
                {
                    array[arrayCursor] = triple;
                    arrayCursor++;
                }
            }
            //create resizeFactor new lines in output file, write content of array and add padding if necessary
            for(int c=0; c<resizeFactor; c++)
            {
                fwrite(&array, sizeof(array), 1, outputFile);
                
                //write padding to output file
                for (int k = 0; k < outputPadding; k++)
                {
                    fputc(0x00, outputFile);
                }
            }
            //skip input file padding
            fseek(inputFile, inputPadding, SEEK_CUR);
        }
    }
    
    
    if(resizeFactor == 1)
    {
        fwrite(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, outputFile);
        fwrite(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1, outputFile);
        int padding = (4 - (bmpInfoHeader.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        for (int i = 0, biHeight = abs(bmpInfoHeader.biHeight); i < biHeight; i++)
        {
            for(int j = 0; j<bmpInfoHeader.biWidth; j++)
            {
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, inputFile);
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outputFile);
            }
            fseek(inputFile, padding, SEEK_CUR);
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outputFile);
            }
        }
        
    }

    // close infile
    fclose(inputFile);

    // close outfile
    fclose(outputFile);

    // success
    return 0;
}
