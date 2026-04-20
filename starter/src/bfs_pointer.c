
#include <stdlib.h>
#include "../include/graph.h"
int bfs_pointer(Graph *g, int source, int *dist)
{
    int n = g->num_vertices;
    for (int i = 0; i < n; i++) {
        dist[i] = -1; // Initialize distances to -1 (unreachable)
    }
    int* queue = (int*)malloc(n * sizeof(int)); // Queue for BFS
    if (queue == NULL) {
        return -1; // Memory allocation failed
    }
    int front = 0, rear = 0; // Initialize queue pointers
    dist[source] = 0; // Distance to source is 0
    queue[rear++] = source; // Enqueue source vertex
    while (front < rear) {
        int u = queue[front++]; // Dequeue vertex
        Edge* e = g->vertices[u].head; // Get head of neighbor linked list
        while (e != NULL) {
            int v = e->dst; // Get neighbor vertex
            if (dist[v] == -1) { // If vertex v is unvisited
                dist[v] = dist[u] + 1; // Update distance to vertex v
                queue[rear++] = v; // Enqueue vertex v  
            }
            e = e->next; // Move to next neighbor
        }
    }
    free(queue); // Free allocated memory
    return rear; // Return number of visited vertices
}
