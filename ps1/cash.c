// Returns how many coins are needed when giving change

// Imports
#include <cs50.h>
#include <stdio.h>
#include <math.h>

// Main code
int main(void)
{
    
    // Save user input
    float dollars = 0.00;
    
    // Prompt user for change input
    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0.009);
    
    // Convert float to integer (dollars to cents)
    // Save the number of coins needed
    int cents = round(dollars * 100), num_coins = 0;
    
    // Pay with largest possible coins, increment coin count
    while (cents >= 25)
    {
        cents -= 25;
        num_coins ++;
    }
    
    while (cents >= 10)
    {
        cents -= 10;
        num_coins ++;
    }
    
    while (cents >= 5)
    {
        cents -= 5;
        num_coins ++;
    }
    
    while (cents >= 1)
    {
        cents -= 1;
        num_coins ++;
    }
    // Print number of coins needed
    printf("%i\n", num_coins); 
}
