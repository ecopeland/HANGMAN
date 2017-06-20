#include <stdio.h>
#include "unit_test.h"

int main(int argc, char* argv[])
{
 Status (*tests[])(char*, int) =
 {
 test_ecopelan_init_default_returns_nonNULL,
 test_ecopelan_get_size_on_init_default_returns_0,
 test_ecopelan_get_capacity_on_init_default_returns_7,
 test_ecopelan_init_c_string_returns_nonNULL,
 test_ecopelan_get_capacity_on_init_c_string,
 test_ecopelan_get_size_on_init_c_string,
 test_ecopelan_capacity_one_greater_than_size_on_init_c_string,
 //test_ecopelan_get_capacity_with_invalid_hMy_string,
 test_ecopelan_string_compare_returns_negative,
 test_ecopelan_string_compare_returns_0,
 test_ecopelan_string_compare_returns_positive,
 test_ecopelan_string_extraction_returns_SUCCESS,
 test_ecopelan_string_insertion_returns_SUCCESS,
 test_ecopelan_string_push_back_with_invalid_hString_returns_FAILURE,
 test_ecopelan_string_push_back_returns_SUCCESS,
 test_ecopelan_string_pop_back_with_invalid_hString_returns_FAILURE,
 test_ecopelan_string_pop_back_returns_SUCCESS,
 test_ecopelan_string_pop_back_returns_FAILURE_if_string_empty,
 test_ecopelan_string_at_with_invalid_hString_returns_NULL,
 test_ecopelan_string_at_returns_nonNULL,
 test_ecopelan_string_at_with_index_out_of_bounds_returns_NULL,
 test_ecopelan_string_c_str_with_invalid_hString_returns_NULL,
 test_ecopelan_string_c_str_returns_nonNULL,
 test_ecopelan_string_c_str_adds_capacity_for_NULL_terminator,
 test_ecopelan_string_c_str_does_not_alter_string_size,
 test_ecopelan_string_concat_with_invalid_hResult_returns_FAILURE,
 test_ecopelan_string_concat_with_invalid_hAppend_returns_FAILURE,
 test_ecopelan_string_concat_returns_SUCCESS,
 //test_ecopelan_string_concat_does_not_alter_hAppend,
 
 test_ecopelan_string_empty_returns_TRUE,
 test_ecopelan_string_empty_returns_FALSE,
 test_ecopelan_string_destroy_sets_phMy_string_to_NULL
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
 test_string_assignment();

 return 0;
}
