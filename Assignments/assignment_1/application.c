/*
 * In this file, you should implement an application that compares the performance of a dynamic array and a linked list, as described in the README. Don't forget to include your name and @oregonstate.edu email address below.
 *
 * Name: Pranav Prabhu
 * Email: prabhup@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dynarray.h"
#include "list.h"

#define TEST_DATA_SIZE 1000000

/*
 * This function generates an array of random integers of size n.
 */
int* generate_random_array(int n) {
	int* arr = malloc(n * sizeof(int));
	
	for (int i = 0; i < n; i++) {
		arr[i] = rand();
	}
	
	return arr;
}

int main(int argc, char const *argv[]) {
	int* test_data = generate_random_array(TEST_DATA_SIZE);
	
	  /*
	   * You should write code here to insert the data in test_data into a dynamic array using the dynamic array interface you implemented. As you're doing this, measure the following two things:
	   *   1. the total amount of time it takes to insert all the data into the dynamic array
	   *   2. the maximum amount of time it takes to insert any single element into the dynamic array
	   *
	   * To help with this, you can use the C functions time() and difftime() from the time.h library. Don't forget to include time.h above!
	   */
	
	//									1. Dynamic Array

	//								     METHOD 1 - Using clock_t
	//								     1. Calculating Total Time
	clock_t start_time, end_time;
	double total_time = 0, max_time = 0;

	struct dynarray* da = dynarray_create();

	start_time = clock();
	for (int i = 0; i < TEST_DATA_SIZE; i++) {
		dynarray_insert(da, &test_data[i]);
	}
	end_time = clock();

	total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

	printf("\n\n\n\t\t\t\t\t1. Dynamic Array\n---------------------------------------------------------------\n");
	printf("\nAll data has been successfully copied to the new array!\nTotal time taken: %f seconds", total_time);

	//							2. Calculating Max Time
	for (int i = 0; i < TEST_DATA_SIZE; i++) {
		start_time = clock();
		dynarray_insert(da, &test_data[i]);
		end_time = clock();

		total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

		if (total_time > max_time) {
			max_time = total_time;
		}
	}

	printf("\nMax time taken to insert a single element: %f seconds", max_time);

	dynarray_free(da);

	//							METHOD 2 - Using time_t
	/*
	time_t start_time, end_time;
	double total_time = 0;
	struct dynarray* da = dynarray_create();

	time(&start_time);
	for (int i = 0; i < TEST_DATA_SIZE; i++) {
		dynarray_insert(da, &test_data[i]);
		//printf("\nRandom Data Values:\t%d", *&test_data[i]);
	}
	time(&end_time);

	total_time = difftime(end_time, start_time) / CLOCKS_PER_SEC;
	
	printf("\n\n\nAll data has been successfully copied to the new array!\n\n\nTotal time taken: %f seconds", total_time);
	printf("\n\n\n");
	dynarray_free(da);
	*/




	  /*
	    * You should write code here to insert the data in test_data into a linked list using the linked list interface you implemented. As you're doing this, measure the following two things:
	    *   1. the total amount of time it takes to insert all the data into the linked list
	    *   2. the maximum amount of time it takes to insert any single element into the linked list
	    *
	    * Again, you can use the C functions time() and difftime() from time.h to help with this.
	  */

	//									2. Linked List

	//								   1. Calculating Total Time
	struct list* linked_list = list_create();

	start_time = clock();
	for (int i = 0; i < TEST_DATA_SIZE; i++) {
		list_insert(linked_list, &test_data[i]);
	}
	end_time = clock();
		
	total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

	printf("\n\n\n\t\t\t\t\t2. Linked List\n---------------------------------------------------------------\n");
	printf("\nAll data has been successfully copied to the new linked list!\nTotal time taken: %f seconds", total_time);

	//								   2. Calculating Max Time
	max_time = 0;
	for (int i = 0; i < TEST_DATA_SIZE; i++) {
		start_time = clock();
		list_insert(linked_list, &test_data[i]);
		end_time = clock();

		total_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

		if (total_time > max_time) {
			max_time = total_time;
		}
	}
	
	printf("\nMax time taken to insert a single element: %f seconds", max_time);
	printf("\n\n\n");

	list_free(linked_list);

	free(test_data);

	/*
	 * How do the times associated with the dynamic array compare to the times associated with the linked list? How does this change if you modify the value of TEST_DATA_SIZE above?

	 * Based on the computed time results, the linked list takes considerably less time to traverse through its body and insert elements compared to the dynamic array because everytime new elements are added and when size reaches maximum capcity, the dynamic array has to resize itself which is a costly operation whereeas the linked list could simply insert elements without having to worry much about the resize part. Hence, the linked list if more efficient here. As the size of TEST_DATA_SIZE varies, the amount of time it takes to return total and max time also varies. As size increases, time also increases. However, the linked list takes considerably less time when compared to the dynamic array.
	 */

  return 0;
}

// Citation:
// https://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/
