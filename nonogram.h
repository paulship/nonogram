#include <stdint.h>

#ifndef NONOGRAM_H
#define NONOGRAM_H

/*
    Enum represents the states that a cell can be. 
*/
typedef enum
{
    UNKNOWN,        /* Initial state for a cell. */
    DEFF_FILL,      /* Definitely filled */
    DEFF_BLANK,     /* Definitely blank */
    POSS_FILL,      /* All the possibilities we have tested so far are filled - only used during a scan */
    POSS_BLANK,     /* All the possibilities we have tested so far are blank - only used during a scan */
    INDETERMINATE   /* Various possibilties have been tested so far - unable to draw a conclusion - only used during a scan */
} CELLSTATE_T;

/*
    Represents a possibly solution for a cellstrip. Is intended to form a linked list of possible solutions, containing
    a pointer to an array of cellstates, whose length is equal to the length of the CELLSTRIP_T structure that refers
    to it.
*/
struct POSSIBLE_T
{
    CELLSTATE_T* candidate;
    struct POSSIBLE_T* next;
};

/*
    Refers to a strip of cells. Contains information about its length and state of the cells, information about the
    filled in regions, and pointer to a linked list of potential solutions.
*/
typedef struct 
{
    uint16_t length;
    uint16_t n_regions;
    uint16_t* region_size;
    struct POSSIBLE_T* possible_list;
    CELLSTATE_T** cells;
} CELLSTRIP_T;

/*
    Represents the game state. Contains an array of cellstates, and a pointer to a number of strips.
*/
typedef struct
{
    uint16_t rows;
    uint16_t columns;
    CELLSTATE_T* cells;
    CELLSTRIP_T* strips;
} GAME_T;

#endif /* defined NONOGRAM_H */
