#ifndef HANGMAN_H
#define HANGMAN_H

typedef struct treeNode Node;
 struct treeNode{
	MY_STRING key;
	MY_VECTOR words;
	Node* left;
	Node* right;
 };
 
 typedef void* NODE;
 
 typedef struct tree Tree;
 struct tree{
	Node* root;
};

 typedef void* TREE;
 
 MY_STRING key_init_default(int length);
 
 //Generate word key value with My_string->data. Key is index of Vector array
 // where vector contains only one My_string with that specific word.
 // There will be no duplicate keys.
 Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess);
 
 //generate array of vectors with strings of word length from dictionary
 MY_VECTOR generate_vector_length(int length);
 
 //generate new vector (copy of largest node vector)
 MY_VECTOR generate_vector_words(TREE hTree, MY_STRING key);
 

 //Precondition: length is possible word length, guess is alphabetical character,
 // and root (hTree) is either NULL or the root of a pre-existing key tree (AVL/BST).
 //Postcondition: If the given root (hTree) is NULL, this function generates
 // a tree given the arguments in #4 above and the words in the dictionary.
 // If the root (hTree) is not NULL, it should traverse the tree, find the
 // largest word group and use that as the dictionary.
 //BST: left_subtree (keys)  ≤  node (key)  ≤  right_subtree (keys)
 TREE generate_key_tree(TREE hTree, MY_STRING key, int length, char guess);
 
 //generate tree node with key
 NODE node_key_init(MY_STRING key);
 
 Status assign_root(TREE hTree, NODE hNode);
 
 //print tree nodes
 void print_tree(TREE hTree);
 
 //insert node into tree
 Status insert_node(TREE hTree, MY_STRING key);
 
 //search tree with key
 NODE search_tree(TREE hTree, MY_STRING key);
 
 //find largest node in tree
 NODE largest_node(TREE hTree);
 
 //destroy tree
 void tree_destroy(TREE hTree);
 
 #endif