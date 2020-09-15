#include <stdio.h>
#include <stdint.h>

typedef uint8_t  BYTE;

/**
 * RGBTRIPLE
 *
 * This structure describes a color consisting of relative intensities of
 * red, green, and blue.
 *
 * Adapted from http://msdn.microsoft.com/en-us/library/aa922590.aspx.
 */
typedef struct
{
    BYTE  rgbtBlue;
    BYTE  rgbtGreen;
    BYTE  rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;


void group_average(int size, RGBTRIPLE group[size], RGBTRIPLE *pixel);

int main(int argc, char* argv[])
{
    // int items[3][3] = {
    //     {1,2,3},
    //     {4,5,6},
    //     {7,8,9}
    // };

    // int *ptr = *items;
    // int i;

    // for (i = 0; i < 9; i++)
    // {
    //     // increase value
    //     *(ptr + i) += 1;
    // }
    // for (i = 0; i < 9; i++)
    // {
    //     printf("item: %d\n", *(ptr + i));
    // }

    // make a few of these...
    RGBTRIPLE test = {3,5,6};
    RGBTRIPLE test2 = {4,8,12};
    RGBTRIPLE test3 = {7,6,21};
    RGBTRIPLE test4 = {3,5,12};
    RGBTRIPLE test5 = {0,0,0};

    // // array of them
    // RGBTRIPLE img[2][2] = {
    //     {test, test2},
    //     {test3, test4}
    // };

    RGBTRIPLE group[3] = {test, test2, test3};
    // RGBTRIPLE *ptr = *img;

    // int i;
    // for (i = 0; i< 4; i++, ptr++)
    // {
    //     ptr->rgbtRed = 12;
    //     printf("RED: %d\n", ptr->rgbtRed);
    // }

    // pointer just for fun
    // RGBTRIPLE *ptr = &test;

    // printf("%d\n", (*ptr).rgbtRed);

    // int somewhere = 21;
    // int *ptr_s = &somewhere;

    // // print actual address
    // printf("%p\n", ptr_s);

    // // print value
    // printf("%d\n", *ptr_s);

    // // now address again
    // printf("%p\n", &somewhere);

    group_average(2, group, &test5);

    printf("RED: %d\n", test5.rgbtRed);

    return 0;
}

// return int average of array
int int_avg(int size, int items[size])
{
    float sum = 0.0;
    for (int i = 0; i < size; i++)
    {
        sum+=items[i];
    }
    float pre_comp = sum / size;
    int post_comp = (int) (pre_comp + 0.5);
    printf("pre avg: %f\n", pre_comp);
    printf("average: %d\n", post_comp);

    return post_comp;
}

// set RGBTRIPLE struct with average valuse of group
void group_average(int size, RGBTRIPLE group[size], RGBTRIPLE *pixel)
{
    // init 3 arrays for red, blue, green
    int reds[size], blues[size], greens[size];

    // populate arrays
    for (int i = 0; i < size; i++)
    {
        reds[i] = group[i].rgbtRed;
        greens[i] = group[i].rgbtGreen;
        blues[i] = group[i].rgbtBlue;

    }

    (*pixel).rgbtRed = int_avg(size, reds);
    (*pixel).rgbtGreen = int_avg(size, greens);
    (*pixel).rgbtBlue = int_avg(size, blues);


    return;
}