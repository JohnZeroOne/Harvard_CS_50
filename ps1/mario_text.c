//import string
#include <cs50.h>
//import printf
#include <stdio.h>
//main program no args
int main(void)
{
    //scope brick_input
    int brick_input = 8;
    //int brick = 1;
    //display characters for an individual brick
    string brick_string = "#";
    //blank char for spacing
    string blank_string = "";
    
    //get the brick height from user
    //keep asking until it is between 1-8
    do
    {
        brick_input = get_int("Height: ");
    }
    while (brick_input < 1 || brick_input > 8);
    
    
    //print a char for each row of bricks until we reach user input
    for (int i = 0; i < brick_input; i++)
    {
        //blank_string -= blank_string;
        //need to use %[brick_input]s instead of %8s
        printf("%*s\n", brick_input, brick_string);
        //brick *= 10;
        //need to concat. brick string here, using [i]
    }
}
 
