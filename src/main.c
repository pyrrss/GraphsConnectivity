#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "graphsUtil.h"

void loadGraph(char* fileName, Graph *graph)
{
    FILE *file = fopen(fileName, "r");

    if(file == NULL)
    {
        printf("Error leyendo archivo \n");
        exit(1);
    }

    int graphOrder;
    fscanf(file, "%d", &graphOrder);
    
    createGraph(graph, graphOrder);
    
    char buffer[256];

    while(fgets(buffer, sizeof(buffer), file) != NULL)
    {

        int source;
        sscanf(buffer, "%d", &source); // -> obtiene vértice desde el que se lee lista de adyacencia

        char *token = strtok(buffer, ":");
        token = strtok(NULL, ", ");

        while(token != NULL)
        {   
            int destiny = atoi(token);

            if(destiny > 0) // -> si es 0 significa lista de adyacencia vacia para el nodo actual
            {
                addEdge(graph, source, destiny);
            }

            token = strtok(NULL, ", ");
        }
        
        

    }

    fclose(file);

}

int main(int argc, char *argv[])
{
    
    //char *currentGraphFile = "../graphsExamples/graph9";
    char *currentGraphFile = argv[1];

    
    if(argc < 2)
    {
        printf("Se requiere un archivo como argumento \n");
        exit(1);
    }

    Graph graph;
    
    loadGraph(currentGraphFile, &graph);
    showGraph(&graph);

    int maxGrade = getMaxGrade(&graph);
    int minGrade = getMinGrade(&graph);

    printf("\n");
    printf("Grado máximo: %d", maxGrade);
    printf("\n");
    printf("Grado mínimo: %d \n", minGrade);

    if(!isConnected(&graph, NULL))
    {

        printf("El grafo es disconexo");

    } else{
        
        printf("El grafo es conexo");
        
    }
    
    printf("\n");
    int k = getKConnectivity(&graph);
    printf("EL grafo es %d-conexo", k);

    // FALTA MANEJO WHILE TRUE E INTERFAZ TERMINAL

    printf("\n");
    return 0;
}
