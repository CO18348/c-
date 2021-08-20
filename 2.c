// DFS algorithm in C

#include <stdio.h>
#include <stdlib.h>

struct node {
  int vertex;
  struct node* next;
};

struct node* createNode(int v);
struct node* head;

struct Graph {
  int numVertices;
  int* visited;
  struct node** adjLists;
};

// Print the stack
/*void printStack(struct Graph* graph, int v, int u) {

    struct node* temp = graph->adjLists[v];
    printf("\n Adjacent vertices of vertex %d\n ", v);
    while (temp && u!=1) {
      printf("%d -> ", temp->vertex);
      temp = temp->next;
    }
    printf("\n");
}*/

// DFS algo
void DFS(struct Graph* graph, int vertex) {
  struct node* adjList = graph->adjLists[vertex];
  struct node* temp = adjList;

  graph->visited[vertex] = 1;
  int u;

  struct node *newNode, *t;
    newNode = (struct node*)malloc(sizeof(struct node));
    if(newNode == NULL)
    {
        printf("Unable to allocate memory.");
    }
    else
    {
        newNode->vertex = vertex; // Link the data part
        newNode->next = NULL;
        t = head;
        // Traverse to the last node
        while(t->next != NULL)
            t = t->next;
        t->next = newNode; // Link address part
    }

  //printf("\nVisiting %d \n", vertex);

  while (temp != NULL) {
    int connectedVertex = temp->vertex;
    u=graph->visited[connectedVertex];

    if (graph->visited[connectedVertex] == 0) {
      //printStack(graph,vertex,u);
      DFS(graph, connectedVertex);
    }
    temp = temp->next;
  }
}

void createList(int n)
{

    head = (struct node *)malloc(sizeof(struct node));
    head->vertex = 0; // Link the data field with data
    head->next = NULL; // Link the address field to NULL

}

void displayList()
{
    struct node *t;
    if(head == NULL)
    {
        printf("List is empty.");
    }
    else
    {
        t = head;
        printf("Visited nodes are:");
        t=t->next;
        printf("\n\n");
        while(t != NULL)
        {
            printf("%d ", t->vertex); // Print data of current node
            t = t->next;                 // Move to next node
        }
        printf("\n\n");
    }
}


// Creating a node
struct node* createNode(int v) {
  struct node* newNode = malloc(sizeof(struct node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

// Creating a graph
struct Graph* createGraph(int vertices) {
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->numVertices = vertices;

  graph->adjLists = malloc(vertices * sizeof(struct node*));

  graph->visited = malloc(vertices * sizeof(int));

  int i;
  for (i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
    graph->visited[i] = 0;
  }
  return graph;
}

// Adding an edge
void addEdge(struct Graph* graph, int src, int dest) {
  struct node* newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

//Main function
int main() {

  int n;
  printf("Enter number of edges you wish to add in the graph:");
  scanf("%d",&n);
  struct Graph* graph = createGraph(n);

  int a[n],b[n];
  for(int i=0; i<n; i++)
  {
      printf("Enter the first vertex of the edge %d:",i);
      scanf("%d",&a[i]);
      printf("Enter the second vertex of the edge %d:",i);
      scanf("%d",&b[i]);
      addEdge(graph, a[i], b[i]);
  }
  createList(n);
  DFS(graph, 0);
  displayList();
  return 0;
}
