#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_RANK 4
#define bloom_size 701
#define user_size 10
#define MAXLINE 2048
#define SEED 0x12345678
int main()
{
    char *str;
    FILE *filePointer;
    filePointer = fopen("input4.txt", "r");

    while (fgetc(filePointer) != EOF)
    {
        
        fscanf(filePointer, "%s", str);
        printf("%s", str);
    }
    return 0;
}