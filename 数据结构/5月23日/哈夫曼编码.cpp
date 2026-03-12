#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 27 // 26大写字母 + '_'

typedef struct
{
    int freq;
} Node;

typedef struct
{
    Node *data;
    int size;
    int capacity;
} MinHeap;

void swap(Node *a, Node *b)
{
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap *heap, int index)
{
    while (index > 0 && heap->data[(index - 1) / 2].freq > heap->data[index].freq)
    {
        swap(&heap->data[(index - 1) / 2], &heap->data[index]);
        index = (index - 1) / 2;
    }
}

void heapifyDown(MinHeap *heap, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left].freq < heap->data[smallest].freq)
        smallest = left;
    if (right < heap->size && heap->data[right].freq < heap->data[smallest].freq)
        smallest = right;

    if (smallest != index)
    {
        swap(&heap->data[index], &heap->data[smallest]);
        heapifyDown(heap, smallest);
    }
}

void push(MinHeap *heap, int freq)
{
    if (heap->size == heap->capacity)
    {
        heap->capacity *= 2;
        heap->data = (Node*)realloc(heap->data, heap->capacity * sizeof(Node));
    }
    heap->data[heap->size].freq = freq;
    heapifyUp(heap, heap->size);
    heap->size++;
}

int pop(MinHeap *heap)
{
    if (heap->size == 0)
        return -1;
    int val = heap->data[0].freq;
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return val;
}

void initHeap(MinHeap *heap, int capacity)
{
    heap->data = (Node*)malloc(capacity * sizeof(Node));
    heap->size = 0;
    heap->capacity = capacity;
}

void freeHeap(MinHeap *heap)
{
    free(heap->data);
}

int main()
{
    char line[101];
    while (fgets(line, sizeof(line), stdin))
    {
        line[strcspn(line, "\n")] = '\0'; // 去除换行符
        if (strcmp(line, "END") == 0)
            break;

        int freq[MAX_CHARS] = {0};
        int len = strlen(line);
        if (len == 0)
            continue;

        // 统计字符频率
        for (int i = 0; i < len; i++)
        {
            char c = line[i];
            int idx = (c == '_') ? 26 : c - 'A';
            freq[idx]++;
        }

        // 计算不同字符的数量
        int unique = 0;
        for (int i = 0; i < MAX_CHARS; i++)
        {
            if (freq[i] > 0)
                unique++;
        }

        int original = len * 8;
        int compressed;

        if (unique == 0)
        {
            continue;
        }
        else if (unique == 1)
        {
            compressed = len * 1;
        }
        else
        {
            MinHeap heap;
            initHeap(&heap, unique);

            for (int i = 0; i < MAX_CHARS; i++)
            {
                if (freq[i] > 0)
                {
                    push(&heap, freq[i]);
                }
            }

            compressed = 0;
            while (heap.size > 1)
            {
                int a = pop(&heap);
                int b = pop(&heap);
                int sum = a + b;
                compressed += sum;
                push(&heap, sum);
            }
            freeHeap(&heap);
        }

        double ratio = (double)original / compressed;
        printf("%d %d %.1f\n", original, compressed, ratio);
    }
    return 0;
}