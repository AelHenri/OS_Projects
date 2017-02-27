#ifndef QUEUE
#define QUEUE
/**
  * This sample is about how to implement a queue in c
  *
  * Type of item is int
  * Add item to tail
  * Get item from head
  * Can get the size
  * Can display all content
  */
/**
 * The Node struct,
 * contains item and the pointer that point to next node.
 */

typedef struct Node{
    int item;
    struct Node* next;
}Node;
/**
 * The Queue struct, contains the pointers that
 * point to first node and last node, the size of the Queue,
 * and the function pointers.
 */
typedef struct Queue{
    Node* head;
    Node* tail;

    void (*push) (struct Queue*, int); // add item to tail
    // get item from head and remove it from queue
    int (*pop) (struct Queue*);
    // get item from head but keep it in queue
    int (*peek) (struct Queue*);
    // display all element in queue
    void (*display) (struct Queue*);
    // size of this queue
    int size;
}Queue;

/**
 * Create and initiate a Queue
 */
Queue createQueue();

/**
 * Push an item into queue, if this is the first item,
 * both queue->head and queue->tail will point to it,
 * otherwise the oldtail->next and tail will point to it.
 */
void push(Queue* queue, int item);
/**
 * Return and remove the first item.
 */
int pop(Queue* queue);
/**
 * Return but not remove the first item.
 */
int peek(Queue* queue);
/**
 * Show all items in queue.
 */
void display(Queue* queue);
/**
 * Create and initiate a Queue
 */

#endif
