#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 
#define MAX_RANK 4
#define bloom_size 701
#define user_size 10
int total_books = 0;
typedef struct Node
{
    int key;
    char string[50];
    struct Node *right, *left;
    int rank;
} node;
node* zipTree=NULL;
// zipTree = NULL;
typedef struct User
{
    //  char name[50];
    int entry_number;
    int bloom_filter[701];
    struct User *next;

} user;
user *head = NULL;
void traversal(node *root);
node *insert(node *x, node *root);
int randomRankGenerator(void);
void Node_Genrator(int key,char book_name[]);
char *string_generator(char *book_name);
void preorder(node* root);
int hash_code(int key);
user *user_genrate(int entry_number);
int searchingKey(int x, node *root);
int main()
{ 

     FILE *filePointer ;
     filePointer = fopen("input.txt", "r") ;
     if (filePointer==NULL)
     {
        printf("file is not opening\n");
     }
     int book_number;
     
    //  fscanf(filePointer,"%d",&book_number);
    // //  printf("%d ",book_number);
    //  Node_Genrator(book_number,);
    char book_name[50];
    
     while (fgetc(filePointer)!=EOF)
     {  
       fscanf(filePointer,"%d",&book_number);
       fscanf(filePointer,"%s",book_name);
       total_books++;
       Node_Genrator(book_number,book_name);
       
     }
     fclose(filePointer);
     
    // node *zipTree;
    // zipTree = (node *)malloc(sizeof(node));

    // zipTree = NULL;
    // node *x;
    // x = (node *)malloc(sizeof(node));
    // x->key = 6;
    // x->rank = 2;
    // inserting->right = NULL;
    // inserting->left = NULL;
    // inserting->rank = randomRankGenerator();
    // zipTree = insert(x, zipTree);
    // node *y;
    // y = (node *)malloc(sizeof(node));
    // y->key = 9;
    // y->rank = 1;
    // node *temp2;
    // temp2 = zipTree;

    // zipTree = insert(y, zipTree);
    // node *a;
    // a = (node *)malloc(sizeof(node));
    // a->key = 91;
    // a->rank = 21;
    // zipTree = insert(a, zipTree);
    // node *b;
    // b = (node *)malloc(sizeof(node));
    // b->key = 19;
    // b->rank = 331;
    // zipTree = insert(b, zipTree);
    // node *c;
    // c = (node *)malloc(sizeof(node));
    // c->key = 912;
    // c->rank = 111;
    // zipTree = insert(c, zipTree);
    traversal(zipTree);
    printf("\n");
   //preorder  (zipTree);
    printf("\n\n**%d**\n\n",total_books);
    int entry_number;
        printf("Please,Enter your entry number\n");
        scanf("%d", &entry_number);
        getchar();
        user *us = user_genrate(entry_number);
    char quit='C';
    char user_choice;
    while (quit != 'Q')
    {
        
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
        if(user_choice != 'R'){
            
        printf("If you want to borrow a book press B or If you want recommendtation of book press R\n");
        scanf("%c", &user_choice);
        getchar();
        }
        
        if (user_choice == 'B')
        {
            int book_number;
            printf("Please,enter the book number you want to borrow\n");
            scanf("%d", &book_number);
            int book_search ;
            char choice;
            book_search=searchingKey(book_number,zipTree);
            while (book_search != 1 && choice != 'E')
            {
                if (book_search == 0)
                {
                    printf("your entered book is not available\n");
                }
                printf("If you want to search another book then press A OR if you wnat to exist the press E \n");
                scanf("%c", &choice);
                getchar();
                if (choice == 'A')
                {
                    printf("Please,enter the book number you want to borrow\n");
                    scanf("%d", &book_number);
                   book_search=searchingKey(book_number,zipTree);
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
            printf("Recommende book : %d\nif u want to borrow this book then press A or press R to recommend again : ",book_number);
            scanf("%c",&user_choice);
            getchar();
            if(user_choice=='A'){

                us->bloom_filter[hash_number] = 1;
            }
            
            
            //}
        }
        
        
        if(user_choice=='A'){
            printf("If you wnat to quit enter Q Else enter C(continue)\n");
            scanf("%c",&quit);
            getchar();
        }
        
    }
    // temp2 = zipTree;
    return 0;
}
int randomRankGenerator(void)
{
    int temp = rand();
    temp = temp % MAX_RANK;
    printf("%d ", temp);
    return temp + 1;
}
void traversal(node *root)
{
    // printf(",,");
    if (root == NULL)
    {
        // printf("*");
        return;
    }
    // traverse the left subtree
    traversal(root->left);

    // visit the root
    printf("%d , %d , %s\n", root->rank, root->key, root->string);

    // traverse the right subtree
    traversal(root->right);
}
void preorder(node* root) 
{ 
    if (root != NULL) 
    { 
        printf("%d ", root->key); 
        preorder(root->left); 
        preorder(root->right);
    } 
}
int searchingKey(int x, node *root)
{
    if (x == root->key)
    {
        return 1;
    }
    if(x<root->key){
        if(root->left==NULL){
            return 0;
        }
        else{
        return searchingKey(x , root->left);
        }
    }
    else{
        if(root->right==NULL){
            return 0;
        }
        else{
        return searchingKey(x , root->right);
        }
    }
    
}
node *insert(node *x, node *root)
{

    if (root == NULL)
    {
        printf(" *%d* ", x->key);
        x->right = NULL;
        x->left = NULL;
        
        return x;
    }
    if (x->key < root->key)
    {
        printf("Hello\n");
        if (insert(x, root->left) == x)
        {
            if (x->rank < root->rank)
            {
                printf("Hello6\n");
                root->left = x;
            }
            else
            {
                printf("Hello5\n");
                root->left = x->right;
                x->right = root;
                
                return x;
            }
        }
    }
    else
    {
        printf("Hello2\n");
        if (insert(x, root->right) == x)
        {

            if (x->rank <= root->rank)
            {
                printf("Hello4\n");
                root->right = x;
            }
            else
            {
                printf("Hello3\n");
                root->right = x->left;
                // root->right = NULL;
                x->left = root;
                
                return x;
            }//good project
        }
    }
    
    return root;
}
// char *string_generator(char *book_name){
//     char *temp=book_name;
//     return temp;
// }
void Node_Genrator(int key,char book_name[]){
    node* x;
    x = (node *)malloc(sizeof(node));
    x->key = key;
    x->rank = randomRankGenerator();
    strcpy(x->string,book_name);
    zipTree = insert(x, zipTree);
  
}
int hash_code(int key)
{
    return key % bloom_size;
}
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