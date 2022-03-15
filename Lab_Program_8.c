

#include <stdio.h>
#include <stdlib.h>

#define SIZE_TXT 50
#define SIZE_NUM 12

typedef enum Menu
{
  CH_EXIT,
  CH_CREATE,
  CH_INS_FRNT,
  CH_INS_END,
  CH_DEL_FRNT,
  CH_DEL_END,
  CH_DISP,
  CH_END
} menu_t;

typedef struct employee
{
  char ssn[SIZE_NUM];
  char name[SIZE_TXT];
  char dept[SIZE_TXT];
  char dsgn[SIZE_TXT];
  char phone[SIZE_NUM];
  double salary;
} employee_t;

typedef struct dllnode
{
  employee_t empl;
  struct dllnode *left;
  struct dllnode *right;
} dllnode_t;

#define MALLOC(ptr, size)                  \
  ptr = malloc(size);                      \
  if (!ptr)                                \
  {                                        \
    printf("Err: Memory not available\n"); \
    exit(1);                               \
  }

//---------------------------------
// create a node with required data
dllnode_t *createnode()
{
  dllnode_t *node;
  MALLOC(node, sizeof(dllnode_t))
  // get employee details and fill the same
  printf("Enter employee details:\n");
  printf("SSN: ");
  scanf("%s", node->empl.ssn);
  printf("Name: ");
  scanf("%s", node->empl.name);
  printf("Dept: ");
  scanf("%s", node->empl.dept);
  printf("Designation: ");
  scanf("%s", node->empl.dsgn);
  printf("Phone: ");
  scanf("%s", node->empl.phone);
  printf("Salary: ");
  scanf("%lf", &node->empl.salary);
  node->left = NULL;
  node->right = NULL;

  return node;
}
//--------------------
// insert a node in front in DLL
// new node becomes the head
dllnode_t *ins_front(dllnode_t *head)
{
  dllnode_t *node;
  node = createnode();
  if (head == NULL)
  {
    head = node;
  }
  else
  {
    node->right = head;
    head->left = node;
    head = node;
  }
  return head;
}
//--------------------
// insert a node in end in DLL
// new node becomes the tail
dllnode_t *ins_end(dllnode_t *tail)
{
  dllnode_t *node;

  node = createnode();
  if (tail == NULL)
  {
    tail = node;
  }
  else
  {
    tail->right = node;
    node->left = tail;
    tail = node;
  }

  return tail;
}
//--------------------
// delete a node from front in DLL
// next node becomes the head
dllnode_t *del_front(dllnode_t *head)
{
  dllnode_t *node;
  if (head == NULL)
    printf("there is no employe data to delete ,\t please enter an employe data first \n");
  else if (head->right == NULL)
  {
    head = NULL;
    free(head);
  }
  else
  {
    node = head;
    head = head->right;
    head->left = NULL;
    free(node);
  }
  return head;
}
//--------------------
// delete a node at the end
// prev node becomes the tail
dllnode_t *del_end(dllnode_t *tail)
{
  dllnode_t *node;
  node = tail;
  if (tail == NULL)
  {
    printf("there is no employe data to delete ,\t please enter an employe data first \n");
  }
  else if (tail->left == NULL)
  {
    tail = NULL;
    free(tail);
  }
  else
  {
    tail = tail->left;
    tail->right = NULL;
    free(node);
  }
  return tail;
}
//---------------------------------
void display(dllnode_t *head)
{
  unsigned int count = 1;
  dllnode_t *temp;

  if (head == NULL)
  {
    printf("DLL is empty\n");
    return;
  }
  temp = head;
  // Display all the nodes in the DLL
  while (temp != NULL)
  {
    printf("\n Employe %u data :\n", count);
    printf("\t\tSSN: %s\n", temp->empl.ssn);
    printf("\t\tName: %s\n", temp->empl.name);
    printf("\t\tDept: %s\n", temp->empl.dept);
    printf("\t\tDesignation: %s\n", temp->empl.dsgn);
    printf("\t\tPhone: %s\n", temp->empl.phone);
    printf("\t\tSalary: %.2lf\n", temp->empl.salary);
    temp = temp->right;
    count++;
  }
  return;
}
//-------------------------------------

//---------------------------------
menu_t menu()
{
  menu_t choice = CH_END;
  do
  {
    printf("Enter your menu choice:\n");
    printf("%u for Create DLL\n", CH_CREATE);
    printf("%u for Insert Front\n", CH_INS_FRNT);
    printf("%u for Insert End \n", CH_INS_END);
    printf("%u for Delete Front\n", CH_DEL_FRNT);
    printf("%u for Delete End \n", CH_DEL_END);
    printf("%u for Display data\n", CH_DISP);
    printf("%u for Exit.\n", CH_EXIT);
    scanf("%u", &choice);
  } while (choice >= CH_END);

  return choice;
}
// ----------------------
void fn_exit()
{
  exit(0);
}

//---------------------------------
// create DLL
dllnode_t *createdll()
{
  dllnode_t *head = NULL;
  dllnode_t *tail = NULL;
  unsigned int count = 0;
  printf("Enter num of nodes to Add: ");
  scanf("%d", &count);
  for (unsigned int i = 0; i < count; i++)
  {
    // insert code here
    head = ins_front(head);
  }
  return head;
}
//---------------------------------
int main(int argc, char *argv[])
{
  dllnode_t *head = NULL;
  dllnode_t *tail = NULL;
  menu_t choice;

  while (1)
  {
    choice = menu();
    switch (choice)
    {
    case CH_EXIT:
      fn_exit();
      break;
    case CH_CREATE:
      if (head != NULL)
      {
        printf("Er: DLL already created\n");
        continue;
      }
      head = createdll();
      dllnode_t *temp = head;
      // traverse DLL to find tail node
      while (temp->right != NULL)
      {
        temp = temp->right;
      }
      tail = temp;
      break;
    case CH_INS_FRNT:
      head = ins_front(head);
      break;
    case CH_INS_END:
      tail = ins_end(tail);
      break;
    case CH_DEL_FRNT:
      head = del_front(head);
      break;
    case CH_DEL_END:
      tail = del_end(tail);
      break;
    case CH_DISP:
      display(head);
      break;
    default:
      printf("Invalid choice %u\n", choice);
      break;
    } // end switch
  }   // end while(1)
}
