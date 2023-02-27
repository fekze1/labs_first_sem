#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "src.h"

int status(char *method, char *dir, char *param, char *input_name, char *output_name)
{		
	FILE *input_file = fopen(input_name, "r");
	if (!input_file)
	{
		printf("\033[91minvalid input file\033[0m\n");
		return 0;
	}

	int failed_values = 0;
	int array_length = 10;
	Student array[array_length];
	char *name;
	char group[8];
	float grade;

	name = input_string(input_file);

	int key = 0;
	for (int i = 0; i < array_length; i++)
	{	
		if(fscanf(input_file, "%s %f\n", group, &grade) < 2)
		{
			printf("\033[91mrecording of\033[0m \033[93m%s\033[0m \033[91mfailed due to invalid type of some values\033[0m\n", name);
			failed_values++;
			fscanf(input_file, "%*s\n");
			free(name);
			name = input_string(input_file);
			continue;
		}
		Student student = create_student(name, group, grade);
		array[key] = student;
		key++;
		name = input_string(input_file);
		
	}

	array_length -= failed_values;
	
	if (fclose(input_file) == EOF)
	{
		printf("\033[91mreading failed\033[0m\n");
		for (int i = 0; i < array_length; i++) free((array[i]).full_name);
		return 0;	
	}
	
	printf("\033[92mfile\033[0m \033[93m%s\033[0m \033[92mread succesfully\033[0m\n", input_name);
	
	if (strcmp(method, "pairinsertion") == 0) pairInsertion_sort(array, array_length, get_cmp_ptr(param, dir));

	if (strcmp(method, "comb") == 0) comb_sort(array, array_length, get_cmp_ptr(param, dir));

	if (strcmp(method, "qsort") == 0) qsort(array, array_length, sizeof(Student), get_cmp_ptr(param, dir));

	FILE *output_file = fopen(output_name, "w");
	if (!output_file){
		printf("\033[91minvalid output file\033[0m");
		for (int i = 0; i < array_length; i++) free((array[i]).full_name);
		return 0;
	}

	for (int i = 0; i < array_length; i++) fprintf(output_file, "%s\n%s %f\n", array[i].full_name, array[i].group_number, array[i].average_grade);

	if (fclose(output_file) == EOF)
	{
		printf("\033[91mrecording failed\033[0m\n");
		for (int i = 0; i < array_length; i++) free((array[i]).full_name);
		return 0;
		
	}
	printf("\033[92mwrite to file\033[0m \033[93m%s\033[0m \033[92msuccesfull\033[0m\n", output_name);
	
	for (int i = 0; i < array_length; i++) free((array[i]).full_name);
	
	return 0;
}

int main(int argc, char *argv[])
{	
	int res = 0;
	char *sort_method;
	char *direction;
	char *parameter;
	char *input_name;
	char *output_name;

	while ((res = getopt(argc, argv, "s:d:p:i:o:")) != -1)
	{
		switch (res)
		{
			case 's': sort_method = optarg; break;
			case 'd': direction = optarg; break;
			case 'p': parameter = optarg; break;
			case 'i': input_name = optarg; break;
			case 'o': output_name = optarg; break;
			case '?': 
				printf("\033[91minvalid value\033[0m\n"); 
				return 0;
				break;
		}
	}

	if ((strcmp(sort_method, "pairinsertion") != 0) && (strcmp(sort_method, "comb") != 0) && (strcmp(sort_method, "qsort") != 0)) printf("invalid sort method\n");
	else if ((strcmp(direction, "increase") != 0) && (strcmp(direction, "decrease") != 0)) printf("invalid direction\n");
	else if ((strcmp(parameter, "grade") != 0) && (strcmp(parameter, "name") != 0) && (strcmp(parameter, "group") != 0)) printf("invalid parameter\n");

	else status(sort_method, direction, parameter, input_name, output_name);
	
	return 0;
}
