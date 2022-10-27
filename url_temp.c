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
void make_bloom_zero(void)
{
    for (int i = 0; i < bloom_size; i++)
    {
        bloom_filter[i] = 0;
    }
}
int main()
{

    FILE *filePointer;
    int book_number_input;

    //  fscanf(filePointer,"%d",&book_number);
    // //  printf("%d ",book_number);
    //  Node_Genrator(book_number,);
    char url[1000];
    filePointer = fopen("input4.txt", "r");
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
        scanf("%s",&ch);
        getchar();
        if(ch=='A'){
            printf("\t\tPlease enter the url u want to check : ");
            char url1[200];
            scanf("%s",url1);
            getchar();
            if(bloom_filter[MurmurOAAT_32(url1, SEED)] == 1){
                printf("\t\t\tYour entered website maybe malacious!!\n");
            }
            else{
                printf("\t\t\tYour entered url is safe to visit <3.\n");
            }
        }
        else if(ch=='B'){
            printf("\t\tPlease enter the url u want to reprot : ");
            char url1[200];
            scanf("%s",url1);
            getchar();
            bloom_filter[MurmurOAAT_32(url1, SEED)] = 1;
            printf("\t\t\tWe have recorded your reported url and will warn on use this url.\n");
        }
        else if(ch=='Q'){
            break;
        }
        else{
            printf("Please enter a correct choice!!\n");
        }
    }
}