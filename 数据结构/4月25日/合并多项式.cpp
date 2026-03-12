#include <stdio.h>
int t[100001];
int a, b;//每次输入a和b,a代表系数,b代表幂数
int main()
{
    int n, m;
    //第一个多项式
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &a, &b);
        t[b] = a;
    }
   // 第二个多项式
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &a, &b);
        t[b] += a;
    }
    int term = 0;
    for (int i = 0; i < 100001; i++)
    {
        if (t[i] != 0)
        {
            printf("%d %d", t[i], i);
            printf("\n");
            term = 1;
        }
    }
    //如果合并后多项式为0,输出0(term巧妙的操作)
    if (term == 0)
    {
        printf("0");
    }
}