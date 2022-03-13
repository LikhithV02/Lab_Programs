#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* define hash data node
 * containing key as 4 digits value,
 * data as anything e.g. name
 */

#define SIZE_NAME 100
#define SIZE_HASH 100
typedef struct node
{
    int key;
    char name[SIZE_NAME];
} node_t;

node_t hash[SIZE_HASH] = {{0, ""}};

int hashfn(int key)
{
    return (key % SIZE_HASH);
}
//-------------------------------------------------------
// check the next available slot.
// If none available, return -1
int linear_probe(int curr)
{
    int temp = curr;
    // check for next slot to be free
    // ensure to roll over
    temp = (temp + 1) % SIZE_HASH;
    while (temp != curr)
    {
        if (hash[temp].key == 0)
        {
            return temp;
        }
        temp++;
    }
    // no empty slot is found
    return -1;
}
//-------------------------------------------------------
int main(int argc, char *argv[])
{
    FILE *fp;
    node_t data;
    int hash_val;

    if (argc < 2)
    {
        printf("Usage: %s <filename>", argv[1]);
        exit(1);
    }

    // read data and insert into hash
    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        printf("Error in opening file %s\n", argv[1]);
        exit(1);
    }
    while (fscanf(fp, "%d %s", &data.key, data.name) != EOF)
    {
        // validate data key, should be 4 digits only
        if (data.key < 1000 || data.key > 9999)
        {
            // invalid record
            printf("Key %d is not 4 digits\n", data.key);
            continue;
        }
        hash_val = hashfn(data.key);
        // check hash is empty, if so enter values
        if (hash[hash_val].key == 0)
        {
            hash[hash_val].key = data.key;
            strncpy(hash[hash_val].name, data.name, SIZE_NAME);
            continue;
        }
        // hash is not empty.
        // Perform linear probe to find empty slot
        hash_val = linear_probe(hash_val);
        if (hash_val == -1)
        { // no empty slots
            printf("Hash full. Can't enter key %d\n", data.key);
            exit(1);
        }
        // insert data into hash
        hash[hash_val].key = data.key;
        strncpy(hash[hash_val].name, data.name, SIZE_NAME);
    } // end while
    // print all hash entries
    for (int i = 0; i < SIZE_HASH; i++)
    {
        if (hash[i].key != 0)
        {
            printf("%d %d %s\n", i, hash[i].key, hash[i].name);
        }
    } // end for print hash entries
    return 0;
}