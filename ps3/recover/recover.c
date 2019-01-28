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
    // open file specified
    FILE *file = fopen(argv[1], "r");
    // check that file can be read
    if (file == NULL)
    {
        fprintf(stderr, "File could not be read\n");
        return 2;
    }
}
