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
                        if (ch == 'B')//if you want to borrow a book
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
//function for generating random rank of node
int randomRankGenerator(void)
{
    int temp = rand();
    temp = temp % MAX_RANK;
    // printf("%d ", temp);
    return temp + 1;
}

//function for printing book name
void printing_book_name(int x, node *root)
{
    if (x == root->key)//if book number matches with key value of root
    {
        
        
        printf("%s", root->string);

        
        return;
    }
    if (x < root->key)//if book number is less than key value of root go to left of root
    {

        return printing_book_name(x, root->left);
    }
    else//if book number is more than key value of root go to left of root
    {

        return printing_book_name(x, root->right);
    }
}
//function for traversing in zip tree
void traversal(node *root)
{
   
    if (root == NULL)
    {
        
        return;
    }
    // traverse the left subtree
    traversal(root->left);

    // visit the root
    printf("%d , %d , %s\n", root->rank, root->key, root->string);

    // traverse the right subtree
    traversal(root->right);
}
//preorder traversal
void preorder(node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}
//function for searching book number 
int searchingKey(int x, node *root)
{
    if (x == root->key)//if book number matches with key value of root 
    {
        return 1;
    }

    if (x < root->key)//if book number is less  than  key value of root then go to left of root
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
    else//if book number is more  than  key value of root then go to right of root
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
//Function for insertion in ziptree
node *insert(node *x, node *root)
{

    if (root == NULL)//if root is null then make x as root
    {

        x->right = NULL;
        x->left = NULL;

        return x;
    }
    if (x->key < root->key)//if key value of x is less than key value of root then go to left of root and insert 
    {

        if (insert(x, root->left) == x)
        {
            if (x->rank < root->rank)//if rank of x is less than root's rank then insert it to left
            {

                root->left = x;
            }
            else//if rank of x is greater than root's rank then make x's right equal to root's left and x's right equal to root
            {

                root->left = x->right;
                x->right = root;

                return x;
            }
        }
    }
    else//if key value of x is greater than key value of root then go to right of root and insert
    {

        if (insert(x, root->right) == x)
        {

            if (x->rank <= root->rank)//if rank of x is less than or equal to root's rank then insert it to right
            {

                root->right = x;
            }
            else//if rank of x is greater than root's rank then make x's left equal to root's  right and x's left equal to root
            {

                root->right = x->left;
                // root->right = NULL;
                x->left = root;

                return x;
            } 
        }
    }

    return root;
}
//Function for generating a node by  allocating size of a node and passing it's key , rank string 
void Node_Genrator(int key, char book_name[])
{
    node *x;
    x = (node *)malloc(sizeof(node));
    x->key = key;
    x->rank = randomRankGenerator();
    strcpy(x->string, book_name);
    zipTree = insert(x, zipTree);
}
//Function for generating hash number
int hash_code(int key)
{
    return key % bloom_size;
}

//Function for searching a user or inserting a node of user in  linked list if user id is not present
user *user_genrate(int entry_number)
{

    if (head == NULL)//if no node is present
    {
        user *temp;
        temp = (user *)malloc(sizeof(user));//allocating memory for user node
       
        temp->entry_number = entry_number;//storing user's entry number 

        for (int i = 0; i < 701; i++)
        {
            temp->bloom_filter[i] = 0;//making all values 0 initially in the array of bloom filter
        }

        temp->read = 0;
        temp->next = NULL;
        head = temp;
        return temp;
    }
    else//if already a node is present
    {
        user *temp = head;
       
        while (temp != NULL && temp->entry_number != entry_number)//until we get null or the if the entry number is searched in the linked list
        {
            temp = temp->next;
        }
        if (temp == NULL)//entry number is not present in the linked list
        {
            user *temp2;
            temp2 = (user *)malloc(sizeof(user));//allocating memory for new node
            
            temp2->entry_number = entry_number;//storing user's entry number

            for (int i = 0; i < 701; i++)
            {
                temp2->bloom_filter[i] = 0;//making all values 0 initially in the array of bloom filter
            }
            temp2->read = 0;
            temp2->next = head;
            head = temp2;
            return temp2;
        }
        int count = 0;
       
        return temp;
    }
}