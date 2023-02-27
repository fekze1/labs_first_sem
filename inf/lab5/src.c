#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "src.h"

Student create_rand_student()
{
    char *name = get_rand_name();
    name[6] = toupper(name[6]);
    char group[8];
    get_rand_group(group);
    float grade = get_rand_float(0, 5);

    return create_student(name, group, grade);
}

void free_twodim_arr( int arrays_amount, int elements_amount, Student array[][elements_amount])
{
    for (int i = 0; i < arrays_amount; i++)
    {
        for (int j = 0; j < elements_amount; j++)
        {
            free(array[i][j].full_name);
        }
    }
}

float get_rand_float(int min, int max)
{
    srand(clock());
    return (float)(rand() * 1.0  / RAND_MAX ) * (max - min) + min;
}

int get_rand_int(int min, int max)
{
    srand(clock());
    return rand() % (max - min + 1) + min;
}

char *get_rand_name()
{
    char *name = (char *)malloc(11 * sizeof(char) + 1);
    memcpy(name, "Agent ", 6 * sizeof(char));
    for (int i = 6; i < 11; i++) name[i] = "smith"[get_rand_int(0, 4)];
    name[11] = '\0';

    return name;
}

void get_rand_group(char group_ptr[8])
{
    group_ptr[0] = "SBM"[get_rand_int(0, 2)];
    group_ptr[1] = get_rand_int(0, 9) + '0';
    group_ptr[2] = get_rand_int(0, 9) + '0';
    group_ptr[3] = '-';
    group_ptr[4] = get_rand_int(0, 9) + '0';
    group_ptr[5] = get_rand_int(0, 9) + '0';
    group_ptr[6] = get_rand_int(0, 9) + '0';
    group_ptr[7] = '\0';
}


cmp_ptr get_cmp_ptr(char *cmp_name, char *dir)
{
    if ((strcmp(cmp_name, "name") == 0) && (strcmp(dir, "increase") == 0)) return &student_cmp_FN;
    if ((strcmp(cmp_name, "name") == 0) && (strcmp(dir, "decrease") == 0)) return &student_cmpr_FN;

    if ((strcmp(cmp_name, "group") == 0) && (strcmp(dir, "increase") == 0)) return &student_cmp_group;
    if ((strcmp(cmp_name, "group") == 0) && (strcmp(dir, "decrease") == 0)) return &student_cmpr_group;

    if ((strcmp(cmp_name, "grade") == 0) && (strcmp(dir, "increase") == 0)) return &student_cmp_grade;
    if ((strcmp(cmp_name, "grade") == 0) && (strcmp(dir, "decrease") == 0)) return &student_cmpr_grade;

}

int find_length(const char *string) 
{
    int length = 0;

    while (*string) 
    {
        ++string, ++length;
    }

    return length;
}


char *splice_strings(char * str1, const char * str2) 
{
    int strLen1, i;
    for (strLen1 = 0; str1[strLen1] != '\0'; ++strLen1);
        for (i = strLen1; str2[i - strLen1] != '\0'; ++i) 
        {
             str1[i] = str2[i - strLen1];
        }
    str1[i] = '\0';

    return str1;
}

char *input_string(FILE *file) 
{
    char *string = (char *)malloc(1);
    char buffer[81];
    int n, str_length = 0;
    *string = '\0';

    do
    {
        n = fscanf(file, "%80[^\n]", buffer);

        if(n < 0){

        free(string);
        string = NULL;
        continue;

        }

        if(n == 0)
        {

            fscanf(file, "%*c");

        }
        else 
        {

            str_length += find_length(buffer);
            string = (char *)realloc(string, str_length + 1);
            string = splice_strings(string, buffer);

        }
    }while(n > 0);

    return string;
}

int get_gap(int gap)
{
	gap = gap * 10 / 13;
	if (gap < 1) return 1;
	return gap;
}

void comb_sort(Student *base, size_t length, int(*compar)(const void *, const void *))
{
	int gap = length;
	int flag = 1;

	while(gap != 1 || flag == 1)
	{
		gap = get_gap(gap);
		flag = 0;

		for (int i = 0; i < ((int)length - gap); i++)
		{
			if (compar(&base[i], &base[i + gap]) == 1)
			{
				swap(&base[i], &base[i + gap]);
			}
		}
	}
}

void pairInsertion_sort(Student *base, size_t length, int(*compar)(const void *, const void *))
{

	int i = 0;
	int j;
	Student key1;
	Student key2;

	while (i < (int)length - 1)
	{
		key1 = base[i];
		key2 = base[i + 1];

		if (compar(&key1, &key2) == -1)
		{
			Student key3 = key1;
			key1 = key2;
			key2 = key3;
		}

		j = i - 1;

		while (j >= 0 && (compar(&base[j], &key1) == 1))
		{
			base[j + 2] = base[j];
			j--;
		}

		base[j + 2] = key1;

		while (j >= 0 && (compar(&base[j], &key2) == 1))
		{
			base[j + 1] = base[j];
			j--;
		}

		base[j + 1] = key2;

		i += 2;
		
	}

	if (i == (int)length - 1)
	{
		key2 = base[i];
		j = i - 1;

		while (j >= 0 && (compar(&base[j], &key2) == 1))
		{
			base[j + 1] = base[j];
			j--;	
		}

		base[j + 1] = key2;
	}

}

int student_cmp_grade(const void *student1, const void *student2)
{
	const Student *tmp1 = student1;
	const Student *tmp2 = student2;
	if (tmp1->average_grade > tmp2->average_grade) return 1;
	else if (tmp1->average_grade < tmp2->average_grade) return -1;
	return 0;
}

int student_cmpr_grade(const void *student1, const void *student2)
{
	const Student *tmp1 = student1;
	const Student *tmp2 = student2;
	if (tmp1->average_grade > tmp2->average_grade) return -1;
	else if (tmp1->average_grade < tmp2->average_grade) return 1;
	return 0;
}

int student_cmp_FN(const void *student1, const void *student2)
{
	const Student *tmp1 = student1;
	const Student *tmp2 = student2;
	
	return strcmp(tmp1->full_name, tmp2->full_name);
}

int student_cmpr_FN(const void *student1, const void *student2)
{
	const Student *tmp1 = student1;
	const Student *tmp2 = student2;
	
	return -1 * strcmp(tmp1->full_name, tmp2->full_name);
}

int student_cmp_group(const void *student1, const void *student2)
{
	const Student *tmp1 = student1;
	const Student *tmp2 = student2;
	
	return -1 * strcmp(tmp1->group_number, tmp2->group_number);
}

int student_cmpr_group(const void *student1, const void *student2)
{
	const Student *tmp1 = student1;
	const Student *tmp2 = student2;
	
	return -1 * strcmp(tmp1->group_number, tmp2->group_number);
}

Student create_student(char *full_name, char group_number[8], float average_grade)
{
	Student new;
	
	new.full_name = full_name;
	
	strcpy(new.group_number, group_number);
	
	new.average_grade = average_grade;
	
	return new;
}

void print_student(const Student student)
{
	printf("full name: %s\n", student.full_name);
	printf("group number: %s\n", student.group_number);
	printf("average grade: %f\n", student.average_grade);
}

void print_array(Student array[], int amount)
{
	for (int i = 0; i < amount; i++) printf("array[%d]: %s, %s, %f\n", i, array[i].full_name, array[i].group_number, array[i].average_grade);
}

void swap(Student *temp1, Student *temp2)
{
	Student tmp = *temp1;
	*temp1 = *temp2;
	*temp2 = tmp;
}
