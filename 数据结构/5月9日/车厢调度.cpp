//题目大意:借助一个栈能否将1,2,3,....n转化为想要的顺序
#include <stdio.h>
#include <stdbool.h>

bool canReorder(int n, int arr[])
{
    int stack[n];
    int top = -1;
    int i = 1;
    int j = 0;
    while (i <= n)
    {
        stack[++top] = i;
        while (top != -1 && stack[top] == arr[j])
        {
            top--;
            j++;
        }
        i++;
    }
    return top == -1;
}

int main()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    if (canReorder(n, arr))
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
    return 0;
}