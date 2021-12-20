/*
 * This file is where you should implement your queue. It already contains skeletons of the functions you need to implement (along with documentation for each function).
 *
 * Name: Pranav Prabhu
 * Email: prabhup@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "dynarray.h"

/*
 * This is the structure that will be used to represent a queue. This structure specifically contains a single field representing a dynamic array that should be used as the underlying data storage for the queue. You should not modify this structure.
 */
struct queue {
	struct dynarray* array;
};

/*
 * This function should allocate and initialize a new, empty queue and return a pointer to it.
 */
struct queue* queue_create() {
	struct queue* q = malloc(sizeof(struct queue));
	q->array = dynarray_create();
	return q;
}

/*
 * This function should free the memory associated with a queue. While this function should free up all memory used in the queue itself, it should not free any memory allocated to the pointer values stored in the queue. This is the responsibility of the caller.
 *
 * Parameter:
 *   queue - the queue to be destroyed (may not be NULL)
 */
void queue_free(struct queue* queue) {
	dynarray_free(queue->array);
	free(queue);
}

/*
 * This function should indicate whether a given queue is currently empty. Specifically, it should return 1 if the specified queue is empty (i.e. contains no elements) and 0 otherwise.
 *
 * Parameter:
 *   queue - the queue whose emptiness is being questioned (may not be NULL)
 */
int queue_isempty(struct queue* queue) {
	if (dynarray_size(queue->array) == 0) return 1;
 	return 0;
}

/*
 * This function should enqueue a new value into a given queue. The value to be enqueued is specified as a void pointer. This function must have O(1) average runtime complexity.
 *
 * Parameters:
 *   queue - the queue into which a value is to be enqueued (may not be NULL)
 *   val - the value to be enqueued (note that this parameter has type void*, which means that a pointer of any type can be passed)
 */
void queue_enqueue(struct queue* queue, void* val) {
	dynarray_insert(queue->array, val);
}

/*
 * This function should return the value stored at the front of a given queue *without* removing that value.  This function must have O(1) average runtime complexity.
 *
 * Parameter:
 *   queue - the queue from which to query the front value (may not be NULL)
 */
void* queue_front(struct queue* queue) {
	return get_top(queue->array);
}

/*
 * This function should dequeue a value from a given queue and return the dequeued value. This function must have O(1) average runtime complexity.
 *
 * Parameter:
 *   queue - the queue from which a value is to be dequeued (may not be NULL)
 *
 * Return:
 *   This function should return the value that was dequeued.
 */
void* queue_dequeue(struct queue* queue) {
	void* popped_value = remove_top(queue->array);
	
	return popped_value;
}
