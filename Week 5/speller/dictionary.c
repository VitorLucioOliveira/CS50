// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Maximum number of a word * the highest value of a letter
const unsigned int N = LENGTH * 'Z';

// Hash table
node *table[N];

// Word count

int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);

    for (node *i = table[index]; i != NULL; i = i->next)
    {
        if (strcasecmp(word, i->word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    unsigned int sum = 0;

    // Sum the values of the letters od the word
    for (int i = 0; word[i] != '\0'; i++)
    {
        sum += toupper(word[i]);
    }

    // ensures that it returns a value between 0 and N-1
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dicionario = fopen(dictionary, "r");

    // CHECK
    if (dicionario == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    while (fscanf(dicionario, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));

        // CHECK
        if (new_node == NULL)
        {
            return false;
        }

        // Copy the word into the node
        strcpy(new_node->word, word);
        new_node->next = NULL;

        // Hash the Node
        int index = hash(new_node->word);

        // Add to Linked list
        new_node->next = table[index];
        table[index] = new_node;
        word_count++;
    }

    fclose(dicionario);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *j = table[i];

        while (j != NULL)
        {
            node *tmp = j;
            j = j->next;
            free(tmp);
        }
        // Garante que só retorna true se deu certo
        if (i == N - 1 )
        {
            return true;
        }
    }
    return false;
}
