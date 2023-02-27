#include <stddef.h>
#include <stdio.h>
#ifndef SRC_H
#define SRC_H

typedef struct 
{
	char *full_name;
	char group_number[8];
	float average_grade;
} Student;

typedef int (*cmp_ptr)(const void *, const void *);

Student create_rand_student();

void free_twodim_arr(int arrays_amount, int elements_amount, Student array[][elements_amount]);

float get_rand_float(int min, int max);

int get_rand_int(int min, int max);

char *get_rand_name();

void get_rand_group(char group_ptr[8]);

cmp_ptr get_cmp_ptr(char *cmp_name, char *dir);

int find_length(const char *string);

char *splice_strings(char * str1, const char * str2);

char *input_string(FILE *file);

int get_gap(int gap);

void comb_sort(Student *base, size_t length, int(*compar)(const void *, const void *));

void pairInsertion_sort(Student *base, size_t length, int(*compar)(const void *, const void *));

int student_cmp_grade(const void *student1,const void *student2);

int student_cmpr_grade(const void *student1,const void *student2);

int student_cmp_FN(const void *student1,const void *student2);

int student_cmpr_FN(const void *student1,const void *student2);

int student_cmp_group(const void *student1,const void *student2);

int student_cmpr_group(const void *student1,const void *student2);

Student create_student(char *full_name, char group_number[8], float average_grade);

void print_student(const Student student);

void print_array(Student array[], int amount);

void swap(Student *temp1, Student *temp2);


#endif 
