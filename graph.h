#define GRAPH struct graph
#define NODE struct node

NODE{
    //structure of node to describe vertex
    int vertex;
    int value;
    NODE *next;
};

GRAPH{
    //the list of node's lists
    int numVertices;
    NODE** list;
};

NODE *createNode(int vertex, int value);
GRAPH* createGraph(int numVert);
void addEdge(GRAPH *graph, int start, int end, int value);
void printGraph(GRAPH *graph);

