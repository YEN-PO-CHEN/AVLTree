#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
bool first_node = true;
typedef struct AVLTree
{
    char phone[11];
    char name[100];
    int height;
    struct AVLTree *left;
    struct AVLTree *right;
} Tree;
Tree *create_Tree(char *Name, char *Phone)
{
    Tree *now = (Tree *)malloc(sizeof(Tree));
    now->left = now->right = NULL;
    now->height = 1;
    strncpy(now->phone, Phone, 10);
    strncpy(now->name, Name, strlen(Name));
    return now;
}
int node_null(Tree *node) { return node ? node->height : 0; }
int high(Tree *Left, Tree *Right)
{
    int l = node_null(Left);
    int r = node_null(Right);
    return l > r ? l : r;
}
void Left_Rotation(Tree **Head)
{
    Tree *temp = (*Head)->right;
    (*Head)->right = temp->left;
    temp->left = (*Head);
    (*Head)->height = high((*Head)->left, (*Head)->right) + 1;
    temp->height = high(temp->left, temp->right) + 1;
    (*Head) = temp;
}
void Right_Rotation(Tree **Head)
{
    Tree *temp = (*Head)->left;
    (*Head)->left = temp->right;
    temp->right = (*Head);
    (*Head)->height = high((*Head)->left, (*Head)->right) + 1;
    temp->height = high(temp->left, temp->right) + 1;
    (*Head) = temp;
}
Tree *AVL_Insert(Tree *Head, char *Name, char *Phone)
{
    if (!Head)
        return create_Tree(Name, Phone);
    int a = strcmp(Name, Head->name);
    if (a > 0)
        Head->right = AVL_Insert(Head->right, Name, Phone);
    else if (a < 0)
        Head->left = AVL_Insert(Head->left, Name, Phone);
    Head->height = high(Head->left, Head->right) + 1;
    int change = node_null(Head->left) - node_null(Head->right);
    if (change > 1) //對Head而言 左邊比右邊多2層以上
    {
        if (node_null(Head->left->left) > node_null(Head->left->right)) //對Head而言 左邊比右邊多
            Right_Rotation(&Head);
        else //對Head而言 左邊比右邊少
        {
            Left_Rotation(&(Head->left));
            Right_Rotation(&Head);
        }
    }
    else if (change < -1)
    {
        if (node_null(Head->right->left) > node_null(Head->right->right))
        {
            Right_Rotation(&(Head->right));
            Left_Rotation(&Head);
        }
        else
            Left_Rotation(&Head);
    }
    return Head;
}
void PreOrder_AVL(Tree *Current)
{
    if (Current)
    {
        if (first_node)
            first_node = false;
        else
            printf(" ");
        printf("%s", Current->name);
        PreOrder_AVL(Current->left);
        PreOrder_AVL(Current->right);
    }
}
bool D_0 = false;
void search(Tree **Head, char *Name)
{
    Tree *temp = *Head;
    while (1) //string compare
    {
        if (temp == NULL)
        {
            if (*Head == NULL)
            {
                if (D_0)
                    printf("\n");
                else
                    D_0 = true;
            }
            else
                printf("\n");
            printf("%s", Name);
            printf(" null");
            break;
        }
        int a = strcmp(Name, temp->name);
        if (a == 0)
        {
            printf("\n%s ", Name);
            for (int i = 0; i < 10; ++i)
                printf("%c", (temp->phone)[i]);
            break;
        }
        if (a > 0)
            temp = temp->right;
        if (a < 0)
            temp = temp->left;
    }
}
int main()
{
    Tree *head = NULL;
    int mode = 0;
    while (1)
    {
        char Input[100];
        if (scanf("%s", Input) == EOF)
            return 0;
        if (Input[1] == '\0')
        {
            switch (Input[0])
            {
            case 'D':
                mode = 0;
                break;
            case 'S':
                mode = 1;
                if (!head)
                    first_node = false;
                PreOrder_AVL(head);
                first_node = true;
                break;
            case 'E':
                return 0;
            }
        }
        else
        {
            char Phone[100];
            char Name[1000];
            switch (mode)
            {
            case 0:
                scanf("%s", Phone);
                head = AVL_Insert(head, Input, Phone);
                break;
            case 1:
                search(&head, Input);
                break;
            }
        }
    }
}