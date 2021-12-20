/*
 * This file is where you should implement your dynamic array. It already contains skeletons of the functions you need to implement (along with documentation for each function). Feel free to implement any additional functions you might need. Also, don't forget to include your name and @oregonstate.edu email address below.
 *
 * Name: Pranav Prabhu
 * Email: prabhup@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include "dynarray.h"

/*
 * This is the definition of the dynamic array structure you'll use for your implementation. Importantly, your dynamic array implementation will store each data element as a void* value. This will permit data of any type to be stored in your array.  Because each individual element will be stored in your array as type void*, the data array needs to be an array of void*. Hence it is of type void**. You should not modify this structure.
 */
struct dynarray {
	void** data;
	int size;
	int capacity;
};

/*
 * This function should allocate and initialize a new, empty dynamic array and return a pointer to it. The array you allocate should have an initial capacity of 2.
 */
struct dynarray* dynarray_create() {
	struct dynarray* arr = malloc(sizeof(struct dynarray));
	arr->size = 0;
	arr->capacity = 2;
	arr->data = malloc(2 * sizeof(void*));
	return arr;
}

/*
 * This function should free the memory associated with a dynamic array. In particular, while this function should free up all memory used in the array itself (i.e. the underlying `data` array), it should not free any memory allocated to the pointer values stored in the array. In other words, this function does not need to traverse the array and free the individual elements. This is the responsibility of the caller.
 *
 * Parameters:
 *   da - the dynamic array to be destroyed (may not be NULL)
 */
void dynarray_free(struct dynarray* da) {
	free(da->data);
	free(da);
}

/*
 * This function should return the size of a given dynamic array (i.e., the number of elements stored in it, not the capacity).
 */
int dynarray_size(struct dynarray* da) {
	return da->size;
}

/*
 * This function resizes the dynamic array to allow more room for newly added values (data) to the array. In other words, this function helps to simply double the size of the dynamic array.
 *
 * Parameters:
 *   da - the dynamic array
 *   new_size - size of the new dynamic array
*/
void dynarray_resize(struct dynarray* da, int new_size) {
	/* creates a new dynamic array of void** (since type is unknown) */
	void** type = malloc(new_size * sizeof(void*));

	/* copies over elements from the old array to the newly resized dynamic array */
	for (int i = 0; i < da->size; i++) {
		type[i] = da->data[i];
	}

	/* frees up (deletes) dynamic memory taken up by the old dynamic array and assigns the new_meory back to da */
	free(da->data);
	da->data = type;
}

/*
 * This function should insert a new value to a given dynamic array. For simplicity, this function should only insert elements at the end of the array. In other words, it should always insert the new element immediately after the current last element of the array. If there is not enough space in the dynamic array to store the element being inserted, this function should double the size of the array.
 *
 * Parameters:
 *   da - the dynamic array into which to insert an element (may not be NULL)
 *   val - the value to be inserted (note that this parameter has type void*, which means that a pointer of any type can be passed)
 */
void dynarray_insert(struct dynarray* da, void* val) {
	if (da->size >= da->capacity) dynarray_resize(da, da->size*2);
	
	da->data[da->size] = val;
	da->size++;
}

/*
 * This function should remove an element at a specified index from a dynamic array. All existing elements following the specified index should be moved forward to fill in the gap left by the removed element. In other words, if the element at index i is removed, then the element at index i+1 should be moved forward to index i, the element at index i+2 should be moved forward to index i+1, the element at index i+3 should be moved forward to index i+2, and so forth.
 *
 * Parameters:
 *   da - the dynamic array from which to remove an element (may not be NULL)
 *   idx - the index of the element to be removed (the value of `idx` must be between 0 (inclusive) and n (exclusive), where n is the number of elements stored in the array.
 */
void dynarray_remove(struct dynarray* da, int idx) {
	if (idx > da->size - 1) {
		printf("ERROR: Specified index out of bounds!");
		return;
	}

	for (int i = idx; i < da->size - 1; i++) da->data[i] = da->data[i+1];

	da->data[da->size - 1] = 0;
	da->size = da->size - 1;
}

/*
 * This function should return the element value of an existing element stored at a specified index in the dynamic array. Note that this value should be returned as type void*.
 *
 * Parameters:
 *   da - the dynamic array from which to get a value (may not be NULL)
 *   idx - the index of the element whose value should be returned (the value of `idx` must be between 0 (inclusive) and n (exclusive), where n is the number of elements stored in the array)
 */
void* dynarray_get(struct dynarray* da, int idx) {
	if (da == NULL || dynarray_size(da) <= idx || idx < 0) {
		printf("ERROR: Specified element index is out of bouds!");
		exit(0);
	}
	
	return da->data[idx];
}

/*
 * This function should update (i.e. overwrite) the value of an existing element in a dynamic array.
 *
 * Parameters:
 *   da - the dynamic array in which to set a value (may not be NULL)
 *   idx - the index of the element whose value should be updated (the value of `idx` must be between 0 (inclusive) and n (exclusive), where n is the number of elements stored in the array
 *   val - the new value to be set (note that this parameter has type void*, which means that a pointer of any type can be passed)
 */
void dynarray_set(struct dynarray* da, int idx, void* val) {
	if (da == NULL || dynarray_size(da) <= idx || idx < 0) {
		printf("ERROR: Specified element index is out of bouds!");
		return;
	}
	
	da->data[idx] = val;
}
