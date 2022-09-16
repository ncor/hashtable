#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashtable.h"


hashtable createHashtable() {
	hashtable* ht = (hashtable*)malloc(1 * sizeof(hashtable));
	ht->items = NULL;
	ht->size = 0;
	
	return *ht;
}

bool hashtableHas(hashtable ht, char* key) {
	item* items = ht.items;

	for (int i = 0; i < ht.size; i++)
		if (strcmp(items[i].key, key) == 0)
			return true;

	return false;
}

void hashtableExpand(hashtable* ht, int additionalSize) {
	int prevSize = ht->size;
	item* items = ht->items;

	ht->size = prevSize + additionalSize;
	ht->items = (item*)realloc(ht->items, ht->size * sizeof(item));
	
	for (int i = 0; i < prevSize; i++)
		ht->items[i] = items[i];
}

/*
 * hashtableHas method is not optimal
 * because of O(n^2) worst time complexity.
 */
void hashtableSet(hashtable* ht, char* key, int value) {
	bool set = false; 

	for (int i = 0; i < ht->size; i++) {
		item currentItem = ht->items[i];
	
		if (strcmp(currentItem.key, key) == 0) {
			ht->items[i].value = value;
			set = true;
			break;
		}
	}
	
	if (!set) {
		if (!ht->items)
			ht->items = (item*)malloc(1 * sizeof(item));

		hashtableExpand(ht, 1);
		ht->items[ht->size - 1] = (item){ key, value };
	}
}

/*
 * hashtableHas method is not optimal
 * because of O(n^2) worst time complexity.
 */
void hashtableDelete(hashtable* ht, char* key) {
	bool found = false;

	for (int i = 0; i < ht->size; i++) {
		item currentItem = ht->items[i];

		if (strcmp(currentItem.key, key) == 0) {
			found = true;
			break;
		}
	}

	if (found) {
		bool deleted = false;
		item* items = ht->items;

		ht->size = ht->size - 1;
		ht->items = (item*)realloc(ht->items, ht->size * sizeof(item));

		for (int i = 0; i < ht->size; i++) {
			if (strcmp(items[i].key, key) == 0)
				deleted = true;

			if (deleted) {
				ht->items[i] = items[i + 1];
			} else {
				ht->items[i] = items[i];
			}
		}
	}
}

int* hashtableGet(hashtable ht, char* key) {
	for (int i = 0; i < ht.size; i++) {
		if (strcmp(ht.items[i].key, key) == 0)
			return &ht.items[i].value;
	}

	return NULL;
}

