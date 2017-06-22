#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "vector.h"
#include "hangman.h"

int main(int argc, char * argv[])
{
	/* //initial dictionary
	int i;
	FILE* fp;
	fp = fopen("dictionary.txt", "r");
	MY_STRING hString = my_string_init_default();
	
	if(hString == NULL || fp == NULL){
		exit(1);
	}
	
	//create array of vectors of My_strings
	MY_VECTOR array[30];
	for(i = 1; i < 30; i++){
		array[i] = vector_init_default();
		if(array[i] == NULL){
			exit(1);
		}
	}
	//push string to vector at array position of string size (word length)
	while(my_string_extraction(hString, fp)){
		if(my_string_get_size(hString) < 30){
			vector_push_back(array[my_string_get_size(hString)], hString);
		}
		if(fgetc(fp) == ' '){
			continue;
		}
	}
	for(i = 1; i < 30; i++){
		//print the size of each of the vectors 
		// (providing a count of how many words of each length)
		printf("Vectors containing strings of length %2d: %d\n", i, vector_get_size(array[i]));
		//destroy array of vectors
		vector_destroy(&array[i]);
	}
	my_string_destroy(&hString);
	fclose(fp);
	return 0; */
	
	MY_STRING hString1 = my_string_init_c_string("The");
	MY_STRING key1 = my_string_init_c_string("---");
	MY_STRING new_key1 = my_string_init_default();

	MY_STRING hString2 = my_string_init_c_string("Truck");
	MY_STRING key2 = my_string_init_c_string("-----");
	MY_STRING new_key2 = my_string_init_default();

	MY_STRING hString3 = my_string_init_c_string("happy");
	MY_STRING key3 = my_string_init_c_string("--ppy");
	MY_STRING new_key3 = my_string_init_default();

	MY_STRING hString4 = my_string_init_c_string("awesome");
	MY_STRING key4 = my_string_init_c_string("--e---e");
	MY_STRING new_key4 = my_string_init_default();

	get_word_key_value(key1, new_key1, hString1, 'T');
	get_word_key_value(key2, new_key2, hString2, 'r');
	get_word_key_value(key3, new_key3, hString3, 'h');
	get_word_key_value(key4, new_key4, hString4, 'z');


	printf("%s\n", my_string_c_str(new_key1));
	printf("%s\n", my_string_c_str(new_key2));
	printf("%s\n", my_string_c_str(new_key3));
	printf("%s\n", my_string_c_str(new_key4));

	my_string_destroy(&hString1);
	my_string_destroy(&hString2);
	my_string_destroy(&hString3);
	my_string_destroy(&hString4);
	my_string_destroy(&key1);
	my_string_destroy(&key2);
	my_string_destroy(&key3);
	my_string_destroy(&key4);
	my_string_destroy(&new_key1);
	my_string_destroy(&new_key2);
	my_string_destroy(&new_key3);
	my_string_destroy(&new_key4);

	return 0;
}