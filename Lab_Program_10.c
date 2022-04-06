#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Menu
{
  CH_EXIT,
  CH_CREATE,
  CH_TRAVERSE,
  CH_SEARCH,
  CH_END
} menu_t;
typedef struct bstnode
{
  int elem;
  struct bstnode *left;
  struct bstnode *right;
} bstnode_t;

// pointer to function type
typedef void (*pfv)();

#define SIZE_BUF (1000)
//#define SEP " ,"

#define MALLOC(ptr, size)                  \
  ptr = malloc(size);                      \
  if (!ptr)                                \
  {                                        \
    printf("Err: Memory not available\n"); \
    exit(1);                               \
  }

//---------------------------------
// insert a node in a BST
void insert(bstnode_t *root, bstnode_t *node)
{
  bstnode_t *temp = root;
  while (temp != NULL)
  {
    if (temp->elem == node->elem)
    {
      return;
    }
    else if (node->elem < temp->elem)
    {
      // traverse left subtree
      if (temp->left)
      { // left subree exists
        temp = temp->left;
      }
      else
      {
        temp->left = node;
        return;
      }
    }
    else
    {
      // traverse right subtree
      if (temp->right)
      {
        temp = temp->right;
      }
      else
      {
        temp->right = node;
        return;
      }
    }
  }
  return;
}
//--------------------
void inorder(bstnode_t *root)
{
  if (root)
  { // explore when not null
    inorder(root->left);
    printf("%d ", root->elem);
    inorder(root->right);
  }
  return;
}
//--------------------
void preorder(bstnode_t *root)
{
  if (root)
  { // explore when not null
    printf("%d ", root->elem);
    preorder(root->left);
    preorder(root->right);
  }
  return;
}
//--------------------
void postorder(bstnode_t *root)
{
  if (root)
  { // explore when not null
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->elem);
  }
  return;
}
//---------------------------------
void traverse(bstnode_t *root)
{
  printf("Inorder Traversal:\n");
  inorder(root);
  printf("\n");
  printf("Pre Order Traversal:\n");
  preorder(root);
  printf("\n");
  printf("Post order traversal:\n");
  postorder(root);
  printf("\n");

  return;
}
//-------------------------------------
// search for a key
bstnode_t *search(bstnode_t *root, int key)
{
  if (!root)
  {
    return root; // tree is empty, key not found
  }
  // do preorder traversal to check for key
  if (root->elem == key)
  {
    printf("Key found\n");
  }
  else if (key < root->elem)
  { // left subtree
    search(root->left, key);
  }
  else
  {
    search(root->right, key);
  }
  return NULL; // should never reach here.
}
//---------------------------------
menu_t menu()
{
  menu_t choice = CH_END;
  do
  {
    printf("Enter your activity choice:\n");
    printf("%u for Create BST\n", CH_CREATE);
    printf("%u for BST traversal\n", CH_TRAVERSE);
    printf("%u for search BST\n", CH_SEARCH);
    printf("%u for Exit.\n", CH_EXIT);
    scanf("%u", &choice);
  } while (choice >= CH_END);
  getchar();
  return choice;
}
// ----------------------
void fn_exit()
{
  exit(0);
}

//---------------------------------
// create BST
bstnode_t *create()
{
  char inp[SIZE_BUF];
  char *token = NULL;
  bstnode_t *root = NULL;
  bstnode_t *node = NULL;
  printf("Enter SPACE separated values: ");
  fgets(inp, SIZE_BUF, stdin);
  token = strtok(inp, " ,");
  while (token != NULL)
  {
    // for each input, create a node
    MALLOC(node, sizeof(bstnode_t))
    node->elem = atoi(token); // this can be read from stdin as well
    node->left = NULL;
    node->right = NULL;
    token = strtok(NULL, " ,");
    if (!root)
    {
      root = node;
    }
    else
    {
      // add the node to BST
      insert(root, node);
    }
  } // end while
  return root;
}
//---------------------------------
int main(int argc, char *argv[])
{
  bstnode_t *root = NULL;
  bstnode_t *node = NULL;
  menu_t choice;
  int key;
  // initialize array of functions in the same order of menu choice
  // pfv fn[] = {fn_exit, create, traverse, search};

  while (1)
  {
    choice = menu();
    switch (choice)
    {
    case CH_EXIT:
      fn_exit();
      break;
    case CH_CREATE:
      root = create();
      break;
    case CH_TRAVERSE:
      traverse(root);
      break;
    case CH_SEARCH:
      printf("Enter key to search: ");
      scanf("%d", &key);
      node = search(root, key);
      if (node)
      {
        printf("Key %d found in BST with root %d\n", key, root->elem);
      }
      else
      {
        printf("Key %d not found in BST\n", key);
      }
      break;
    default:
      break;
    }
  }
}