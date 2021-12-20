/*
 * This file is where you should implement your binary search tree. It already contains skeletons of the functions you need to implement (along with documentation for each function).
 *
 * Name: Pranav Prabhu
 * Email: prabhup@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "stack.h"

/*
 * This structure represents a single node in a BST. In addition to containing pointers to its two child nodes (i.e. `left` and `right`), it contains two fields representing the data stored at this node. The `key` field is an integer value that should be used as an identifier for the data in this node. Nodes in the BST should be ordered based on this `key` field. The `value` field stores data associated with the key. You should not modify this structure.
 */
struct bst_node {
	int key;
	void* value;
	struct bst_node* left;
	struct bst_node* right;
};


/*
 * This structure represents an entire BST. It specifically contains a reference to the root node of the tree. You should not modify this structure.
 */
struct bst {
	struct bst_node* root;
};

/*
 * This function should allocate and initialize a new (empty) BST and return a pointer to it.
 */
struct bst* bst_create() {
	struct bst* bst = malloc(sizeof(struct bst));
	bst->root = NULL;
	return bst;
}

/*
 * Helper function for bst_free()
*/
void node_free(struct bst_node* node) {
	if (node != NULL) {
		node_free(node->left);
		node_free(node->right);
		free(node);
	}
}

/*
 * This function should free the memory associated with a BST. While this function should up all memory used in the BST itself, it should not free any memory allocated to the pointer values stored in the BST. This is the responsibility of the caller.
 *
 * Parameter:
 *   bst - the BST to be destroyed (may not be NULL)
 */
void bst_free(struct bst* bst) {
	node_free(bst->root);
	free(bst);
}

/*
 * Helper function for bst_size()
*/
int get_bst_size(struct bst_node* node) {
	if (node == NULL) return 0;
	return get_bst_size(node->left) + get_bst_size(node->right) + 1;
}

/*
 * This function should return the total number of elements stored in a given BST.
 *
 * Parameter:
 *   bst - the BST whose elements are to be counted (may not be NULL)
 */
int bst_size(struct bst* bst) {
	return get_bst_size(bst->root);
}

/*
 * Helper function for bst_insert()
*/
struct bst_node* node_insert(struct bst_node* node, int key, void* value) {
	if (node == NULL) {
		struct bst_node* new_node = malloc(sizeof(struct bst_node));

		new_node->key = key;
		new_node->value = value;
		new_node->left = NULL;
		new_node->right = NULL;

		return new_node;
	} else if (key < node->key) {
		node->left = node_insert(node->left, key, value);
	} else {
		node->right = node_insert(node->right, key, value);
	}

	return node;
}

/*
 * This function should insert a new key/value pair into the BST. The key should be used to order the key/value pair with respect to the other data stored in the BST.  The value should be stored along with the key, once the right location in the tree is found.
 *
 * Parameters:
 *   bst - the BST into which a new key/value pair is to be inserted (may not be NULL)
 *   key - an integer value that should be used to order the key/value pair being inserted with respect to the other data in the BST
 *   value - the value being inserted into the BST. This should be stored in the BST alongside the key. Note that this parameter has type void*, which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
	bst->root = node_insert(bst->root, key, value);
}

/*
 * Helper function for bst_remove()
*/
void node_remove(struct bst_node* node, struct bst_node* parent, int key) {
	if (node == NULL) {
		return;
	} else if (key < node->key) {
		parent = node;
		node_remove(node->left, parent, key);
	} else if (key > node->key) {
		parent = node;
		node_remove(node->right, parent, key);
	} else {
		if (node->left != NULL && node->right != NULL) {			
			parent = node;
			struct bst_node* leftmost = node->right;

			while (leftmost->left != NULL) {
				parent = leftmost;
  			leftmost = leftmost->left;
			}
			
			node->key = leftmost->key;
			node->value = leftmost->value;

			if (parent != node) parent->left = leftmost->right;
			if (parent == node) parent->right = leftmost->right;
			free(leftmost);
		} else if (node->left != NULL) {
			parent = node;
			node->key = node->left->key;
			node->value = node->left->value;
			node_remove(node->left, parent, node->left->key);
		} else if (node->right != NULL) {
			parent = node;
			node->key = node->right->key;
			node->value = node->right->value;
			node_remove(node->right, parent, node->right->key);
		} else {
			if (parent != NULL) {
				if (parent->left == node) parent->left = NULL;
				else parent->right = NULL;
			}

			free(node);
		}
	}
}

/*
 * This function should remove a key/value pair with a specified key from a given BST. If multiple values with the same key exist in the tree, this function should remove the first one it encounters (i.e. the one closest to the root of the tree).
 *
 * Parameters:
 *   bst - the BST from which a key/value pair is to be removed (may not be NULL)
 *   key - the key of the key/value pair to be removed from the BST
 */
void bst_remove(struct bst* bst, int key) {
	struct bst_node* current = NULL;
	node_remove(bst->root, current, key);
}

/*
 * This function should return the value associated with a specified key in a given BST. If multiple values with the same key exist in the tree, this function should return the first one it encounters (i.e. the one closest to the root of the tree). If the BST does not contain the specified key, this function should return NULL.
 *
 * Parameters:
 *   bst - the BST from which a key/value pair is to be removed (may not be NULL)
 *   key - the key of the key/value pair whose value is to be returned
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL, if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
	if (bst->root == NULL) return NULL;

	struct bst_node* current_node = bst->root;

	while (current_node != NULL) {
		if (key == current_node->key) {
			return current_node->value;
		} else if (key < current_node->key) {
			current_node = current_node->left;
		} else {
			current_node = current_node->right;
		}
	}
	
	return NULL;
}

/*********************************************************
 ***
 *** BST puzzle functions
 ***
 ********************************************************/

/*
 * Helper function for bst_height()
*/
int get_height(struct bst_node* node) {
	if (node == NULL) return -1;

	int bst_left = get_height(node->left);
	int bst_right = get_height(node->right);

	if (bst_left > bst_right) return bst_left + 1;
	return bst_right + 1;
}

/*
 * This function should return the height of a given BST, which is the maximum depth of any node in the tree (i.e. the number of edges in the path from the root to that node). Note that the height of an empty tree is -1 by convention.
 *
 * Parameter:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   Should return the height of bst.
 */
int bst_height(struct bst* bst) {
	return get_height(bst->root);
}

/*
 * Helper function for bst_path_sum()
*/
int get_path_sum(struct bst_node* node, int sum) {
	if (node == NULL) return 0;

	if (node) {
		sum -= *((int*)node->value);

		if (sum == 0 && node->right == NULL && node->left == NULL) return 1;

		return get_path_sum(node->left, sum) || get_path_sum(node->right, sum);
	}

	return 0;
}

/*
 * This function should determine whether a specified value is a valid path sum within a given BST. In other words, this function should check whether the given BST contains any path from the root to a leaf in which the keys sum to the specified value.
 *
 * Parameters:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in which the keys add up to `sum` or should return 0 otherwise.
 */
int bst_path_sum(struct bst* bst, int sum) {
	if (bst->root == NULL) return 0;
	return get_path_sum(bst->root, sum);
}

/*
 * Helper function for bst_range_sum()
*/
int get_range_sum(struct bst_node* node, int lower, int upper) {
	if (node == NULL) return 0;

	int sum = 0;

	if (node) {
		if (node->key >= lower && node->key <= upper) {
			sum += node->key;
		}

		sum += get_range_sum(node->left, lower, upper);
		sum += get_range_sum(node->right, lower, upper);
	}

	return sum;
}

/*
 * This function should compute a range sum in a given BST. Specifically, it should compute the sum of all keys in the BST between a given lower bound and a given upper bound. For full credit, you should not process any subtree whose keys cannot be included in the range sum.
 *
 * Parameters:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this should be considered an *inclusive* bound; in other words a key that's equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this should be considered an *inclusive* bound; in other words a key that's equal to this bound should be included in the sum
 *
 * Return:
 *   Should return the sum of all keys in `bst` between `lower` and `upper`.
 */
int bst_range_sum(struct bst* bst, int lower, int upper) {
	if (bst->root == NULL) return 0;
	return get_range_sum(bst->root, lower, upper);
}

/*********************************************************
 ***
 *** BST iterator definition (extra credit only)
 ***
 ********************************************************/

/*
 * Structure used to represent a binary search tree iterator. It contains only a reference to a stack to be used to implement the iterator. You should not modify this structure.
 */
struct bst_iterator {
	struct stack* stack;
};

/*
 * Helper function for bst_iterator_create()
*/
void push_elements(struct bst_node* node, struct bst_iterator* iter) {
	while (node != NULL) {
		stack_push(iter->stack, node);
		node = node->left;
	}
}

/*
 * This function should allocate and initialize an iterator over a specified BST and return a pointer to that iterator.
 *
 * Parameter:
 *   bst - the BST for over which to create an iterator (may not be NULL)
 */
struct bst_iterator* bst_iterator_create(struct bst* bst) {
	struct bst_iterator* iterator = malloc(sizeof(struct bst_iterator));
	iterator->stack = stack_create();

	if (bst->root != NULL) {
		push_elements(bst->root, iterator);
	}
	
	return iterator;
}

/*
 * This function should free all memory allocated to a given BST iterator. It should NOT free any memory associated with the BST itself. This is the responsibility of the caller.
 *
 * Parameters:
 *   iter - the BST iterator to be destroyed (may not be NULL)
 */
void bst_iterator_free(struct bst_iterator* iter) {
	stack_free(iter->stack);
	free(iter);
}

/*
 * This function should indicate whether a given BST iterator has more nodes to visit. It should specifically return 1 (true) if the iterator has at least one more node to visit or 0 (false) if it does not have any more nodes to visit.
 *
 * Parameter:
 *   iter - the BST iterator to be checked for remaining nodes to visit (may not be NULL)
 */
int bst_iterator_has_next(struct bst_iterator* iter) {
	return !stack_isempty(iter->stack);
}

/*
 * This function should return both the value and key associated with the current node pointed to by the specified BST iterator and advance the iterator to point to the next node in the BST (in in-order order).
 *
 * Because a function can't return two things, the key associated with the current node should be returned the normal way, while its value should be returned via the argument `value`. Specifically, the argument `value` is a pointer to a void pointer. The current BST node's value (a void pointer) should be stored at the address represented by `value` (i.e. by dereferencing `value`). This will look something like this: *value = current_node->value;
 *
 * Parameters:
 *   iter - BST iterator; the key and value associated with this iterator's current node should be returned, and the iterator should be updated to point to the next node in the BST (in in-order order); may not be NULL.
 *   value - pointer at which the current BST node's value should be stored before this function returns.
 *
 * Return:
 *   This function should return the key associated with the current BST node pointed to by `iter`.
 */
int bst_iterator_next(struct bst_iterator* iter, void** value) {
	struct bst_node* current = stack_pop(iter->stack);
	
	if (value) *value = current->value;
	push_elements(current->right, iter);
	
	return current->key;
}
