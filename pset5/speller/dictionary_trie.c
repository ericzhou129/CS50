/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

/**
 * This structure defines a Trie.
 */
//Questions:
//(1) how is each subsequent array connected to one another
//(2) does the recursion lead from one node to another?
//(3) how do you crawl through this tree?
typedef struct node
{
    bool is_word;
    struct node *children[27]; // this creates an array of 27 node pointers
}
node;

node *root;

// declare variables
char word[LENGTH + 1];


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 * 
 */
bool load(const char *dictionary)
{
   /**
    * Trie
    *   A trie is made up of nodes containing arrays of node points. These pointers
    *   point to each letter in the alphabet with '\' at the end.
    *   When a node is NULL, then that is the end of the word sequence 
    *   Thus, each node must also indicate if it is the last letter within a valid word
    * 
    * PSEUDOCODE:
    *   For every dictionary word, iterate through the trie
    *   Each element in children corresponds to a different letter
    *   Check the value at children[i] --> 
    *       if NULL, malloc a new node, have children [i] point to it
    *       if not NULL, move to new node and continue
    *   if at end of word, set is_word to true. 
    * 
    * Note:
    * The point here is not to store the letter of each word within the node. Rather, the location where the pointer to the next
    * array lives, is representative of the letter. 
    */
    
    // open dictionary file and error check
    FILE *dict = fopen(dictionary,"r");
    if (dict == NULL)
    {
        fprintf(stderr, "Could not open file");
        return 2;
    }
    
    // while not at end of file, loop through each word in the dictionary
    while (fscanf(dict, "%s\n", word) !=EOF) // scan string ending with \n
    {
        int i=0; // set counter to 0
        node *current_node = &root; // initialize the current_node to root to start
        current_node -> is_word = FALSE; // is this initizlization necessary?
        
        while(word[i] != '\n') // iterate through each letter of word
        {
            int letter_num = word[i] - 97; // turn the letter into a number 
            
            // search through all children of root node, if NULL then add new node for the next character
            if(curent_node -> children[letter_num] == NULL) 
            {
                node *new_node = malloc(sizeof(node)); // malloc a new node
                
                if(new_node == NULL) // error check
                {
                    unload();
                    return false;
                }
        
                current_node -> children[letter_num] = &new_node // pointer within array is set to address of the new node
                
                current_node = &new_node // point the current node to the address of the new node (correct syntax?)
            }
            
            // else set current node pointer to address stored within array
            else 
            {
                current_node = current_node ->children[letter_num]; // (correct syntax?)
            }
            
            i++;
        }
        
        // if we've reached the end of the word, then set the last node to is_word = true
        if(word[i] == '\n')
        {
            current_node -> is_word = TRUE;
        }
    }
    
    return TRUE;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return count;
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    
    int i;
    
    // iterate through each linked list in the hashtable
    for(i=0; i<26; i++){
        // set first node of the linked list as head
        node *head = hashtable[i];
        // set a cursor that iterates through the linked list
        node *cursor = head;
        // unload each node in a linked list
        while(cursor != NULL){
            node *temp = cursor;
            cursor = cursor -> next;
            free(temp);
        }
    }
    
        // if we get to the last letter of the dictionary, return true
    if(i==26){
        return true;
    }
    else{
        return false;
  }

}
    

