#ifndef SG_QUEUE_H
#define SG_QUEUE_H

struct sg_queue_node {
    int data;
    struct sg_queue_node *next;
};

struct sg_queue {
    struct sg_queue_node *head;
    struct sg_queue_node *tail;
};

struct sg_queue *sg_queue_create(void);
void sg_queue_enqueue(struct sg_queue *q, int data);
int sg_queue_dequeue(struct sg_queue *q);
int value_at(struct sg_queue *q, int index);
void sg_queue_print(struct sg_queue *q);
size_t sg_queue_size(struct sg_queue *q);
void sg_queue_destroy(struct sg_queue **q);

#endif