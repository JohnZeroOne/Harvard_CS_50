//using solution to mario/less modified
//import string
#include <cs50.h>
//import printf
#include <stdio.h>
//main program no args
int main(void)
{
    //scope brick_input
    int brick_input = 0;
    //display characters for an individual brick
    //string brick_string = "#";
    //blank char for spacing
    //string blank_string = " ";
    
    //get the brick height from user
    //keep asking until it is between 1-8
    do
    {
        brick_input = get_int("Height: ");
    }
    while (brick_input < 1 || brick_input > 8);
    
    brick_input += 1;
    
    //print a newline for each row
    for (int i = 0; i < (brick_input - 1); i++)
    {   
        //fill the spaces with blank chars
        for (int j = brick_input; j > (i + 2); j--)
        {
            putchar(' ');
        }
        //fill with x bricks
        for (int k = 0; k < (i + 1); k++)
        {
            putchar('#');
        }
        //space in middle
        putchar(' ');
        putchar(' ');
        //fill with x bricks
        for (int l = 0; l < (i + 1); l++)
        {
            putchar('#');
        }
        
        printf("\n");
    }
}
 
