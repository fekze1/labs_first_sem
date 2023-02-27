#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include <ctype.h>
#include "src.h"

int status(char *method, char *dir, char *param, char *arrays_amount, char *elements_amount)
{	
	int arrays = atoi(arrays_amount);
	int elements = atoi(elements_amount);

	if(arrays == 0 || elements == 0)
	{
		printf("\033[91mcan't be proceed due to invalid values\033[0m\n");
		return 0;
	}

	Student array[arrays][elements];

	for (int i = 0; i < arrays; i++)
	{
		for (int j = 0; j < elements; j++)
		{
			array[i][j] = create_rand_student();
		}
	}
	
	double all_time_spent;
	double average_time = 0;
	clock_t all_start = clock();
	
	for (int i = 0; i < arrays; i++)
	{	
		clock_t start = clock();
		if (strcmp(method, "pairinsertion") == 0)
		{
			pairInsertion_sort(array[i], elements, get_cmp_ptr(param, dir));
		}
		else if (strcmp(method, "comb") == 0)
		{
			comb_sort(array[i], elements, get_cmp_ptr(param, dir));
		}
		else if (strcmp(method, "qsort") == 0)
		{
			qsort(array[i], elements, sizeof(Student), get_cmp_ptr(param, dir));
		}
		clock_t finish = clock();
		average_time += finish - start;
	}
	
	clock_t all_finish = clock();
	all_time_spent = (double)(all_finish - all_start) / CLOCKS_PER_SEC;;
	average_time /= arrays * CLOCKS_PER_SEC * 1.0;
	
	printf("\033[92mtotal time spent:\033[0m \033[93m%lf\033[0m \033[92mseconds\033[0m\n", all_time_spent);
	printf("\033[92maverage time spent on one array:\033[0m \033[93m%lf\033[0m \033[92mseconds\033[0m\n", average_time);

	free_twodim_arr( arrays, elements, array);
	return 0;
}

int main(int argc, char *argv[])
{	
	int res;
	char *sort_method;
	char *direction;
	char *parameter;
	char *arrays_amount;
	char *elements_amount;

	while ((res = getopt(argc, argv, "s:d:p:a:e:")) != -1)
	{
		switch (res)
		{
			case 's': sort_method = optarg; break;
			case 'd': direction = optarg; break;
			case 'p': parameter = optarg; break;
			case 'a': arrays_amount = optarg; break;
			case 'e': elements_amount = optarg; break;
			case '?': 
				printf("invalid value"); 
				return 0;
				break;
		}
	}

	if ((strcmp(sort_method, "pairinsertion") != 0) && (strcmp(sort_method, "comb") != 0) && (strcmp(sort_method, "qsort") != 0)) printf("invalid sort method\n");
	else if ((strcmp(direction, "increase") != 0) && (strcmp(direction, "decrease") != 0)) printf("invalid direction\n");
	else if ((strcmp(parameter, "grade") != 0) && (strcmp(parameter, "name") != 0) && (strcmp(parameter, "group") != 0)) printf("invalid parameter\n");

	else status(sort_method, direction, parameter, arrays_amount, elements_amount);
	
	return 0;
}
