/*
题目大意:
输入二叉树的高度和第几个下落的小球
小球从根结点进行下落,如果当前结点是false就向左下坠,为true则向右下坠,每次下坠会改变当前结点状态
输出最后下落到的叶结点

*/

#include <stdio.h>
void change(int arry[], int n)
{
    int i = 1;
    while (i < n)
    {
        if (arry[i] == 0)
        {
            arry[i] = 1;
            i = i * 2;
        }
        else if (arry[i] == 1)
        {
            arry[i] = 0;
            i = i * 2 + 1;
        }
    }
}

void print(int arry[], int n)
{
    int i = 1;
    int target;
    while (i < n)
    {
        if (arry[i] == 0)
        {
            arry[i] = 1;
            target = i;
            i = i * 2;
        }
        else if (arry[i] == 1)
        {
            arry[i] = 0;
            target = i;
            i = i * 2 + 1;
        }
    }
    printf("%d", target);
}

int main()
{

    int deepth, I; //,deepth表示满二叉树的高度I表示第几个小球下落
    scanf("%d%d", &deepth, &I);
    int total = 1;
    for (int i = 0; i < deepth; i++)
    {
        total *= 2;
    }
    int visited[total];
    for (int i = 0; i < total; i++)
    {
        visited[i] = 0;
    }

    for (int i = 1; i <= I - 1; i++)
    {
        change(visited, total);
    }
    print(visited, total);
}