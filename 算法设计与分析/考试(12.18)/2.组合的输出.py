from itertools import combinations

n, r = map(int, input().split())

for c in combinations(range(1, n + 1), r):
    for x in c:
        print(f"{x:3d}", end="")
    print()


#python
"""
n, r = map(int, input().split())
comb = []

def dfs(start):
    if len(comb) == r:
        for x in comb:
            print(f"{x:3d}", end="")
        print()
        return

    for i in range(start, n + 1):
        comb.append(i)
        dfs(i + 1)
        comb.pop()

dfs(1)

"""

#c
"""
int n, r;
int comb[100];  
void dfs(int start, int len)
{
    if (len == r)
    {
        for (int i = 0; i < r; i++)
            printf("%3d", comb[i]);
        printf("\n");
        return;
    }

    for (int i = start; i <= n; i++)
    {
        comb[len] = i;
        dfs(i + 1, len + 1);
    }
}
"""

#c++
"""
int n, r;
vector<int> comb;

void dfs(int start)
{
    if (comb.size() == r)
    {
        for (int x : comb)
            cout << setw(3) << x;
        cout << '\n';
        return;
    }

    for (int i = start; i <= n; i++)
    {
        comb.push_back(i);
        dfs(i + 1);
        comb.pop_back();
    }
}
"""