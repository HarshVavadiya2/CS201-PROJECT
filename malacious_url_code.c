#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_RANK 4
#define bloom_size 701
#define user_size 10
#define MAXLINE 2048
#define SEED 0x12345678
unsigned long MurmurOAAT_32(char *str, unsigned long h)
{
    // One-byte-at-a-time hash based on Murmur's mix
    // Source: https://github.com/aappleby/smhasher/blob/master/src/Hashes.cpp
    for (; *str; ++str)
    {
        h ^= *str;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h % 701;
}
int bloom_filter[bloom_size];
//making all the bloom filter value 0
void make_bloom_zero(void)
{
    for (int i = 0; i < bloom_size; i++)
    {
        bloom_filter[i] = 0;
    }
}
int main()
{

    FILE *filePointer;//pointer for reading input from file
    
    
    char url[1000];
    filePointer = fopen("input4.txt", "r");//opening file in reading mode
    if (filePointer == NULL)
    {
        printf("file is not opening\n");
    }
    else
    {

        while (fgetc(filePointer) != EOF)
        {
            
            fscanf(filePointer, "%s",url);
            
            bloom_filter[MurmurOAAT_32(url, SEED)] = 1;
            
        }
        
    }
    
    fclose(filePointer);
    
    char ch='A';
    while (ch!='Q')
    {   
        printf("Please enter choice \n\tA : Check url\n\tB : Report url\n\tQ : Quit\n\t\tChoice : ");
        scanf("%s",&ch);//taking input of choice
        getchar();
        if(ch=='A'){//if you want to check url whether it is malicious or not
            printf("\t\tPlease enter the url or domain name u want to check : ");
            char url1[200];
            scanf("%s",url1);//taking input of url
            getchar();
            if(bloom_filter[MurmurOAAT_32(url1, SEED)] == 1){//if it's bloom filter at hash code is 1 then url is malicious
                printf("\t\t\tYour entered website maybe malacious!!\n");
            }
            else{//if it's bloom filter at hash code is 0 then url is safe
                printf("\t\t\tYour entered url is safe to visit <3.\n");
            }
        }

        else if(ch=='B'){//if you want to report url
            printf("\t\tPlease enter the url u want to reprot : ");
            char url1[200];
            scanf("%s",url1);
            getchar();
            bloom_filter[MurmurOAAT_32(url1, SEED)] = 1;
            printf("\t\t\tWe have recorded your reported url and will warn on use this url.\n");
        }
        //if you want to quit
        else if(ch=='Q'){
            break;
        }
        else{
            printf("Please enter a correct choice!!\n");
        }
    }
}