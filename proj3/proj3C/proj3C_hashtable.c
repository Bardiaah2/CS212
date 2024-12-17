#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "proj3C_hashtable.h"

unsigned int hash(const char *key)
{
  unsigned int hash = 0;
  for (int i = 0; key[i] != '\0'; i++)
  {
    hash = hash * 31 + key[i];
  }
  return hash % BUCKET_SIZE;
}

void initialize(HashTable *ht){
    ht->slots_used = 0;
    ht->nodes_used = 0;
    ht->max_nodes = 0;

    for (int i=0; i<BUCKET_SIZE; i++){
        ht->bucket[i] = NULL;
    }
}

Node *createNode(const char *key, int value){
    Node *node = malloc(sizeof(Node));
    if (!node){
        fprintf(stderr, "Failed to allocate memory for new node.\n");
        exit(EXIT_FAILURE);
    }

    node->value = value;
    node->key = malloc(sizeof(key) * sizeof(char *));
    memcpy(node->key, key, sizeof(key)*sizeof(char *));
    node->next = NULL;

    return node;
}

void insert(HashTable *ht, const char *key, int value){
    long int slot = hash(key);
    Node *node = createNode(key, value);

    int nodes = 0;
    if (ht->bucket[slot]){
        Node *temp = ht->bucket[slot];
        while (temp->next){
            temp = temp->next;
            nodes++;
        }
        temp->next = node;
    } else {
        ht->bucket[slot] = node;
        ht->slots_used++;
    }

    ht->nodes_used++;
    if (nodes > ht->max_nodes){
        ht->max_nodes = nodes;
    }
}

void get(HashTable *ht, const char *key, int **result, int *count){
    long int slot = hash(key);
    if (ht->bucket[slot] == NULL){
        return;
    }

    int *values;
    values = malloc(ht->max_nodes * sizeof(int));
    for (int i = 0; i < ht->max_nodes; i++)
    {
        values[i] = 0;
    }
    Node *temp = ht->bucket[slot];
    while (temp){
		if (strcmp(key, temp->key) == 0){
        	values[*count] = temp->value;
        	(*count)++;
		}
        temp = temp->next;
    }
    if (*count == 0){
        free(values);
        return;
    }
    *result = values;
}

void freeNode(Node *node){
        if (node->next){
            freeNode(node->next);
        }
        free(node->key);
        free(node);
    }

void freeHashTable(HashTable *ht){
    for (int i=0; i<BUCKET_SIZE; i++){
        if (ht->bucket[i]){
            freeNode(ht->bucket[i]);
        }
    }
}

float calculateLoadFactor(HashTable *ht){
    return (float) ht->slots_used / (float) BUCKET_SIZE;
}
