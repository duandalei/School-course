#include <bits/stdc++.h>

using namespace std;
int main()
{
    int M, N;
    cin >> M >> N;
    queue<int> memory;
    unordered_set<int> wordSet;

    int lookupCount = 0; 

    for (int i = 0; i < N; i++)
    {
        int word;
        cin >> word;
        if (wordSet.find(word) == wordSet.end()) // wordSet.end()是一个无效迭代器,不指向任何元素
        {
            lookupCount++;
            if (memory.size() == M)
            {
                int oldestWord = memory.front();
                memory.pop();
                wordSet.erase(oldestWord);
            }
            memory.push(word);
            wordSet.insert(word);
        }
    }
    cout << lookupCount << endl;
    return 0;
}

