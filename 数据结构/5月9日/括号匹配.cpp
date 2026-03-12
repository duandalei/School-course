#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    char bracket;
    struct node *next;
} StackNode, *stack;
int main()
{
    char c;
    stack L;
    L = (stack)malloc(sizeof(StackNode));
    L->next = NULL;
    while ((c = getchar()) != '@')
    {   if(c=='('||c==')'){
        if (c == '(')
        {
            StackNode *s;
            s = (stack)malloc(sizeof(StackNode));
            s->bracket = c;
            s->next = L->next;
            L->next = s;
        }
        else
        {
            StackNode *p = L->next;
            if (p == NULL)
            {
                printf("NO");
                return 0;
            }
            if ((p->bracket == '(' && c != ')') )
            {
                printf("YES");
                return 0;
            }
            L->next = p->next;
            free(p);
        }
    }
    }
    if (L->next == NULL)
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }
    free(L);
    return 0;
}
