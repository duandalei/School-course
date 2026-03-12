#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct treenode
{
    char data;
    struct treenode *left;
    struct treenode *right;
} *Tree, TreeNode;

bool isempty(char s[])
{
    return strlen(s) == 0;
}
char *target_left(char s[], char left[], char c)
{
    int len = strlen(s);
    int i = 0;
    for (i = 0; i < len; i++)
    {
        if (s[i] == c)
        {
            break;
        }
        left[i] = s[i];
    }
    left[i] = '\0';
    return left;
}
char *target_right(char s[], char right[], char c)
{
    int len = strlen(s);
    int i, k = 0;
    for (i = 0; i < len; i++)
    {
        if (s[i] == c)
        {
            break;
        }
    }
    for (int j = i + 1; j < len; j++)
    {
        right[k++] = s[j];
    }
    right[k] = '\0';
    return right;
}

char target_preElement(char s1[], char s2[])
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    for (int i = 0; i < len1; i++)
    {
        for (int j = 0; j < len2; j++)
        {
            if (s1[i] == s2[j])
            {
                return s1[i];
            }
        }
    }
    return 0;
}

Tree origin_tree(Tree &T, char preOrder[], char inOrder[])
{
    if (isempty(preOrder))
    {
        return NULL;
    }
    T = (Tree)malloc(sizeof(TreeNode));
    T->data = preOrder[0];
    T->left = NULL;
    T->right = NULL;
    if (strlen(inOrder) == 1)
    {
        return T;
    }
   
    char left_inorder[100], right_inorder[100];
    target_left(inOrder, left_inorder, T->data);  
    target_right(inOrder, right_inorder, T->data);

    
    int left_inorder_count = strlen(left_inorder);

    
    char left_preorder[100], right_preorder[100];
    strncpy(left_preorder, preOrder + 1, left_inorder_count);
    left_preorder[left_inorder_count] = '\0';
    strcpy(right_preorder, preOrder + 1 + left_inorder_count);

  
    T->left = origin_tree(T->left, left_preorder, left_inorder);
    T->right = origin_tree(T->right, right_preorder, right_inorder);
    return T;
}
void postOrder(Tree T)
{
    if (T == NULL)
    {
        return;
    }
    postOrder(T->left);
    postOrder(T->right);
    printf("%c", T->data);
}
int main()
{
    char preOrder[100], inOrder[100];
    scanf("%s%s", preOrder, inOrder);
    Tree T;
    origin_tree(T, preOrder, inOrder);
    postOrder(T);
}