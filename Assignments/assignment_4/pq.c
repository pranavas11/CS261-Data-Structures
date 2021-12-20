/*
 * In this file, you will write the structures and functions needed to implement a priority queue. Feel free to implement any helper functions you need in this file to implement a priority queue.
 *
 * Name: Pranav Prabhu
 * Email: prabhup@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include "dynarray.h"
#include "pq.h"

/*
 * This is the structure that represents a priority queue. You must define this struct to contain the data needed to implement a priority queue.
 */
struct pq {
	struct dynarray* arr;
};

struct pq_node {
	void* data;
	int priority;
};

/*
 * This function should allocate and initialize an empty priority queue and return a pointer to it.
 */
struct pq* pq_create() {
	struct pq* priority_queue = malloc(sizeof(struct pq));
	priority_queue->arr = dynarray_create();
  	return priority_queue;
}

/*
 * This function should free the memory allocated to a given priority queue. Note that this function SHOULD NOT free the individual elements stored in the priority queue. That is the responsibility of the caller.
 *
 * Parameter:
 *   pq - the priority queue to be destroyed (may not be NULL)
 */
void pq_free(struct pq* pq) {
	dynarray_free(pq->arr);
	free(pq);
}

/*
 * This function should return 1 if the specified priority queue is empty and 0 otherwise.
 *
 * Parameter:
 *   pq - the priority queue whose emptiness is to be checked (may not be NULL)
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	return !dynarray_size(pq->arr);
}

void percolate_up(struct pq* pq, int index) {
	while (index > 0) {
		int parent_node = (index - 1) / 2;
		
		struct pq_node* idx = dynarray_get(pq->arr, index);
		struct pq_node* parent = dynarray_get(pq->arr, parent_node);
		
		if (idx->priority >= parent->priority) break;

		dynarray_set(pq->arr, index, parent);
		dynarray_set(pq->arr, parent_node, idx);
		index = parent_node;
	}
}

/*
 * This function should insert a given element into a priority queue with a specified priority value. Note that in this implementation, LOWER priority values are assigned to elements with HIGHER priority. In other words, the element in the priority queue with the LOWEST priority value should be the FIRST one returned.
 *
 * Parameters:
 *   pq - the priority queue into which to insert an element (may not be NULL)
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted element. Note that in this implementation, LOWER priority values should correspond to elements with HIGHER priority. In other words, the element in the priority queue with the LOWEST priority value should be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
	struct pq_node* new_node = (struct pq_node*)malloc(sizeof(struct pq_node));
	new_node->data = value;
  	new_node->priority = priority;
	dynarray_insert(pq->arr, new_node);
	percolate_up(pq, dynarray_size(pq->arr) - 1);
}

/*
 * This function should return the value of the first item in a priority queue (i.e., the item with LOWEST priority value).
 *
 * Parameter:
 *   pq - the priority queue from which to fetch a value (may not be NULL or empty)
 *
 * Return:
 *   Should return the value of the first item in pq (i.e., the item with LOWEST priority value).
 */
void* pq_first(struct pq* pq) {
	struct pq_node* pq_data = dynarray_get(pq->arr, 0);
	return pq_data->data;
}

/*
 * This function should return the priority value of the first item in a priority queue (i.e., the item with LOWEST priority value)
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value (may not be NULL or empty)
 *
 * Return:
 *   Should return the priority value of the first item in pq (i.e., the item with LOWEST priority value).
 */
int pq_first_priority(struct pq* pq) {
	struct pq_node* pq_priority = dynarray_get(pq->arr, 0);
	return pq_priority->priority;
}

void percolate_down(struct pq* pq, int index) {
	int left_node = (2 * index) + 1;
	int right_node = (2 * index) + 2;
	
	struct pq_node* left_priority;
	struct pq_node* right_priority;
	struct pq_node* index_priority;

	if (left_node >= dynarray_size(pq->arr)) {
		left_priority = NULL;
	} else {
		left_priority = dynarray_get(pq->arr, left_node);
	}
	
	if (right_node >= dynarray_size(pq->arr)) {
		right_priority = NULL;
	} else {
		right_priority = dynarray_get(pq->arr, right_node);
	}

	if (index >= dynarray_size(pq->arr)) {
		return;
	} else {
		index_priority = dynarray_get(pq->arr, index);
	}

	if (left_priority == NULL && right_priority == NULL) return;
	
	if (left_priority != NULL && right_priority == NULL) {
		if (index_priority->priority > left_priority->priority) {
			dynarray_set(pq->arr, index, left_priority);
			dynarray_set(pq->arr, left_node, index_priority);
			percolate_down(pq, left_node);
		} else return;
	} else if (left_priority == NULL && right_priority != NULL) {
		if (index_priority->priority > right_priority->priority) {
			dynarray_set(pq->arr, index, right_priority);
			dynarray_set(pq->arr, right_node, index_priority);
			index = right_node;
			percolate_down(pq, right_node);
		} else return;
	} else if (left_priority != NULL && right_priority != NULL) {
		if (left_priority->priority < right_priority->priority) {
			dynarray_set(pq->arr, index, left_priority);
			dynarray_set(pq->arr, left_node, index_priority);
			percolate_down(pq, left_node);
		} else {
			dynarray_set(pq->arr, index, right_priority);
			dynarray_set(pq->arr, right_node, index_priority);
			percolate_down(pq, right_node);
		}
	}
}

/*
 * This function should return the value of the first item in a priority queue (i.e., the item with LOWEST priority value, and then remove that item from the queue).
 *
 * Parameter:
 *   pq - the priority queue from which to remove a value (may not be NULL or empty)
 *
 * Return:
 *   Should return the value of the first item in pq (i.e., the item with LOWEST priority value).
 */
void* pq_remove_first(struct pq* pq) {
	struct pq_node* first = dynarray_get(pq->arr, 0);
	void* temp = first->data;

	free(first);

	dynarray_set(pq->arr, 0, dynarray_get(pq->arr, dynarray_size(pq->arr) - 1));
	dynarray_remove(pq->arr, dynarray_size(pq->arr) - 1);
	percolate_down(pq, 0);

  	return temp;
}
