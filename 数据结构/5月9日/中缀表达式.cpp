#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
int numbers[100];
char operators[100];
int num, ope;
// 判断是否是运算符
bool isoperator(char c)
{
    switch (c)
    {
    case '+':
    case '-':
    case '*':
    case '/':
        return true;
    default:
        return false;
    }
}

// 判断是否是阿拉伯数字
bool isnumber(char c)
{
    return c >= '0' && c <= '9';
}
// 1.判断圆括号是否匹配
bool bracketCheck1(char arry[])
{
    int len = strlen(arry);
    int k = 0; // k用来模拟栈
    for (int i = 0; i < len; i++)
    {
        if (arry[i] == '(')
        {
            k++;
        }
        if (arry[i] == ')')
        {
            k--;
        }
        if (k < 0)
            return false;
    }
    if (k == 0)
    {
        return true;
    }
    return false;
}
// 2.判断中缀表达式中是否只含有运算符和阿拉伯数字和括号
bool number_operatorCheck(char arry[])
{
    int len = strlen(arry);
    for (int i = 0; i < len; i++)
    {
        if (!isoperator(arry[i]) && !isnumber(arry[i]) && arry[i] != '(' && arry[i] != ')')
        {
            return false;
        }
    }
    return true;
}
// 3.判断操作符左右元素是否合法
bool adjacent_operatorCheck(char arry[])
{
    int len = strlen(arry);
    for (int i = 0; i < len; i++)
    {
        if (arry[i] == '-')
        { //-当作负号来使用而不是减号
            if (i == 0 || arry[i - 1] == '(')
            {
                i++;
            }
        }
        if (isoperator(arry[i]))
        { // 第一个字符是除"-"号外的运算符,最后一个字符是运算符
            if (i == 0 || i == len - 1)
            {
                return false;
            }
            if (isoperator(arry[i - 1]) || isoperator(arry[i + 1]))
            { // 两个及以上的运算符连在一起
                return false;
            }
            if (arry[i - 1] == '(' || arry[i + 1] == ')')
            { // 出现'('后直接连接运算符,运算符后直接连接')'
                return false;
            }
        }
    }
    return true;
}
// 4.两个括号直接相连,或者括号里没东西
bool bracketCheck2(char arry[])
{
    int len = strlen(arry);
    for (int i = 0; i < len; i++)
    {
        if (arry[i] == '(' && arry[i + 1] == ')')
        {
            return false;
        }
        if (arry[i] == ')' && arry[i + 1] == '(')
        {
            return false;
        }
    }
    return true;
}

// 以上为判断四则表达式是否正确所用函数,以下为计算中缀表达式值的函数(共用isnumber函数)
int operators_compare(char c)
{
    switch (c)
    {
    case '+':
        return 10;
    case '-':
        return 10;
    case '*':
        return 20;
    case '/':
        return 20;
    default:
        return 5;
    }
}

void back_num(int operator_numbers[], int &index, char c)
{
    if (index < 2)
        return;
    if (c == '+')
    {
        int term = operator_numbers[index] + operator_numbers[index - 1];
        index--;
        operator_numbers[index] = term;
    }
    // 除了"+"和"*",其余的要注意顺序
    if (c == '-')
    {
        int term = operator_numbers[index - 1] - operator_numbers[index];
        index--;
        operator_numbers[index] = term;
    }
    if (c == '*')
    {
        int term = operator_numbers[index] * operator_numbers[index - 1];
        index--;
        operator_numbers[index] = term;
    }
    if (c == '/')
    {    if(operator_numbers[index]==0){
        printf("no");
        exit(EXIT_FAILURE);
    }
        int term = operator_numbers[index - 1] / operator_numbers[index];
        index--;
        operator_numbers[index] = term;
    }
}

int final_target(char s[])
{
    int len = strlen(s);
    int i = 0;
    while (i < len)
    {
        if (isnumber(s[i]))
        {
            // 修改：解析多位数字
            int val = 0;
            while (i < len && isnumber(s[i]))
            {
                val = val * 10 + (s[i] - '0');
                i++;
            }
            i--; // 回退一步，因为外层循环会增加i
            numbers[++num] = val;
        }
        else
        {
            if (s[i] == '(')
            {
                operators[++ope] = s[i];
            }
            if (s[i] == ')')
            {
                while (ope > 0 && operators[ope] != '(')
                {
                    back_num(numbers, num, operators[ope]);
                    ope--;
                }
                if (ope > 0)
                    ope--; // 弹出左括号
            }
            else
            {
                // 修改：正确处理运算符优先级
                while (ope > 0 && operators_compare(s[i]) <= operators_compare(operators[ope]))
                {
                    back_num(numbers, num, operators[ope]);
                    ope--;
                }
                operators[++ope] = s[i];
            }
        }
        i++;
    }
    
    while (ope > 0)
    {
        back_num(numbers, num, operators[ope]);
        ope--;
    }
    return numbers[1];
}

int main()
{
    char s[200];
    scanf("%s", s);
    if (bracketCheck1(s) && number_operatorCheck(s) && adjacent_operatorCheck(s) && bracketCheck2(s))
    {
        int target = final_target(s);
        printf("%d", target);
        return 0;
    }
    printf("no");
    return 0;
}
