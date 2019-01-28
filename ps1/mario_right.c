//import string
#include <cs50.h>
//import printf
#include <stdio.h>
//main program no args
int main(void)
{
    //scope brick_input
    int brick_input = 8;
    //display characters for an individual brick
    string brick_string = "#";
    //blank char for spacing
    string blank_string = " ";
    
    //get the brick height from user
    //keep asking until it is between 1-8
    do
    {
        brick_input = get_int("Height: ");
    }
    while (brick_input < 1 || brick_input > 8);
    
    brick_input += 1;
    
    //print a char for each row of bricks until we reach user input
    for (int i = 0; i < brick_input; i++)
    {   
        for (int j = 0; j < i; j++)
        {
            putchar('#');
        }
        printf("\n");
    }
}
 
