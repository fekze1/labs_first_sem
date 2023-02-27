#include <stdio.h>
#include <math.h>

long double natLog(long double number, long double  acc, int *amountPointer){
    long double sum = number;
    long double p = number;
    long double y = number;
	long double prev  = 0;
	int i = 2;
    while (fabs(p - prev) > acc){
		prev = p;
        y *= -number;
        p = y / i;
        sum += p;
		i += 1;
		*amountPointer += 1;
    }
    return sum;
}

void cleanBuffer(){
    scanf("%*[^\n]");
}

long double checkCond(long double *number, int values, int status){
    while (values != 1 || *number <= -1 || *number > 1){
        printf("input correct number: ");
        cleanBuffer();
        values = scanf("%Lf", number);
		if (values == -1) {return 1;};
    }
    return  0;
}

long double checkRow(long double *number, int values, int status){
    while (values != 1 || *number <= 0){
        printf("input correct number: ");
        cleanBuffer();
        values = scanf("%Lf", number);
		if (values == -1) {return 1;};
    }
    return 0;
}
int findLen(long double number){
	int length = 0;
	while (number <= 1){
		number *= 10;
		length += 1;
	}
	return length;
}
int main(void){
	int status = 0;
    long double userNum = 0;
    long double userAcc = 0;
	long double *ptrNum = &userNum;
	long double *ptrAcc = &userAcc;
	int numInRow = 0;
	int *numInRowPointer = &numInRow;
    printf("input x: ");
    int recValues = scanf("%Lf", &userNum);
	if (recValues != 1 || userNum <= -1 || userNum > 1){
		if (recValues == -1) {return -1;};
		status = checkCond(ptrNum, recValues, status);
		if (status == 1) {return -1;};
	}
	cleanBuffer();
    printf("input accuarcy: ");
    recValues = scanf("%Lf", &userAcc);
	if (recValues != 1 || userAcc <= 0){
		if (recValues == 1) {return -1;};
        status = checkRow(ptrAcc, recValues, status);
		if (status == 1) {return -1;};
    }
	int amountOfDig = findLen(userAcc);
	long double realResult = log(1 + userNum);
    long double result = natLog(userNum, userAcc, numInRowPointer);
    printf("ln(1 + x) = %.*Lf, real: %.33Lf, difference: +-%.33lf \n", amountOfDig, result, realResult, fabs(realResult - result));
	printf("number of members in a row: %d", numInRow);
	return 0;
}
