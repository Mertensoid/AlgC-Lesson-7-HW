//
//  main.c
//  AlgC-Lesson-7-HW
//
//  Created by admin on 04.08.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20

void solution1();
void solution2();
void solution3();
void menu();

int main(int argc, const char * argv[]) {
    menu();
    return 0;
}

void menu() {
    int solutionNumber;
    printf("Choose solution (1..3):\n");
    scanf("%d", &solutionNumber);
    switch (solutionNumber) {
        case 1:
            solution1();
            break;
        case 2:
            solution2();
            break;
        case 3:
            solution3();
            break;
        default:
            printf("Wrong solution number!");
            break;
    }
}

int matrix[MAX][MAX];
int num = 0;

void readMatrix() {
    const char* fileName = "/Users/admin/Documents/Обучение/GeekBrains/GB-iOS-Algorithms/AlgC-Homework-7/matrix.txt";
    
    printf("Enter vert num:\n");
    scanf("%d", &num);
    
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("No file");
        exit(1);
    }
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);
}

void printMatrix(int currentMatrix[MAX][MAX]) {
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            printf("%d ", currentMatrix[i][j]);
        }
        printf("\n");
    }
}

void solution1() {
    readMatrix();
    printMatrix(matrix);
}

struct queue {
    int items[MAX];
    int front;
    int rear;
};

struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);

void display(struct queue* q);
int isEmpty(struct queue* q);

void printQueue(struct queue* q);

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

struct Graph* createGraph(int vertices);
void addEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);

void bfs(struct Graph* graph, int startVertex) {
    struct queue* q = createQueue();
 
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);
 
    while(!isEmpty(q)){
        int currentVertex = dequeue(q);
        printf("Visited %d\n", currentVertex);
 
       struct node* temp = graph->adjLists[currentVertex];
 
       while(temp) {
            int adjVertex = temp->vertex;
            if(graph->visited[adjVertex] == 0){
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
       }
    }
}

void dfs(struct Graph* graph, int vertex) {
        struct node* adjList = graph->adjLists[vertex];
        struct node* temp = adjList;
 
        graph->visited[vertex] = 1;
        printf("Visited %d \n", vertex);
 
        while(temp!=NULL) {
            int connectedVertex = temp->vertex;
 
            if(graph->visited[connectedVertex] == 0) {
                dfs(graph, connectedVertex);
            }
            temp = temp->next;
        }
}
 
struct node* createNode(int v) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}
 
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
 
void addEdge(struct Graph* graph, int src, int dest) {
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
 
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

struct queue* createQueue() {
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(struct queue* q) {
    if(q->rear == -1)
        return 1;
    else
        return 0;
}

void enqueue(struct queue* q, int value) {
    if (q->rear == MAX-1)
        printf("\nQueue is Full!!");
    else {
        if(q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(struct queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        item = -1;
    }
    else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

void printQueue(struct queue *q) {
    int i = q->front;
    if(isEmpty(q)) {
        printf("Queue is empty\n");
    } else {
        for (i = q->front; i < q->rear + 1; i++) {
                printf("%d ", q->items[i]);
        }
    }
}

void solution2() {
    struct Graph* graph = createGraph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
 
    dfs(graph, 0);
}

void solution3() {
    struct Graph* graph = createGraph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
 
    bfs(graph, 0);
}

