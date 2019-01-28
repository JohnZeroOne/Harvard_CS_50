// Resizes a BMP file

// #include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // printf("argc: %i\n", argc);
    // 3 command line args not supplied
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // n given is not from 1 to 100
    int n = atoi(argv[1]); // atoi is not good for handling unknown inputs
    if (n < 1 || n > 100)
    {
        printf("Resize n must be from 1 to 100\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // Update outfile's header info
    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // modify dimensions
    bi.biHeight *= n; // need to account for padding?
    bi.biWidth *= n; // not including padding
    // modify image size
    bi.biSizeImage =
    ((sizeof(RGBTRIPLE) * bi.biWidth) + padding)
                * abs(bi.biHeight);

    // modify file size
    bf.bfSize = bi.biSizeImage +
                    sizeof(BITMAPFILEHEADER) +
                    sizeof(BITMAPINFOHEADER);


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write row pixels n times
            for (int k = 0; k < n; k++)
                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                // write padding if necessary
                padding = 4(-(biWidth * sizeof(RGBTRIPLE) % 4) % 4);
                int pad = 0x000000; // one unit of padding
                while (padding != 0) // fill padding until it's a multiple of 4
                {
                    fputc(%inptr, pad);
                    padding = 4(-(biWidth * sizeof(RGBTRIPLE) % 4) % 4);
                }
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        /*
        // then add it back (to demonstrate how) <- meaningless comment
        // filling with padding?
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
        */
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
