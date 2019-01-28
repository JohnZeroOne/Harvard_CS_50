// Encrypts a password into a hash given salt
// Takes 2 command line arguments, pass, salt

#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc == 3)
    {
        printf("%s \n", crypt(argv[1], argv[2])); 
        return 0;
    }
    else
    {
        printf("Wrong args.");
            return 1;
    } 
}
 
