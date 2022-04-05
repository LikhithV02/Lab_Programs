#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define EPSILON 1.0e-10
typedef enum Menu
{
    CH_EXIT,
    CH_CREATE_P1,
    CH_CREATE_P2,
    CH_EVAL_P1,
    CH_EVAL_P2,
    CH_SUM_POLY,
    CH_EVAL_SUM,
    CH_END
} menu_t;

typedef struct term
{
    float coeff;
    unsigned int px;
    unsigned int py;
    unsigned int pz;
    struct term *next;
} term_t;

#define MALLOC(ptr, size)                      \
    ptr = malloc(size);                        \
    if (!ptr)                                  \
    {                                          \
        printf("Err: Memory not available\n"); \
        exit(1);                               \
    }

//---------------------------------
menu_t menu()
{
    menu_t choice;
    do
    {
        printf("Enter your menu choice:\n");
        printf("%u for Create Poly-1\n", CH_CREATE_P1);
        printf("%u for Create Poly-2\n", CH_CREATE_P2);
        printf("%u for Eval Poly-1 \n", CH_EVAL_P1);
        printf("%u for Eval Poly-2\n", CH_EVAL_P2);
        printf("%u for Sum two polynomials \n", CH_SUM_POLY);
        printf("%u for Eval Summ\n", CH_EVAL_SUM);
        printf("%u for Exit.\n", CH_EXIT);
        scanf("%u", &choice);
    } while (choice >= CH_END);

    return choice;
}
//---------------------------------
// create a node with required data
term_t *createnode()
{
    term_t *node;
    MALLOC(node, sizeof(term_t))
    node->next = NULL;
    printf("Enter Coefficient (0 for exit: ");
    scanf("%f", &node->coeff);
    if (abs(node->coeff) >= 1.0e-10)
    {
        // coeff is nonzero, get powers of x, y, and z
        printf("power of x: ");
        scanf("%u", &node->px);
        printf("power of y: ");
        scanf("%u", &node->py);
        printf("power of z: ");
        scanf("%u", &node->pz);
    }
    return node;
}
//--------------------
// insert a node (in SCLL in front
// head can't be NULL
// insert node in the front
void insert(term_t *head, term_t *node)
{

    node->next = head->next;
    head->next = node;
    return;
}
//--------------------
void create_poly(term_t *head)
{
    term_t *node;
    while (1)
    {
        printf("Enter polynomial term ");
        node = createnode();
        if (abs(node->coeff) < EPSILON)
        {
            // all terms are over
            return;
        }
        insert(head, node);
    }
}
//---------------------------------
void display(term_t *head)
{
    term_t *temp;
    temp = head->next;
    if (temp == head)
    {
        // empty SCLL
        printf("Given polynomial is empty\n");
        return;
    }
    printf("%.2fx**%dy**%dz**%d ", temp->coeff,
           temp->px, temp->py, temp->pz);
    temp = temp->next;
    while (temp != head)
    {
        // traverse the linked list
        printf("%+.2fx**%dy**%dz**%d ", temp->coeff,
               temp->px, temp->py, temp->pz);
        temp = temp->next;
    }
    printf("\n");
    return;
}
//---------------------------------
float power(float base, unsigned expon)
{
    float res = 1.0;
    for (unsigned int i = 0; i < expon; i++)
    {
        res = res * base;
    }
    return res;
}
void eval_poly(term_t *head)
{
    float sum = 0.0;
    float val = 1.0;
    float x;
    float y;
    float z;
    term_t *temp;

    // check if polynomial is empty.
    if (head->next == head)
    {
        printf("Polynomial is empty, no terms in it.\n");
        return;
    }
    printf("Enter the values of variables, \
          x, y and z (SPACE Separated): ");
    scanf("%f %f %f", &x, &y, &z);

    temp = head->next;
    while (temp != head)
    {
        val = temp->coeff * power(x, temp->px);
        val = val * power(y, temp->py);
        val = val * power(z, temp->pz);
        sum = sum + val;
        temp = temp->next;
    }
    printf("Given polynomial\n");
    display(head);
    printf("polynomial evaluation : %.2f\n", sum);
    return;
}
//---------------------------------
void polysum(term_t *head1, term_t *head2, term_t *headsum)
{
    term_t *node1;
    term_t *node2;

    // first iterate over polynomial 1 and
    //  if there exists a corresponding terms in poly2
    //  add the two terms an insert this sum value ot polysum

    // traverse first polynomial
    node1 = head1->next;
    while (node1 != head1)
    {
        bool found = false;
        node2 = head2->next;
        while (node2 != head2)
        {
            if ((node1->px == node2->px) &&
                (node1->py == node2->py) &&
                (node1->pz == node2->py))
            {
                // two terms are same, add these and insert into headsum
                found = true;
                term_t *node;
                MALLOC(node, sizeof(term_t))
                node->next = NULL;
                node->coeff = node1->coeff + node2->coeff;
                if ((node->coeff >= EPSILON) || (node->coeff <= -EPSILON))
                {
                    // coeff is non-zero
                    node->px = node1->px;
                    node->py = node1->py;
                    node->pz = node1->pz;
                    insert(headsum, node);
                }
            } // if comparing two nodes
            node2 = node2->next;
        }
        // if node1 is not found in node2, add it to poly sum
        if (!found)
        {
            term_t *node;
            MALLOC(node, sizeof(term_t))
            node->next = NULL;
            node->coeff = node1->coeff;
            node->px = node1->px;
            node->py = node1->py;
            node->pz = node1->py;
            insert(headsum, node);
        }
        node1 = node1->next;
    } // end while node 1
    // find al lthose terms of poly2 that are not in poly1 and
    // add these to head sum

    node2 = head2->next;
    while (node2 != head2)
    {
        bool found = false;
        node1 = head1->next;
        while (node1 != head1)
        {
            if ((node1->px == node2->px) &&
                (node1->py == node2->py) &&
                (node1->pz == node2->pz))
            {
                found = true;
            }
            node1 = node1->next;
        } // ende while node1
        // term of poly2 is not in poly1, add it to sumhead
        if (!found)
        {
            term_t *node;
            MALLOC(node, sizeof(term_t))
            node->next = NULL;
            node->coeff = node2->coeff;
            node->px = node2->px;
            node->py = node2->py;
            node->pz = node2->pz;
            insert(headsum, node);
        }
        node2 = node2->next;
    } // end while node 2
}

// ----------------------
void fn_exit()
{
    exit(0);
}
//---------------------------------
int main(int argc, char *argv[])
{
    term_t *head1 = NULL;
    term_t *head2 = NULL;
    term_t *headsum = NULL;
    menu_t choice;

    // initialize the header nodes for each of the polynomials
    MALLOC(head1, sizeof(term_t))
    MALLOC(head2, sizeof(term_t))
    MALLOC(headsum, sizeof(term_t))
    head1->next = head1;
    head2->next = head2;
    headsum->next = headsum;

    while (1)
    {
        choice = menu();
        switch (choice)
        {
        case CH_EXIT:
            fn_exit();
            break;
        case CH_CREATE_P1:
            if (head1->next != head1)
            {
                printf("Polynomial 1 given below already created. \n");
                display(head1);
                continue;
            }
            create_poly(head1);
            display(head1);
            break;
        case CH_CREATE_P2:
            if (head2->next != head2)
            {
                printf("Polynomia2 1 given below already created. \n");
                display(head2);
                continue;
            }
            create_poly(head2);
            display(head2);
            break;
        case CH_EVAL_P1:
            eval_poly(head1);
            break;
        case CH_EVAL_P2:
            eval_poly(head2);
            break;
        case CH_SUM_POLY:
            if (headsum->next != headsum)
            {
                printf("Sum of polynomials already done");
                display(headsum);
                continue;
            }
            polysum(head1, head2, headsum);
            display(headsum);
            break;
        case CH_EVAL_SUM:
            eval_poly(headsum);
            break;
        default:
            printf("Invalid choice %u\n", choice);
            break;
        }
    }
}
