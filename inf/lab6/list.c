#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List *newList(){
	return (List *)calloc(1, sizeof(List));
}

void deleteList(List *list) {
    Item *tmpPtr = list->first, *tmpPtr_prev;
    while (tmpPtr) {
        tmpPtr_prev = tmpPtr;
        tmpPtr = tmpPtr->next;
        free(tmpPtr_prev);
    }
    free(list);
}

void printList(const List *list) {
    Item *tmpPtr = list->first;
    printf("\"");
    while (tmpPtr) {
        printf("%c", tmpPtr->data);
        tmpPtr = tmpPtr->next;
    }
    printf("\"\n");
}

void addToList(List *list, char data) {

	Item *newItem = (Item *)malloc(sizeof(Item));
	newItem->data = data;
	newItem->next = NULL;

	if (!list->first){
		list->first = newItem;
		list->last = newItem;
	}else{
		list->last->next = newItem;
		list->last = newItem;
	}
	
}

int initList(List *list){
	printf("> ");
	
	char currentChar = getchar();
	
	if (currentChar == EOF) return 1;

	while (currentChar != '\n'){
		while (currentChar == ' ' || currentChar == '\t'){
		
			currentChar = getchar();
			if (currentChar == '\n') return 0;
			
			if (currentChar != ' ' && currentChar != '\t'){
				if (list->first) addToList(list, ' ');
			} 
		}
		
		addToList(list, currentChar);
		currentChar = getchar();
	}

	return 0;
}
