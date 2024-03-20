#include <stdio.h>
#include <malloc.h>
#include "graph.c"

int check(int n, int m, int start, int finish) {
    //to check the input
    if (n < 0 || n > 5000) {
        printf("bad number of vertices");
        exit(0);
    }

    if (m < 0 || m > n * (n - 1) / 2) {
        printf("bad number of edges");
        exit(0);
    }

    if (start < 1 || start > n || finish < 1 || finish > n) {
        printf("bad vertex");
        exit(0);
    }
}

int minEdge(NODE *list, int *passed, int *minPaths) {
    //to find the edge with the smllest value
    if (!list)
        return -1;

    int minDst = INT_MAX;
    int minIdx = -1;
    NODE *cur = list;

    while (cur) {
        int vertex = cur->vertex;
        if (*(passed + vertex) != 1 && *(minPaths + vertex) <= minDst) {
            minDst = *(minPaths + vertex);
            minIdx = vertex;
        }
        cur = cur->next;
    }
    return minIdx;
}

void dijkstra(int n, int s, int f, GRAPH *graph, int *minPaths, int *prev, int *passed) {
    //realization of dijkstra
    *(minPaths + s - 1) = 0;
    NODE *list = NULL;
    NODE *node = createNode(s - 1, 0);
    list = node;
    //start of graph

    while (list) {
        int minLen = minEdge(list, passed, minPaths);
        if (minLen == -1)
            break;
        *(passed + minLen) = 1;
        NODE *nodeList = graph->list[minLen];

        while (nodeList) {
            int vertex = nodeList->vertex - 1;

            if (*(minPaths + minLen) + nodeList->value
                <= *(minPaths + vertex)) {
                *(minPaths + vertex) = *(minPaths + minLen) + nodeList->value;
                *(prev + vertex) = minLen;

                NODE *newNode = createNode(vertex, *(minPaths + minLen) + nodeList->value);
                newNode->next = list;
                list = newNode;
            }
            nodeList = nodeList->next;
        }
    }

    int path[graph->numVertices];
    int pathLen = 0;

    int curr = f - 1;
    while (curr != -1) {
        path[pathLen++] = curr + 1;
        curr = *(prev + curr);
    }

    for (int i = 0; i < graph->numVertices; ++i) {
        if (*(minPaths + i) == INT_MAX)
            printf("oo ");
        else if (*(minPaths + i) > INT_MAX)
            printf("INT_MAX+ ");
        else
            printf("%d ", *(minPaths + i) - *(minPaths + s - 1));
    }
    printf("\n");

    int check1 = 0, check2 = 0;

    for (int i = 0; i < pathLen; ++i) {
        if (path[i] == s || path[i] == f)
            check1++;
        if (*(minPaths + i + 1) >= INT_MAX && *(minPaths + i + 1) != INT_MAX)
            check2++;
    }

    if (check1 != 2 && s != f) {
        printf("no path");
        exit(0);
    }
    else if (*(minPaths + pathLen - 1) > INT_MAX && check2 > 2) {
        printf("overflow");
        exit(0);
    }
    for (int i = 0; i < pathLen; ++i)
        printf("%d ", path[i]);

    printf("\n");
}

int main() {
    int n, s, f, m, start, end, value, numLines = 0;
    int *minPaths, *passed, *prev;
    GRAPH *graph;

    scanf("%d", &n);
    scanf("%d %d", &s, &f);
    scanf("%d", &m);

    check(n, m, s, f);
    graph = createGraph(n);

    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &start, &end, &value);

        if (!((value >= 0) && (value <= INT_MAX))) {
            printf("bad length");
            return 0;
        }

        addEdge(graph, start, end, value);
        numLines++;
    }

    if (numLines < m) {
        printf("bad number of lines");
        return 0;
    }

    minPaths = (int *) malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i)
        *(minPaths + i) = INT_MAX;

    passed = (int *) malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i)
        *(passed + i) = 0;

    prev = (int *) malloc(sizeof(int) * n);
    for (int i = 0; i < n; ++i)
        *(prev + i) = -1;

    dijkstra(n, s, f, graph, minPaths, prev, passed);

    free(graph);
    free(minPaths);
    free(passed);
    free(prev);

    return 0;
}
