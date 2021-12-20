/*
 * This file is where you should implement your stack.  It already contains skeletons of the functions you need to implement (along with documentation for each function). Feel free to implement any additional functions you might need.
 *
 * Name: Pranav Prabhu
 * Email: prabhup@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "stack.h"

/*
 * This is the structure that will be used to represent a stack. This structure specifically contains a single field representing a linked list that should be used as the underlying data storage for the stack. You should not modify this structure.
 */
struct stack {
	struct list* list;
};

/*
 * This function should allocate and initialize a new, empty stack and return a pointer to it.
 */
struct stack* stack_create() {
	struct stack* new_stack = malloc(sizeof(struct stack));
	new_stack->list = list_create();
  	return new_stack;
}

/*
 * This function should free the memory associated with a stack. While this function should up all memory used in the stack itself, it should not free any memory allocated to the pointer values stored in the stack.  This is the responsibility of the caller.
 *
 * Parameter:
 *   stack - the stack to be destroyed (may not be NULL)
 */
void stack_free(struct stack* stack) {
	list_free(stack->list);
  	free(stack);
}

/*
 * This function should indicate whether a given stack is currently empty. Specifically, it should return 1 if the specified stack is empty (i.e. contains no elements) and 0 otherwise.
 *
 * Parameter:
 *   stack - the stack whose emptiness is being questioned (may not be NULL)
 */
int stack_isempty(struct stack* stack) {
	return list_isempty(stack->list);
}

/*
 * This function should push a new value onto a given stack. The value to be pushed is specified as a void pointer. This function must have O(1) average runtime complexity.
 *
 * Parameters:
 *   stack - the stack onto which a value is to be pushed (may not be NULL)
 *   val - the value to be pushed (note that this parameter has type void*, which means that a pointer of any type can be passed)
 */
void stack_push(struct stack* stack, void* val) {
	list_insert(stack->list, val);
}

/*
 * This function should return the value stored at the top of a given stack *without* removing that value.  This function must have O(1) average runtime complexity.
 *
 * Parameter:
 *   stack - the stack from which to query the top value (may not be NULL)
 */
void* stack_top(struct stack* stack) {
	return get_value(stack->list);
}

/*
 * This function should pop a value from a given stack and return the popped value.  This function must have O(1) average runtime complexity.
 *
 * Parameter:
 *   stack - the stack from which a value is to be popped (may not be NULL)
 *
 * Return:
 *   This function should return the value that was popped.
 */
void* stack_pop(struct stack* stack) {
	void* get_val = get_value(stack->list);
	list_remove(stack->list, get_value(stack->list), compare);
	
	return get_val; 
}
