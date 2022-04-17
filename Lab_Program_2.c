#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool ispat(char src[], char pat[], size_t len)
{
    bool res = true;
    for (size_t i = 0; i < len; i++)
    {
        if (src[i] != pat[i])
        {
            res = false;
            break;
        }
    }
    return res;
}

void copyrepl(char *dst, char *rep, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        dst[i] = rep[i];
    }
}
char *patreplace(char *src, char *pat, char *rep)
{
    /* check if pattern exist in the string */
    size_t srclen = strlen(src);
    size_t patlen = strlen(pat);
    size_t replen = strlen(rep);
    char *res = calloc(srclen * replen + 1, sizeof(char));
    size_t ai = 0; // index into answer buffer.

    for (size_t si = 0; si < srclen - patlen + 1;)
    {
        /* check if pattern exists in the source*/
        if (ispat(&src[si], pat, patlen))
        {
            // pattern is found. replace the pattern
            copyrepl(&res[ai], rep, replen);
            ai += replen;
            si += patlen;
        }
        else
        {
            res[ai++] = src[si++];
        }
    }
    return res;
}

int main(int argc, char *argv[argc + 1])
{
    if (argc < 4)
    {
        printf("Usage: %s <text> <pattern> <replacetext>", argv[0]);
        exit(1);
    }
    char *src = argv[1];
    char *pat = argv[2];
    char *rep = argv[3];
    char *ans = NULL;

    char *result = patreplace(src, pat, rep);
    printf("Replace String: %s\n", result);
}