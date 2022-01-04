#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count = 0;

struct node
{
  int sem, phno;
  char name[20], branch[10], usn[20];
  struct node *next;
} *first = NULL, *last = NULL, *temp = NULL, *temp1;

void create()
{
  int sem, phno;
  char name[20], branch[10], usn[20];
  temp = (struct node *)malloc(sizeof(struct node));
  printf("\n Enter usn,name, branch, sem, phno of student : ");
  scanf("%s %s %s %d %d", usn, name, branch, &sem, &phno);
  strcpy(temp->usn, usn);
  strcpy(temp->name, name);
  strcpy(temp->branch, branch);
  temp->sem = sem;
  temp->phno = phno;
  temp->next = NULL;
  count++;
}

void insert_atfirst()
{
  if (first == NULL)
  {
    create();
    first = temp;
    last = first;
  }
  else
  {
    create();
    temp->next = first;
    first = temp;
  }
}

void insert_atlast()
{
  if (first == NULL)
  {
    create();
    first = temp;
    last = first;
  }
  else
  {
    create();
    last->next = temp;
    last = temp;
  }
}

void display()
{
  temp1 = first;
  if (temp1 == NULL)
  {
    printf("List empty to display \n");
    return;
  }
  printf("\n Linked list elements from begining : \n");
  while (temp1 != NULL)
  {
    printf("%s %s %s %d %d\n", temp1->usn, temp1->name, temp1->branch,
           temp1->sem, temp1->phno);
    temp1 = temp1->next;
  }
  printf(" No of students = %d ", count);
}

int deleteend()
{
  struct node *temp;
  temp = first;
  if (temp->next == NULL)
  {
    free(temp);
    first = NULL;
  }
  else
  {
    while (temp->next != last)
      temp = temp->next;
    printf("%s %s %s %d %d\n", last->usn, last->name, last->branch, last->sem,
           last->phno);
    free(last);
    temp->next = NULL;
    last = temp;
  }
  count--;
  return 0;
}

int deletefront()
{
  struct node *temp;
  temp = first;
  if (temp->next == NULL)
  {
    free(temp);
    first = NULL;
    return 0;
  }
  else
  {
    first = temp->next;
    printf("%s %s %s %d %d", temp->usn, temp->name, temp->branch, temp->sem,
           temp->phno);
    free(temp);
  }
  count--;
  return 0;
}

int main()
{
  int ch, n, i;
  first = NULL;
  temp = temp1 = NULL;
  printf("-----------------MENU----------------------\n");
  printf("\n 1- create a SLL of n emp");
  printf("\n 2 - Display from beginning");
  printf("\n 3 - Insert at end");
  printf("\n 4 - delete at end");
  printf("\n 5 - Insert at beg");
  printf("\n 6 - delete at beg");
  printf("\n 7 - exit\n");
  printf("-------------------------------------------\n");
  while (1)
  {
    printf("\n Enter choice : ");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
      printf("\n Enter no of students : ");
      scanf("%d", &n);
      for (i = 0; i < n; i++)
        insert_atfirst();
      break;
    case 2:
      display();
      break;
    case 3:
      insert_atlast();
      break;
    case 4:
      deleteend();
      break;
    case 5:
      insert_atfirst();
      break;
    case 6:
      deletefront();
      break;
    case 7:
      exit(0);
    default:
      printf("wrong choice\n");
    }
  }
  return 0;
}
