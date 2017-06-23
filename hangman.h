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
 
 //generate vector with strings of word length from dictionary
 //MY_VECTOR generate_vector_length(int length);

 //MY_VECTOR generate_vector_words(char guess);

 //Precondition: length is possible word length, guess is alphabetical character,
 // and root (hTree) is either NULL or the root of a pre-existing key tree (AVL/BST).
 //Postcondition: If the given root (hTree) is NULL, this function generates
 // a tree given the arguments in #4 above and the words in the dictionary.
 // If the root (hTree) is not NULL, it should traverse the tree, find the
 // largest word group and use that as the dictionary.
 //BST: left_subtree (keys)  ≤  node (key)  ≤  right_subtree (keys)
 //TREE* generate_key_tree();
 
 //generate tree node with key
 NODE node_key_init(MY_STRING key);
 
 //insert node into tree
 TREE insert_node(TREE hTree, MY_STRING key, MY_STRING word);
 
 //search tree with key
 NODE search_tree(TREE hTree, MY_STRING key);
 
 //destroy tree
 void tree_destroy(TREE* phTree);
 
 #endif