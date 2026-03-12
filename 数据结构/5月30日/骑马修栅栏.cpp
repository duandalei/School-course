#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 501

int F;
int degree[MAX_VERTEX];
int adj[MAX_VERTEX][MAX_VERTEX];
int circuit[2100];
int circuit_pos;

void find_euler_circuit(int start)
{
    for (int i = 1; i < MAX_VERTEX; ++i)
    {
        if (adj[start][i] > 0)
        {
            adj[start][i]--;
            adj[i][start]--;
            find_euler_circuit(i);
        }
    }
    circuit[circuit_pos++] = start;
}

int main()
{
    scanf("%d", &F);
    memset(degree, 0, sizeof(degree));
    memset(adj, 0, sizeof(adj));

    for (int i = 0; i < F; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a][b]++;
        adj[b][a]++;
        degree[a]++;
        degree[b]++;
    }

    int start = 1;

    for (int i = 1; i < MAX_VERTEX; ++i)
    {
        if (degree[i] % 2 != 0)
        {
            start = i;
            break;
        }
    }

    for (int i = 1; i < MAX_VERTEX; ++i)
    {
        if (degree[i] > 0)
        {
            start = i;
            break;
        }
    }

    circuit_pos = 0;
    find_euler_circuit(start);

    for (int i = circuit_pos - 1; i >= 0; --i)
    {
        printf("%d\n", circuit[i]);
    }

    return 0;
}