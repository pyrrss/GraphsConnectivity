#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "graphsUtil.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

bool loadGraph(char* fileName, Graph *graph)
{
    FILE *file = fopen(fileName, "r");

    if(file == NULL)
    {
        printf(RED "Error leyendo archivo %s. Verifique que el nombre sea correcto \n" RESET, fileName);
        return false;
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
    return true;

}

void showMenu() {

    printf("\n" BOLD CYAN "--- Menu Principal ---\n" RESET);
    printf(YELLOW "1. " RESET "Cargar Grafo desde archivo\n");
    printf(YELLOW "2. " RESET "Imprimir Grafo\n");
    printf(YELLOW "3. " RESET "Grado Máximo\n");
    printf(YELLOW "4. " RESET "Grado Mínimo\n");
    printf(YELLOW "5. " RESET "Comprobar si es Conexo\n");
    printf(YELLOW "6. " RESET "Obtener k-conexidad\n");
    printf(YELLOW "0. " RESET "Salir\n");
    printf(CYAN "Seleccione una opción: " RESET);

}


int main(int argc, char *argv[])
{
    int choice;
    Graph graph;
    bool graphLoaded = false;

    while (true) {
        showMenu();

        if (scanf("%d", &choice) != 1) {
            printf(RED "Opción no válida. Por favor, intente de nuevo.\n" RESET);
            while (getchar() != '\n'); 
            //choice = -1;
            continue;
        }

        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        switch (choice) {
            case 1: {
                char fileName[256];
                printf("Ingrese el nombre del archivo del grafo: ");
                scanf("%s", fileName);
                if(loadGraph(fileName, &graph))
                {   
                    graphLoaded = true;
                    printf(GREEN "Grafo cargado exitosamente.\n" RESET);
                } else {
                    printf(RED "Error al cargar el grafo. Intente de nuevo \n" RESET);
                    graphLoaded = false;
                }
                break;
            }
            case 2: {
                if (graphLoaded) {
                    printf("\n");
                    showGraph(&graph);
                } else {
                    printf(RED "Primero cargue un grafo desde un archivo.\n" RESET);
                }
                break;
            }
            case 3: {
                if (graphLoaded) {
                    int maxGrade = getMaxGrade(&graph);
                    printf(GREEN "\nEl grado máximo es: %d\n" RESET, maxGrade);
                } else {
                    printf(RED "Primero cargue un grafo desde un archivo.\n" RESET);
                }
                break;
            }
            case 4: {
                if (graphLoaded) {
                    int minGrade = getMinGrade(&graph);
                    printf(GREEN "\nEl grado mínimo es: %d\n" RESET, minGrade);
                } else {
                    printf(RED "Primero cargue un grafo desde un archivo.\n" RESET);
                }
                break;
            }
            case 5: {
                if (graphLoaded) {
                    if(!isConnected(&graph, NULL)){
                        printf(RED "\nEl grafo es disconexo\n" RESET);
                    } else {
                        printf(GREEN "\nEl grafo es conexo\n" RESET);
                    }
                } else {
                    printf(RED "Primero cargue un grafo desde un archivo.\n" RESET);
                }
                break;
            }
            case 6: {
                if (graphLoaded) {
                    int k = getKConnectivity(&graph);
                    printf(GREEN "El grafo es %d-conexo\n" RESET, k);
                } else {
                    printf(RED "Primero cargue un grafo desde un archivo.\n" RESET);
                }
                break;
            }
            case 0:
                printf(MAGENTA "Saliendo del programa...\n" RESET);
                return 0;
            default:
                printf(RED "Opción no válida. Por favor, intente de nuevo.\n" RESET);
        }
    }

    printf("\n");
    return 0;
}

   

   
    
 