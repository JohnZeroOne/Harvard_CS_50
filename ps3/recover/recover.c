// recovers jpeg image files from a raw memory card dump

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // check that program is run with correct number of args.
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // open memory card file
    FILE *file = fopen(argv[1], "r");

    // check that file can be read
    if (file == NULL)
    {
        fprintf(stderr, "File could not be read\n");
        return 2;
    }

    // set up a memory buffer to read into
    unsigned char *buffer = malloc(8192 * sizeof(char));

    // array to store jpg file names
    char *filename = malloc(8 * sizeof(char));
    int counter = 0;

    // file to write images to
    FILE *img = NULL;
    // detect end of file EOF
    while (fread(buffer, 512, 1, file) == 1)
    {
        // find beginning of a new JPEG
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // close any previous jpeg file
            if (img)
            {
                fclose(img);
            }

            // add new filename to file array
            sprintf(filename, "%03i.jpg", counter);

            // increment counter for file name
            counter++;

            // open a new JPEG
            img = fopen(filename, "w");
        }
        if (img)
        {
            // fprintf(stderr, "test for segfault\n");
            // write 512 bytes to current file
            fwrite(buffer, 512, 1, img); // img == null causing segmentation fault
        }


    }
    // end
    // close files
    fclose(file);
    fclose(img);
    // free memory after use
    free(buffer);
    free(filename);
    return 0;
}
