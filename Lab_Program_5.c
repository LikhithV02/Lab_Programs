// Evaluation of Suffix Expression
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX 50
int stack[MAX];
char post[MAX];
int top = -1;
/*FUNCTION PROTOYPE */
void pushstack(int tmp);
void calculator(char c);
int main()
{
    int i;
    printf("Insert a postfix notation :: ");
    scanf("%s", post);
    for (i = 0; i < strlen(post); i++)
    {
        if (post[i] >= '0' && post[i] <= '9')
        {
            pushstack(i);
        }
        if (post[i] == '+' || post[i] == '-' || post[i] == '*' || post[i] == '/' || post[i] == '^')
        {
            calculator(post[i]);
        }
    }
    printf("\n\nResult :: %d", stack[top]);
    return 0;
}
void pushstack(int tmp)
{
    top++;
    stack[top] = (int)(post[tmp] - 48);
}
void calculator(char c)
{
    int a, b, ans;
    a = stack[top];
    stack[top] = '\0';
    top--;
    b = stack[top];
    stack[top] = '\0';
    top--;
    switch (c)
    {
    case '+':
        ans = b + a;
        break;
    case '-':
        ans = b - a;
        break;
    case '*':
        ans = b * a;
        break;
    case '/':
        ans = b / a;
        break;
    case '^':
        ans = pow(b, a);
        break;
    default:
        ans = 0;
    }
    top++;
    stack[top] = ans;
}
//4B Towers of Hanoi
#include <stdio.h>
void towers(int, char, char, char);
int main()
{
    int num;
    printf("Enter the number of disks : ");
    scanf("%d", &num);
    printf("The sequence of moves involved in the Tower of Hanoi are :\n");
    towers(num, 'A', 'C', 'B');
    return 0;
}
void towers(int num, char frompeg, char topeg, char auxpeg)
{
    if (num == 1)
    {
        printf("\n Move disk 1 from peg %c to peg %c", frompeg, topeg);
        return;
    }
    towers(num - 1, frompeg, auxpeg, topeg);
    printf("\n Move disk %d from peg %c to peg %c", num, frompeg, topeg);
    towers(num - 1, auxpeg, topeg, frompeg);
}