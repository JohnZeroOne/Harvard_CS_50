// Resizes a BMP file

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
    int n = atoi(argv[1]); // atoi is not good for handling unknown/erroneous inputs
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
    // modify dimensions
    BITMAPFILEHEADER bf_out = bf;
    BITMAPINFOHEADER bi_out = bi;

    bi_out.biHeight = bi_out.biHeight * n;
    bi_out.biWidth = bi_out.biWidth * n; // doesn't include padding

    // determine input file's padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // determine new padding for scanlines
    int padding_new = (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //padding_new *= n; // this was working, now it is not

    // modify image size
    bi_out.biSizeImage = ((sizeof(RGBTRIPLE) * bi_out.biWidth) + padding_new) * abs(bi_out.biHeight);

    // modify file size
    bf_out.bfSize = bi_out.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines (for each row in file)
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // vertical writes, iterate n times
        for (int j = 0; j < n; j++)
        {
            // iterate over pixels in scanline (for each pixel in row)
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write pixels n times
                for (int l = 0; l < n; l++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // write outfile padding
            for (int m = 0; m < padding_new; m++)
            {
                fputc(0x00, outptr);
            }
            // reset infile pointer if necessary
            if (j < n - 1)
            {
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }
        // skip over infile padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}