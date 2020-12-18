#include <math.h>
#include "helpers.h"

#include <stdio.h>

#define MAX_PIXEL 255

int average(RGBTRIPLE rgb);
void reflect_row(int size, RGBTRIPLE row[size]);
void group_average(int size, RGBTRIPLE group[size], RGBTRIPLE *pixel);
void group_edge(int size, RGBTRIPLE group[size], RGBTRIPLE *pixel);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int size = height * width;

    RGBTRIPLE *point = *image;

    int avg = 0;
    for (int i = 0; i < size; i++, point++)
    {
        avg = average(*point);
        (*point).rgbtRed = avg;
        (*point).rgbtGreen = avg;
        (*point).rgbtBlue = avg;
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        reflect_row(width, image[i]);
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // need a copy to preserve original values
    RGBTRIPLE copy_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j] = image[i][j];
        }
    }

    int x, y, n;
    RGBTRIPLE group[9];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            x = j - 1;
            y = i - 1;
            n = 0;
            for (y = i - 1; y <= i + 1; y++)
            {
                for (x = j - 1; x <= j + 1; x++)
                {
                    if ((x >= 0 && y >= 0) && (x < width && y < height))
                    {
                        group[n] = copy_image[y][x];
                        n++;
                    }
                }
            }
            group_average(n, group, &image[i][j]);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // need a copy to preserve original values
    RGBTRIPLE copy_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j] = image[i][j];
        }
    }

    RGBTRIPLE blank = {0, 0, 0};

    int x, y, n;
    RGBTRIPLE group[9];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            x = j - 1;
            y = i - 1;
            n = 0;
            for (y = i - 1; y <= i + 1; y++)
            {
                for (x = j - 1; x <= j + 1; x++)
                {
                    if ((x >= 0 && y >= 0) && (x < width && y < height))
                    {
                        group[n] = copy_image[y][x];
                    }
                    else
                    {
                        group[n] = blank;
                    }
                    n++;
                }
            }
            group_edge(n, group, &image[i][j]);
        }
    }
    return;
}

// return the average value of three integers
int average(RGBTRIPLE rgb)
{
    int r, g, b;
    r = rgb.rgbtRed;
    g = rgb.rgbtGreen;
    b = rgb.rgbtBlue;

    float pre_comp = (r + g + b) / 3.0;
    int post_comp = (int)(pre_comp + 0.5);

    return post_comp;
}

// reflect an array
void reflect_row(int size, RGBTRIPLE row[size])
{
    int i, j;
    // start at ends and work in until cross over
    for (i = 0, j = size - 1; i != j && i < j; i++, j--)
    {
        RGBTRIPLE temp = row[j];
        row[j] = row[i];
        row[i] = temp;
    }

    return;
}

// return int average of array
int int_avg(int size, int items[size])
{
    float sum = 0.0;
    for (int i = 0; i < size; i++)
    {
        sum += items[i];
    }
    float pre_comp = sum / size;
    int post_comp = (int)(pre_comp + 0.5);

    return post_comp;
}

// set RGBTRIPLE struct with average values of group
void group_average(int size, RGBTRIPLE group[size], RGBTRIPLE *pixel)
{
    int reds[size], blues[size], greens[size];

    for (int i = 0; i < size; i++)
    {
        reds[i] = group[i].rgbtRed;
        blues[i] = group[i].rgbtBlue;
        greens[i] = group[i].rgbtGreen;
    }

    (*pixel).rgbtRed = int_avg(size, reds);
    (*pixel).rgbtBlue = int_avg(size, blues);
    (*pixel).rgbtGreen = int_avg(size, greens);

    return;
}

/* take two doubles and return sum of squares rounded to
*  nearest int
*/
int sum_squares(double x_val, double y_val)
{
    int post_comp = 0;
    double pre_comp = sqrt((pow(x_val, 2) + pow(y_val, 2)));

    post_comp = (int)(pre_comp + 0.5);

    return post_comp;
}

// compute and return sobel filter value for a given array
int sobel(int size, int items[size])
{
    const int G_X[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    const int G_Y[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    double x_val = 0.0;
    double y_val = 0.0;

    for (int i = 0; i < size; i++)
    {
        printf("%d\n", items[i]);
        x_val += (items[i] * G_X[i]);
        y_val += (items[i] * G_Y[i]);
    }

    int post_comp = sum_squares(x_val, y_val);
    if (post_comp > MAX_PIXEL)
    {
        post_comp = MAX_PIXEL;
    }

    return post_comp;
}

// set RGBTRIPLE struct with new values based on sobel alg
void group_edge(int size, RGBTRIPLE group[size], RGBTRIPLE *pixel)
{
    int reds[size], blues[size], greens[size];

    for (int i = 0; i < size; i++)
    {
        reds[i] = group[i].rgbtRed;
        blues[i] = group[i].rgbtBlue;
        greens[i] = group[i].rgbtGreen;
    }

    (*pixel).rgbtRed = sobel(size, reds);
    (*pixel).rgbtBlue = sobel(size, blues);
    (*pixel).rgbtGreen = sobel(size, greens);

    return;
}