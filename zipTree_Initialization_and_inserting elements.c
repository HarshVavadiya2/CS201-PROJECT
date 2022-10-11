#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_RANK 4
typedef struct Node
{
    int key;
    struct Node *right, *left;
    int rank;
} node;
void traversal(node *root);
node *insert(node *x, node *root);
int randomRankGenerator(void);
int main()
{
    node *zipTree;
    // zipTree = (node *)malloc(sizeof(node));

    zipTree = NULL;
    node *x;
    x = (node *)malloc(sizeof(node));
    x->key = 6;
    x->rank = 2;
    // inserting->right = NULL;
    // inserting->left = NULL;
    // inserting->rank = randomRankGenerator();
    zipTree = insert(x, zipTree);
    node *y;
    y = (node *)malloc(sizeof(node));
    y->key = 9;
    y->rank = 1;
    node *temp2;
    temp2 = zipTree;

    zipTree = insert(y, zipTree);
    node *a;
    a = (node *)malloc(sizeof(node));
    a->key = 91;
    a->rank = 21;
    zipTree = insert(a, zipTree);
    node *b;
    b = (node *)malloc(sizeof(node));
    b->key = 19;
    b->rank = 331;
    zipTree = insert(b, zipTree);
    node *c;
    c = (node *)malloc(sizeof(node));
    c->key = 912;
    c->rank = 111;
    zipTree = insert(c, zipTree);
    traversal(zipTree);

    temp2 = zipTree;
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
    printf("%d , %d\n", root->rank, root->key);

    // traverse the right subtree
    traversal(root->right);
}
node *insert(node *x, node *root)
{

    if (root == NULL)
    {
        printf(" *%d* ", x->key);
        x->right = NULL;
        x->left = NULL;
        // int randomRank = z;
        // x->rank = randomRank;
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
            }
        }
    }
    return root;
}