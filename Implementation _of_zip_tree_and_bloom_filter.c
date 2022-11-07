#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_RANK 4//maximum rank of the zip tree element 
#define bloom_size 701//size of user bloom filter
#define user_size 10
int max_book_number = 0;//Intializeing maximum book number
//Defining node of zip tree for store element
typedef struct Node
{
    int key;//store book number
    char string[50];//store book name
    struct Node *right, *left;//right will point right node of ziptree and left will point left node 
    int rank;//store rank of node
} node;

node *zipTree = NULL; //ziptree is a pointer which will point to the root of the zip tree

//Defining structure for the user 
typedef struct User
{
    int entry_number;//store entry number of an user
    int read;//read will store how many book user has read
    int bloom_filter[701];//bloom filter of user
    struct User *next;//this will point the next user in linked list

} user;
void printing_book_name(int x, node *root);
user *head = NULL;
void traversal(node *root);
node *insert(node *x, node *root);
int randomRankGenerator(void);
void Node_Genrator(int key, char book_name[]);
char *string_generator(char *book_name);
void preorder(node *root);
int hash_code(int key);
user *user_genrate(int entry_number);
int searchingKey(int x, node *root);
int main()
{
    double time_spent = 0.0;//for calculating the execution time
    clock_t begin = clock();//clock starts

    FILE *filePointer;//file pointer which point to the input file
    filePointer = fopen("input.txt", "r");
    if (filePointer == NULL)
    {
        printf("file is not opening\n");
    }
    int book_number_input;//store book number from input file
    char book_name[50];//store book name from input file
    // int kuch = 0;

    while (fgetc(filePointer) != EOF)
    {
        fscanf(filePointer, "%d", &book_number_input);//scanf book number from input file
        fscanf(filePointer, "%s", book_name);//scanf book name from file

        if (max_book_number < book_number_input)//To find maximum numberth of book
        {
            max_book_number = book_number_input;
        }

        Node_Genrator(book_number_input, book_name);//This will genrate node of zip tree
    }
    fclose(filePointer);//file will close

    clock_t end = clock();//clock ends
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The execution time for creating zipTree is %f.\n",time_spent);
    
    char ch = 'A';
    int book_search;//for search book
    int book_number;//for store book number
    while (1)
    {
        int entry_number;//store entry number of user
        printf("\nPlease,Enter your entry number\n");
        scanf("%d", &entry_number);
        getchar();

        user *us = user_genrate(entry_number);//us will point user ,if user is new than use will point that user otherwise it will point to existing user

        printf("\nIf you want to borrow a book press B or If you want recommendtation of book press R\n");
        scanf("%c", &ch);
        getchar();
        while (ch != 'Q')//if user will press Q then loop will break out
        {
           
            if (ch == 'B')//if user choose B (for borrow)
            {

                printf("\nPlease,enter the book number you want to borrow\n");
                scanf("%d", &book_number);
                getchar();

                book_search = searchingKey(book_number, zipTree);//book serach store book number using searching key that user want to borrow
                while (ch == 'B')
                {
                    if (book_search == 0)//if book is not found or not present in storage
                    {
                        printf("\nYour entered book is not available\n");
                        printf("If you want to search another book then press B OR if you wnat to exit the press Q\n");
                        scanf("%c", &ch);
                        getchar();
                        if (ch == 'B')
                        {
                            printf("\nPlease,enter the book number you want to borrow\n");
                            scanf("%d", &book_number);
                            getchar();
                            book_search = searchingKey(book_number, zipTree);
                        }
                    }
                    else//if book is found
                    {
                        printf("Borrowed book name : ");
                        printing_book_name(book_number,zipTree);//this function will print book that user wnat to borrow
                        printf("\nSuccesfully borrowed\n");
                        int hash_number = hash_code(book_number);//hash number store hash number for update bloom filter
                        if (us->bloom_filter[hash_number] == 0)//if index of bloom filter corresponding to hashnumber is eqaul to 0 then reset bloom filter 
                        {
                            us->read++;
                            float percent = (us->read / max_book_number) * 100;
                            if (percent >= 90)
                            {
                                for (int i = 0; i < 701; i++)
                                {
                                    us->bloom_filter[i] = 0;
                                }
                                us->read = 1;
                                printf("Bloom Filter has been reset(your history of read books have been deleted)\n");
                            }
                        }
                        us->bloom_filter[hash_number] = 1;//otherwise update to 1 means user has borrow that book

                        printf("If you want to borrow book then press B OR If you want recommendtation of book press R OR if you wnat to exit the press Q\n");
                        scanf("%c", &ch);
                        getchar();
                        break;
                    }
                }
            }
            else if (ch == 'R')//if user choose R for book recommandtation
            {
                int checking = 0;//Checking is recommanded book is present or not
                int random_book;
                while (checking == 0)//if checking is 1 that means recommanded is present
                {
                    random_book = (rand() % max_book_number) + 1;//random number will store randome book number
                    if (searchingKey(random_book, zipTree) == 1)
                    {
                        checking++;
                    }
                }
                int hash_number = hash_code(random_book);//hash number store hash number for update bloom filter
                while (us->bloom_filter[hash_number] == 1)//if bloom_filter[hash_number] is 1 means that book is already borrow by user 
                {

                    checking = 0;
                    while (checking == 0)
                    {

                        random_book = (rand() % max_book_number) + 1;
                        if (searchingKey(random_book, zipTree) == 1)
                        {
                            checking++;
                        }
                    }
                    hash_number = hash_code(random_book);
                }
                printf("Recommended book number : %d\nRecommended book name : ", random_book);
                printing_book_name(random_book,zipTree);
                printf("\nIf u want to borrow this book then press B or press R to recommend again : ");
                scanf("%c", &ch);
                getchar();
                if (ch == 'B')
                {
                    printf("Succesfully borrowed\n");

                    us->read++;
                    float percent = (us->read / max_book_number) * 100;
                    if (percent >= 90)
                    {
                        for (int i = 0; i < 701; i++)
                        {
                            us->bloom_filter[i] = 0;
                        }
                        us->read = 1;
                        printf("Bloom Filter has been reset(your history of read books have been deleted)\n");
                    }
                    us->bloom_filter[hash_number] = 1;
                    printf("\nIf you want to borrow book then press B OR If you want recommendtation of book press R OR if you wnat to exit the press Q\n");
                    scanf("%c", &ch);
                    getchar();
                }
            }
            else
            {
                printf("Please enter the correct choice!!\n");
                scanf("%c", &ch);
                getchar();
            }
        }
    }
    // temp2 = zipTree;
    return 0;
}
int randomRankGenerator(void)
{
    int temp = rand();
    temp = temp % MAX_RANK;
    // printf("%d ", temp);
    return temp + 1;
}
void printing_book_name(int x, node *root)
{
    if (x == root->key)
    {
        
        
        printf("%s", root->string);

        
        return;
    }
    if (x < root->key)
    {

        return printing_book_name(x, root->left);
    }
    else
    {

        return printing_book_name(x, root->right);
    }
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
void preorder(node *root)
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
    if (x < root->key)
    {
        if (root->left == NULL)
        {
            return 0;
        }
        else
        {
            return searchingKey(x, root->left);
        }
    }
    else
    {
        if (root->right == NULL)
        {
            return 0;
        }
        else
        {
            return searchingKey(x, root->right);
        }
    }
}
node *insert(node *x, node *root)
{

    if (root == NULL)
    {

        x->right = NULL;
        x->left = NULL;

        return x;
    }
    if (x->key < root->key)
    {

        if (insert(x, root->left) == x)
        {
            if (x->rank < root->rank)
            {

                root->left = x;
            }
            else
            {

                root->left = x->right;
                x->right = root;

                return x;
            }
        }
    }
    else
    {

        if (insert(x, root->right) == x)
        {

            if (x->rank <= root->rank)
            {

                root->right = x;
            }
            else
            {

                root->right = x->left;
                // root->right = NULL;
                x->left = root;

                return x;
            } // good project
        }
    }

    return root;
}
// char *string_generator(char *book_name){
//     char *temp=book_name;
//     return temp;
// }
void Node_Genrator(int key, char book_name[])
{
    node *x;
    x = (node *)malloc(sizeof(node));
    x->key = key;
    x->rank = randomRankGenerator();
    strcpy(x->string, book_name);
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
        temp->read = 0;
        temp->next = NULL;
        head = temp;
        return temp;
    }
    else
    {
        user *temp = head;
        // int flag = 0;
        while (temp != NULL && temp->entry_number != entry_number)
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
            temp2->read = 0;
            temp2->next = head;
            head = temp2;
            return temp2;
        }
        int count = 0;
        // for (int i = 0; i < 701; i++)
        // {
        //     if (temp->bloom_filter[i] == 1)
        //         count++;
        // }
        // if (count == 701)
        // {
        //     for (int i = 0; i < 701; i++)
        //     {
        //         (temp->bloom_filter[i] = 0);
        //     }
        // }
        // temp->read = 0;
        return temp;
    }
}