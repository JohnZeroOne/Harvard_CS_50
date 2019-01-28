#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shift(char c);

int main(int argc, string argv[])
{
    // Check that user has input only 1 command line argument
    if (argc == 2)
    {
        // Check that argv[1] only contains numbers by iterating its elements
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            // If the string contains a non-letter end execution
            if (isalpha(argv[1][i]) == 0)
            {
                // This code is repeated later, should jmp or write function
                printf("Usage: ./vigenere keyword\n");
                return 1;
            }
        }
        // Get user entry of plaintext to encipher
        string plaintext;
        do
        {
            plaintext = get_string("plaintext: ");
        }
        while (strlen(plaintext) < 0);
        printf("ciphertext: ");
        // Encipher alphabetical characters and print user text
        for (int i = 0, j = 0, n = strlen(plaintext); i < n; i++, j++)
        {
            char c = plaintext[i];
            int key;
            if (isalpha(c))
            {
                // Convert key argument to number
                // this wont work when char isnt alpha, for is still incrementing
                int m = strlen(argv[1]);
                key = shift(argv[1][j % m]);
                if (isupper(c))
                {
                    printf("%c", (((c - 65) + key) % 26) + 65);
                }
                if (islower(c))
                {
                    printf("%c", (((c - 97) + key) % 26) + 97);
                }
                 
            }
            else
            {
                j--;
                printf("%c", c);
            }
        }
        printf("\n");
        return 0;
    }
    else // User entered invalid command line arguments
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
}
int shift(char c)
{
    // Cast the key string to a numeric value repr. alpha. ie, A = 0
    int key = (int) c;
    if (isupper(c))
    {
        key -= 65;
    }
    else
    {
        key -= 97;
    }
    return key;
}
