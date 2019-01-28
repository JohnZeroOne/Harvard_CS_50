// Enciphers plaintext by shifting the text with a numerical key

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check that user has input only 1 command line argument
    if (argc == 2)
    {
        // Check that argv[1] only contains numbers by iterating its elements
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            // If the string contains a non-number end execution
            if (isdigit(argv[1][i]) == 0)
            {
                // This is repeated later, should be able to jmp
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        // Validated user input, convert to an integer shift
        // int shift = (int) argv[1]; // Casting
        int shift = atoi(argv[1]);
        /*
        printf("Success\n");
        printf("%i\n", shift);
        return 0;
        */
        // Get user entry of plaintext to encipher
        string plaintext;
        do
        {
            plaintext = get_string("plaintext: ");
        }
        while (strlen(plaintext) < 0);
        printf("ciphertext: ");
        // Encipher alphabetical characters and print user text
        for (int i = 0, n = strlen(plaintext); i < n; i++)
        {
            char c = plaintext[i];
            if (isalpha(c))
            {
                if (isupper(c))
                {
                    printf("%c", (((c - 65) + shift) % 26) + 65);
                }
                if (islower(c))
                {
                    printf("%c", (((c - 97) + shift) % 26) + 97);
                }
            }
            else
            {
                printf("%c", c);
            }
        }
        printf("\n");
        return 0;
    }
    else // User entered invalid command line arguments
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

}
