#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_RANK 4
#define bloom_size 701
#define user_size 10
int total_books = 0;
int hash_code(int key)
{
    return key % bloom_size;
}

typedef struct User
{
    //  char name[50];
    int entry_number;
    int bloom_filter[701];
    struct User *next;

} user;
user *head = NULL;
user *user_genrate(int entry_number)
{

    if (head == NULL)
    {
        user *temp;
        temp = (user *)malloc(sizeof(user));
        // strcpy(temp->name, name);
        temp->entry_number = entry_number;
        for (int i = 0; i < 701; i++)
        {
            temp->bloom_filter[i] = 0;
        }
        temp->next = NULL;
        head = temp;
        return temp;
    }
    else
    {
        user *temp = head;
        int flag = 0;
        while (temp != NULL && temp->entry_number == entry_number)
        {
            temp = temp->next;
        }
        if (temp == NULL)
        {
            user *temp2;
            temp2 = (user *)malloc(sizeof(user));
            // strcpy(temp2->name, name);
            temp2->entry_number = entry_number;
            for (int i = 0; i < 701; i++)
            {
                temp2->bloom_filter[i] = 0;
            }
            temp2->next = head;
            head = temp2;
            return temp2;
        }
        int count=0;
        for (int i = 0; i < 701; i++)
            {
                if(temp->bloom_filter[i] ==1) count++;
            }
            if(count==701){
               for (int i = 0; i < 701; i++)
            {
                (temp->bloom_filter[i] =0) ;
            } 
            }
        return temp;
    }
}

int main()
{
    char quit;
    while (quit != 'Q')
    {
        int entry_number;
        printf("Please,Enter your entry number\n");
        scanf("%d", &entry_number);
        // if (head==NULL)
        // {
        //    user* temp;
        //    temp=(user *)malloc(sizeof(user));
        //     strcpy(temp->name,name);
        //     for (int i = 0; i < 701; i++)
        //     {
        //        temp->bloom_filter[i]=0;
        //     }
        //     temp->next=NULL;
        //     head=temp;

        // }
        // else
        // {
        //     user *temp = head;
        //     int flag = 0;
        //     while (temp != NULL && strcmp(temp->name, name))
        //     {
        //         temp = temp->next;
        //     }
        //     if (temp == NULL)
        //     {
        //     }
        // }
        getchar();
        user *us = user_genrate(entry_number);
        char user_choice;
        printf("If you want to borrow a book press B or If you want recommendtation of book press R\n");
        scanf("%c", &user_choice);
        if (user_choice == 'B')
        {
            int book_number;
            printf("Please,enter the book number you want to borrow\n");
            scanf("%d", &book_number);
            int book_search = 0;
            char choice;
            // search
            while (book_search != 1 && choice != 'E')
            {
                if (book_search == 0)
                {
                    printf("your entered book is not available\n");
                }
                printf("If you want to search another book then press A OR if you wnat to exist the press E \n");
                scanf("%c", &choice);
                if (choice == 'A')
                {
                    printf("Please,enter the book number you want to borrow\n");
                    scanf("%d", &book_number);
                    // SEARCH
                }
            }
            if (book_search == 1)
            {
                int hash_number = hash_code(book_number);
                us->bloom_filter[hash_number] == 1;
            }
        }
        else
        {

            // get random_book
            int random_book = (rand() % total_books) + 1;
            int hash_number = random_book;
            // if(us->bloom_filter[hash_number]==0){
            //     printf("Recommende book : ");
            //     us->bloom_filter[hash_number]=1;
            // }
            // else{

            // }
            while (us->bloom_filter[hash_number] != 0)
            {

                int random_book = (rand() % total_books) + 1;
                hash_number = random_book;
            }

            // if(us->bloom_filter[hash_number]==0){
            printf("Recommende book : ");
            us->bloom_filter[hash_number] = 1;
            //}
        }
    }
}
// int user_array[bloom_size];
// for (int i = 0; i < bloom_size; i++)
//     user_array[i] = 0;
// FILE *filepointer;
// filepointer = fopen("input.txt", "r");
// int book_number;
// while (fgetc(filepointer) != EOF)
// {
//     fscanf(filepointer, "%d", &book_number);
//     int hash_number = hash_code(book_number);
//     user_array[hash_number] = 1;
// }
// char c;
// while (c != 'Q')
// {
//     int number;
//     printf("Please,Enter the book number you want to borrow\n");
//     scanf("%d", &number);
//     if (user_array[hash_code(number)])
//     {
//         printf("I think you have borrowed this book previously\n");
//         printf("Please Enter another book number\n");
//     }
//     else
//     {
//         printf("Thank you for your interest,You successfully borrowed a book\n");
//         user_array[hash_code(number)] = 1;
//     }
//     getchar();
//     printf("For quit enter Q Else C\n");
//     scanf("%c", &c);
// }

// fclose(filepointer);
