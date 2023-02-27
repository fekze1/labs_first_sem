#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include <ctype.h>
#include "src.h"

int status(char *method, char *dir, char *param, char *arrays_amount, char *start, char *finish, char *step)
{	
	int tmp_finish = atoi(finish);
	int tmp_start = atoi(start);
	int itr = atoi(step);
	
	double all_data[(tmp_finish - tmp_start) / itr];
	
	for (int elements = tmp_start; elements < tmp_finish + 1; elements += itr)
	{	
	    int arrays = atoi(arrays_amount);

	    Student array[arrays][elements];

	    for (int i = 0; i < arrays; i++)
	    {
	        for (int j = 0; j < elements; j++) array[i][j] = create_rand_student();
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
	    all_time_spent = (double)(all_finish - all_start) / CLOCKS_PER_SEC;
	    average_time /= arrays * CLOCKS_PER_SEC * 1.0;

	 	free_twodim_arr(arrays, elements, array);

	 	all_data[elements / itr - 1] = average_time;
 	}
 	
	printf("\033[92melements amount:\033[0m\n");
 	for (int i = tmp_start; i < tmp_finish + 1; i += itr)
 	{
 		if (i + 1 == tmp_finish + 1) printf("%d\n", i);
 		else printf("%d, ", i);
 	}

	printf("\n\033[92mtime spent:\033[0m\n");
 	for (int i = 0; i < (tmp_finish - tmp_start) / itr + 1; i++)
 	{
 		if (i + 1 == (tmp_finish - tmp_start) / itr + 1) printf("%.8lf\n", all_data[i]);
 		else printf("%.8lf, ", all_data[i]);
 	}
    return 0;
}

int main(int argc, char *argv[])
{
    int res;
    char *sort_method;
    char *direction;
    char *parameter;
    char *arrays_amount;
    char *start;
    char *finish;
    char *step;

    while ((res = getopt(argc, argv, "s:d:p:a:b:f:m:")) != -1)
    {
        switch (res)
        {
            case 's': sort_method = optarg; break;
            case 'd': direction = optarg; break;
            case 'p': parameter = optarg; break;
            case 'a': arrays_amount = optarg; break;
            case 'b': start = optarg; break;
            case 'f': finish = optarg; break;
            case 'm': step  = optarg; break;
            case '?':
                printf("invalid value");
                return 0;
                break;
        }
    }

    if ((strcmp(sort_method, "pairinsertion") != 0) && (strcmp(sort_method, "comb") != 0) && (strcmp(sort_method, "qsort") != 0)) printf("invalid sort method\n");
    else if ((strcmp(direction, "increase") != 0) && (strcmp(direction, "decrease") != 0)) printf("invalid direction\n");
    else if ((strcmp(parameter, "grade") != 0) && (strcmp(parameter, "name") != 0) && (strcmp(parameter, "group") != 0)) printf("invalid parameter\n");

    else status(sort_method, direction, parameter, arrays_amount, start, finish, step);

    return 0;
}
