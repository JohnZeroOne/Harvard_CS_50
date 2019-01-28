// Checks the validity of a credit card number entered by user

// Import extra functionality
#include <stdio.h>
#include <cs50.h>

// Main program
int main(void)
{
    // Get credit card number from the user
    long long cc_number;
    do
    {
        cc_number = get_long_long("Number: ");
    }
    while (cc_number < 1);
    
    // Count the number of digits in cc_num
    int num_digits = 0;
    long long temp_cc_number = cc_number;
    
    //printf("temp cc number %lld \n", temp_cc_number);
    
    while (temp_cc_number > 0)
    {
        temp_cc_number /= 10;
        num_digits += 1;
        //printf("cc number %lld \n", cc_number);
        //printf("num digits %i \n", num_digits);
    }
    
    if (num_digits < 13 || num_digits > 16)
    {
        printf("INVALID\n");
        return 0;
    }
    
    // Luhn's algorithm
    int luhn = 0;
    int i = 0;
    // Reset temp variable
    temp_cc_number = cc_number;
    // Multiply & sum every even digit
    // not sure if this if is necessary for odd digit length
    if (num_digits % 2 != 0)
    {
        i = 1;
    }
    
    for ( ; i < num_digits; i += 2)
    {
        temp_cc_number /= 10;
        int temp_luhn = (temp_cc_number % 10) * 2;
        // Add numbers by single digit
        if (temp_luhn > 9)
        {
            temp_luhn -= 9;
        }
        luhn += temp_luhn;
        temp_cc_number /= 10;
        //printf("cc number %lld \n", cc_number);
        //printf("luhn %i \n", luhn);
    }
    
    //printf("cc number %lld \n", cc_number);
    //printf("after even, luhn %i \n", luhn);
    
    // Add to remaining odd digits
    temp_cc_number = cc_number;
    for (i = 0; i < num_digits; i += 2)
    {
        luhn += (temp_cc_number % 10);
        temp_cc_number /= 100;
    }
    //printf("after odd, luhn %i \n", luhn);
    // Validate checksum
    if (luhn % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    // Brand check
    temp_cc_number = cc_number;
    //printf("temp cc %lld \n", temp_cc_number);
    // Get the first 2 digits of the card
    for (i = 0; i < (num_digits - 2); i++)
    {
        temp_cc_number /= 10;
        //printf("temp cc for loop: %lld \n", temp_cc_number);
    }
    // equivalent
    //temp_cc_number = temp_cc_number % (num_digits - 2);
    //printf("two digits: %lld \n", temp_cc_number);
    // Validate identifier
    string brand = "INVALID";
    if (temp_cc_number == 34 || temp_cc_number == 37)
    {
        brand = "AMEX";
    }
    if (temp_cc_number >= 51 && temp_cc_number <= 55)
    {
        brand = "MASTERCARD";
    }
    if (temp_cc_number / 10 == 4)
    {
        brand = "VISA";
    }
    // Return output
    printf("%s\n", brand);
}
