#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "vector.h"

int main(int argc, char * argv[])
{
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
	return 0;
}