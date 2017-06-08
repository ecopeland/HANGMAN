#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_string.h"

//test my_string_init_default//
Status test_init_default_returns_nonNULL(char* buffer, int length)
{
  MY_STRING hString = NULL;
  hString = my_string_init_default();
  if(hString == NULL){
    my_string_destroy(&hString);
    strncpy(buffer, "test_init_default_returns_nonNULL\n"
	    "my_string_init_default returns NULL", length);
    return FAILURE;
  }
  else {
    my_string_destroy(&hString);
    strncpy(buffer, "\test_init_default_returns_nonNULL\n", length);
    return SUCCESS;
  }
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_default();
  if(my_string_get_size(hString) != 0){
    status = FAILURE;
    printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
    strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
	    "Did not receive 0 from get_size after init_default\n", length);
  }
  else{
    status = SUCCESS;
    strncpy(buffer, "test_get_size_on_init_default_returns_0\n", length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_get_capacity_on_init_default_returns_7(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_default();
  if(my_string_get_capacity(hString) != 7){
    status = FAILURE;
    printf("Expected a capacity of 7 but got %d\n", my_string_get_capacity(hString));
    strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n"
	    "Did not receive 7 from get_capacity after init_default\n", length);
  }
  else{
    status = SUCCESS;
    strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n", length);
  }
  my_string_destroy(&hString);
  return status;
}

//Status test_init_default_returns_valid_string_object(){}

//test my_string_init_c_string//
//Status test_my_string_init_c_string_with_invalid_c_string(){}
Status test_init_c_string_returns_nonNULL(char* buffer, int length)
{
  MY_STRING hString = NULL;
  hString = my_string_init_c_string("testing... 1 2 3");
  if(hString == NULL){
    my_string_destroy(&hString);
    strncpy(buffer, "test_init_c_string_returns_nonNULL\n"
	    "my_string_init_c_string returns NULL", length);
    return FAILURE;
  }
  else {
    my_string_destroy(&hString);
    strncpy(buffer, "\test_init_c_string_returns_nonNULL\n", length);
    return SUCCESS;
  }
}

Status test_get_capacity_on_init_c_string(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_c_string("testing... 1 2 3");
  if(my_string_get_capacity(hString) != 17){
    status = FAILURE;
    printf("Expected a capacity of 17 but got %d\n", my_string_get_capacity(hString));
    strncpy(buffer, "test_get_capacity_on_init_c_string\n"
	    "Did not receive 17 from get_capacity after init_c_string\n", length);
  }
  else{
    status = SUCCESS;
    strncpy(buffer, "test_get_capacity_on_init_c_string\n", length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_get_size_on_init_c_string(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_c_string("testing... 1 2 3");
  if(my_string_get_size(hString) != 16){
    status = FAILURE;
    printf("Expected a size of 16 but got %d\n", my_string_get_capacity(hString));
    strncpy(buffer, "test_get_size_on_init_c_string\n"
	    "Did not receive 16 from get_size after init_c_string\n", length);
  }
  else{
    status = SUCCESS;
    strncpy(buffer, "test_get_size_on_init_c_string\n", length);
  }
  my_string_destroy(&hString);
  return status;
}

Status test_capacity_one_greater_than_size_on_init_c_string(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_c_string("testing... 1 2 3");
  if((my_string_get_capacity(hString) - my_string_get_size(hString)) != 1){
    status = FAILURE;
    printf("Expected difference between capacity and size to be 1 but got %d\n",
	   (my_string_get_capacity(hString) - my_string_get_size(hString)));
    strncpy(buffer, "test_capacity_one_greater_than_size_on_init_c_string\n"
	    "Did not receive 1 from (get_capacity - get_size) after init_c_string\n", length);
  }
  else{
    status = SUCCESS;
    strncpy(buffer, "test_capacity_one_greater_than_size_on_init_c_string\n", length);
  }
  my_string_destroy(&hString);
  return status;
}

//test my_string_get_capacity//
//Status test_get_capacity_with_invalid_hMy_string(){}

//test my_string_get_size//
//Status test_get_size_with_invalid_hMy_string(){}

//test my_string_compare//
//Status test_string_compare_with_invalid_hLeft_string(){}
//Status test_string_compare_witn_invalid_hRight_string(){}
Status test_string_compare_returns_negative(char* buffer, int length)
{
  MY_STRING hLeft_string = NULL;
  MY_STRING hRight_string = NULL;
  Status status;
  hLeft_string = my_string_init_c_string("t");
  hRight_string = my_string_init_c_string("test");
  if(my_string_compare(hLeft_string, hRight_string) >= 0){
    status = FAILURE;
    printf("Expected integer less than zero but got %d\n",
	   my_string_compare(hLeft_string, hRight_string));
    strncpy(buffer, "test_string_compare_returns_negative\n"
	    "Did not receive negative integer from string_compare after init_c_string(s)\n",
	    length);
  }
  else{
    status = SUCCESS;
    strncpy(buffer, "test_string_compare_returns_negative\n", length);
  }
  my_string_destroy(&hLeft_string);
  my_string_destroy(&hRight_string);
  return status;
}

Status test_string_compare_returns_0(char* buffer, int length)
{
  MY_STRING hLeft_string = NULL;
  MY_STRING hRight_string = NULL;
  Status status;
  hLeft_string = my_string_init_c_string("test");
  hRight_string = my_string_init_c_string("test");
  if(my_string_compare(hLeft_string, hRight_string) != 0){
    status = FAILURE;
    printf("Expected 0 but got %d\n",
	   my_string_compare(hLeft_string, hRight_string));
    strncpy(buffer, "test_string_compare_returns_0\n"
	    "Did not receive 0 from string_compare after identical init_c_string(s)\n",
	    length);
  }
  else{
    status = SUCCESS;
    strncpy(buffer, "test_string_compare_returns_0\n", length);
  }
  my_string_destroy(&hLeft_string);
  my_string_destroy(&hRight_string);
  return status;
}

Status test_string_compare_returns_positive(char* buffer, int length)
{
  MY_STRING hLeft_string = NULL;
  MY_STRING hRight_string = NULL;
  Status status;
  hLeft_string = my_string_init_c_string("test");
  hRight_string = my_string_init_c_string("t");
  if(my_string_compare(hLeft_string, hRight_string) > 0){
    status = FAILURE;
    printf("Expected integer greater than zero but got %d\n",
	   my_string_compare(hLeft_string, hRight_string));
    strncpy(buffer, "test_string_compare_returns_positive\n"
	    "Did not receive positive integer from string_compare after init_c_string(s)\n",
	    length);
  }
  else{
    status = SUCCESS;
    strncpy(buffer, "test_string_compare_returns_positive\n", length);
  }
  my_string_destroy(&hLeft_string);
  my_string_destroy(&hRight_string);
  return status;
}

//test my_string_extraction//
//Status test_extraction_with_invalid_hString(){}
Status test_string_extraction_returns_SUCCESS(char* buffer, int length)
{
  
}

//test my_string_insertion//
//Status test_my_string_insertion_with_invalid_hString(){}
Status test_string_insertion_returns_SUCCESS(char* buffer, int length)
{
  
}

//test my_string_push_back//
//Status test_string_push_back_with_invalid_hString(){}
Status test_string_push_back_returns_SUCCESS(char* buffer, int length)
{
  
}

//test my_string_pop_back//
//Status test_string_pop_back_with_invalid_hString(){}
Status test_string_pop_back_returns_SUCCESS(char* buffer, int length)
{
  
}

//test my_string_at//
//Status test_string_at_with_invalid_hString(){}
Status test_string_at_returns_nonNULL(char* buffer, int length)
{
  
}

Status test_string_at_with_index_out_of_bounds_returns_NULL(char* buffer, int length)
{
  
}

//test my_string_c_str//
//Status test_string_c_str_with_invalid_hString(){}
Status test_string_c_str_returns_nonNULL(char* buffer, int length)
{
  
}

Status test_string_c_str_adds_capacity_for_NULL_terminator(char* buffer, int length)
{
  
}

Status test_string_c_str_does_not_alter_string_size(char* buffer, int length)
{
  
}

//test my_string_concat//
//Status test_string_concat_with_invalid_hResult(){}
//Status test_string_concat_with_invalid_hAppend(){}
Status test_string_concat_returns_SUCCESS(char* buffer, int length)
{
  
}

Status test_string_concat_does_not_alter_hAppend(char* buffer, int length)
{
  
}

Status test_string_concat_does_not_alter_hResult_or_hAppend_on_FAILURE(char* buffer, int length)
{
  
}

//test my_string_empty//
//Status test_string_empty_with_invalid_hString(){}

Status test_string_empty_returns_TRUE(char* buffer, int length)
{
  
}

Status test_string_empty_returns_FALSE(char* buffer, int length)
{
  
}

//test my_string_destroy//
//Status test_string_destroy_with_invalid_phString(){}
Status test_string_destroy_free_object_memory(char* buffer, int length)
{
  
}

Status test_string_destroy_sets_phMy_string_to_NULL(char* buffer, int length)
{
  
}

