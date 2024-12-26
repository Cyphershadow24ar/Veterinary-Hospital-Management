#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define V 13  // Adjusted size for the new number of clinics
#define INF 99999  // Representing infinity for unreachable nodes

void saveToDotFile(int parent[], int dist[], int graph[V][V], char *vertex[], int src, int dest) {
    FILE *f = fopen("graph.dot", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(f, "graph G {\n");
    // Add nodes with labels
    for (int i = 0; i < V; i++) {
        fprintf(f, "    \"%s\" [label=\"%s\"];\n", vertex[i], vertex[i]);
    }
    // Add edges with weights labeled as "km"
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph[i][j] != 0 && graph[i][j] != INF) {
                fprintf(f, "    \"%s\" -- \"%s\" [label=\"%d km\"];\n", vertex[i], vertex[j], graph[i][j]);
            }
        }
    }
    // Highlight the shortest path in red with thicker lines
    int v = dest;
    while (parent[v] != -1) {
        fprintf(f, "    \"%s\" -- \"%s\" [color=red, penwidth=2.0, label=\"%d km\"];\n",
                vertex[parent[v]], vertex[v], graph[parent[v]][v]);
        v = parent[v];
    }
    fprintf(f, "}\n");
    fclose(f);
    printf("Graph saved to 'graph.dot'.\n");
}

void printPath(int parent[], int v, char *vertex[]) {
    if (parent[v] == -1) {
        printf("%s", vertex[v]);
        return;
    }
    printPath(parent, parent[v], vertex);
    printf(" -> %s", vertex[v]);
}

void printSolution(int dist[], int parent[], char *vertex[], int visitedSequence[], int src, int dest) {
    printf("\nSource: %s\nDestination: %s\n", vertex[src], vertex[dest]);
    printf("Shortest Distance: %d\n", dist[dest]);
    printf("Path: ");
    printPath(parent, dest, vertex);
    printf("\nVisit Sequence: %d\n", visitedSequence[dest]);
}

int getIndex(char *vertex[], char *name) {
    for (int i = 0; i < V; i++) {
        if (strcmp(vertex[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {
    char *vertex[V] = {
        "CVRGU", "Hello Pet Cares", "Anisha Pet Care Clinic", "Petvetcure", 
        "Govt. Veterinary Hospital", "Vet Surgery Dept. OUAT", "Bhubaneswar Pet Clinic", 
        "Aashrey Pet Clinic", "Royal Pet Clinic", "VetCare Pet Clinic", 
        "Blue Cross Vet Clinic", "Petland Veterinary Clinic", "Dr. Panda’s Pet Clinic"
    };

    int graph[V][V] = {
        {0, 12, 15, 12, 14, 15, 16, 14, 15, 14, 20, 13, 15},  // CVRGU
        {12, 0, 5, INF, INF, INF, INF, INF, INF, INF, INF, 10, INF},  // Hello Pet Cares
        {15, 5, 0, INF, INF, INF, INF, INF, INF, 3, 5, INF, INF},  // Anisha Pet Care Clinic
        {12, INF, INF, 0, 6, INF, INF, INF, INF, INF, INF, INF, INF},  // Petvetcure
        {14, INF, INF, 6, 0, 5, INF, 8, INF, INF, INF, INF, INF},  // Govt. Veterinary Hospital
        {15, INF, INF, INF, 5, 0, INF, INF, INF, 7, INF, INF, INF},  // Vet Surgery Dept. OUAT
        {16, INF, INF, INF, INF, INF, 0, 2, INF, INF, INF, INF, INF},  // Bhubaneswar Pet Clinic
        {14, INF, INF, INF, 2, INF, INF, 0, 3, INF, INF, INF, INF},  // Aashrey Pet Clinic
        {15, INF, 3, INF, INF, INF, INF, 3, 0, 5, INF, INF, INF},  // Royal Pet Clinic
        {14, INF, 5, INF, INF, INF, INF, INF, 5, 0, 6, INF, INF},  // VetCare Pet Clinic
        {20, INF, INF, 4, INF, INF, INF, INF, INF, INF, INF, 6, INF},  // Blue Cross Vet Clinic
        {15, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 2},  // Petland Veterinary Clinic
        {14, INF, INF, INF, 2, INF, INF, 3, INF, INF, INF, INF, 0}   // Dr. Panda’s Pet Clinic
    };

    int dist[V], visited[V], visitedSequence[V], parent[V];
    int src = 0, seq = 1;
    char destName[50];

    printf("Enter the destination vertex name (e.g., 'Hello Pet Cares', 'Govt. Veterinary Hospital', etc.): ");
    scanf(" %[^\n]%*c", destName);
    int dest = getIndex(vertex, destName);
    if (dest == -1) {
        printf("Invalid vertex name entered!\n");
        return 1;
    }

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
        visitedSequence[i] = -1;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int k = 0; k < V - 1; k++) {
        int min = INF, u = -1;
        for (int i = 0; i < V; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }
        if (u == -1) break;  // No reachable vertices
        visited[u] = 1;
        visitedSequence[u] = seq++;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printSolution(dist, parent, vertex, visitedSequence, src, dest);
    saveToDotFile(parent, dist, graph, vertex, src, dest);
    return 0;
}
