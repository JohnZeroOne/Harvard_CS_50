// Takes a hash and tries to crack the underlying password
// 
// Currently only works with 1 letter passwords
// Outpu
// Need to implement uppercase guess and check
// Need to extend characters from 1 to 5

#define _XOPEN_SOURCE
#include <cs50.h>
// #include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>



const string ALPHA_LOW = "abcdefghijklmnopqrstuvwxyz";
const string ALPHA_HIGH = "ABCEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, string argv[])
{
    // User enters too many, too few CL args.
    if (argc != 2 || strlen(argv[1]) != 13)
    {
        printf("Usage ./crack hash\n");
        return 1;
    }
    else // Success
    {
        // a = 50OqznXGVcOJU
        // b = 50/C8COQ1sLRg
        
        // Get the first 2 chars. of hash
        char salt[3];
        salt[0] = argv[1][0];
        salt[1] = argv[1][1];

        // Crack
        char plaintext[5];
        // Dictionary attack, not implemented
        
        // Bruteforce attack
        int alpha_len = strlen(ALPHA_LOW);
        for (int i = 0; i < alpha_len; i++)
        {
            // set plaintext as a, b, c, etc
            plaintext[0] = ALPHA_LOW[i];
            printf("Plaintext: %c\n", plaintext[0]);
            // hashes match, password found
            // this isn't producing the same hash as running the command alone
            // something is different in the inputs with pointers
            printf("resulting hash: %s\n", crypt(&plaintext[0], salt));
            if (strcmp(crypt(&plaintext[0], salt), argv[1]) == 0)
            {
                // End
                printf("%c\n", plaintext[0]);
                return 0;
            }  
        }
        printf("Password not found\n");
        return 1;           
    }   
}

