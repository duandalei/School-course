/*
输入
6
1 5 6
5 2 3
2 0 0
3 4 0
6 0 0
4 0 0

输出
1 5 2 3 4 6
2 5 4 3 1 6
2 4 3 5 6 1


*/

//构建树的一种巧妙思路
#include <stdio.h>
#include <stdlib.h>
typedef struct treenode
{
    char data;
    int left;
    int right;
} *Tree, TreeNode;
void preorder(Tree tree, int root)
{
    if (root == 0)
        return;
    printf("%d ", tree[root].data);
    preorder(tree, tree[root].left);
    preorder(tree, tree[root].right);
}

void inorder(Tree tree, int root)
{
    if (root == 0)
        return;

    inorder(tree, tree[root].left);
    printf("%d ", tree[root].data);
    inorder(tree, tree[root].right);
}

void postorder(Tree tree, int root)
{
    if (root == 0)
        return;

    postorder(tree, tree[root].left);
    postorder(tree, tree[root].right);
    printf("%d ", tree[root].data);
}

int main()
{
    int n, root = 1;
    scanf("%d", &n);
    TreeNode *tree = (Tree)malloc(sizeof(TreeNode) * (n + 1));
    for (int i = 0; i < n; i++)
    {
        int u, l, r;
        scanf("%d%d%d", &u, &l, &r);
        tree[u].data = u;
        tree[u].left = l;
        tree[u].right = r;
    }
    preorder(tree, root);
    printf("\n");
    inorder(tree, root);
    printf("\n");
    postorder(tree, root);
    printf("\n");
}