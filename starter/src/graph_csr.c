
#include <stdlib.h>
#include "../include/graph.h"
CSRGraph *convert_to_csr(Graph *g)
{
    int n = g->num_vertices;
    CSRGraph *csr = (CSRGraph *)malloc(sizeof(CSRGraph));
    if (csr == NULL)    {
        return NULL; // Memory allocation failed
    }
    csr->num_vertices = n;
    csr->num_edges = 0;
    for (int i = 0; i < n; i++) {
        Edge *e = g->vertices[i].head;
        while (e != NULL) {
            csr->num_edges++;
            e = e->next;
        }
    }
    csr->row_ptr = (int *)malloc((n + 1) * sizeof(int));
    if (csr->row_ptr == NULL) {
        free(csr);
        return NULL;
    }
    csr->col_idx = (int *)malloc(csr->num_edges * sizeof(int));
    if (csr->col_idx == NULL) {
        free(csr->row_ptr);
        free(csr);
        return NULL;
    }
    int edge_idx = 0;
    csr->row_ptr[0] = 0;
    for (int i = 0; i < n; i++) {
        Edge *e = g->vertices[i].head;
        while (e != NULL) {
            csr->col_idx[edge_idx++] = e->dst;
            e = e->next;
        }
        csr->row_ptr[i + 1] = edge_idx;
    }
    return csr;
}
void free_csr(CSRGraph *g)
{
    if (!g)
    {
        return;
    }
    free(g->row_ptr);
    free(g->col_idx);
    free(g);
}
