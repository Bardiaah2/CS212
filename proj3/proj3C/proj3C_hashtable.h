#ifndef proj3C_hashtable_h
#define proj3C_hashtable_h

typedef struct Node {
    int value;
    char *key;
    struct Node *next;
} Node;


#define BUCKET_SIZE 100
typedef struct HashTable{
    int slots_used; // Number of used slots used
    int nodes_used; // Number of nodes used
    int max_nodes;  // Max number of nodes used by a slot
    Node *bucket[BUCKET_SIZE];
} HashTable;

unsigned int hash(const char *key);
void initialize(HashTable *ht);
Node *createNode(const char *key, int value);
void insert(HashTable *ht, const char *key, int value);
void get(HashTable *ht, const char *key, int **result, int *count);
void freeHashTable(HashTable *ht);
float calculateLoadFactor(HashTable *ht);

#endif
