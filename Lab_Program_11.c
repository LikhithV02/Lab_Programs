#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// create a direted graph (directed) of N cities and
// perform both BFS and DFS traversal
// it is a directed graph
// first create a graph using adjacency matrix
// Optionally create the graph as adjacency list as well
// input to the program is as below
// line 1: <n> <0|1> <start
// where  n is number of vertices, 0-undirected, 1-directed
// and <start> is the vertex to start traversal froma
// line 2 to n+1: <city number>: list of cities SPACE Separated
/* example input
4 0 1
1: 2 4
2: 3 4
3:
4: 1 2 3
*/
#define BUF_SIZE 1000 // maxbuffer size
#define UNDIRECTED 0
#define DIRECTED 1
//-------------------
// BFS traversal
// graph is nxn adrray
void bfs(unsigned int n, unsigned int adjm[n + 1][n + 1], unsigned int visited[n + 1], unsigned int start)
{
  // maintain a Queue of nodes to be visited;
  unsigned int node;                // current nsode under traveral
  unsigned int front = 0, rear = 0; // 0 implies empty queue
  unsigned int queue[n + 1];        // queue should be large enough

  queue[++rear] = start; // add start node to queue
  visited[start] = 1;    // mark start node visited
  while (rear > front)
  { // queue is not empty
    // add unvisited nodes to queues
    // node from the front of queue
    node = queue[++front];
    printf("%d ", node);
    // check adjacency list of add nodes to queue
    for (unsigned int i = 1; i <= n; i++)
    {
      if ((adjm[node][i] == 1) && (visited[i] == 0))
      {
        queue[++rear] = i;
        visited[i] = 1;
      }
    } // end for
  }   // end while
}
//-------------------
// DFS traversal.
// graph is an n*n array given as adj matrix
// visited is an array indicating if node is visited or not
void dfs(unsigned int n, unsigned int adjm[n + 1][n + 1], unsigned int visited[n + 1], unsigned int start)
{
  visited[start] = 1;
  printf("%d ", start);
  for (unsigned int i = 1; i <= n; i++)
  {
    // traverse the unvisited node in adj list
    if ((adjm[start][i] == 1) && (visited[i] == 0))
    {
      dfs(n, adjm, visited, i);
    }
  }
  return;
}
//-------------------
// size of adjm is (n+1)*(n+1)
void initgraph(unsigned int n, unsigned int adjm[n + 1][n + 1], unsigned int dir)
{
  char buf[BUF_SIZE];
  char *token;
  unsigned int node; // graph node
  unsigned int nbr;  // adjacency list
  // for each vertex, gets its connected nodes
  for (int i = 0; i <= n; i++)
  {
    fgets(buf, BUF_SIZE, stdin);
    token = strtok(buf, "; \n");
    if (token == NULL)
    {
      continue; // node not present
    }
    node = atoi(token); // get the node number
    if (node > n)
    { // invalid node, ignore
      continue;
    }
    // get the next node
    token = strtok(NULL, " \n");
    while (token)
    { // process all the nodes
      nbr = atoi(token);
      token = strtok(NULL, " ");
      if (nbr > n)
      {
        continue; // nbr node is invalid
      }
      // set the value in adjacency matrix
      adjm[node][nbr] = 1;
      if (dir == UNDIRECTED)
      {
        adjm[nbr][node] = 1;
      }
    } // end while token
  }   // end for
} // end initgraph
//-------------------
int main()
{
  unsigned int n;     // nummber of vertices
  unsigned int dir;   // type of graph undirected or directed
  unsigned int start; // the start vertex for traversal

  scanf("%d %d %d", &n, &dir, &start);

  if (start > n)
  {
    printf("Start vertex %d is invalid\n", start);
  }

  // allocate space for adjacency matrix
  // for ease of use, node numbers are used from 1 to n
  unsigned int adjm[n + 1][n + 1];
  unsigned int visited[n + 1];
  for (size_t i = 0; i <= n; i++)
  {
    for (size_t j = 0; j <= n; j++)
    {
      adjm[i][j] = 0; // initiaze graph with no edges
    }
  }

  initgraph(n, adjm, dir);
  for (size_t i = 0; i <= n; i++)
  {
    visited[i] = 0; // 1 means visited
  }
  for (size_t i = 1; i <= n; i++)
  {
    if (visited[i] == 0)
    {
      printf("\nBFS traversal started from %zu\n", start);
      bfs(n, adjm, visited, start);
    }
  }
  printf("\n");
  for (size_t i = 0; i <= n; i++)
  {
    visited[i] = 0; // 1 means visited
  }
  for (size_t i = 1; i <= n; i++)
  {
    if (visited[i] == 0)
    {
      printf("\nDFS traversal started from %zu\n", start);
      dfs(n, adjm, visited, start);
    }
  }
  printf("\n");
}
