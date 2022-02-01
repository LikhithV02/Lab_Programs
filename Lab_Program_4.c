#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * This program converts Infix expression to Postfix expression
 */

typedef struct
{
  size_t capacity;
  int top;
  char *elem;
} stack_t;

stack_t *create(size_t capacity);
void push(stack_t *s, char elem);
char pop(stack_t *s);
int isoperator(char sym);
int precedence(char sym);
void InfixtoPostfix(char *infix, char *postfix);

/**
 * Function to create a stack
 **/

stack_t *create(size_t capacity)
{
  stack_t *stack = malloc(sizeof(stack_t));
  if (stack != NULL)
  {
    stack->capacity = capacity;
    stack->elem = (char *)calloc(capacity, sizeof(char));
    if (stack->elem != NULL)
    {
      stack->top = -1;
    }
    else
    {
      stack = NULL;
    }
  }
  return stack;
}

/**
 * Function to push elements onto stack
 **/

void push(stack_t *s, char elem)
{
  s->elem[++s->top] = elem;
}

/**
 * Function to pop elements from stack
 **/

char pop(stack_t *s)
{
  return s->elem[s->top--];
}

/**
 * Function to check whether the element is an operator
 **/

int isoperator(char sym)
{
  if (sym == '^' || sym == '*' || sym == '/' || sym == '+' || sym == '-' || sym == '%')
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
 * Function to determine the precedence of the operator
 **/

int precedence(char sym)
{
  if (sym == '^')
  {
    return 3;
  }
  else if (sym == '*' || sym == '/' || sym == '%')
  {
    return 2;
  }
  else if (sym == '+' || sym == '-')
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
 * Function to convert infix expression to postfix expression
 **/

void InfixtoPostfix(char *infix, char *postfix)
{
  int length;
  int i = 0;
  int j = 0;
  char element;

  stack_t *stack = NULL;
  length = strlen(infix);
  stack = create(length);
  push(stack, '(');

  while (infix[i] != '\0')
  {
    if (infix[i] == '(')
    {
      push(stack, infix[i]);
    }
    else if (isalnum(infix[i]))
    {
      postfix[j++] = infix[i];
    }
    else if (isoperator(infix[i]) == 1)
    {
      element = pop(stack);
      while (isoperator(element) == 1 && (precedence(element) >= precedence(infix[i])))
      {
        postfix[j++] = element;
        element = pop(stack);
      }
      push(stack, element);
      push(stack, infix[i]);
    }
    else if (infix[i] == ')')
    {
      element = pop(stack);
      while (element != '(')
      {
        postfix[j++] = element;
        element = pop(stack);
      }
    }
    else
    {
      printf("Invalid infix Expression.\n");
      exit(0);
    }
    i++;
  }

  postfix[j] = '\0';
  printf("Postfix string : %s\n", postfix);
  free(stack);
  free(stack->elem);
}

int main(int argc, char *argv[argc + 1])
{
  char infix[100];
  strncpy(infix, argv[1], 100);
  char postfix[100];
  strcat(infix, ")");
  InfixtoPostfix(infix, postfix);
  return 0;
}