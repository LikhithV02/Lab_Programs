#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHOICE_CREATE 1
#define CHOICE_INSERT_FRONT 2
#define CHOICE_DELETE_FRONT 3
#define CHOICE_INSERT_END 4
#define CHOICE_DELETE_END 5
#define CHOICE_DISPLAY 6
#define CHOICE_EXIT 0

typedef struct node
{
  char usn[10];
  char name[20];
  char branch[5];
  unsigned short int sem;
  char phno[10];
  struct node *next_node;
} node_t;

typedef struct header
{
  node_t *front;
  node_t *rear;
} header_t;

int menu()
{
  int choice;

  printf("\n\t create list - %u\n", CHOICE_CREATE);
  printf("\t to insert at the first - %u\n", CHOICE_INSERT_FRONT);
  printf("\t to delete at the first - %u\n", CHOICE_DELETE_FRONT);
  printf("\t to insert at the end - %u\n", CHOICE_INSERT_END);
  printf("\t to delete at the end - %u\n", CHOICE_DELETE_END);
  printf("\t to display list - %u\n", CHOICE_DISPLAY);
  printf("\t to exit - %u\n", CHOICE_EXIT);
  printf("\t\t PLEASE ENTER YOUR CHOISE : ");
  scanf("%d", &choice);
  // getchar();

  return choice;
}

/*
 * create function
 */
header_t *create(header_t *hdr)
{
  hdr = (header_t *)malloc(sizeof(header_t));
  hdr->front = NULL;
  hdr->rear = NULL;

  return hdr;
}

/*
 * insert function
 */
header_t *insert(header_t *hdr, int choice)
{
  node_t *node;

  node = (node_t *)malloc(sizeof(node_t));

  printf("\t enter the usn : ");
  // fgets(node->usn ,10 , stdin);
  scanf("%s", node->usn);

  printf("\t enter the name : ");
  // fgets(node->name , 20 , stdin);
  scanf("%s", node->name);
  // getchar();

  printf("\t enter the branch : ");
  // fgets(node->branch , 5 , stdin);
  scanf("%s", node->branch);

  printf("\t enter the semester : ");
  scanf("%hu", &node->sem);
  // getchar();

  printf("\t enter the phone number : ");
  // fgets(node->phno , 10 , stdin);
  scanf("%s", node->phno);

  node->next_node = NULL;

  if (hdr->front == NULL)
  {
    hdr->front = node;
    hdr->rear = node;
  }
  else
  {
    if (choice == CHOICE_INSERT_FRONT)
    {
      node->next_node = hdr->front;
      hdr->front = node;
      // printf("1\n");
    }
    else
    {
      hdr->rear->next_node = node;
      hdr->rear = node;
      // printf("0\n");
    }
  }
  return hdr;
}

/*
 * delete function
 */

header_t *deletee(header_t *hdr, int choice)
{
  if (hdr->front != NULL)
  {
    if (choice == CHOICE_DELETE_FRONT)
    {
      hdr->front = hdr->front->next_node;
    }
    else
    {
      node_t *prev;
      node_t *curr;
      prev = hdr->front;
      curr = prev->next_node;

      if (curr == NULL)
      {
        hdr->front = NULL;
        hdr->rear = NULL;
        return hdr;
      }
      else
      {
        while (curr->next_node != NULL)
        {
          prev = curr;
          curr = curr->next_node;
        }

        prev->next_node = NULL;
        hdr->rear = prev;
        free(curr);
      }
    }
  }
  else
    printf("there is no node inserted , please insert a node first\n");

  return hdr;
}

/*
 *
 */

void display(header_t *hdr)
{
  int cnt = 1;
  node_t *temp;
  temp = hdr->front;
  while (temp != NULL)
  {
    printf("student %d info :\n", cnt);
    printf("\tusn - %s\n", temp->usn);       // fputs(temp->usn , stdout);
    printf("\tname - %s\n", temp->name);     // fputs(temp->name , stdout);
    printf("\tbranch - %s\n", temp->branch); // fputs(temp->branch , stdout);
    printf("\tsemester - %d\n", temp->sem);
    printf("\tphone number - %s\n", temp->phno); // fputs(temp->phno , stdout);
    cnt++;

    temp = temp->next_node;
  }
  if (hdr->front == NULL)
    printf("there is no student data to display\nplease enter a student data by choosing insert from menu\n");
}

int main()
{
  int choice;
  header_t *hdr = NULL;
  while (1)
  {
    choice = menu();
    switch (choice)
    {
    case CHOICE_CREATE:
      if (hdr == NULL)
      {
        hdr = create(hdr);
        printf("please choose insert :\n");
      }
      else
        printf("there is already a list created\n");
      break;

    case CHOICE_INSERT_FRONT:
      if (hdr == NULL)
        hdr = create(hdr);
      hdr = insert(hdr, CHOICE_INSERT_FRONT);
      printf("a node is inserted at front :\n");
      break;

    case CHOICE_INSERT_END:
      if (hdr == NULL)
        hdr = create(hdr);
      hdr = insert(hdr, CHOICE_INSERT_END);
      printf("\t\ta node is inserted at end :\n");
      break;

    case CHOICE_DELETE_FRONT:
      hdr = deletee(hdr, CHOICE_DELETE_FRONT);
      printf("\t\ta node is deleted at front :\n");
      break;

    case CHOICE_DELETE_END:
      hdr = deletee(hdr, CHOICE_DELETE_END);
      printf("\t\ta node is deleted at end :\n");
      break;

    case CHOICE_DISPLAY:
      display(hdr);
      break;

    case CHOICE_EXIT:
      free(hdr);
      exit(0);
    }
  }
  return 0;
}
