#include <stdio.h>
long long N, n = 0, sum = 0, a[10000001]; 
long long pop()
{
    long long i, t, lchild;
    a[0] = a[1];
    a[1] = a[n];
    n--;
    i = 1;
    while (i * 2 <= n) 
    {
        lchild = i * 2;
        if (lchild + 1 <= n && a[lchild + 1] < a[lchild]) 
        {
            lchild++;
        }
        if (a[i] > a[lchild])
        {
            t = a[i];
            a[i] = a[lchild];
            a[lchild] = t;
            i = lchild;
        }
        else
        {
            break;
        }
    }
    return a[0];
}
void push(long long num)
{
    long long i, t;
    n++;
    a[n] = num;
    i = n;
    while (i > 1 && a[i] < a[i / 2]) 
    {
        t = a[i];
        a[i] = a[i / 2];
        a[i / 2] = t;
        i /= 2;
    }
}
int main()
{
    long long i, num, x, y;
    scanf("%lld", &N);
    for (i = 1; i <= N; i++)
    {
        scanf("%lld", &num);
        push(num);
    }
    for (i = 1; i < N; i++)
    {
        x = pop();
        y = pop();
        push(x + y);
        sum += x + y;
    }
    printf("%lld", sum);
}