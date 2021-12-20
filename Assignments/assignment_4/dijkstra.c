/*
 * In this file, you'll implement Dijkstra's algorithm to find the least expensive paths in the graph defined in `airports.dat`.
 *
 * Name: Pranav Prabhu
 * Email: prabhup@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

#define DATA_FILE "airports.dat"
#define START_NODE 0
#define INFINITY 100000

struct node {
	int key;
	int cost;
	struct node* prev;
};

struct node_tuple {
	struct node* prev;
	struct node* next;
};

struct node* create_node(int key) {
	struct node* new_node = malloc(sizeof(struct node));
	new_node->key = key;
	new_node->cost = INFINITY;
	new_node->prev = NULL;
	return new_node;
}

struct node_tuple* create_node_tuple(struct node* node, struct node* prev) {
	struct node_tuple* nt = malloc(sizeof(struct node_tuple));
  	nt->prev = prev;
	nt->next = node;
  	return nt;
}

void print_path(struct node* node) {
	if (node->prev != NULL) {
		print_path(node->prev);
		printf(" -> ");
	}
	printf("%d", node->key);
}

void Dijkstra(int** graph, int num_nodes, int start_node) {
	struct node** new_node = malloc(num_nodes * sizeof(struct node*));
	
	for (int i = 0; i < num_nodes; i++) {
		new_node[i] = create_node(i);
	}

	struct pq* pq = pq_create();
	pq_insert(pq, create_node_tuple(new_node[START_NODE], NULL), 0);

	while (!pq_isempty(pq)) {
		int c = pq_first_priority(pq);
		struct node_tuple* nt = pq_remove_first(pq);
		struct node* n = nt->next;

		if (c < n->cost) {
			n->cost = c;
			n->prev = nt->prev;

			for (int i = 0; i < num_nodes; i++) {
				if (graph[n->key][i]) {
          				pq_insert(pq, create_node_tuple(new_node[i], n), c + graph[n->key][i]);
				}
			}
		}

		free(nt);
	}

	for (int i = 0; i < num_nodes; i++) {
		print_path(new_node[i]);
		printf(": %d\n", new_node[i]->cost);
	}

	pq_free(pq);
	for (int i = 0; i < num_nodes; i++) free(new_node[i]);
	free(new_node);
}

int main(int argc, char const *argv[]) {
	int nodes, edges, node_i, node_j;

	FILE* fp = fopen(DATA_FILE, "r");

	fscanf(fp, "%d", &nodes);
	fscanf(fp, "%d", &edges);

	int** matrix = malloc(nodes * sizeof(int*));
	for (int i = 0; i < nodes; i++) matrix[i] = calloc(nodes, sizeof(int));

	for (int j = 0; j < edges; j++) {
		fscanf(fp, "%d", &node_j);
		fscanf(fp, "%d", &node_i);
		fscanf(fp, "%d", &matrix[node_j][node_i]);
	}

	fclose(fp);

	printf("\n\n\nMatrix:\n\n");
	for (int i = 0; i < nodes; i++) {
  		printf("[");
  		for (int j = 0; j < nodes; j++) {
    			printf("%5d", matrix[i][j]);
    			if (j < nodes - 1) printf(", ");
  		}
  		printf("]\n");
	}

	printf("\n\n\nPath Sum:\n\n");
	Dijkstra(matrix, nodes, START_NODE);

	for (int i = 0; i < nodes; i++) free(matrix[i]);
	free(matrix);
	 
  	return 0;
}
