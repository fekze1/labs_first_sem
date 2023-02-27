#include "myArray.h"
#include <stdio.h>
#include <stdlib.h>

void cleanBuffer(){
	scanf("%*[^\n]");
}
float checkInt(float *numberPtr, int recValues, float status){
    int numberInt = *numberPtr;
    while (numberInt != *numberPtr || recValues <= 0 || *numberPtr < 0){
		if (recValues == -1){
			return status;
		}
		cleanBuffer();
        printf("input correct number: ");
        recValues = scanf("%f", numberPtr);
        numberInt = *numberPtr;
    }
    return status;
}

int checkStatus(float *status, int recValues) {
    int statusInt = *status;
    while(recValues <= 0 || statusInt != *status || *status < 1 || *status > 5){
        if (recValues == -1){
			return statusInt = 0;
        }
        cleanBuffer();
        printf("input correct number: ");
        recValues = scanf("%f", status);
        statusInt = *status;
    }
    return statusInt;
}


float checkValues(float *numberPtr, int recValues, float status){
    while (recValues <= 0){
    	if (recValues == -1){
    		return status;
    	}
    	cleanBuffer();
        printf("input correct number: ");
        recValues = scanf("%f", numberPtr);
    }
    return status;
}

float arrayInit(float **array, float *lenPtr, float status){
    printf("input amount of elements: ");
    int recValues = scanf("%f", lenPtr);
    status = checkInt(lenPtr, recValues, status);
    *array = (float*)malloc(*lenPtr*sizeof(float));
    return status;
}

float arrayInput(float *array, int lenInt, float status){
    for (int i = 0; i < lenInt; i++){
        printf("input array[%d]: ", i);
        int recValues = scanf("%f", &array[i]);
        status = checkValues(&array[i], recValues, status);
        if (status == -1) {break;};
    }
    return status;
}

float printArray(float *array, int lenInt){
    printf("----------\n");
    for (int i = 0; i < lenInt; i++){
        printf("array[%d]: %f\n", i, array[i]);
    }
    return 0;
}

float deleteElem(float **array, int *lenIntPtr, int index){
    for (int i = 0; i < *lenIntPtr; i++){
        if (i == index){
            for (int j = i; j < *lenIntPtr - 1; j++){
                (*array)[j] = (*array)[j + 1];
            }
        }
    }
    *lenIntPtr -= 1;
    *array = (float *)realloc(*array, *lenIntPtr*sizeof(float));
    return 0;
}

float inputElem(float **array, int *lenIntPtr, int index, float value){
    if (index >= *lenIntPtr){
        printf("invalid value, element inserted in end\n");
        *lenIntPtr += 1;
        *array = (float*)realloc(*array, *lenIntPtr*sizeof(float));
        (*array)[*lenIntPtr - 1] = value;
        return 0;
    }else{
        *lenIntPtr += 1;
        *array = (float*)realloc(*array, *lenIntPtr*sizeof(float));
        for (int i = *lenIntPtr - 1; i >= index; i--){
            if(i != index){
                (*array)[i] = (*array)[i - 1];
            }else {
                (*array)[i] = value;
            }
        }
        return 0;
    }
}
