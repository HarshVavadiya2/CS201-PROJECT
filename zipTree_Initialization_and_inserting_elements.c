#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 
#define MAX_RANK 4
typedef struct Node
{
    int key;
    char string[50];
    struct Node *right, *left;
    int rank;
} node;
node* zipTree=NULL;
// zipTree = NULL;
void traversal(node *root);
node *insert(node *x, node *root);
int randomRankGenerator(void);
void Node_Genrator(int key,char book_name[]);
char *string_generator(char *book_name);
void preorder(node* root);
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
    preorder(zipTree);
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