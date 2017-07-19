/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

typedef struct node
{
    char value[LENGTH + 1];
    struct node *next;
}
node;

//creates hashtable, or array of type node* or array containg pointers to node
node *hashtable[HASHTABLE_SIZE];

bool isLoaded = false;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    
    char * copiedWord = malloc(LENGTH * 1 + 1);
    strcpy(copiedWord, word);
    
    //converts word to lowercase
    for(int i = 0; copiedWord[i]; i++)
    {
        copiedWord[i] = tolower(copiedWord[i]);
    }
    
    //stores pointer to a node into array with appropriate index/hash
    node *pointer = hashtable[hashFunction(copiedWord)];
    
    while(pointer != NULL)
    {
        if(strcmp(copiedWord, pointer->value) == 0)
        {
            free(copiedWord);
            return true;
        }
        else
        {
            pointer = pointer->next;
        }
    }
    
    free(copiedWord);
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    
    //opens dictionary file and checks for any errors
    FILE *dictionaryFile = fopen(dictionary, "r");
    if(dictionaryFile == NULL)
    {
        printf("Can't open dictionary file %s\n", dictionary);
        unload();
        return false;
    }
    
    //creates buffer variable with enough capacity to store longest word and ending marker
    char word[LENGTH + 1];
    
    //scans dictionary file line by line and stores every line in buffer variable called word
    while(fscanf(dictionaryFile, "%s", word) != EOF)
    {
        //hashes word from dictionary
        int hash = hashFunction(word);
        //creates new node and stores it address into pointer
        node *newNodePointer = malloc(sizeof(node));
        //checks for errors with memory
        if(newNodePointer == NULL)
        {
            printf("Pointer to new node is null\n");
            return false;
        }
        //if there are no errors, copies word from dictionary into newly created node
        strcpy(newNodePointer->value, word);
        
        //sets pointer to next node to be same as what head of linked list pointed at
        newNodePointer->next = hashtable[hash];
        //finally changes head of linked list to point to newly created node
        hashtable[hash] = newNodePointer;
    }
    
    isLoaded = true;
    
    fclose(dictionaryFile);
    
    //if everything before completed succesfully returns true
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    //declare empty pointer
    node *pointer = NULL;
    int size = 0;
    
    //if dictionary is loaded, calculate size
    if(isLoaded)
    {
        for(int counter = 0; counter<HASHTABLE_SIZE; counter++)
        {
            pointer = hashtable[counter];
            while(pointer != NULL)
            {
                pointer = pointer->next;
                size++;
            }
        }
        return size;
    }
    
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    node *cursor = NULL;
    for(int i= 0; i<HASHTABLE_SIZE; i++)
    {
        cursor = hashtable[i];
        while(cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    
    return true;
}


int hashFunction(char *input)
{
    unsigned int hash = 0;
    for(int i = 0, n = strlen(input); i<n; i++)
    {
        hash = (hash << 2) ^ input[i];
    }
    return hash % HASHTABLE_SIZE;
}
