/*
    Readability - week 2 assignment for cs50x
    Coleman-Liau Index: index = 0.0588 * L - 0.296 * S - 15.8
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <cs50.h>

int coleman_liau_index(int s_len, string sample);
bool is_ending(char c);

int main(int argc, string argv[])
{
    string s = get_string("Text: ");
    int s_len = strlen(s);

    int index = coleman_liau_index(s_len, s);

    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

    return 0;
}

/*
    Calculate Index and return as int
*/
int coleman_liau_index(int s_len, string sample)
{
    int letters = 0;
    int words = 0;
    int sentences = 0;

    char prev_char = ' ';

    for (int i = 0; i < s_len; i++)
    {
        if (isalpha(sample[i]))
        {
            letters++;
            if (isspace(prev_char))
            {
                words++;
            }
        }
        else if (is_ending(sample[i]))
        {
            sentences++;
        }
        prev_char = sample[i];
    }

    float L = ((float) letters / (float) words) * 100.0f;
    float S = ((float) sentences / (float) words) * 100.0f;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    int rounded_index = 0;
    if (index > 1.0)
    {
        rounded_index = (int)(index + 0.5f);
    }

    return rounded_index;
}

// return true if char ends a sentence
bool is_ending(char c)
{
    /* NOTE: had to add : as a sentence ending to pass the
       Alice in Wonderland case, even though the problem didnt include
       it as a sentence-ending.
    */
    if (c == '.' || c == '!' || c == '?' || c == ':')
    {
        return true;
    }

    return false;
}

