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
 * This structure defines a hash table which is an array of linked lists
 */
    // A linked list
typedef struct node{
    char word[LENGTH + 1];
    struct node *next;
} node;
    // Array of linked lists --> A hash table
node *hashtable[26];
// for (int i = 0; i<=26; i++){
//     hashtable[i] = NULL;
// }

// Variables
char word_a[LENGTH + 1];
int count=0;

// Prototypes
int hash(const char *word);



/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // declare the head node
    node *cursor = hashtable[hash(word)];
    
    // a loop that traverses a linked list starting from the head pointer
    //node *cursor = head;
    
    char *dict_word;
    while (cursor != NULL){
        dict_word = cursor -> word;
        // strcasecmp on cursor -> word and word
        if(strcasecmp(word, dict_word)==0){
            return true;
        }
        else{
            cursor = cursor->next;
        }
        // if(strcasecmp(word, dict_word) != 0){
        //     cursor = cursor->next;
        // }
        // else if(strcasecmp(word,dict_word) ==0){
        //     return true;
        // }

    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 * 
 */
bool load(const char *dictionary)
{
    for (int i = 0; i<26; i++){
        hashtable[i] = NULL;
    }
    
    // open file as a FILE file type and error check
    FILE *dict = fopen(dictionary, "r");
    
    if (dict == NULL){
        fprintf(stderr, "Could not open file");
        return 2;
    }
     
    // while not at end of file, store each dictionary word in word
    while (fscanf(dict, "%s", word_a) !=EOF){
        // (1) HASH FUNCTION
        // printf('%s', word);
        printf("%s", word_a);
        int int_letter = hash(word_a);
        
        
        // (2) HASH TABLE
        // store word in linked list
            // malloc a new node pointer for each new word and error check 
        node *new_node = malloc(sizeof(node));
        //node *head = malloc(sizeof(node));
        if(new_node == NULL){
            unload();
            return false;
        }
            // if the word is the first in the list, store as "head" pointer
            
            // copy word into the word property of the node
        strcpy(new_node -> word, word_a);
        
            // if the linked list is empty
        if(hashtable[int_letter] == 0){
            new_node->next = NULL;
            hashtable[int_letter] = new_node;
            count++;
        }
            // if the word is not first in list, store to new_node->word and connect to head
        else{
                // the "next" value of node points to the previous head
            new_node->next = hashtable[int_letter];
                // the head now points to new_node
            hashtable[int_letter] = new_node;
            count++;
        }
        
            // insert head pointer into array of pointers(hash table)
        //hashtable[int_leter] = head;
        
            //TODO: NEED TO FREE MEMORY AT SOME POINT AFTER 
    }
    return true;
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
    


/**
 * Hash function which returns the bin number according to the first letter of the word
 */

int hash(const char *word){
    // (1) HASH FUNCTION
            // convert the first letter of the word to an int
        char letter = word[0];
        int int_letter = (int)letter;
            // if the letter is upper case
        if(int_letter<=90 && int_letter >=65 ){
                // convert to lower case
            int_letter+= 32;
                // convert to hash# where a = 0
            int_letter-=97;
        }
            // if the letter is lower case 
        else if(int_letter<=122 & int_letter>=97){
                // convert to hash#
            int_letter-=97;
        }
            // error check, if input is not a letter
        else{
            return false;
        }
    
    return int_letter;
}
