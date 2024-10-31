#include <stdio.h>

typedef struct Node
{

    int vertex;
    struct Node *next; // -> Cada vértice apunta al siguiente vértice en la lista de adyacencia

} Node;

typedef struct Graph
{

    int order;
    Node **adjacencyLists; // -> Lista de listas de adyacencias (cada vértice tiene su propia lista de adyacencia)

} Graph;