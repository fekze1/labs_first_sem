#include <stdio.h>

int power(int number, int degree){
    int result = 1;
    for (int i = 0; i < degree; ++i){
        result *= number;
    }
    return result;
}

int findLen(int number){
    int length = 0;
    while (number > 0){
        length += 1;
        number /= 10;
    }
    return length;
}

int delDigs(int number){
    int result = number;
    int degree = 1;
    while (number > 0){
        int digit = number % 10;
        int numberWD = number / 10;
        while (numberWD > 0){
            int nextDigit = numberWD % 10;
            if (digit == nextDigit){
                int rigthNum = result % power(10, degree);
                result -= rigthNum;
                result /= 10;
                result += rigthNum % power(10, findLen(rigthNum) - 1);
                numberWD /= 10;
                break;
            }else{
                numberWD /= 10;
            }
        }
        number /= 10;
        degree += 1;
    }
    return result;
}

int main(void){
    int userNum = 0;
    scanf("%d", &userNum);
    int result = delDigs(userNum);
    printf("%d", result);
}
