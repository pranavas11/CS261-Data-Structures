#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include "queue.h"

#define MAX_STR_LEN 256

/*
 * This function prompts the user for input and stores a maximum of `n` characters of the string they enter into `dest`. Any trailing line ending characters are removed from the input string. Returns 1 if a string was successfully read from the user or 0 otherwise.
 */
int get_user_str(char* dest, int n) {
	printf("\n\n\nEnter a string, and we'll check whether it's a palindrome:\n");
	if (fgets(dest, MAX_STR_LEN, stdin) != NULL) {
		/*
	     	 * If a string was successfully read from the user, remove any trailing line ending characters. Here's some documentation on strcspn() to help understand how this works:
	     	 *
	     	 * https://en.cppreference.com/w/c/string/byte/strcspn
	     	 */
	    	dest[strcspn(dest, "\r\n")] = '\0';
	    	return 1;
	  } else {
	    	return 0;
	  }
}

char* purge_string(char *str) {
	char *copy = malloc(sizeof(char) * MAX_STR_LEN);	// copy is a dynamically allocated variable on the heap, which stores an array of 1023 characters
	int counter = 0, x = 0;

	for (int i = 0; str[i] != '\0'; i++) {
		// if str contains alphabetic characters only, increase counter and x
		if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
			copy[x] = str[i];
			x += 1;
			counter += 1;
		}
	}

	copy[counter] = '\0';			// set copy to a null character

	return copy;
}

void play_game() {
	char* in = malloc(MAX_STR_LEN * sizeof(char));
	char* str = malloc(MAX_STR_LEN * sizeof(char));
	struct stack* stack;
	struct queue* queue;

	while (get_user_str(in, MAX_STR_LEN)) {
		/*
     		 * Inside this loop body, you'll have an input string from the user in `in`. You should use your stack and your queue to test whether that string is a palindrome (i.e. a string that reads the same backward as forward, e.g. "ABCBA" or "Madam, I'm Adam"). For each string input by the user, print a message letting the user know whether or not their string is is a palindrome.
     		 *
     		 * When you test whether the user's string is a palindrome, you should ignore any non-letter characters (e.g. spaces, numbers, punctuation, etc.), and you should ignore the case of letters (e.g. the characters 'a' and 'A' should be considered as equal). The C functions isalpha() and tolower() from ctype.h might help with this.
     		 */

		int length = strlen(in);
		int new_len = 0;
		
		for (int i = 0; i < length; i++) {
			if (isalpha(in[i])) {
				str[new_len] = tolower(in[i]);
				new_len++;
			}
		}

		//char* str = purge_string(lowercase);

		stack = stack_create();
		for (int i = 0; i < new_len; i++) {
			stack_push(stack, &str[i]);
		}

		queue = queue_create();
		for (int i = 0; i < new_len; i++) {
			queue_enqueue(queue, &str[i]);
		}

		bool compare_chars = 1;
		for (int i = 0; i < new_len; i++) {
			char* s = stack_pop(stack);
			char* q = queue_dequeue(queue);
			if (*s != *q) {
				compare_chars = 0;
			}
		}

		if (compare_chars == 1) {
			printf("\nThe string \"%s\" is a palindrome", in);
			printf("\n");
		} else {
			printf("\nThe string \"%s\" is not a palindrome", in);
			printf("\n");
		}

		stack_free(stack);
		queue_free(queue);

		break;
	}
	
	free(in);
	free(str);
}

int main(int argc, char const *argv[]) {
	play_game();

	char answer[9];

	while (true) {
		printf("\n\n\nDo you want to play again (y/n)? ");
		scanf("%s", answer);
		getchar();
		
		if (strncmp(answer, "Yes", 5) == 0 || strncmp(answer, "yes", 5) == 0 || strncmp(answer, "Y", 5) == 0 || strncmp(answer, "y", 5) == 0) play_game();
		else {
			printf("\n\n\nSorry to see you go! Please play again later!\n\n\n");
			break;
		}
	}

	return 0;
}
