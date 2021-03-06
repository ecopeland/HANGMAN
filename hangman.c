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


 //generate vector with strings of word length from dictionary
 MY_VECTOR generate_vector_length(int length)
 {
	//int count = 0;
	FILE* fp;
	fp = fopen("dictionary.txt", "r");
	MY_STRING hString = my_string_init_default();
	MY_VECTOR hDictionary = vector_init_default();

	//checks
	if(hDictionary == NULL || hString == NULL || fp == NULL){
		//printf("test");
		return NULL;
	}

	/* //create array of vectors of My_strings
	MY_VECTOR array[30];
	for(i = 1; i < 30; i++){
		array[i] = vector_init_default();
		if(array[i] == NULL){
			return NULL;
		}
	} */

	//push string to vector at array position of string size (word length)
	while(my_string_extraction(hString, fp)){
		//printf("test");
		if(my_string_get_size(hString) == length){
            //count++;
			//printf("%d\n", count);
            MY_STRING match_string = NULL;
            my_string_assignment(&match_string, hString);
			vector_push_back(hDictionary, match_string);
		}
		//printf("test");
		if(fgetc(fp) == ' '){
			//printf("test");
			continue;
		}
	}

	/* for(i = 1; i < 30; i++){
		//print the size of each of the vectors
		// (providing a count of how many words of each length)
		printf("Vectors containing strings of length %2d: %d\n", i, vector_get_size(array[i]));
		//destroy array of vectors
		vector_destroy(&array[i]);
	} */

	my_string_destroy(&hString);
	fclose(fp);
	return (MY_VECTOR)hDictionary;
 }

 //generate new vector (copy of largest node vector)
 MY_VECTOR generate_vector_words(TREE hTree, MY_STRING key)
 {
	int i;
	Node* temp_node = NULL;
	MY_VECTOR temp_vector = vector_init_default();

	//checks
	if(hTree == NULL || key == NULL || temp_vector == NULL){
		return NULL;
	}

	//find node with largest vector and assign temp_node to that node
	temp_node = largest_node(hTree);

	//assign key of largest node to key
	my_string_assignment(&key, temp_node->key);

	//copy the vector of the largest node to temp_vector
	for(i = 0; i < vector_get_size(temp_node->words); i++){
		if(!vector_push_back(temp_vector, vector_at(temp_node->words, i))){
			return NULL;
		}
	}
	return temp_vector;
 }


 //generate tree node with key
 NODE node_key_init(MY_STRING key)
 {
	//MY_STRING* temp_key = NULL;
	Node* new_node = NULL;
	new_node = (Node*)malloc(sizeof(Node));
	//check
	if(new_node == NULL){
		return NULL;
	}
	else{
		new_node->key = NULL;		
		my_string_assignment(&(new_node->key), key);
#if 0
		new_node->words = vector_init_default();
		//check
		if(new_node->words == NULL){
			my_string_destroy(&(new_node->key));
			free(new_node);
                        new_node = NULL;
			return NULL;
		}
#else
                new_node->words = NULL;
#endif
		new_node->left = NULL;
		new_node->right = NULL;
		return (NODE)new_node;
	}
 }

 void assign_node_words(NODE hNode, MY_VECTOR hDictionary){
     Node* pNode = (Node*)hNode;
     if(pNode == NULL || hDictionary == NULL){
         return;
     }
     pNode->words = hDictionary;
     return;
 }

 void assign_tree_root(TREE hTree, NODE hNode){
	Tree* pTree = (Tree*)hTree;
	Node* pNode = (Node*)hNode;
	if(pTree == NULL || pNode == NULL){
		return;
	}
	pTree->root = pNode;
	return;
 }

 //print tree nodes
 void print_node(NODE hNode){
	Node* root = (Node*)hNode;
	if(root == NULL){
		return;
	}
	if(root->left != NULL){
		print_node(root->left);
	}
        printf("%s: %d\n", my_string_c_str(root->key), vector_get_size(root->words));
	if(root->right != NULL){
		print_node(root->right);
	}
	return;
 }

 //insert node into tree
 Status insert_node(TREE hTree, MY_STRING key)
 {
	Node* current = NULL;
	Node* parent = NULL;
	Node* temp_node = (Node*)node_key_init(key);
	Tree* pTree = (Tree*)hTree;
	//checks
	if(temp_node == NULL || key == NULL){
		return FAILURE;
	}
	//if tree is empty
	if(pTree == NULL){
		pTree->root = temp_node;
	}
	//if tree is not empty (hTree != NULL)
	else{
		current = pTree->root;
		if(current == NULL){
			return FAILURE;
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
	return SUCCESS;
 }

 //search tree with key
 NODE search_tree(TREE hTree, MY_STRING key)
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
	return (NODE)current;
 }

 //find largest node in tree
 NODE largest_node(TREE hTree)
 {
	int largest_size = 0;
	Node* largest = NULL;
	Node* root = NULL;
	Tree* pTree = (Tree*)hTree;
	//checks
	if(pTree == NULL || (root = pTree->root) == NULL){
		return NULL;
	}
	while(root){
		if(root->right == NULL){
			if(root->left == NULL){
				if(largest_size < vector_get_size(root->words)){
					largest = root;
					largest_size = vector_get_size(largest);
				}
				break;
			}
			else{
				root = root->left;
				if(largest_size < vector_get_size(root->words)){
					largest = root;
					largest_size = vector_get_size(largest);
				}
			}
		}
		else{
			if(root->left == NULL){
				root = root->right;
				if(largest_size < vector_get_size(root->words)){
					largest = root;
					largest_size = vector_get_size(largest->words);
				}
			}
		}
	}
	return largest;
 }

 //destroy node
 void node_destroy(NODE* phNode){
     Node* pNode = (Node*) *phNode;
     if(pNode == NULL){
         return;
     }
     node_destroy((NODE*)&(pNode->left));
     node_destroy((NODE*)&(pNode->right));
     my_string_destroy(&(pNode->key));
     vector_destroy(&(pNode->words));
     free(pNode);
     pNode = NULL;
 }

 //Precondition: length is possible word length, guess is alphabetical character,
 // and root (hTree) is either NULL or the root of a pre-existing key tree (AVL/BST).
 //Postcondition: If the given root (hTree) is NULL, this function generates
 // a tree given the arguments in #4 above and the words in the dictionary.
 // If the root (hTree) is not NULL, it should traverse the tree, find the
 // largest word group and use that as the dictionary.
 //BST: left_subtree (keys)  ≤  node (key)  ≤  right_subtree (keys)
 TREE generate_key_tree(TREE hTree, MY_STRING key, int length, char guess)
 {
	//build tree with all keys from dictionary
	MY_STRING word = NULL;
	MY_STRING temp_key = NULL;
	MY_VECTOR dictionary = NULL;
	Tree* pTree = (Tree*)hTree;

	//checks
	if(key == NULL || length <= 0 || !isalpha(guess)){
		return NULL;
	}
	if(!my_string_assignment(&temp_key, key)){
		return NULL;
	}
	//if root is NULL
	if(pTree == NULL || pTree->root == NULL){
		Node* temp_node = (Node*)node_key_init(key);
		dictionary = generate_vector_length(length);
		//valgrind has major issue with line below/above? (technically it says issue with this exact comment line?!)
		temp_node->words = dictionary;
		pTree->root = temp_node;
	}
	//if root is not null
	else{
		//generate new dictionary with largest word group
		dictionary = generate_vector_words((TREE)pTree, key);
	}
	//create tree with dictionary
	while(vector_get_size(dictionary)){
		int index = vector_get_size(dictionary) - 1;
		word = vector_at(dictionary, index);

		//get_word_key_value
		get_word_key_value(key, temp_key, word, guess);

		//add node to tree
		if(!insert_node((TREE)pTree, key)){
			node_destroy((TREE)pTree);
			return NULL;
		}
		//delete words from dictionary (as add new nodes)
		vector_pop_back(dictionary);
	}
	vector_destroy(&dictionary);
	return (TREE)pTree;
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
