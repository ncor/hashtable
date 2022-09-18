#include <stdbool.h>


typedef struct item {
	char* key;
	int value;
} item;

typedef struct hashtable {
	item* items;
	int size;
} hashtable;


hashtable createHashtable();

bool hashtableHas(hashtable ht, char* key);

void hashtableExpand(hashtable* ht, int additionalSize);

void hashtableSet(hashtable* ht, char* key, int value);

void hashtableDelete(hashtable* ht, char* key);

int* hashtableGet(hashtable ht, char* key);
