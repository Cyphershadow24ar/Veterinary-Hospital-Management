#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the number of vertices (clinics) and a large value to represent infinity
#define V 13  // Adjusted size for the number of clinics
#define INF 99999  // A high value used to indicate no connection between vertices

// Function to save the graph and shortest path into a DOT file for visualization
void saveToDotFile(int parent[], int dist[], int graph[V][V], char *vertex[], int src, int dest) {
    FILE *f = fopen("graph.dot", "w");  // Open a file to write the DOT representation
    if (f == NULL) {  // Handle file opening errors
        printf("Error opening file!\n");
        return;
    }
    fprintf(f, "graph G {\n");  // Start the DOT graph definition
    
    // Add each vertex to the DOT graph
    for (int i = 0; i < V; i++) {
        fprintf(f, "    \"%s\" [label=\"%s\"];\n", vertex[i], vertex[i]);
    }
    
    // Add all edges to the graph with weights
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {  // Avoid duplicate edges
            if (graph[i][j] != 0 && graph[i][j] != INF) {  // Include only valid edges
                fprintf(f, "    \"%s\" -- \"%s\" [label=\"%d km\"];\n", vertex[i], vertex[j], graph[i][j]);
            }
        }
    }
    
    // Highlight the shortest path in red with thicker edges
    int v = dest;  // Start from the destination vertex
    while (parent[v] != -1) {  // Trace back the path using the parent array
        fprintf(f, "    \"%s\" -- \"%s\" [color=red, penwidth=2.0, label=\"%d km\"];\n",
                vertex[parent[v]], vertex[v], graph[parent[v]][v]);
        v = parent[v];  // Move to the parent vertex
    }
    fprintf(f, "}\n");  // End the DOT graph definition
    fclose(f);  // Close the file
    printf("Graph saved to 'graph.dot'.\n");  // Notify the user
}

// Recursive function to print the shortest path using the parent array
void printPath(int parent[], int v, char *vertex[]) {
    if (parent[v] == -1) {  // Base case: source vertex reached
        printf("%s", vertex[v]);
        return;
    }
    printPath(parent, parent[v], vertex);  // Recursively print the path
    printf(" -> %s", vertex[v]);  // Print the current vertex
}

// Function to print the shortest distance, path, and visit sequence
void printSolution(int dist[], int parent[], char *vertex[], int visitedSequence[], int src, int dest) {
    printf("\nSource: %s\nDestination: %s\n", vertex[src], vertex[dest]);  // Print source and destination
    printf("Shortest Distance: %d\n", dist[dest]);  // Print the shortest distance
    printf("Path: ");
    printPath(parent, dest, vertex);  // Print the path using the recursive function
    printf("\nVisit Sequence: %d\n", visitedSequence[dest]);  // Print the visit sequence
}

// Function to find the index of a vertex by its name
int getIndex(char *vertex[], char *name) {
    for (int i = 0; i < V; i++) {  // Loop through the vertex array
        if (strcmp(vertex[i], name) == 0) {  // Compare names
            return i;  // Return the index if found
        }
    }
    return -1;  // Return -1 if not found
}

// Main function to implement Dijkstra's algorithm and visualize the graph
int main() {
    // Define the names of the clinics
    char *vertex[V] = {
        "CVRGU", "Hello Pet Cares", "Anisha Pet Care Clinic", "Petvetcure", 
        "Govt. Veterinary Hospital", "Vet Surgery Dept. OUAT", "Bhubaneswar Pet Clinic", 
        "Aashrey Pet Clinic", "Royal Pet Clinic", "VetCare Pet Clinic", 
        "Blue Cross Vet Clinic", "Petland Veterinary Clinic", "Dr. Panda’s Pet Clinic"
    };

    // Define the adjacency matrix of the graph
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

    // Initialize arrays for distance, visited nodes, visit sequence, and parent nodes
    int dist[V], visited[V], visitedSequence[V], parent[V];
    int src = 0, seq = 1;  // Start with source as the first vertex and sequence as 1
    char destName[50];  // Buffer to store the destination name

    // Prompt the user to input the destination vertex name
    printf("Enter the destination vertex name (e.g., 'Hello Pet Cares', 'Govt. Veterinary Hospital', etc.): ");
    scanf(" %[^\n]%*c", destName);  // Read the destination name from the user
    int dest = getIndex(vertex, destName);  // Get the index of the destination vertex
    if (dest == -1) {  // Handle invalid vertex names
        printf("Invalid vertex name entered!\n");
        return 1;  // Exit with an error code
    }

    // Initialize the arrays
    for (int i = 0; i < V; i++) {
        dist[i] = INF;  // Set all distances to infinity
        visited[i] = 0;  // Mark all vertices as unvisited
        visitedSequence[i] = -1;  // Initialize visit sequence as -1
        parent[i] = -1;  // Set parent nodes as -1
    }
    dist[src] = 0;  // Distance to the source is 0

    // Main loop for Dijkstra's algorithm
    for (int k = 0; k < V - 1; k++) {
        int min = INF, u = -1;  // Initialize minimum distance and vertex
        for (int i = 0; i < V; i++) {  // Find the vertex with the smallest distance
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }
        if (u == -1) break;  // Exit if no reachable vertices are found
        visited[u] = 1;  // Mark the current vertex as visited
        visitedSequence[u] = seq++;  // Record the visit sequence

        for (int v = 0; v < V; v++) {  // Update distances for adjacent vertices
            if (!visited[v] && graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];  // Update distance
                parent[v] = u;  // Update parent node
            }
        }
    }

    // Print the solution (shortest path and details)
    printSolution(dist, parent, vertex, visitedSequence, src, dest);
    // Save the graph and shortest path to a DOT file
    saveToDotFile(parent, dist, graph, vertex, src, dest);
    return 0;  // Exit the program
}
