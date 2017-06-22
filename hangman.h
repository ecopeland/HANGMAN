#ifndef HANGMAN_H
#define HANGMAN_H

typedef struct treeNode Node;
 struct treeNode{
	MY_STRING key;
	MY_VECTOR words;
	Node* left;
	Node* right;
 };
 
 typedef struct tree Tree;
 struct tree{
	Node* root;
};
 
 MY_STRING key_init_default(int length);
 
 //Generate word key value with My_string->data. Key is index of Vector array
 // where vector contains only one My_string with that specific word.
 // There will be no duplicate keys.
 Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess);
 
 //generate vector with strings of word length from dictionary
 MY_VECTOR generate_vector_length(int length);

 //MY_VECTOR generate_vector_words(char guess);

 //Precondition: length is possible word length, guess is alphabetical character,
 // and root is either NULL or the root of a pre-existing key tree (AVL/BST).
 //Postcondition: If the given root (hTree) is NULL, this function generates
 // a tree given the arguments in #4 above and the words in the dictionary.
 // If the root (hTree) is not NULL, it should traverse the tree, find the
 // largest word group and use that as the dictionary.
 //BST: left_subtree (keys)  ≤  node (key)  ≤  right_subtree (keys)
 //Tree* generate_key_tree(int length, char guess, Tree* hTree);
 
 //Generate tree node with key
 Node* node_key_init(MY_STRING key);
 
 //insert node into tree
 //Status insert_node(Tree* hTree, Node* new_node);
 
 //search tree for key
 //Node* search_tree(Tree* hTree, MY_STRING key);
 
 //Look-up by “key” yields a Vector of all of the ​My_strings
 // that have been added to the ​Vector associated with that key. 
 //Status look_up_key(Tree* hTree, MY_STRING key);
 
 #endif