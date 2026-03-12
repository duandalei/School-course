/*
输入
10
H 9
I 1 1
D 1
D 0
H 6
I 3 6
I 4 5
I 4 5
I 3 4
D 6
输入
6 4 6 5


*/

#include <bits/stdc++.h>

using namespace std;

struct Node
{
    int data;
    Node *next;
} a[100010], *head, *tail;

int m, k, cnt;
char c;
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    head = new Node();
    head->next = NULL, tail = head;
    cin >> m;
    while (m--)
    {
        cin >> c;
        if (c == 'H')
        {
            cin >> k;
            a[++cnt].data = k;
            a[cnt].next = head->next;
            head->next = &a[cnt];
        }
        if (c == 'D')
        {
            cin >> k;
            if (k == 0)
            {
                head->next = head->next->next;
            }
            else
            {
                a[k].next = a[k].next->next;
            }
        }
        if (c == 'I')
        {
            int x;
            cin >> k >> x;
            a[++cnt].data = x;
            a[cnt].next = a[k].next;
            a[k].next = &a[cnt];
        }
    }
    head = head->next;
    while (head != NULL)
    {
        cout << head->data << " ";
        head = head->next;
    }
    return 0;
}