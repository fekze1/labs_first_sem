#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void addElem(List* list, char data, int ind) {
    Item* tmpItem = list->first;

    for (int i = 0; i < ind; i++) {
        tmpItem = tmpItem->next;
    }

    Item* tmp = malloc(sizeof(Item));
    tmp->data = data;
    tmp->next = tmpItem->next;
    tmpItem->next = tmp;

}

int dupEvenLen(List* list) {

    Item* tmpItem = list->first;
    Item* tmpStart = tmpItem;
    int length = 0;
    int number = 0;

    while (tmpItem) {
        if (tmpItem->next == NULL) {
            length++;
            if (length % 2 == 0) {
                addToList(list, ' ');

                while (tmpStart->data != ' ') {
                    addToList(list, tmpStart->data);
                    tmpStart = tmpStart->next;
                }

            }
            break;
        }
        if (tmpItem->data == ' ') {
            if (length % 2 == 0) {
                Item* tmpNext = tmpItem->next;
                while (tmpStart->data != ' ') {
                    addElem(list, tmpStart->data, number);
                    number++;
                    tmpStart = tmpStart->next;
                }
                addElem(list, ' ', number);

                tmpItem = tmpNext;
                tmpStart = tmpItem;
                number += 2;
                length = 0;

            }
            else {
                tmpItem = tmpItem->next;
                tmpStart = tmpItem;
                length = 0;
                number++;
            }
        }
        else {
            tmpItem = tmpItem->next;
            length++;
            number++;
        }
    }

    return 0;

}


void debugPrint(List* list) {
    Item* tmp = list->first;
    while (tmp) {
        printf("data: %c\n", tmp->data);
        if (tmp->next != NULL) {
            printf("next: %c\n\n", tmp->next->data);
        }
        else {
            printf("next node doesnt exist\n\n");
        }
        tmp = tmp->next;

    }
}


int status() {
    int status = 0;
    List* list = newList();
    status = initList(list);

    if (status == 1) {
        deleteList(list);
        return 0;
    }

    printf("input: ");
    printList(list);

    status = dupEvenLen(list);

    printf("result: ");
    printList(list);



    deleteList(list);
}

int main() {
    while (status());
    return 0;
}
