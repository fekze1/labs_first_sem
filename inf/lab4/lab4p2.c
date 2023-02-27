#include <stdio.h>
#include <stdlib.h>
#include "myStrings.h"

#define DEL " \t"
#define PROMPT " >"

char *delNotUnic(char *string){

	if (string == NULL){
		return NULL;
	}
	
    char *str = duplicateString(string);
    int str_len = findLength(str);
    char *result = calloc(str_len + 1, sizeof(char));
    int res_length = 0;
    char *word = getWord(str, DEL);

    while (word != NULL){
        int word_len  = findLength(word);
        int tmp = 0;
        for (int i = 0; i < word_len; i++){
            for (int j = i + 1; j < word_len; j++){
                if (word[i] == word[j]){
                    tmp = 1;
                    break;
                }
            }
        }
        if (tmp == 1){
            copyMemory(result + res_length, word, word_len);
            res_length += word_len;
            result[res_length] = ' ';
            ++res_length;
        }

        word = getWord(NULL, DEL);
    }

    free(str);

    if (res_length > 0){
        --res_length;
    }

    result[res_length] = '\0';
    result = (char *)realloc(result, res_length + 1);

    return result;
}

int status(){
	char *input = inputString(PROMPT);
	if (input == NULL){
		return 0;
	}
    printf("input:\"%s\"\n", input);

    char *result = delNotUnic(input);
    printf("result:\"%s\"\n", result);

    free(input);
    free(result);

}

int main(){

	while(status());

    return 0;
}
