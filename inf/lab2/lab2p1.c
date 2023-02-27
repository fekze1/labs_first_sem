#include <stdio.h>
#include <math.h>

long double natLog(long double number, int amount){
    long double sum = number;
    long double p = number;
    long double y = number;
    for (int i = 2; i <= amount; i++){
        y *= -number;
        p = y / i;
        sum += p;
    }
    return sum;
}

void cleanBuffer(){
    scanf("%*[^\n]");
}

long double checkCond(long double *number, int values, int status){
    while (values != 1 || *number <= -1 || *number > 1){
        cleanBuffer();
        printf("input correct number: ");
        values = scanf("%Lf", number);
        if(values == -1) {return -1;};
    }
    return 0;
}

int checkRow(float *number, int *numberInt, int  values, int status){
    while (values != 1 || *number <= 0 || *number != *numberInt){
        cleanBuffer();
        printf("input correct number: ");
        values = scanf("%f", number);
        if(values == -1) {return -1;};
        *numberInt = *number;
    }
    return 0;
}

int main(){
	int status = 0;
    long double userNum = 0;
    float  userAmount = 0;
	long double *ptrNum = &userNum;
	float *ptrAmount = &userAmount;
    printf("input x: ");
    int recValues = scanf("%Lf", &userNum);
    if (recValues != 1 || userNum <= -1 || userNum > 1){
        if(recValues == -1) {return -1;};
        status = checkCond(ptrNum, recValues, status);
        if(status == -1) {return -1;};
    }
    cleanBuffer();
    printf("input n: ");
    recValues = scanf("%f", &userAmount);
    int userAmountInt = userAmount;
	int *ptrAmountInt = &userAmountInt;
    if (recValues != 1 || userAmount <= 0 || userAmount != userAmountInt){
        if(recValues == -1) {return -1;};
        status = checkRow(ptrAmount, ptrAmountInt, recValues, status);
        if(status == -1) {return -1;};
    }
    long double realResult = log(1 + userNum);
    long double result = natLog(userNum, userAmount);
    printf("ln(1 + x) = %.16Lf, real: %.16Lf", result, realResult);
    return 0;
}
