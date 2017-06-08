#include <stdio.h>
#include "unit_test.h"

//test my_string_init_default
void test_my_string_init_default(){}

//test my_string_init_c_string
void test_my_string_init_c_string(){}

//test my_string_get_capacity
void test_my_string_get_capacity(){}

//test my_string_get_size
void test_my_string_get_size(){}

//test my_string_compare
void test_my_string_compare(){}

//test my_string_extraction
void test_my_string_extraction(){}

//test my_string_insertion
void test_my_string_insertion(){}

//test my_string_push_back
void test_my_string_push_back(){}

//test my_string_pop_back
void test_my_string_pop_back(){}

//test my_string_at
void test_my_string_at(){}

//test my_string_c_str
void test_my_string_c_str(){}

//test my_string_concat
void test_my_string_concat(){}

//test my_string_empty
void test_my_string_empty(){}

//test my_string_destroy
void test_my_string_destroy(){}

int main(int argc, char* argv[])
{
 Status (*tests[])(char*, int) =
 {
 test_init_default_returns_nonNULL,
 test_get_size_on_init_default_returns_0
 };
 int number_of_functions = sizeof(tests) / sizeof(tests[0]);
 int i;
 char buffer[500];
 int success_count = 0;
 int failure_count = 0;
 for(i=0; i<number_of_functions; i++)
 {
 if(tests[i](buffer, 500) == FAILURE)
 {
 printf("FAILED: Test %d failed miserably\n", i);
 printf("\t%s\n", buffer);
 failure_count++;
 }
 else
 {
// printf("PASS: Test %d passed\n", i);
// printf("\t%s\n", buffer);
 success_count++;
 }
 }
 printf("Total number of tests: %d\n", number_of_functions);
 printf("%d/%d Pass, %d/%d Failure\n", success_count,
 number_of_functions, failure_count, number_of_functions);
 return 0;
}
