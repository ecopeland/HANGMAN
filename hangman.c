#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"
#include "vector.h"
#include "hangman.h"

/* 
4. An ​AssociativeArray
​ module, as described during a later lab, which allows using ​MyString
​ data as the “key” or “index” to locate a particular ​Vector of Mystrings.
 The ​AssociativeArray can be based on (implemented using) the ​AVL Tree
​ that you have researched and written on your own or in your lab pairing 
 (or the easy way out: a regular Binary Search Tree). 
 There will be no duplicate keys. When a new ​MyString data item is 
 added to the ​AssociativeArray, a “key” value (also a MyString object) 
 will be given. That “key” is located in the AVL tree (or added to the 
 AVL tree), and the data ​MyString is added to the ​Vector associated 
 with that “key”. Look-up by “key” yields a Vector of all of the ​MyStrings
​ that have been added to the ​Vector associated with that key. 
5. A function ​generate_key_tree which takes 3 arguments, a guess (character),
 word length (integer) and the root of a pre-existing key tree which
 may be NULL. This function should generate a tree (either AVL or regular BST)
 given the arguments as described in #4 above and the words in the dictionary
 if the 3rd argument is NULL. If the third argument is not NULL, it should
 traverse the tree, find the largest word group and use that as the dictionary.
 You may want to refer to L8 for hints. 
 */
 
 //char guess;
 //int length;
 //MY_VECTOR vector[30];
 //MY_STRING current_word_family;
 //MY_STRING word;
 
 
 //Generate word key value with My_string->data. Key is index of Vector array
 // where vector contains only one My_string with that specific word.
 // There will be no duplicate keys.
 MY_STRING key_init_default(int length)
 {
	int i;
	MY_STRING key = my_string_init_default();
	//checks
	if(key == NULL){
		return NULL;
	}
	if(length <= 0){
		return NULL;
	}
	else{
		for(i = 0; i < length; i++){
			if(!my_string_push_back(key, '-')){
				my_string_destroy(&key);
				return NULL;
			}
		}
	}
	return key;
 }
 
 //Precondition: current_word_family, new_key, and word are all handles to
 // valid MY_STRING opaque objects. guess is an alphabetical character that
 // can be either upper or lower case. *current_word_family is the old key*
 // *word is the string from the dictionary - hTree->(node)words->(vector)data->(my_string)data*
 //Postcondition: Returns SUCCESS after replacing the string in new_key with
 // the key value formed by considering the current word family, the word,
 // and the guess. Returns FAILURE in the case of a resizing problem with 
 // the new_key string.
 Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
 {
	int i;
	Status return_status;
	
	//check inputs (preconditions)
	if(current_word_family == NULL || new_key == NULL || word == NULL){
		return FAILURE;
	}
	//works for both upper and lower case
	Status uppercase = isupper(guess);
	if(uppercase){
		guess = tolower(guess);
	}
	if(!(guess >= 'a' && guess <= 'z')){
		return FAILURE;
	}
	
	//if all checks clear - create new key
	for(i = 0; i < my_string_get_size(word); i++){
		if(guess == tolower(*my_string_at(word, i)) || guess == tolower(*my_string_at(current_word_family, i))){
			//if uppercase guess and first letter of word,
			// revert back to uppercase for new key
			if(i == 0){
				if(uppercase){
					guess = toupper(guess);
				}
			}
			return_status = my_string_push_back(new_key, guess);
		}
		else{
			return_status = my_string_push_back(new_key, *my_string_at(current_word_family, i));
		}
	}
	return return_status;
 }

 
/*  //generate vector with strings of word length from dictionary
 MY_VECTOR generate_vector_length(int length)
 {
	
	//int i;
	FILE* fp;
	fp = fopen("dictionary.txt", "r");
	MY_STRING hString = my_string_init_default();
	
	if(hString == NULL || fp == NULL){
		return NULL;
	}
	
	// //create array of vectors of My_strings
	// MY_VECTOR array[30];
	// for(i = 1; i < 30; i++){
		// array[i] = vector_init_default();
		// if(array[i] == NULL){
			// exit(1);
		// }
	// }

	MY_VECTOR hVector = vector_init_default();
	//push string to vector if string from dictionary has correct word length
	while(my_string_extraction(hString, fp)){
		if(my_string_get_size(hString) == length){
			vector_push_back(hVector, hString);
		}
		if(fgetc(fp) == ' '){
			continue;
		}
	}

	// for(i = 1; i < 30; i++){
		// //print the size of each of the vectors 
		// // (providing a count of how many words of each length)
		// printf("Vectors containing strings of length %2d: %d\n", i, vector_get_size(array[i]));
		// //destroy array of vectors
		// vector_destroy(&array[i]);
	// }

	my_string_destroy(&hString);
	fclose(fp);
	return hVector;
 }  */
 
 /*
 MY_VECTOR generate_vector_words(MY_STRING key)
 {
	int i;
	FILE* fp;
	fp = fopen("dictionary.txt", "r");
	MY_STRING hString = my_string_init_default();
	
	if(hString == NULL || fp == NULL){
		return NULL;
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
 }
 */
 
 
 //generate tree node with key
 NODE* node_key_init(MY_STRING key)
 {
	//MY_STRING* temp_key = NULL;
	Node* new_node = NULL;
	new_node = (Node*)malloc(sizeof(Node));
	//check
	if(new_node == NULL){
		free(new_node);
		return NULL;
	}
	else{
		new_node->key = NULL;
		my_string_assignment(new_node->key, key);
		new_node->words = vector_init_default();
		//check
		if(new_node->words == NULL){
			my_string_destroy(&(new_node->key));
			free(new_node);
			return NULL;
		}
		new_node->left = NULL;
		new_node->right = NULL;
		return (NODE*)new_node;
	}
 }
  

 //insert node into tree
 TREE* insert_node(TREE* hTree, MY_STRING key, MY_STRING word)
 {
	Node* current = NULL;
	Node* parent = NULL;
	Node* temp_node = (Node*)node_key_init(key);
	Tree* pTree = (Tree*)hTree;
	//checks
	if(temp_node == NULL || key == NULL || word == NULL){
		return NULL;
	}
	//if tree is empty
	if(pTree == NULL){
		//create vector adding all the words from the dictionary
		vector_push_back(temp_node->words, word);
		pTree->root = temp_node;
	}
	//if tree is not empty (hTree != NULL)
	else{
		current = pTree->root;
		if(current == NULL){
			return NULL;
		}
		while(1) {                
			parent = current;
			
			//use my_string_compare(current_key (=left), new_key (=right))
			// to determine which child it should be
			if(my_string_compare(key, current->key) <= 0){
				//go to left of the tree
				current = current->left;                
				//insert to the left
				if(current == NULL) {
					parent->left = temp_node;
					break;
				}
			}
			else {
				//go to right of the tree
				current = current->right;
				//insert to the right
				if(current == NULL) {
					parent->right = temp_node;
					break;
				}
			}
		}            
	}
	return (TREE*)pTree;
 }
 
 //search tree with key
 NODE* search_tree(TREE* hTree, MY_STRING key)
 {
	Tree* pTree = (Tree*)hTree;
	//checks
	if(pTree == NULL || key == NULL){
		return NULL;
	}
	Node* current = pTree->root;
	if(current == NULL){
		return NULL;
	}
	
	//My_string* pKey = (My_string*)key;
	//printf("Visiting elements: ");
	
	while(current != NULL){
		//when find the key
		if(my_string_compare(key, current->key) == 0){
			break;
		}
		else{
			if(my_string_compare(key, current->key) < 0){
				//go to left of the tree
				current = current->left; 
			}				
			else{
				//go to right of the tree
				current = current->right;
			}
		}
	}
	return (NODE*)current;
 }
 
 //Precondition: length is possible word length, guess is alphabetical character,
 // and root (hTree) is either NULL or the root of a pre-existing key tree (AVL/BST).
 //Postcondition: If the given root (hTree) is NULL, this function generates
 // a tree given the arguments in #4 above and the words in the dictionary.
 // If the root (hTree) is not NULL, it should traverse the tree, find the
 // largest word group and use that as the dictionary.
 //BST: left_subtree (keys)  ≤  node (key)  ≤  right_subtree (keys)
 TREE* generate_key_tree(){
	 return NULL;
 }
 
 
 /************************EXTRA CREDIT**********************************/
 /*
 Your Hangman program, then, should do the following: 
 
1. Prompt the user for a word length, re-prompting as necessary until she
 enters a number such that there's at least one word that's exactly that long.
 That is, if the user wants to play with words of length -42 or 137, since no
 English words are that long, you should reprompt her. 
 
2. Prompt the user for a number of guesses, which must be an integer
 greater than zero. Don't worry about unusually large numbers of guesses –
 after all, having more than 26 guesses is clearly not going to help
 your opponent! 
 
3. Prompt the user for whether she wants to have a running total of the
 number of words remaining in the word list. This completely ruins the illusion
 of a fair game that you'll be cultivating, but it's quite useful for testing
 (and grading!) 
 
4. Play a game of Hangman using the Evil Hangman algorithm, as described below: 
 a. Select the ​Vector of all words in the English language whose length
 matches the input length. 
 
 b. Print out how many guesses the user has remaining, along with any letters
 the player has guessed and the current blanked-out version of the word. If
 the user chose earlier to see the number of words remaining, print that out too. 
 
 c. Prompt the user for a single letter guess, re-prompting until the user
 enters a letter that she hasn't guessed yet. Make sure that the input is exactly
 one character long and that it's a letter of the alphabet. 
 
 d. Partition the words in the dictionary into groups by word family.
 The word family is the “key” in the ​AssociativeArray, and the words
 (already contained in ​MyStrings from having been read into the ​Vector of Vectors
 of MyStrings initially), are added to the ​Vector in the AssociativeArray
​ which is associated with the given “key” word family. 

 e. Find the most common “word family” in the remaining words,
 remove all words from the word list that aren't in that family,
 and report the position of the letters (if any) to the user.
 If the word family doesn't contain any copies of the letter,
 subtract a remaining guess from the user. 
 
 f. If the player has run out of guesses, pick a word from the word list
 and display it as the word that the computer initially “chose.” 
 
 g. If the player correctly guesses the word, congratulate her. 
 
5. Ask if the user wants to play again and loop accordingly. 
 
It's up to you to think about how you want to partition words into word families.
 Think about what data structures would be best for tracking word families and
 the master word list. Would an associative array work? How about a stack or queue?
 Thinking through the design before you start coding will save you a lot of time
 and headache.  
*/