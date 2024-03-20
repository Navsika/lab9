#include <stdio.h>
#include <malloc.h>
#include "graph.h"

NODE* createNode(int vertex, int value){
    //create a vertex of graph
    NODE* newNode = malloc(sizeof(NODE));
    newNode->vertex = vertex;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

GRAPH* createGraph(int numVert){
    //create graph with creation of lists
    GRAPH* newGraph = malloc(sizeof(GRAPH));
    newGraph->numVertices = numVert;

    newGraph->list = malloc(numVert * sizeof(NODE*));
    for (int i = 0; i < numVert; ++i)
        newGraph->list[i] = NULL;
    return newGraph;
}

void addEdge(GRAPH *graph, int start, int end, int value){
    //add edge between two vertex (
    //an undirected graph)
    NODE *node = createNode(end, value);
    node->next = graph->list[start - 1];
    graph->list[start - 1] = node;

    node = createNode(start, value);
    node->next = graph->list[end - 1];
    graph->list[end - 1] = node;
}

void printGraph(GRAPH *graph){
    for (int i = 0; i < graph->numVertices; ++i) {
        NODE *temp = graph->list[i];
        printf("%d: ", i + 1);
        while (temp != NULL){
            printf("%d ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}
