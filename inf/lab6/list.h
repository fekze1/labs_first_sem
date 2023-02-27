#include <stdio.h>
#include <stdlib.h>
#ifndef LIST_H
#define LIST_H

typedef struct Item{
	char data;
	struct Item *next;
}Item;

typedef struct {
	Item *first;
	Item *last;
}List;

List *newList();

void deleteList(List *list);

void printList(const List *list);

void addToList(List *list, char data);

int initList(List *list);

#endif
