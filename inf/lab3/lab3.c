#include <stdio.h>
#include <stdlib.h>
#include "myArray.h"

float findAV(float *array, int lenInt){
	float sum = 0;
	for (int i = 0; i < lenInt; i++){
		sum += array[i];
	}
	float averageValue = sum / lenInt;
	return averageValue;
}

float findDiffWithAV(float **array, int *lenIntPtr, float averageValue){
	for (int i = 0; i < *lenIntPtr; i++){
		(*array)[i] = averageValue - (*array)[i];
	}
	return 0;
}

float delByCond(float **array, int *lenIntPtr, float averageValue, float *status){
	if (averageValue > 0){
		for (int i = 0; i < *lenIntPtr; i++){
			if ((*array)[i] < 0) {
				*status = deleteElem(array, lenIntPtr, i);
				i -= 1;
			}
		}
	}else{
		for (int i = 0; i < *lenIntPtr; i++){
			if((*array)[i] > 0){
				*status =  deleteElem(array, lenIntPtr, i);
				i -= 1;
			}
		}
	}
	return 0;	
}
int checkIndex(float index, int *indexInt,  int recValues, int length, int status){
	while(recValues <= 0 || *indexInt != index || index < 0 || index >= length){
		if (recValues == -1){
			return status;
		}
		printf("invalid value, input correct value: ");
		recValues = scanf("%f", &index);
		*indexInt = index;
	}
	return status;
}

void menu(){
	float status = 0;
	float *statusPtr = &status;
	float length = 0;
	float *lenPtr = &length;
	float *array; 
	arrayInit(&array, lenPtr, status);
	status = arrayInput(array, length, status);
	int lenInt = length;
	int *lenIntPtr = &lenInt;
	while (status != -1){
		printf("'1' - find average value\n'2' - print array\n'3' - exit\n'4' - delete element by index\n'5' - input element by index\n");
		printf("input command: ");
		int recValues = scanf("%f", &status);
		int statusInt = checkStatus(statusPtr, recValues);
		switch(statusInt){
			case 1: ;
				int statusTmp = 3;
				float averageValue = findAV(array, lenInt);
				printf("average value: %f\n", averageValue);
				printf("'1' - find difference between AV and elements, delete elements that are bigger than AV\n'2' - find defference between AV and elements\n'3' - continue\n");
				scanf("%d", &statusTmp);
				switch(statusTmp){
					case 1:
						status = findDiffWithAV(&array, lenIntPtr, averageValue);
						status = delByCond(&array, lenIntPtr, averageValue, statusPtr);
					break;
					case 2:
						status = findDiffWithAV(&array, lenIntPtr, averageValue);
					break;
					default:
						status = 0;
					break;
					
				}
			break;
			case 2:
				printArray(array, lenInt);
			break;
			default:
				status = -1;
			break;
			case 4: ;
				if (length == 0){
					printf("invalid action, empty array\n");
					break;
				}
				float index = 0;
				float *indexPtr = &index;
				printf("input index: ");
				recValues = scanf("%f", &index);
				int indexInt = index;
				int *indexIntPtr = &indexInt; 
				status = checkIndex(index, indexIntPtr, recValues, length, status);			
				status = deleteElem(&array, lenIntPtr, indexInt);
			break;
			case 5: ;
				index = 0;
				indexPtr = &index;
				float value = 0;
				printf("input index: ");
				recValues = scanf("%f", &index);
				indexInt = index;
				status = checkInt(indexPtr, recValues, status);
				indexInt = index;
				printf("input value: ");
				scanf("%f", &value);
				status = inputElem(&array, lenIntPtr, indexInt, value);
			break;
		}
	}
	free(array);
}

int main(){
	menu();
	return 0;
}
