#include <stdbool.h>

#include "graphStructs.h"

void showGraph(Graph *graph);

void createGraph(Graph *graph, int graphOrder);

void addEdge(Graph *graph, int source, int destiny);

int getMaxGrade(Graph *graph);

int getMinGrade(Graph *graph);

void DFS(Graph *graph, int vertexIndex, bool *visited, bool *deleted);

bool isConnected(Graph *graph, bool *deleted);

bool testKValue(Graph *graph, int k, bool *deleted);

int getKConnectivity(Graph *graph);

