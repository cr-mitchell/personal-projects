// search.c
// by: Charles Mitchell

/* I completed this project for my private wealth management internship
summer 2022. My manager asked me to do a data clean-up which was checking
which names were in one file, but not the other. Instead of doing it manually,
I decided to create this program to search through the files and print the names
that was not in one of the files, but was in the other. I can not provide the files
with the names for legal purposes */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE 1000
#define MAX_CHAR 50

int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./search text1.txt text2.txt\n");
        return 1;
    }

    // opens the two files from the command line and reads them
    FILE *fptr1 = fopen(argv[1], "r");
    FILE *fptr2 = fopen(argv[2], "r");

    // initizalize two 2D arrays to store the names from the files
    char data1[MAX_LINE][MAX_CHAR];
    char data2[MAX_LINE][MAX_CHAR];

    int i = 0;

    // reads the data from one file into one of the arrays
    while (!feof(fptr1) && !ferror(fptr1))
    {
        if (fgets(data1[i], MAX_CHAR, fptr1))
        {
            i++;
        }
    }

    fclose(fptr1);

    int j = 0;

    // reads the data from the other file into the unsused array
    while (!feof(fptr2) && !ferror(fptr2))
    {
        if (fgets(data2[j], MAX_CHAR, fptr2))
        {
            j++;
        }
    }

    fclose(fptr2);

    // these two sets of nested loops lowercases every character in the files
    for (int a = 0; a < 668; a++)
    {
        for (int b = 0; b < MAX_CHAR; b++)
        {
            if (data1[a][b] >= 'A' && data1[a][b] <= 'Z')
            {
                data1[a][b] = data1[a][b] + 32;
            }
        }
    }

    for (int a = 0; a < 624; a++)
    {
        for (int b = 0; b < MAX_CHAR; b++)
        {
            if (data2[a][b] >= 'A' && data2[a][b] <= 'Z')
            {
                data2[a][b] = data2[a][b] + 32;
            }
        }
    }

    int counter = 0;

    /* this loop copies the names that were not in one file but in the other
    and writes over the name next to it */
    for (int x = 0; x < 668; x++)
    {
        for (int y = 0; y < 624; y++)
        {
            if (strcmp(data1[x], data2[y]) == 0)
            {
                for (int z = y; z < 668; z++)
                {
                    strcpy(data1[x], data1[x + 1]);
                }
                counter++;
            }
        }
    }

    char newdata[MAX_LINE][MAX_CHAR];
    int counter2 = 0;

    /* this checks to see which names are duplicated right next to each other
    and copies them into a new array */
    for (int x = 0; x < counter + 1; x++)
    {
        if (strcmp(data1[x], data1[x + 1]) == 0)
        {
            strcpy(newdata[counter2], data1[x]);
            counter2++;
        }
    }

    printf("Names not on the Year End List: \n");

    // prints the names that were stored in the new array 
    for (int x = 0; x < counter2 + 1; x++)
    {
        printf("%s", newdata[x]);
    }
}
