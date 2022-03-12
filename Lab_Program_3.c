#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define CHOICE_CREATE 1
#define CHOICE_DISPLAY 2
#define CHOICE_PUSH 3
#define CHOICE_POP 4
#define CHOICE_PALINDROME 5
#define CHOICE_EXIT 6
#define ERROR INT_MIN
#define SUCCESS 0
/**
 * This program implements a menu driven task to perform
 * operations such as push, pop, demonstrate overflow and underflow
 * and check for palindrome on STACK.
 **/
unsigned int menu()
{
    unsigned int choice = CHOICE_EXIT + 1;
    while (choice > CHOICE_EXIT)
    {
        printf("\nEnter your choice:\n");
        printf("\t %u - Create Stack\n", CHOICE_CREATE);
        printf("\t %u - Display Stack Elements\n", CHOICE_DISPLAY);
        printf("\t %u - Push an element onto Stack\n", CHOICE_PUSH);
        printf("\t %u - Pop an element from the Stack\n", CHOICE_POP);
        printf("\t %u - Check whether palindrome\n", CHOICE_PALINDROME);
        printf("\t %u - Exit\n", CHOICE_EXIT);
        printf("\t choice: ");
        scanf("%d", &choice);
        if (choice > CHOICE_EXIT)
        {
            printf("ERROR: Invalid Choice\n");
        }
    }
    return choice;
}

// Initialising the struct

typedef struct
{
    size_t capacity;
    int top;
    int *elem;
} stack_t;

stack_t *create(size_t capacity);
int push(stack_t *s, int elem);
int pop(stack_t *s);
bool isempty(stack_t *s);
bool isfull(stack_t *s);
int palindrome(char *string);
int fn_exit(stack_t *s);

// Function to create a STACK
stack_t *create(size_t capacity)
{
    stack_t *stack = malloc(sizeof(stack_t));
    if (stack != NULL)
    {
        stack->capacity = capacity;
        stack->elem = (int *)calloc(capacity, sizeof(int));
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

// Function to display elements present in the STACK
void display(stack_t *s)
{
    if (isempty(s))
    {
        printf("\n\t Stack is empty\n");
    }
    else
    {
        printf("\n");
        printf("\t");
        for (size_t i = 0; i <= s->top; i++)
        {
            printf(" %d ", s->elem[i]);
        }
        printf("\n");
    }
}

// Function to check if STACK is full
bool isfull(stack_t *s)
{
    if (s->top == s->capacity - 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Function to push a element on to the STACK
int push(stack_t *s, int elem)
{
    s->elem[++s->top] = elem;
    return SUCCESS;
}

// Function to check if STACK is empty
bool isempty(stack_t *s)
{
    if (s->top == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Function to pop a element on to the STACK
int pop(stack_t *s)
{
    if (isempty(s))
    {
        printf("\n\t Stack underflow\n");
        return ERROR;
    }
    return s->elem[s->top--];
}

// Function to check for palindrome
int palindrome(char *string)
{
    int length;
    int pop_p;
    stack_t *stack_p = NULL;
    length = strlen(string);
    if (length != 0)
    {
        stack_p = create(length);
        for (int i = 0; i < length; i++)
        {
            push(stack_p, string[i]);
        }
        for (int i = 0; i < length; i++)
        {
            pop_p = pop(stack_p);
            if (pop_p != string[i])
            {
                return 0;
            }
            return 1;
        }
    }
    free(stack_p);
    free(stack_p->elem);
}

// Function to free memory allocated to STACK
int fn_exit(stack_t *s)
{
    if (s != NULL)
    {
        free(s);
        free(s->elem);
        return SUCCESS;
    }
    return ERROR;
}

int main()
{
    size_t capacity;
    stack_t *stack = NULL;
    int status;
    int elem;
    char string[100];
    size_t choice;
    while (true)
    {
        choice = menu();
        switch (choice)
        {
        case CHOICE_CREATE:
            if (stack != NULL)
            {
                printf("\n\t Stack already exists\n");
            }
            else
            {
                printf("\n\t Enter stack size : ");
                scanf("%zu", &capacity);
                stack = create(capacity);
            }
            break;
        case CHOICE_DISPLAY:
            if (stack == NULL)
            {
                printf("\n\t Create a stack.\n");
                continue;
            }
            else
            {
                display(stack);
            }
            break;
        case CHOICE_PUSH:
            if (stack == NULL)
            {
                printf("\n\t Create a stack.\n");
                continue;
            }
            else
            {
                if (isfull(stack))
                {
                    printf("\n\t Stack overflow\n");
                }
                else
                {
                    printf("\n\t Enter the element to be pushed onto the stack : ");
                    scanf("%d", &elem);
                    status = push(stack, elem);
                    if (status == SUCCESS)
                    {
                        printf("\t %d has been pushed onto the stack\n", elem);
                    }
                }
            }
            break;
        case CHOICE_POP:
            if (stack == NULL)
            {
                printf("\n\t Create a stack.");
                continue;
            }
            else
            {
                status = pop(stack);
                if (status != ERROR)
                {
                    printf("\n\t %d has been popped from the stack\n", status);
                }
            }
            break;
        case CHOICE_PALINDROME:
            printf("\n\t Enter a string of characters : ");
            scanf("%s", string);
            status = palindrome(string);
            if (status == 1)
            {
                printf("\n\t It is a palindrome.\n");
            }
            else
            {
                printf("\n\t It is not a palindrome.\n");
            }
            break;
        case CHOICE_EXIT:
            if (stack != NULL)
            {
                status = fn_exit(stack);
                if (status == SUCCESS)
                {
                    printf("\n\t Memory has been released\n");
                }
            }
        default:
            fn_exit(stack);
            stack = NULL;
            exit(0);
            break;
        }
    }
}
