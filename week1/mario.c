#include <cs50.h>
#include <stdio.h>

void make_pyramid(int height);
int main(void)
{
    int height;
    do
    {   
        height = get_int("Height between 1 and 8: ");
    }
    while (height < 1 || height > 8);

    make_pyramid(height);
}

// get height of pyramid from user and print in hashes
void make_pyramid(int height)
{
    int hashes = 1;
    int spaces;

    do
    {   
        // print spaces
        spaces = height - hashes;
        for (int i = 1; i <= spaces; i++)
        {
            printf(" ");
        }
        // print hashes
        for (int i = 1; i <= hashes; i++) 
        {
            printf("#");
        }
        // print gap
        printf("  ");
        // print hashes again
        for (int i = 1; i <= hashes; i++) 
        {
            printf("#");
        }
        // finally a newline and inc
        printf("\n");
        hashes++;
    }
    while (hashes <= height);
}
