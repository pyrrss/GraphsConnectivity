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

void mostrarMenu() {
    printf("\n--- Menu Principal ---\n");
    printf("1. Imprimir Grafo\n");
    printf("2. Grado Maximo\n");
    printf("3. Grado Minimo\n");
    printf("4. Comprobar si es Conexo\n");
    printf("5. Obtener k-conexidad\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
}


int main(int argc, char *argv[])
{
    int opcion;
    //char *currentGraphFile = "../graphsExamples/graph9";
    char *currentGraphFile = argv[1];

    
    if(argc < 2)
    {
        printf("Se requiere un archivo como argumento \n");
        exit(1);
    }

    Graph graph;
    
    loadGraph(currentGraphFile, &graph);
    //showGraph(&graph);

    int maxGrade = getMaxGrade(&graph);
    int minGrade = getMinGrade(&graph);

    while (true) {

        mostrarMenu();
        scanf("%d", &opcion);

        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        switch (opcion) {
            case 1:
                printf("\n");
                showGraph(&graph);
                break;
            case 2: {
                printf("\n");
                printf("El grado maximo es: %d\n", maxGrade);
                break;
            }
            case 3: {
                printf("\n");
                printf("El grado minimo es: %d\n", minGrade);
                break;
            }
            case 4: {
                if(!isConnected(&graph, NULL)){
                    printf("\n");
                    printf("El grafo es disconexo");
                    printf("\n");

                } else{
                    
                    printf("\n");
                    printf("El grafo es conexo");
                    printf("\n");
                }
                break;
            }
            case 5:
                int k = getKConnectivity(&graph);
                printf("EL grafo es %d-conexo", k);
                printf("\n");
                break;

            case 0:
                printf("Saliendo del programa...\n");
                return 0;
            default:
                printf("Opcion no valida. Por favor, intente de nuevo.\n");
        }
    }

    printf("\n");
    return 0;
}

   

   
    
 