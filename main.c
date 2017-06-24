#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"
#include "vector.h"
#include "hangman.h"

int main(int argc, char * argv[])
{
	/* //initial dictionary (L7 checkpoint 1)
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
	
	/* //test get_word_key_value (L8)
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
	my_string_destroy(&new_key4); */
	
	//set up
	int i;
	char guess;
	char play = 'Y';
	int length = 0;
	int guesses_remaining = 0;
	TREE hTree = NULL;
	MY_VECTOR dictionary = NULL;;
	Boolean valid_entry = FALSE;
	Boolean used_char = TRUE;
	Boolean WINNING = FALSE;
	
	//initial, win, or lose
	while(toupper(play) == 'Y'){
		//prompt the user to play
		printf("Do you want to play hangman?\n Enter Y or y for Yes: ");
		scanf("%c", &play);
		if(toupper(play) != 'Y'){
			break;
		}
		
		//prompt user for length
		while(length <= 0 || length > 29){
			printf("\nWhat is the length of the word? \n");
			scanf("%d", &length);
			//initialize vector of words with length
			dictionary = generate_vector_length(length);
			if(vector_get_size(dictionary) == 0){
				printf("Sorry, there are no words of length %d\n", length);
				printf("Please try again");
				length = 0;
			}
		}
		
		//initialize key of length
		MY_STRING key = key_init_default(length);
		//create temp_node with key
		NODE temp_node = node_key_init(key);
		
		//prompt user for number of guesses
		while(guesses_remaining <= 0){
			printf("How many guesses would you like? \n");
			scanf("%d", &guesses_remaining);
		}

		//initialize my_string containing guesses
		MY_STRING guesses = my_string_init_default();
		//show user key and number of possible words
		print_tree(temp_node);
		//show user guesses_remaining
		printf("Guesses remaining: %d\n", guesses_remaining);
		//show user guessed characters
		printf("Guessed characters: %s\n", my_string_c_str(guesses));
		
		while(guesses_remaining > 0){
			//prompt user for guess
			while(valid_entry != TRUE || used_char != FALSE){
				printf("What is your guess? \n");
				scanf("%c", &guess);
				if(!isalpha(guess)){
					valid_entry = FALSE;
					printf("%c is not in the alphabet, please try again\n", guess);
				}
				else{
					valid_entry = TRUE;
				}
				for(i = 0; i < (my_string_get_size(guesses) - 1); i++){
					if(guess == *my_string_at(guesses, i)){
						used_char = TRUE;
						printf("%c has already been guessed, please try again\n", guess);
					}
				}
				used_char = FALSE;
				my_string_push_back(guesses, guess);
			}
			//if valid guess and not already used
			guesses_remaining--;
			//build tree with all keys from dictionary (generate_key_tree)
			hTree = generate_key_tree(hTree, key, length, guess);
			dictionary = generate_vector_words(hTree, key);
			//check if win
			if(my_string_compare(key, vector_at(dictionary, 0)) == 0 && vector_get_size(dictionary) == 1){
				WINNING = TRUE;
				break;
			} 
			//if not win
			else{
				print_tree(hTree);
				//show user guesses_remaining
				printf("Guesses remaining: %d\n", guesses_remaining);
				//show user guessed characters
				printf("Guessed characters: %s\n", my_string_c_str(guesses));
			}
			tree_destroy(&hTree);
		}
		
		//if WON
		if(WINNING == TRUE){
			printf("CONGRATULATIONS!\n Because the word was %s, you win!\n", my_string_c_str(key));
		}
		
		//if LOST
		if(WINNING == FALSE){
			printf("SORRY!\n Because the word was %s, you lose!\n", my_string_c_str(vector_at(dictionary, 0)));
		}
			
		//free memory
		tree_destroy(&temp_node);
		vector_destroy(&dictionary);
		my_string_destroy(&key);
		my_string_destroy(&guesses);
	}
	return 0;
}