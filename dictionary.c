/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"



// root of node where words from dictionaries are loaded
INIT_STRUC(ex_root);

// number of words in tries

int ex_wnum;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    //temp pointer for struct
    node *temp_pstc = &ex_root;

    // temp value for number of letter in alphabet
    int num;

    // temp char


    // go through the word that has been loaded
    for( int i = 0; word[i] != '\0'; i++)
    {

        num = (int) tolower(word[i]) - ASCII_START;

        // if it is a letter
        if( isalpha(word[i]) != 0)
           {

                //check for node on the current pointer
            if (temp_pstc->children[num] == NULL)
                {
                    return false;
                }

            temp_pstc = temp_pstc -> children[num];

            }

        // if it is a apostrophe
        else if ( word[i] == '\'' )
            {
                //check for node on the current pointer
                if (temp_pstc->children[APOSTR_NUM] == NULL)
                {

                        return false;

                }

                temp_pstc = temp_pstc -> children[APOSTR_NUM];
            }
    }

    if ( temp_pstc -> in_word != true )
        {
            return false;
        }

    return true;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open the file for reading
    FILE* inpf = fopen( dictionary, "r");

    if ( inpf == NULL)
    {
        printf("Can not open the dictionary!");
        return false;
    }

    // variable for word from dictionary
    char word[LENGTH + 1];

    //root struct for tries

    //temp pointer for struct
    node *temp_pstc = &ex_root;


    // temp value for number of letter in alphabet
    int num;

    // downloading word from dictionary is included in while loop;
    while( fscanf( inpf, "%s", word) != EOF )
    {

        // go through the word that has been loaded
        for( char *c = &word[0]; *c != '\0'; c++)
        {
            // if it is a letter
            if( isalpha(*c) != 0)
            {

                num = *c - ASCII_START;

                //check for node on the current pointer
                if (temp_pstc->children[num] == NULL)
                {

                    // create for a new node
                    temp_pstc->children[num] = ( node * ) malloc( sizeof( node ) );

                    //INIT_STRUC( &(temp_pstc->children[num]) );

                    memset( temp_pstc->children[num], 0, sizeof(node) );


                }

                //
                temp_pstc = temp_pstc -> children[num];
            }

            // if it is a apostrophe
            else if ( *c == '\'' )
            {
                //check for node on the current pointer
                if (temp_pstc->children[APOSTR_NUM] == NULL)
                {

                    // create for a new node
                    temp_pstc->children[APOSTR_NUM] = ( node * ) malloc( sizeof( node ) );

                    //INIT_STRUC( &(temp_pstc->children[APOSTR_NUM]) );

                    //( node * ) malloc( sizeof( node ) );

                    memset( temp_pstc->children[APOSTR_NUM], 0, sizeof(node) );

                }

                temp_pstc = temp_pstc -> children[APOSTR_NUM];
            }
        }

        // finish current word with boolen mark in in_word var
        temp_pstc -> in_word = true;

        // add to number of words
        ex_wnum++;

        // return to root structure
        temp_pstc = &ex_root;

    }


    fclose(inpf);



    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{

    return ex_wnum;
}

/**
 * Recursion function realization
 */

void free_help(node *n)
{

    for( int i = 0; i < (APOSTR_NUM + 1) ; i++)
    {
        if ( n -> children[i] != NULL)
        {
            free_help(n -> children[i]);
        }

    }

    if(n == &ex_root)
    {
        return;
    }

    free(n);
}


/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    free_help(&ex_root);
    //free(ex_root);
    return true;

}
