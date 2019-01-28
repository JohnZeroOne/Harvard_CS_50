#include <cs50.h>
#include <stdio.h>

int collatz();

int main(void)
{
    int n;
    int num_steps = 0;
    // Get user input of n
    do
    {
        n = (int) get_string("n: ");
    }
    while (n < 1);
    // call collatz
    collatz(n, num_steps);
}

int collatz(int n, int num_steps)
{
   // base case
   if (n == 1)
   {
       printf("Steps: %i\n", num_steps);
       return 0;
   }
   // recursive cases
   if (n % 2 == 0) // n is even
   {
       // n / 2
       num_steps ++;
       collatz(n / 2, num_steps);
   }
   if (n % 2 == 1) // n is odd
   {
       // 3n + 1
       num_steps ++;
       collatz((n * 3) + 1, num_steps);
   }
   return 1;
}

// num_steps isn't working as intended, may need to use pointers to pass into function
