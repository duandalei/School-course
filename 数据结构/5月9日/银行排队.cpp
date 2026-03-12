//大意:有m个银行窗口,total表示有total对arrive和time数据,arrive表示每个人到来时间,time表示每个处理业务的时间,求出所有人平均等待时间
//例如输入:2 6 1 3 4 1 5 3 9 2 13 4 13 3    输出 0.00
#include <stdio.h>
int main()
{
    int m, total;
    scanf("%d%d", &m, &total);
    int window[m];
    for (int i = 0; i < m; i++)
    {
        window[i] = 0;
    }
    int arrive, time;
    double sum = 0;
    for (int i = 0; i < total; i++)
    {
        scanf("%d%d", &arrive, &time);
        int minIndex = 0;        // minIndex是当前minTime所对应的窗口编号
        int minTime = window[0]; // minTime是当前所有窗口中需要等待时间最少的
        for (int j = 1; j < m; j++)
        {
            if (window[j] < minTime)
            {
                minIndex = j;
                minTime = window[j];
            }
        }
        if (arrive >= window[minIndex])
        {
            window[minIndex] = arrive + time;
        }
        else
        {
            sum += window[minIndex] - arrive;
            window[minIndex] += time;
        }
    }
    double avg = sum / total;
    printf("%.2f\n", avg);

    return 0;
}