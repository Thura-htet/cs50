// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 11007;

//the number of words in the dictionary for size function
int num_words = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int n = strlen(word);
    char loaded_word[n + 1];
    for (int i = 0; i < n; i++)
    {
        loaded_word[i] = tolower(word[i]);
    }
    loaded_word[n] = '\0';

    // hash the word to obtain a hash value
    int index = hash(loaded_word);

    // traverse the linked list and look for the word
    for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(cursor->word, loaded_word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
//djb2 function taken from http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N; /* N is the size fo the hash table */
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // local variables
    char loaded_word[LENGTH + 1];

    // open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // read strings from the file
    while (fscanf(file, "%s", loaded_word) != EOF)
    {
        // create a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, loaded_word);

        // hash the loaded word
        int index = hash(loaded_word);

        //insert the word(node) into the hash table
        if (table[index] == NULL)
        {
            table[index] = n;
            n->next = NULL;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
        num_words++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return num_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // alternate method is to use recursion
    // iterate over all the arrays in the hash table
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
