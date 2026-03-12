// #include <stdio.h>
// #include <ctype.h>
// #include <stdlib.h>

#include<bits/stdc++.h>

#define MAX_WORDS 10000
#define MAX_LEN 64

typedef struct TrieNode
{
    struct TrieNode *children[26];
} TrieNode;

TrieNode *createNode()
{
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    for (int i = 0; i < 26; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

int insertWord(TrieNode *root, const char *word)
{
    TrieNode *current = root;
    int count = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        int idx = word[i] - 'A';
        if (current->children[idx] == NULL)
        {
            current->children[idx] = createNode();
            count++;
        }
        current = current->children[idx];
    }
    return count;
}

void freeTrie(TrieNode *node)
{
    if (node == NULL)
        return;
    for (int i = 0; i < 26; i++)
    {
        if (node->children[i] != NULL)
        {
            freeTrie(node->children[i]);
        }
    }
    free(node);
}

int main()
{
    char words[MAX_WORDS][MAX_LEN];
    int wordCount = 0;
    char c;
    
    //利用getchar逐渐读取字母并合并为单词,放入words数组中
    while (wordCount < MAX_WORDS && (c = getchar()) != EOF)
    //getchar读取所有字母,直到遇到EOF,连回车也被读取,记为\n存放在缓存区
    {

        while (!isalpha(c) && c != EOF)//isalpha用来判断是不是字母
            c = getchar();
        if (c == EOF) // 当缓冲区已空且用户触发 EOF 时，getchar() 返回 EOF，但内层循环会继续执行
            break;

        int len = 0;
        while (isalpha(c) && len < MAX_LEN - 1)
        {
            words[wordCount][len++] = toupper(c);//将小写全部转化为大写
            c = getchar();
        }
        words[wordCount][len] = '\0';
        wordCount++;
    }

    TrieNode *root = createNode();
    int nodeCount = 1;

    for (int i = 0; i < wordCount; i++)
    {
        nodeCount += insertWord(root, words[i]);
    }

    freeTrie(root);

    printf("%d\n", nodeCount);
    return 0;
}


