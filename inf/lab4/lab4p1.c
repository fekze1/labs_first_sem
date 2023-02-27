#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

#define DEL " \t"
#define PROMPT " >"

char *delNotUnic(const char *string){
	char *str = strdup(string);
	int str_len = strlen(str);
	char *result = calloc(str_len, sizeof(char) + 1);
	int res_length = 0;
	char *word = strtok(str, DEL);

	while (word != NULL){
		int word_len  = strlen(word);
		int tmp = 0;
		for (int i = 0; i < word_len; i++){
			char *tmp1 = strchr(word, word[i]);			
			char *tmp2 = strrchr(word, word[i]);
			
			if (tmp1 != tmp2){
				tmp = 1;
				break;
			}
		}
		if (tmp == 1){
			memcpy(result + res_length, word, word_len * sizeof(char));
			res_length += word_len;
			result[res_length] = ' ';
			++res_length;
		}

		word = strtok(NULL, DEL);
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
	char *input = readline(PROMPT);
	char *result;
	printf("input:\"%s\"\n", input);

	if (input == NULL){
		return 0;
	}else{
		result = delNotUnic(input);
		printf("result:\"%s\"\n", result);	
	}
	
	free(input);
	free(result);
}

int main(){
	while(status());

	return 0;
}
