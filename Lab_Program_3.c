/*stack function implementation */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define STACK_SIZE 5

#define CHOICE_PUSH  1
#define CHOICE_POP 2
#define CHOICE_PALINDROME  3
#define CHOICE_  4
#define CHOICE_EXIT    0

unsigned int menu() {
  unsigned int choice = CHOICE_DELETE + 1;
  while (choice > CHOICE_DELETE) {
    printf("Enter your choice:\n");
    printf("\t %u - Create Array\n", CHOICE_CREATE);
    printf("\t %u - Display Array Elements\n", CHOICE_DISPLAY);
    printf("\t %u - Insert Element at a Position\n", CHOICE_INSERT);
    printf("\t %u - Delete an Element at a Position\n", CHOICE_DELETE);
    printf("\t %u - Exit\n", CHOICE_EXIT);
    printf("\t choice: ");
    scanf("%d", &choice);
    if (choice > CHOICE_DELETE) {
      printf("ERROR: Invalid Choice\n");
    }
  }
  return choice;

typedef struct {
        size_t size;
        int top;
        int* arr;
        }stack_t;

  stack_t*  create(size_t size)
  {
    stack_t* stack = malloc(sizeof(stack_t));
    if (stack != NULL)
    {
      stack->size = size;
      stack->arr = calloc(size , sizeof(int));
      if (stack->arr != NULL)
      {
        stack->top = -1; // stack is empty
      }
      else
      {
        free(stack);
	stack = NULL;
      }
    }  return stack;
  }

  bool  isfull(stack_t* s)
  {
    if (s->top == s->size)
    {
       return true;
    }
    else
    {
       return false;
    }
  }


  int  isempty(stack_t* s)
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




  int  push(stack_t* s, int elem)
  {
    if (isfull(s))    // is stack full?
    {
       return 0;
    }
    s->arr[++s->top]=elem;
    return 1;
  }


  int  pop(stack_t* s)
  {
    if (isempty(s))  // is stack empty
    {
      return 0;
    }
    return (s->arr[s->top--]);
  }


  bool is_palindrome(stack_t* s1 , int* arr , unsigned int mid)
  {
    while(s1->top>=0)
    {
      if(pop(s1)!=arr[mid])
        return 0;
      else
         mid++;
    }
    return 1;
  }

void main()
{
  stack_t* s1;         			//structure declaration 
  unsigned int N,mid;  			//'N' is the maximum number of entries 
  bool result;        			//a variable to store the result 

  // taking the input of maximum number of entries from user
  printf("Please enter the  number of digits::");
  scanf("%d",&N);

  mid=N/2;
  int arr[N];          			// an array to store the sequence of numbers

  // taking a  series of  numbers as input
  printf("Please enter a sequence of single digit  number::\n");
  for(unsigned int i=0;i<N;i++)
    scanf("%d",&arr[i]);

  s1=create(N/2);     			//to create a stucture which has the stack to store only the half series

  for(unsigned int i=0;i<mid;i++)	// this pushes the only first half of series of numbers into the stack
    push(s1 ,arr[i]);

  if(N%2==0)
     result = is_palindrome(s1 , arr , mid);
  else
  {					// condition to check wheather  maximum number of entries is odd or even
     mid++;
     result = is_palindrome(s1 , arr , mid);
  }

  if(result==1)
   printf("The entered sequense of numbers is palindrome!!\n");
  else
   printf("The entered sequense of numbers is not palindrome!!\n");
   free(s1);
}
