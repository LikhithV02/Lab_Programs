#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSERT 1
#define DELETE 2
#define DISPLAY 3
#define EXIT 0

typedef struct
{
  int front;
  int rear;
  char *str;
} queue_t;

unsigned int menu()
{
  unsigned int ch;
  ch = DISPLAY + 1;
  while (ch > DISPLAY)
  {
    printf("\t%u - to Insert an element\n", INSERT);
    printf("\t%u - to delete an element\n", DELETE);
    printf("\t%u - to Display elements in queue\n", DISPLAY);
    printf("\t%u - to Exit\n", EXIT);
    printf("please enter your choice :");
    scanf("%u", &ch);
    if (ch > DISPLAY)
      printf("invalid choice\n");
  }
  return ch;
}

queue_t *create(queue_t *qu, unsigned int size)
{
  qu = malloc(sizeof(queue_t));
  qu->front = -1;
  qu->rear = -1;
  qu->str = calloc(size, sizeof(char));

  return qu;
}

void enqueue(queue_t *q, unsigned int max)
{
  char elem;
  printf("please enter the element to be inserted:");
  scanf(" %c", &elem);

  if ((q->front == -1) && (q->rear == -1))
  {
    q->str[++q->front] = elem;
    q->rear++;
  }
  else if ((q->rear + 1) % max == q->front)
    printf("queue overflow\n");
  else
  {
    q->rear = (q->rear + 1) % max;
    q->str[q->rear] = elem;
  }
}

void dequeue(queue_t *q, unsigned int max)
{
  if ((q->front == -1) && (q->rear == -1))
    printf("queue underflow\n");
  else if (q->front == q->rear)
  {
    q->front = -1;
    q->rear = -1;
  }
  else
  {
    q->str[q->front] = ' ';
    q->front = (q->front + 1) % max;
  }
}

void display(queue_t *q, unsigned int max)
{
  unsigned int temp = q->front;
  if (q->front == -1)
    printf("the queue is empty\n");
  else
  {
    do
    {
      printf("\t%c\n", q->str[temp]);
      temp = (temp + 1) % max;
    } while (temp != q->front);
  }
}

int main()
{
  unsigned int max, choice;
  queue_t *q;

  printf("please enter the size of queue to be created :");
  scanf("%u", &max);

  q = create(q, max);

  while (1)
  {
    choice = menu();
    switch (choice)
    {
    case INSERT:
      enqueue(q, max);
      break;
    case DELETE:
      dequeue(q, max);
      break;
    case DISPLAY:
      display(q, max);
      break;
    case EXIT:
      free(q);
      exit(0);
    }
  }
  return 0;
}