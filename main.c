#include <stdio.h>
#include <stdlib.h>

static int QUEUE_COUNTER = 0;
static int QUEUE_SIZE = 12;

typedef struct Node {
    int value;
    struct Node* node;
} Node;

Node* create_new_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if(node == NULL) {
        perror("AllocMem Error: ");
        exit(1);
    }
    node->value = value;
    node->node = NULL;
    return node;
}

void push_node(Node* node, int value) {
    while(node->node != NULL) {
        node = node->node;
    }
    Node* new_node = create_new_node(value);
    node->node = new_node;
    if(node->node == NULL) {
        perror("NotLinkedNode Error");
        exit(1);
    }
}

void pop_node(Node* node) {
    Node* garbage_node = node->node;
    *node = *node->node;
    free(garbage_node);
}

void show_node(Node* node) {
    while(node != NULL) {
        printf("Node Value: %i Node Address %p\n", node->value, node);
        node = node->node;
    }
}

typedef struct Queue {
    Node** nodes;
} Queue;

Queue* create_new_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if(queue == NULL) {
        perror("AllocMem Error: ");
        exit(1);
    }
    queue->nodes = (Node**)malloc(sizeof(int) * QUEUE_SIZE);
    if(queue->nodes == NULL) {
        perror("AllocMem Error: ");
        exit(1);
    }

    return queue;
}

void enqueue(Queue* queue, Node* new_node) {
    queue->nodes[QUEUE_COUNTER] = new_node;
    QUEUE_COUNTER++;
}

void dequeue(Queue* queue) {
    if(QUEUE_COUNTER == 0) {
        return;
    }
    int nextIndex = 1;
    Node* garbage_node = queue->nodes[0];
    for(size_t i = 0; i < QUEUE_COUNTER; i++) {
        queue->nodes[i] = queue->nodes[nextIndex];
        nextIndex++;
    }
    free(garbage_node);
    QUEUE_COUNTER--;
}

void show_queue(Queue* queue) {
    for(size_t i = 0; i < QUEUE_COUNTER; i++) {
        printf("Index: %lu  Value: %i Address: %p\n",i,queue->nodes[i]->value, queue->nodes[i]);
    }
}

void show_structure(Queue* queue) {
    for(size_t i = 0; i < QUEUE_COUNTER; i++) {
        Node* node = queue->nodes[i];
        printf("Index: %lu\n", i);
        while(node->node != NULL) {
            printf("\t Value: %i Address: %p\n",node->value, node );
            node = node->node;
        }
    }
}

int main(void) {
    Queue* queue = create_new_queue();
    Node* node = create_new_node(0);
    Node* node2 = create_new_node(0);

    for(size_t i = 1; i < 10; i++) {
        push_node(node, (int)i);
        push_node(node2, (int)i);
    }
    enqueue(queue, node2);
    enqueue(queue, node);
    for(size_t i = 0; i < 3; i++) {
        pop_node(node);
    }
    show_structure(queue);
    printf("----------------\n");
    dequeue(queue);
    show_structure(queue);
    dequeue(queue);
    dequeue(queue); // No node to dequeue
    return 0;
}
