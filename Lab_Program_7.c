#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define CHOICE_INSERT_AT_FRONT 1
#define CHOICE_DELETE_AT_FRONT 2
#define CHOICE_INSERT_AT_END 3
#define CHOICE_DELETE_AT_END 4
#define CHOICE_DISPLAY 5
#define CHOICE_STACK_DEMO 6
#define CHOICE_EXIT 7

/**
 * This program implements a menu driven task to perform
 * operations such as insert node at front, delete node at front,
 * insert node at end, delete node at end, display linked list
 * elements and stack demonstration on singly linked list (SLL)
 * of Student Data with the fields : Name, USN, Branch, Sem, Phone number.
 **/

unsigned int menu()
{
  unsigned int choice = CHOICE_EXIT + 1;
  while (choice > CHOICE_EXIT)
  {
    printf("\nEnter your choice:\n");
    printf("\t %u - Insert at the beginning of the list\n", CHOICE_INSERT_AT_FRONT);
    printf("\t %u - Delete at the beginning of the list\n", CHOICE_DELETE_AT_FRONT);
    printf("\t %u - Insert at the end of the list\n", CHOICE_INSERT_AT_END);
    printf("\t %u - Delete at the end of the list\n", CHOICE_DELETE_AT_END);
    printf("\t %u - Display list Elements\n", CHOICE_DISPLAY);
    printf("\t %u - Stack demonstration of SLL\n", CHOICE_STACK_DEMO);
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

/**
 * Initialising the struct
 **/

typedef struct listnode
{
  char name[50];
  char branch[10];
  char USN[10];
  char phno[10];
  int sem;
  struct listnode *link;
} listnode_t;

listnode_t *create();
listnode_t *insert_at_front(listnode_t *list);
listnode_t *delete_at_front(listnode_t *list);
listnode_t *insert_at_end(listnode_t *list);
listnode_t *delete_at_end(listnode_t *list);
void display(listnode_t *list);
void fn_exit(listnode_t *list);
void stack_demo();

/**
 * Function to create a node
 **/

listnode_t *create()
{
  char name[50];
  char branch[10];
  char USN[10];
  char phno[10];
  int sem;

  listnode_t *node = (listnode_t *)malloc(sizeof(listnode_t));

  printf("\t Student name : ");
  scanf("%s", name);
  strncpy(node->name, name, 50);

  printf("\t Student USN : ");
  scanf("%s", USN);
  strncpy(node->USN, USN, 10);

  printf("\t Student branch : ");
  scanf("%s", branch);
  strncpy(node->branch, branch, 10);

  printf("\t Student sem : ");
  scanf("%d", &sem);
  node->sem = sem;

  printf("\t Student phone number : ");
  scanf("%s", phno);
  strncpy(node->phno, phno, 10);

  node->link = NULL;

  return node;
}

/**
 * Function to insert a node at the front of the list
 **/

listnode_t *insert_at_front(listnode_t *list)
{
  listnode_t *temp = NULL;

  if (list == NULL)
  {
    list = create();
    return list;
  }
  else
  {
    temp = create();
    temp->link = list;
    list = temp;
    return list;
  }
}

/**
 * Function to delete a node at the front of the list
 **/

listnode_t *delete_at_front(listnode_t *list)
{
  listnode_t *temp = NULL;

  if (list == NULL)
  {
    printf("List is empty\n");
    return NULL;
  }
  else
  {
    if (list->link == NULL)
    {
      printf("\n\t %s's data has been deleted", list->name);
      free(list);
      return NULL;
    }
    else
    {
      temp = list;
      list = list->link;
      printf("\n\t %s's data has been deleted", temp->name);
      free(temp);
      return list;
    }
  }
}

/**
 * Function to insert a node at the end of the list
 **/

listnode_t *insert_at_end(listnode_t *list)
{
  listnode_t *temp = NULL;
  listnode_t *last = NULL;

  if (list == NULL)
  {
    list = create();
    return list;
  }
  else
  {
    temp = create();
    last = list;
    while (last->link != NULL)
    {
      last = last->link;
    }
    last->link = temp;
    return list;
  }
}

/**
 * Function to delete a node at the end of the list
 **/

listnode_t *delete_at_end(listnode_t *list)
{
  listnode_t *temp = NULL;
  listnode_t *last = NULL;

  if (list == NULL)
  {
    printf("List is empty\n");
    return NULL;
  }
  else
  {
    if (list->link == NULL)
    {
      printf("\n\t %s's data has been deleted", list->name);
      free(list);
      return NULL;
    }
    else
    {
      temp = list;
      while (temp->link != NULL)
      {
        last = temp;
        temp = temp->link;
      }
      printf("\n\t %s's data has been deleted", temp->name);
      free(temp);
      last->link = NULL;
      return list;
    }
  }
}

/**
 * Function to show stack demonstration of SLL
 **/

void stack_demo()
{
  size_t choice;
  listnode_t *stack = NULL;

  while (true)
  {
    printf("\n Stack demo of SLL \n");
    printf("\t 1 - Push an element onto Stack\n");
    printf("\t 2 - Pop an element from Stack\n");
    printf("\t 3 - Display stack elements\n");
    printf("\t 4 - Exit\n");
    printf("\t choice : ");
    scanf("%zu", &choice);
    if (choice > 4)
    {
      printf("ERROR: Invalid Choice\n");
    }

    switch (choice)
    {
    case 1:
      stack = insert_at_front(stack);
      break;
    case 2:
      stack = delete_at_front(stack);
      break;
    case 3:
      display(stack);
      break;
    case 4:
      fn_exit(stack);
      return;
    default:
      return;
    }
  }
}

/**
 * Function to display nodes of singly linked list
 **/

void display(listnode_t *list)
{
  listnode_t *temp = list;
  int count = 0;

  if (temp == NULL)
  {
    printf("List is empty\n");
  }
  else
  {
    while (temp != NULL)
    {
      printf("\n\t Student name : %s", temp->name);
      printf("\n\t Student USN : %s", temp->USN);
      printf("\n\t Student branch : %s", temp->branch);
      printf("\n\t Student sem : %d", temp->sem);
      printf("\n\t Student phone number : %s\n", temp->phno);
      temp = temp->link;
      count++;
    }
    printf("\n\t Number of students = %d ", count);
  }
}

/**
 * Function to free memory allocated to SLL
 **/

void fn_exit(listnode_t *list)
{
  if (list != NULL)
  {
    free(list);
    printf("Memory allocated to the list has been released\n");
  }
}

int main()
{
  size_t choice;
  listnode_t *list = NULL;

  while (true)
  {
    choice = menu();
    switch (choice)
    {
    case CHOICE_INSERT_AT_FRONT:
      list = insert_at_front(list);
      break;
    case CHOICE_DELETE_AT_FRONT:
      list = delete_at_front(list);
      break;
    case CHOICE_INSERT_AT_END:
      list = insert_at_end(list);
      break;
    case CHOICE_DELETE_AT_END:
      list = delete_at_end(list);
      break;
    case CHOICE_DISPLAY:
      display(list);
      break;
    case CHOICE_STACK_DEMO:
      stack_demo();
      break;
    case CHOICE_EXIT:
      fn_exit(list);
      exit(0);
      break;
    default:
      fn_exit(list);
      list = NULL;
      exit(0);
      break;
    }
  }
}