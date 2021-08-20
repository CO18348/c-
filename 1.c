// BFS program

#include <stdio.h>
#include <stdlib.h>
#define SIZE 40

struct queue {
  int items[SIZE];
  int front;
  int rear;
};

struct queue* createQueue();
struct queue* createVisited();
void enqueue(struct queue* q, int);
void visited(struct queue* q, int);
int dequeue(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);
void printVisited(struct queue* arr);

struct node {
  int vertex;
  struct node* next;
};

struct node* createNode(int);

struct Graph {
  int numVertices;
  struct node** adjLists;
  int* visited;
};

// BFS algorithm
void bfs(struct Graph* graph, int startVertex) {
  struct queue* q = createQueue();
  struct queue* arr = createVisited();

  graph->visited[startVertex] = 1;
  enqueue(q, startVertex);


  while (!isEmpty(q)) {
    printf("\n");
    printQueue(q);
    printVisited(arr);
    int currentVertex = dequeue(q);
    visited(arr, currentVertex);


    struct node* temp = graph->adjLists[currentVertex];

    while (temp) {
      int adjVertex = temp->vertex;

      if (graph->visited[adjVertex] == 0) {
        graph->visited[adjVertex] = 1;
        enqueue(q, adjVertex);
      }
      temp = temp->next;
    }
  }
  printf("\n\n\nThe final Visited queue is:");
  printVisited(arr);
  printf("\n\n");
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

// Add edge
void addEdge(struct Graph* graph, int src, int dest) {

  struct node* newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

// Create a queue
struct queue* createQueue() {
  struct queue* q = malloc(sizeof(struct queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

// Create visited queue
struct queue* createVisited() {
  struct queue* arr = malloc(sizeof(struct queue));
  arr->front = -1;
  arr->rear = -1;
  return arr;
}
// Check if the queue is empty
int isEmpty(struct queue* q) {
  if (q->rear == -1)
    return 1;
  else
    return 0;
}

// Adding elements into queue
void enqueue(struct queue* q, int value) {
  if (q->rear == SIZE - 1)
    printf("\nQueue is Full!!");
  else {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}

// Adding elements into visited queue
void visited(struct queue* arr, int value) {
  if (arr->rear == SIZE - 1)
    printf("\nQueue is Full!!");
  else {
    if (arr->front == -1)
      arr->front = 0;
    arr->rear++;
    arr->items[arr->rear] = value;
  }
}
// Removing elements from queue
int dequeue(struct queue* q) {
  int item;
  if (isEmpty(q)) {
    printf("\nQueue is empty");
    item = -1;
  } else {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
      printf("\nResetting queue ");
      q->front = q->rear = -1;
    }
  }
  return item;
}

// Print the queue
void printQueue(struct queue* q) {
  int i = q->front;

  if (isEmpty(q)) {
    printf("\nQueue is empty");
  } else {
    printf("\nQueue contains \n");
    for (i = q->front; i < q->rear + 1; i++) {
      printf("%d ", q->items[i]);
    }
  }
}

// Print the visited queue
void printVisited(struct queue* arr) {
  int i = arr->front;

  if (isEmpty(arr)) {
    printf("\nVisited queue is empty");
  } else {
    printf("\nVisited queue contains \n");
    for (i = arr->front; i < arr->rear + 1; i++) {
      printf("%d ", arr->items[i]);
    }
  }
}

int main() {
  int y;
  printf("Enter the number of vertices you wish to add in the graph:");
  scanf("%d",&y);
  struct Graph* graph = createGraph(y);

  int n;
  printf("Enter number of edges you wish to add in the graph:");
  scanf("%d",&n);
  int a[n],b[n];
  for(int i=0; i<n; i++)
  {
      printf("Enter the first vertex of the edge %d:",i);
      scanf("%d",&a[i]);
      printf("Enter the second vertex of the edge %d:",i);
      scanf("%d",&b[i]);
      addEdge(graph, a[i], b[i]);
  }
  int x;
  printf("Enter the starting node:");
  scanf("%d",&x);
  bfs(graph, x);

  return 0;
}
