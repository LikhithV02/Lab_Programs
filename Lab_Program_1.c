#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define CHOICE_CREATE 1
#define CHOICE_DISPLAY 2
#define CHOICE_INSERT 3
#define CHOICE_DELETE 4
#define CHOICE_EXIT 0
/**
 * This program implements a menu driven task to get familiar with
 * Array insertion, Array deletion and displaying contents of array.
 **/
unsigned int menu()
{
    unsigned int choice = CHOICE_DELETE + 1;
    while (choice > CHOICE_DELETE)
    {
        printf("Enter your choice:\n");
        printf("\t %u - Create Array\n", CHOICE_CREATE);
        printf("\t %u - Display Array Elements\n", CHOICE_DISPLAY);
        printf("\t %u - Insert Element at a Position\n", CHOICE_INSERT);
        printf("\t %u - Delete an Element at a Position\n", CHOICE_DELETE);
        printf("\t %u - Exit\n", CHOICE_EXIT);
        printf("\t choice: ");
        scanf("%d", &choice);
        if (choice > CHOICE_DELETE)
        {
            printf("ERROR: Invalid Choice\n");
        }
    }
    return choice;
}

/**
 * Create and initialize the array of integers of given size.
 * i/p: size of integer array
 * o/p: array pointer when created successfully else NULL
 * Array elements are initialize with INT_MIN (limits.h)
 **/
int *fn_create(size_t size)
{
    int *arr = calloc(size, sizeof(int));
    if (arr != (int *)NULL)
    {
        for (size_t i = 0; i < size; i++)
        {
            *(arr + i) = INT_MIN;
        }
    }
    return arr;
}

/**
 * Display all array elements with non-zero values along with their locations
 * Location display is required because array may contain holes
 **/
void fn_display(size_t arrsize, int arr[arrsize])
{
    for (size_t i = 0; i < arrsize; i++)
    {
        if (arr[i] != INT_MIN)
        {
            printf("Element location=%zu, Element value %d\n", i, arr[i]);
        }
    }
}

/**
 * Ask user array location and element value as an integer.
 * Insert the value at the specified location only if location is empty.
 * The value INT_MIN is not permissible as this is initialized value.
 **/
bool fn_insert(size_t arrsize, int arr[arrsize])
{
    size_t location;
    int value;
    bool retval = false;
    printf("Specify the location at which value to be inserted\n");
    printf("Location should be in the range 0-%zu: ", arrsize - 1);
    scanf("%zu", &location);
    if (location >= arrsize)
    {
        printf("Location %zu exceeds array size %zu\n", location, arrsize);
    }
    else if (arr[location] != INT_MIN)
    {
        printf("Location %zu already occupied with value %d\n", location, arr[location]);
    }
    else
    {
        printf("Enter the value to be inserted at location %zu: ", location);
        scanf("%d", &value);
        arr[location] = value;
        retval = true;
    }
    return retval;
}

/**
 * Ask user array location at which location is to be deleted.
 * Delete the value at the specified location only if location is non-empty.
 **/
bool fn_delete(size_t arrsize, int arr[arrsize])
{
    size_t location;
    bool retval = false;
    printf("Specify location (0-%zu) whose value to be deleted: ", arrsize - 1);
    scanf("%zu", &location);
    if (location >= arrsize)
    {
        printf("Location %zu exceeds array size %zu\n", location, arrsize);
    }
    else if (arr[location] == INT_MIN)
    {
        printf("Location %zu does not contain any value \n", location);
    }
    else
    {
        printf("The value %d at location %zu has been deleted\n", arr[location], location);
        arr[location] = INT_MIN;
        retval = true;
    }
    return retval;
}

/** Releases the memory allocated for array
 * i/p: array pointer
 **/
void fn_exit(int *arr)
{
    if (arr != NULL)
    {
    }
}
int main()
{
    size_t arrsize = 0; // Array size
    int *array = NULL;  // actual array element are stored here
    size_t choice;

    while (true)
    {
        choice = menu();
        switch (choice)
        {
        case CHOICE_CREATE:
            if (array != NULL)
            {
                printf("There already exists an array, with following elements\n");
                fn_display(arrsize, array);
            }
            else
            {
                printf("Please Specify the array size: ");
                scanf("%zu", &arrsize);
                array = fn_create(arrsize);
            }
            break;

        case CHOICE_DISPLAY:
            if (array == NULL)
            {
                printf("Array is not initialized yet. Please first create an array\n");
                continue;
            }
            fn_display(arrsize, array);
            break;

        case CHOICE_INSERT:
            if (array == NULL)
            {
                printf("Array is not initialized yet. Please first create an array\n");
                continue;
            }
            fn_insert(arrsize, array);
            break;

        case CHOICE_DELETE:
            if (array == NULL)
            {
                printf("Array is not initialized yet. Please first create an array\n");
                continue;
            }
            fn_delete(arrsize, array);
            break;

        case CHOICE_EXIT:
        default:
            fn_exit(array);
            free(array);
            exit(0);
            break;
        }
    }
}
