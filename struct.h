/**
 * struct.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a structures and constants that will be need in the code.
 */

 /**
 * Tries structures
 * */


#include <stdio.h>

typedef struct node
{
    bool in_word;

    // there are 26 letter plus '/''
    struct node *children[27];
}
node;

#define ASCII_START 97

#define INIT_STRUC(X) node X = { .in_word = false, .children = { NULL } }

#define APOSTR_NUM 26

//root struct for tries
INIT_STRUC(groot);
