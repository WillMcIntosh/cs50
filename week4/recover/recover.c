#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int jpeg_start(BYTE block[]);
int recover(FILE *f);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: recover image\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 1;
    }

    recover(f);
    fclose(f);
    return 0;
}

// return True if current block has standard jpeg signature
int jpeg_start(BYTE block[])
{
    if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff)
    {
        if ((block[3] & 0xf0) == 0xe0)
        {
            return 1;
        }
    }

    return 0;
}

/* Recover JPEG images from a given file and save to current directory.
*
*/
int recover(FILE *f)
{
    int file_end = 0;
    int file_count = 0;
    char filename[8];
    FILE *img = NULL;

    while (!file_end)
    {
        // read file in 512 byte blocks
        BYTE buffer[512];
        int count = fread(buffer, sizeof(BYTE), 512, f);
        if (count < 512)
        {
            file_end = 1;
        }

        if (count > 4 && jpeg_start(buffer))
        {
            // close existing file if open & create new file
            if (file_count > 0 && img != NULL)
            {
                fclose(img);
                img = NULL;
            }
            sprintf(filename, "%03i.jpg", file_count);
            img = fopen(filename, "w");
            file_count++;
        }
        if (img != NULL)
        {
            fwrite(buffer, sizeof(BYTE), count, img);
        }
        if (file_end && img != NULL)
        {
            fclose(img);
        }
    }

    return 0;
}
