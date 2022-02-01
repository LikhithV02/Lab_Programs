#include <stdio.h>
#include <stdlib.h>

/**
 * This is a program to search a pattern in the main 
 * string using KMP algorithm and replacing the pattern
 * with a replace string in the main string
 **/

int stringlength (int n, char* string);
int *lps (char* pattern, int m);
void kmp_replace (char* string, char* pattern, char* replace);

/**
 * Function to find length of string.
 **/

int stringlength (int n, char* string) {
  if (string[n] == '\0') {
    return n;
  }
  return stringlength(n + 1, string);
}

/**
 * Function to find LPS array and return it calling function
 **/

int *lps (char* pattern, int m) {
  int *lps = (int*)calloc(m, sizeof(int));
  int len = 0;
  int i = 1;
  for (i = 0; i < m; i++) {
    *(lps + i) = 0;
  }
  while (i < m) {
    if (pattern[i] == pattern[len]) {
      *(lps + i) = len + 1;
      len++;
      i++;
    }
    else if (len != 0) {
      len = *(lps + len - 1);
    }
    else {
      *(lps + i) = 0;
      i++;
    }
  }
  return lps;
  free(lps);
}

/**
 * Function to find pattern in a string using KMP algorithm 
 * and replace it with a replace string if it is present in the string
 **/

void kmp_replace (char* string, char* pattern, char* replace) {
  int N = stringlength(0,string);
  int M = stringlength(0,pattern);
  int K = stringlength(0,replace);
  if (M != K) {
    printf ("Length of pattern string and replacement string is not equal.");  //Length of pattern string and replace string should be equal
    exit(0);
  }
  int i = 0;
  int j = 0;
  int k = 0;
  int m = 0;
  int *LPS = NULL;
  LPS = lps(pattern,M);
  while (i < N) {
    if (string[i] == pattern[j]) {
      i++;
      j++;
    }
    else {
      if (j != 0) {
        j = LPS[j-1];
      }
      else {
        if (j == 0 && i == N-1) {
          printf ("Pattern not found");
        }
        i++;
      } 
    }    
    if (j == M) {
      printf ("Pattern found at position %d in string\n", (i-j)+1);
      m = i-j;
      j = LPS[j-1];
      for (k = 0; replace[k] != '\0'; k++) {   
        string[m] = replace[k];
        m++;        
      }
      printf ("New string : %s\n",string); 
    }
  }
}

/**
 * Main function takes in the strings from command line arguments
 **/

int main (int argc, char* argv[argc + 1]) {  
  char* STR = argv[1]; //Main string
  char* PAT = argv[2]; //Pattern string
  char* REP = argv[3]; //Replace string
  kmp_replace(STR,PAT,REP);
  return 0;
}