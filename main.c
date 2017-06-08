#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char * argv[])
{
  //initialize strings
  FILE* fp;
  Status status;
  int size;
  char temp;
  MY_STRING hMy_string0 = my_string_init_default();
  MY_STRING hMy_string1 = my_string_init_c_string("app");
  MY_STRING hMy_string2 = my_string_init_c_string("apple");
  MY_STRING hMy_string3 = my_string_init_c_string("sauce");

  //test my_string_init_default, my_string_init_c_string, 
  // my_string_get_size, and my_string_get_capacity
  //print string0 - test my_string_c_str
  printf("The default string is: %s \n", my_string_c_str(hMy_string0));
  printf("The default string size is %d, and the default string capacity is %d \n",
	 my_string_get_size(hMy_string0), my_string_get_capacity(hMy_string0));
  //print string1
  printf("string1 is: %s \n", my_string_c_str(hMy_string1));
  printf("The size of string1 is: %d \nThe capacity of string1 is: %d \n",
	 my_string_get_size(hMy_string1), my_string_get_capacity(hMy_string1));
  //print string2
  printf("string2 is: %s \n", my_string_c_str(hMy_string2));
  printf("The size of string2 is: %d \nThe capacity of string2 is: %d \n",
	 my_string_get_size(hMy_string2), my_string_get_capacity(hMy_string2));
  
  //test my_string_compare
  printf("The difference between string1 and string2 is: %d \n",
	 my_string_compare(hMy_string1, hMy_string2));
  printf("The difference between string2 and string1 is: %d \n",
	 my_string_compare(hMy_string2, hMy_string1));
  printf("The difference between string1 and string1 is: %d \n",
	 my_string_compare(hMy_string1, hMy_string1));
  
  //test my_string_push_back and my_string_at
  //print original string 1
  printf("The original string1 is: %s \n", my_string_c_str(hMy_string1));
  status = my_string_push_back(hMy_string1, 'l');
  size = my_string_get_size(hMy_string1);
  temp = *my_string_at(hMy_string1, size - 1);
  printf("string1 was pushed back with status = %d \n", status);
  printf("%c was added to string1 \n", temp);
  //print new string 1
  printf("The new string1 is: %s \n", my_string_c_str(hMy_string1));
  printf("The new size of string1 is: %d \nThe new capacity of string1 is: %d \n",
	 my_string_get_size(hMy_string1), my_string_get_capacity(hMy_string1));
  status = my_string_push_back(hMy_string1, 'e');
  size = my_string_get_size(hMy_string1);
  temp = *my_string_at(hMy_string1, size - 1);
  printf("string1 was pushed back with status = %d \n", status);
  printf("%c was added to string1 \n", temp);
  //print new string 1
  printf("The new string1 is: %s \n", my_string_c_str(hMy_string1));
  printf("The new size of string1 is: %d \nThe new capacity of string1 is: %d \n",
	 my_string_get_size(hMy_string1), my_string_get_capacity(hMy_string1));
  printf("The new difference between string1 and string2 is: %d \n",
	 my_string_compare(hMy_string1, hMy_string2));
  
  //test my_string_pop_back and my_string_at
  //print original string 2
  printf("The original string2 is: %s \n", my_string_c_str(hMy_string2));
  size = my_string_get_size(hMy_string2);
  temp = *my_string_at(hMy_string2, size - 1);
  status = my_string_pop_back(hMy_string2);
  printf("string2 was popped back with status = %d \n", status);
  printf("%c was deleted from string2 \n", temp);
  //print new string 2
  printf("The new string2 is: %s \n", my_string_c_str(hMy_string2));
  size = my_string_get_size(hMy_string2);
  temp = *my_string_at(hMy_string2, size - 1);
  status = my_string_pop_back(hMy_string2);
  printf("string2 was popped back with status = %d \n", status);
  printf("%c was deleted from string2 \n", temp);
  //print new string 2
  printf("The new string2 is: %s \n", my_string_c_str(hMy_string2));
  size = my_string_get_size(hMy_string2);
  temp = *my_string_at(hMy_string2, size - 1);
  status = my_string_pop_back(hMy_string2);
  printf("string2 was popped back with status = %d \n", status);
  printf("%c was deleted from string2 \n", temp);
  //print new string 2
  printf("The new string2 is: %s \n", my_string_c_str(hMy_string2));
  size = my_string_get_size(hMy_string2);
  temp = *my_string_at(hMy_string2, size - 1);
  status = my_string_pop_back(hMy_string2);
  printf("string2 was popped back with status = %d \n", status);
  printf("%c was deleted from string2 \n", temp);
  //print new string 2
  printf("The new string2 is: %s \n", my_string_c_str(hMy_string2));
  size = my_string_get_size(hMy_string2);
  temp = *my_string_at(hMy_string2, size - 1);
  status = my_string_pop_back(hMy_string2);
  printf("string2 was popped back with status = %d \n", status);
  printf("%c was deleted from string2 \n", temp);
  //print new string 2
  printf("The new string2 is: %s \n", my_string_c_str(hMy_string2));
  
  //test my_string_empty with empty string
  if (my_string_empty(hMy_string2) == TRUE) 
  {
    printf("string2 is empty\n");
  } 
  else printf("string2 is not empty\n");
  //test my_string_empty with non-empty string
  if (my_string_empty(hMy_string1) == TRUE) 
  {
    printf("string1 is empty\n");
  } 
  else printf("string1 is not empty\n");
  
  //test my_string_concat
  //print string 1
  printf("string1 is: %s \n", my_string_c_str(hMy_string1));
  //print string 3
  printf("string3 is: %s \n", my_string_c_str(hMy_string3));
  status = my_string_concat(hMy_string1, hMy_string3);
  printf("string1 and string3 are concatenated with status = %d \n", status);
  //print concatenated string (new string1)
  printf("string1 is now: %s \n", my_string_c_str(hMy_string1));
  //print string 3 to show no change
  printf("string3 is still: %s \n", my_string_c_str(hMy_string3));
  
  //test my_string_extraction and my_string_insertion
  fp = fopen("dictionary.txt", "r");
  while(my_string_extraction(hMy_string0, fp))
    {
	if(my_string_get_size(hMy_string0) == 29)
	{
	  my_string_insertion(hMy_string0, stdout);
	  printf("\nThe floccinaucinihilipification of this word is entirely justified.\n");
	}
      	if(fgetc(fp) == ' '){
	
	  printf("\n");
	}
    }
  
  //destroy strings
  my_string_destroy(&hMy_string0);
  my_string_destroy(&hMy_string1);
  my_string_destroy(&hMy_string2);
  my_string_destroy(&hMy_string3);
  fclose(fp);

  return 0;
}
