#include <stdio.h>
#include <stdlib.h>

#include "sg_queue.h"

struct sg_queue *sg_queue_create(void) {
    struct sg_queue *q = (struct sg_queue *)malloc(sizeof(struct sg_queue));
    
    if (q == NULL) {
        perror("Error allocating memory for new queue");
        
        exit(EXIT_FAILURE);    
    }
    
    q->head = NULL;
    q->tail = NULL;
    
    return q;
}

void sg_queue_enqueue(struct sg_queue *q, int data) {
    if (q == NULL) {
        return;
    }
    
    struct sg_queue_node *new_node = (struct sg_queue_node *)malloc(sizeof(struct sg_queue_node));
    
    if (new_node == NULL) {
        perror("Error allocating memory for new node");
        
        exit(EXIT_FAILURE);    
    }
    
    new_node->data = data;
    new_node->next = NULL;
    
    if (sg_queue_size(q) == 0) { // First insertion
        q->head = q->tail = new_node;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
}

int sg_queue_dequeue(struct sg_queue *q) {
    if (q == NULL || sg_queue_size(q) == 0) {
        perror("Queue is NULL or has zero elements.");
        
        exit(EXIT_FAILURE); 
    }
    
    struct sg_queue_node *del_node = q->head;
    int data = del_node->data;
    
    q->head = q->head->next;
    
    free(del_node);
    del_node = NULL;
    
    return data;
}

int value_at(struct sg_queue *q, int index) {
    int qsize = sg_queue_size(q);
    
    if (index < 0 || index >= qsize) {
        perror("Index out of bounds.");
        
        exit(EXIT_FAILURE);  
    }
    
    struct sg_queue_node *curr_node = q->head;
    
    int i = 0;
    
    while (i < index) {
        curr_node = curr_node->next;
        
        i++;
    }
    
    return curr_node->data;
}

void sg_queue_print(struct sg_queue *q) {
	struct sg_queue_node *curr_node = q->head;
	
	printf("%s", (curr_node == NULL) ? "[  " : "[");
	
	while (curr_node != NULL) {
		printf("%d, ", (curr_node->data));
		
		curr_node = curr_node->next;
	}
	
	printf("%s\n", "\b\b]");
}

size_t sg_queue_size(struct sg_queue *q) {
    size_t qs = 0;
    
    struct sg_queue_node *curr_node = q->head;
    
    while (curr_node != NULL) {
        qs++;
        
        curr_node = curr_node->next;
    }
    
    return qs;
}

void sg_queue_destroy(struct sg_queue **q) {
    struct sg_queue_node *curr_node = (*q)->head;
    
    while (curr_node != NULL) {
        struct sg_queue_node *next_node = curr_node->next;
        
        free(curr_node);
        curr_node = next_node;
    }
    
    free(*q);
    *q = NULL;
}