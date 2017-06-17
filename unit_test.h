#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"

//test my_string_init_default//
Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_get_capacity_on_init_default_returns_7(char* buffer, int length);

//test my_string_init_c_string//
Status test_my_string_init_c_string_with_invalid_c_string(char* buffer, int length);
Status test_init_c_string_returns_nonNULL(char* buffer, int length);
Status test_get_capacity_on_init_c_string(char* buffer, int length);
Status test_get_size_on_init_c_string(char* buffer, int length);
Status test_capacity_one_greater_than_size_on_init_c_string(char* buffer, int length);

//test my_string_get_capacity//
//Status test_get_capacity_with_invalid_hMy_string(char* buffer, int length);

//test my_string_get_size//
//Status test_get_size_with_invalid_hMy_string(char* buffer, int length);

//test my_string_compare//
//Status test_string_compare_with_invalid_hLeft_string(char* buffer, int length);
//Status test_string_compare_witn_invalid_hRight_string(char* buffer, int length);
Status test_string_compare_returns_negative(char* buffer, int length);
Status test_string_compare_returns_0(char* buffer, int length);
Status test_string_compare_returns_positive(char* buffer, int length);

//test my_string_extraction//
//Status test_extraction_with_invalid_hString(char* buffer, int length);
//Status test_string_extraction_returns_SUCCESS(char* buffer, int length);

//test my_string_insertion//
//Status test_my_string_insertion_with_invalid_hString(char* buffer, int length);
//Status test_string_insertion_returns_SUCCESS(char* buffer, int length);

//test my_string_push_back//
//Status test_string_push_back_with_invalid_hString(){}
Status test_string_push_back_returns_SUCCESS(char* buffer, int length);

//test my_string_pop_back//
//Status test_string_pop_back_with_invalid_hString(){}
Status test_string_pop_back_returns_SUCCESS(char* buffer, int length);
Status test_string_pop_back_returns_FAILURE_if_string_empty(char* buffer, int length);

//test my_string_at//
//Status test_string_at_with_invalid_hString(){}
Status test_string_at_returns_nonNULL(char* buffer, int length);
Status test_string_at_with_index_out_of_bounds_returns_NULL(char* buffer, int length);

//test my_string_c_str//
//Status test_string_c_str_with_invalid_hString();
Status test_string_c_str_returns_nonNULL(char* buffer, int length);
Status test_string_c_str_adds_capacity_for_NULL_terminator(char* buffer, int length);
Status test_string_c_str_does_not_alter_string_size(char* buffer, int length);

//test my_string_concat//
//Status test_string_concat_with_invalid_hResult(){}
//Status test_string_concat_with_invalid_hAppend(){}
Status test_string_concat_returns_SUCCESS(char* buffer, int length);
Status test_string_concat_does_not_alter_hAppend(char* buffer, int length);
Status test_string_concat_does_not_alter_hResult_or_hAppend_on_FAILURE(char* buffer, int length);

//test my_string_empty//
//Status test_string_empty_with_invalid_hString(){}
Status test_string_empty_returns_TRUE(char* buffer, int length);
Status test_string_empty_returns_FALSE(char* buffer, int length);

//test my_string_destroy//
//Status test_string_destroy_with_invalid_phString(){}
Status test_string_destroy_free_object_memory(char* buffer, int length);
Status test_string_destroy_sets_phMy_string_to_NULL(char* buffer, int length);

#endif
