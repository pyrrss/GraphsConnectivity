#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graphsUtil.h"

void showGraph(Graph *graph)
{

    for(int i = 0;i < graph->order;i++)
    {

        Node* currentNode = graph->adjacencyLists[i];
        Node* tempNode = currentNode;

        printf("%d: ", i+1);
        
        // Solo para contar cuantos vertices hay en la lista de adyacencia y luego imprimirlos en orden inverso (como en archivo)
        int counter = 0;
        while(tempNode != NULL) // -> hasta llegar al final de la lista de adyacencia
        {

            counter++;
            tempNode = tempNode->next; // -> avanza a siguiente nodo en lista de adyacencia

        }

        int vertexes[counter];
        int index = 0;

        while(currentNode != NULL) // -> hasta llegar al final de la lista de adyacencia
        {

            vertexes[index] = currentNode->vertex;
            currentNode = currentNode->next;
            index++;

        }

        // Imprimir vertices en orden inverso para mostrar como en archivo 
        for(int j = counter - 1;j >= 0;j--)
        {

            printf("%d ", vertexes[j]+1);

        }
        

        printf("\n");

    }
    


}

void createGraph(Graph *graph, int graphOrder)
{
    graph->order = graphOrder;
    graph->adjacencyLists = malloc(graph->order * sizeof(Node*));

    for(int i = 0;i < graph->order;i++)
    {

        graph->adjacencyLists[i] = NULL;

    }

} 

void addEdge(Graph *graph, int source, int destiny)
{
    // Agrega arista source - destiny
    Node* node = malloc(sizeof(Node));
    node->vertex = destiny - 1;
    node->next = graph->adjacencyLists[source - 1]; // -> apunta a inicio lista de adyacencia de source
    graph->adjacencyLists[source - 1] = node; // -> se agrega a lista de adyacencia de source

}

int getMaxGrade(Graph *graph)
{
        
    int maxGrade = 0;
    
    for(int i = 0;i < graph->order;i++)
    {

        Node *currentNode = graph->adjacencyLists[i];
        int currentGrade = 0;

        if(currentNode == NULL) // -> lista de adyacencia vacia para el nodo actual
        {
            continue;
        }

        while(currentNode != NULL) // -> se recorre lista de adyacencia hasta llegar al final
        {

            currentGrade++;
            currentNode = currentNode->next;

        }

        if(currentGrade > maxGrade)
        {

            maxGrade = currentGrade;
        
        }


    }

    return maxGrade;

}

int getMinGrade(Graph *graph)
{

    int minGrade = graph->order - 1;
    
    for(int i = 0;i < graph->order;i++)
    {

        Node *currentNode = graph->adjacencyLists[i];
        int currentGrade = 0;

        if(currentNode == NULL) // -> lista de adyacencia vacia para el nodo actual
        {

            return 0;
        
        }

        while(currentNode != NULL) // -> se recorre lista de adyacencia hasta llegar al final
        {

            currentGrade++;
            currentNode = currentNode->next;

        }

        if(currentGrade < minGrade)
        {

            minGrade = currentGrade;
            
        }

    }

    return minGrade;

}

void DFS(Graph *graph, int vertexIndex, bool *visited, bool *deleted)
{

    visited[vertexIndex] = true; 

    Node* currentNode = graph->adjacencyLists[vertexIndex]; // -> para recorrer lista de adyacencia

    while(currentNode != NULL) // -> se recorre lista de adyacencia hasta el vertice final
    {   
                                        
        if(!visited[currentNode->vertex]  && currentNode->vertex >= 0 && currentNode->vertex < graph->order)
        {
            // printf("%d ", currentNode->vertex);
            if(deleted == NULL)
            {

                DFS(graph, currentNode->vertex, visited, NULL);
            
            } else {

                if(!deleted[currentNode->vertex])
                {
                    // printf("\n %d ", currentNode->vertex);
                    DFS(graph, currentNode->vertex, visited, deleted);

                } 

            }
            

        }

        currentNode = currentNode->next; // -> avanzar al siguiente vertice en la lista de adyacencia

    }

}

bool isConnected(Graph *graph, bool *deleted)
{

    if(graph->order == 0 || graph->order == 1 ) 
    {
        return true;
    }

    if(getMinGrade(graph) == 0)
    {
        return false;
    }

    
    bool* visitedVertexes = malloc(graph->order * sizeof(bool));
    
    for(int i = 0;i < graph->order;i++)
    {

        visitedVertexes[i] = false;

    }

    int startVertexIndex = 0;
    if(deleted != NULL) // -> solo se usar para k-conectividad, no para conexidad
    {

        for(int i = 0;i < graph->order;i++) // -> para partir desde un vértice no eliminado
        {
            if(!deleted[i])
            {
                startVertexIndex = i;
                break;
            }
        }
   
    }
    

    DFS(graph, startVertexIndex, visitedVertexes, deleted);

    for(int i = 0;i < graph->order;i++)
    {

        if(deleted != NULL) // -> solo entra aca si se esta revisando la k-conexidad
        {

            if(!visitedVertexes[i] && !deleted[i]) // -> caso vertice no visitado y no eliminado, disconexo
            {
                
                free(visitedVertexes);
                return false;

            }

        } else { // -> entra si se quiere solo saber conexidad

            if(!visitedVertexes[i]) // -> caso vertice no visitado, disconexo
            {
                
                free(visitedVertexes);
                return false;

            }

        }


    }

    free(visitedVertexes);
    return true; 

}

// -----------------------------------------------------------------------------

bool testKValue(Graph *graph, int k, bool *deleted)
{

    if(k == 1)
    {
        for(int i = 0;i < graph->order;i++)
        {
            deleted[i] = true;
            bool isConnectedAfterDelete = isConnected(graph, deleted);
            deleted[i] = false;
            if(!isConnectedAfterDelete)
            {
                return false;
            }

        }

    } else if(k == 2) {

        for (int i = 0; i < graph->order; i++) 
        {
            for (int j = i + 1; j < graph->order; j++) 
            {
               
                deleted[i] = true;
                deleted[j] = true;
                bool isConnectedAfterDelete = isConnected(graph, deleted);
                deleted[i] = false; 
                deleted[j] = false; 

                if (!isConnectedAfterDelete) 
                {
                    return false; // Si se desconecta, retorna false
                }
            }
        }
        
    } else if(k == 3) {

        for (int i = 0; i < graph->order; i++) 
        {
            for (int j = i + 1; j < graph->order; j++) 
            {
                for (int l = j + 1; l < graph->order; l++) 
                {
                    deleted[i] = true; 
                    deleted[j] = true; 
                    deleted[l] = true; 
                    bool isConnectedAfterDelete = isConnected(graph, deleted);
                    deleted[i] = false; 
                    deleted[j] = false; 
                    deleted[l] = false; 

                    if (!isConnectedAfterDelete) {
                        return false;
                    }
                }
            }
        }
    } else if(k == 4) {

        for (int i = 0; i < graph->order; i++) {
            for (int j = i + 1; j < graph->order; j++) {
                for (int l = j + 1; l < graph->order; l++) {
                    for (int m = l + 1; m < graph->order; m++) {
                        deleted[i] = true; 
                        deleted[j] = true; 
                        deleted[l] = true; 
                        deleted[m] = true; 
                        bool isConnectedAfterDelete = isConnected(graph, deleted);
                        deleted[i] = false; 
                        deleted[j] = false; 
                        deleted[l] = false; 
                        deleted[m] = false; 

                        if (!isConnectedAfterDelete) {
                            return false; 
                        }
                    }
                }
            }
        }
    }

    return true;

}
/**
 * @brief asdasd
 * @param 
 * @author asdasd
 */
int getKConnectivity(Graph *graph)
{
    if(getMinGrade(graph) == 0)
    {
        return 0;
    }

    bool *deleted = malloc(graph->order * sizeof(bool)); // -> para ir marcando vértices eliminados
    // int *combination = malloc(4 * sizeof(int)); // -> combinaciones de k vertices eliminados
   
    for(int i = 0;i < graph->order;i++)
    {
        deleted[i] = false;
    }

    if(!isConnected(graph, NULL)) // -> si es disconexo es 0-conexo
    {

        return 0;

    }

    for(int k = 1;k <= 4;k++)
    {

        if(!testKValue(graph, k, deleted))
        {

            free(deleted);
            // free(combination);
            return k;

        }

    }

    free(deleted);
    // free(combination);
    return 4; // -> si no falla para ningun k entre 1-4, al menos 4-conexo

}



