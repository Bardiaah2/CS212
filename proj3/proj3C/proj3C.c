#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "proj3C_hashtable.h"

#define MAX_LEN 256

void rmLastChar(char *string){
	if (strncmp(string, "", MAX_LEN) == 0){
		return;
	}
	int len = 0;
	while (string[len] != '\n' && string[len] != '\0'){
		len++;
	}
	if (len >= MAX_LEN){
		return;
	}
	string[len] = '\0';
}

int main(){
	// get file name { 1. empty: exit }
	char filename[MAX_LEN];
	printf("Enter the filename (or leave blank to quit): ");
	fgets(filename, MAX_LEN, stdin);
	rmLastChar(filename);
	if (filename[0] == '\0'){
		printf("No file entered, exiting program...\n");
		exit(0);
	}

	// open file { failed: display message error and reprompt}
	FILE *file;
	if ((file = fopen(filename, "r")) == NULL){
		printf("Failed to open file '%s'. Please try again.\n", filename);
		exit(main());
	}

	// print status messge
	printf("Tokenizing file '%s' and building hash bucket...", filename);

	char buffer[MAX_LEN];
	int line = 0;
	HashTable ht;
	initialize(&ht);
	do{
		// using fgets, strtok, tokenize words and
		if (fgets(buffer, MAX_LEN, file) == NULL){
			break;
		}
		rmLastChar(buffer);
		buffer[0] = tolower(buffer[0]);
		line++;

		// hash them in a hashtable
		insert(&ht, buffer, line);

	} while (strncmp(buffer, "", MAX_LEN));
	printf("done.\n");
	fclose(file);

	// display the load factor, # unique words, max_nodes used
	printf("Load factor: %.2f\n", calculateLoadFactor(&ht));
	printf("Number of unique words: %d\n", (&ht)->nodes_used);
	printf("Maximum number of nodes in a slot: %d\n", (&ht)->max_nodes);

	// prompt to search for words
	do
	{
		printf("Enter a word to search (or leave blank to quit): ");
		fgets(buffer, MAX_LEN, stdin);
		rmLastChar(buffer);
		if (buffer[0] == '\0'){
			break;
		}
		buffer[0] = tolower(buffer[0]);
		int *lines;
		int count = 0;
		get(&ht, (const char *)buffer, &lines, &count);
		// if no word: exit
		if (!count){
			printf("Word '%s' not found.\n", buffer);
			continue;
		}
		// print word and the instances found
		printf("Word '%s' found at line number(s): ", buffer);
		for (int i = 0; i < count; i++)
		{
			printf("%d ", lines[i]);
		}
		printf("\n");
		free(lines);

	} while (strncmp(buffer, "", MAX_LEN));

	// free all
	freeHashTable(&ht);

}
