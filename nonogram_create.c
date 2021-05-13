#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "nonogram.h"
#include "nonogram_strip.h"

static void setup_strip( CELLSTRIP_T* my_strip, CELLSTATE_T* cell_ptr, uint16_t length, uint16_t stepsize );
static void set_strip_regions( CELLSTRIP_T* my_strip, uint16_t n_regions, uint16_t* regions_ptr );

GAME_T* nonogram_create( void )
{
    GAME_T* my_game = malloc( sizeof(GAME_T) );
    if( my_game == NULL )
    {
        return NULL;
    }

    const uint16_t rows = 25;
    const uint16_t columns = 25;

    my_game->rows = rows;
    my_game->columns = columns;

    printf("Allocating memory for cells.\n");
    my_game->cells = malloc( sizeof(CELLSTATE_T) * ( my_game->rows * my_game->columns ) );
    if( my_game->cells == NULL )
    {
        free( my_game );
        return NULL;
    }

    printf("Allocating memory for strips.\n");
    my_game->strips = malloc( sizeof(CELLSTRIP_T) * ( my_game->rows + my_game->columns ) );
    if( my_game->strips == NULL )
    {
        free( my_game->cells );
        free( my_game );
        return NULL;
    }

    printf("Initialising all cell states.\n");
    for( uint16_t n=0; n<(rows*columns); n++ )
    {
        my_game->cells[n] = UNKNOWN;
    }

    printf("Initialising rows.\n");
    for( uint16_t n=0; n<rows; n++ )
    {
        CELLSTATE_T* start_cell = my_game->cells + (n*columns);
        setup_strip( &my_game->strips[n], start_cell, columns, 1 );
    }
    printf("Initialising columns.\n");
    for( uint16_t n=0; n<columns; n++ )
    {
        CELLSTATE_T* start_cell = my_game->cells + (n);
        setup_strip( &my_game->strips[rows+n], start_cell, rows, columns );
    }

    set_strip_regions( &my_game->strips[0], 1, (uint16_t[]){ 11 } );
    set_strip_regions( &my_game->strips[1], 2, (uint16_t[]){ 3, 3 } );
    set_strip_regions( &my_game->strips[2], 3, (uint16_t[]){ 3, 1, 3 } );
    set_strip_regions( &my_game->strips[3], 3, (uint16_t[]){ 2, 2, 2 } );
    set_strip_regions( &my_game->strips[4], 3, (uint16_t[]){ 2, 1, 2 } );
    set_strip_regions( &my_game->strips[5], 3, (uint16_t[]){ 3, 2, 1 } );
    set_strip_regions( &my_game->strips[6], 4, (uint16_t[]){ 2, 1, 2, 2 } );
    set_strip_regions( &my_game->strips[7], 4, (uint16_t[]){ 2, 1, 2, 2 } );
    set_strip_regions( &my_game->strips[8], 4, (uint16_t[]){ 6, 2, 4, 5 } );
    set_strip_regions( &my_game->strips[9], 7, (uint16_t[]){ 2, 3, 1, 2, 2, 1, 3 } );
    set_strip_regions( &my_game->strips[10], 6, (uint16_t[]){ 3, 2, 2, 4, 3, 3 } );
    set_strip_regions( &my_game->strips[11], 10, (uint16_t[]){ 2, 2, 1, 1, 1, 1, 1, 1, 1, 1 } );
    set_strip_regions( &my_game->strips[12], 6, (uint16_t[]){ 2, 1, 3, 2, 1, 2 } );
    set_strip_regions( &my_game->strips[13], 5, (uint16_t[]){ 4, 5, 1, 1, 4 } );
    set_strip_regions( &my_game->strips[14], 4, (uint16_t[]){ 10, 2, 1, 3 } );
    set_strip_regions( &my_game->strips[15], 5, (uint16_t[]){ 2, 4, 2, 5, 2 } );
    set_strip_regions( &my_game->strips[16], 3, (uint16_t[]){ 9, 1, 2 } );
    set_strip_regions( &my_game->strips[17], 4, (uint16_t[]){ 3, 2, 6, 1 } );
    set_strip_regions( &my_game->strips[18], 3, (uint16_t[]){ 4, 1, 1 } );
    set_strip_regions( &my_game->strips[19], 3, (uint16_t[]){ 6, 2, 1 } );
    set_strip_regions( &my_game->strips[20], 2, (uint16_t[]){ 8, 2 } );
    set_strip_regions( &my_game->strips[21], 2, (uint16_t[]){ 11, 2 } );
    set_strip_regions( &my_game->strips[22], 4, (uint16_t[]){ 5, 4, 6, 2 } );
    set_strip_regions( &my_game->strips[23], 5, (uint16_t[]){ 8, 4, 3, 2, 2 } );
    set_strip_regions( &my_game->strips[24], 4, (uint16_t[]){ 9, 4, 3, 5 } );

    set_strip_regions( &my_game->strips[25], 2, (uint16_t[]){ 5, 2 } );
    set_strip_regions( &my_game->strips[26], 2, (uint16_t[]){ 8, 2 } );
    set_strip_regions( &my_game->strips[27], 3, (uint16_t[]){ 6, 4, 3 } );
    set_strip_regions( &my_game->strips[28], 4, (uint16_t[]){ 5, 4, 1, 3 } );
    set_strip_regions( &my_game->strips[29], 4, (uint16_t[]){ 4, 4, 3, 4 } );
    set_strip_regions( &my_game->strips[30], 4, (uint16_t[]){ 3, 5, 6, 5 } );
    set_strip_regions( &my_game->strips[31], 3, (uint16_t[]){ 3, 2, 14 } );
    set_strip_regions( &my_game->strips[32], 3, (uint16_t[]){ 2, 10, 2 } );
    set_strip_regions( &my_game->strips[33], 6, (uint16_t[]){ 1, 5, 4, 1, 5, 1 } );
    set_strip_regions( &my_game->strips[34], 5, (uint16_t[]){ 1, 6, 1, 5, 5 } );
    set_strip_regions( &my_game->strips[35], 4, (uint16_t[]){ 1, 2, 2, 10 } );
    set_strip_regions( &my_game->strips[36], 3, (uint16_t[]){ 1, 2, 6 } );
    set_strip_regions( &my_game->strips[37], 6, (uint16_t[]){ 1, 1, 1, 1, 2, 2 } );
    set_strip_regions( &my_game->strips[38], 6, (uint16_t[]){ 1, 1, 2, 1, 2, 1 } );
    set_strip_regions( &my_game->strips[39], 5, (uint16_t[]){ 1, 3, 1, 1, 3 } );
    set_strip_regions( &my_game->strips[40], 5, (uint16_t[]){ 1, 4, 2, 1, 3 } );
    set_strip_regions( &my_game->strips[41], 5, (uint16_t[]){ 2, 4, 1, 1, 3 } );
    set_strip_regions( &my_game->strips[42], 7, (uint16_t[]){ 2, 3, 1, 1, 1, 1, 1 } );
    set_strip_regions( &my_game->strips[43], 6, (uint16_t[]){ 3, 1, 1, 3, 1, 3 } );
    set_strip_regions( &my_game->strips[44], 5, (uint16_t[]){ 3, 1, 2, 2, 2 } );
    set_strip_regions( &my_game->strips[45], 4, (uint16_t[]){ 6, 5, 1, 1 } );
    set_strip_regions( &my_game->strips[46], 2, (uint16_t[]){ 11, 3 } );
    set_strip_regions( &my_game->strips[47], 3, (uint16_t[]){ 3, 3, 2 } );
    set_strip_regions( &my_game->strips[48], 2, (uint16_t[]){ 5, 1 } );
    set_strip_regions( &my_game->strips[49], 1, (uint16_t[]){ 2 } );

    /* This call initialises all strips with their potential patterns. */
    printf("Calculating potential strips.\n");
    nonogram_strip_init_all( my_game );

    return( my_game );
}

static void setup_strip( CELLSTRIP_T* my_strip, CELLSTATE_T* cell_ptr, uint16_t length, uint16_t stepsize )
{
    my_strip->length = length;
    my_strip->cells = malloc( sizeof(CELLSTATE_T*) * length );
    for( uint16_t n=0; n<length; n++ )
    {
        my_strip->cells[n] = cell_ptr;
        cell_ptr += stepsize;
    }
}

static void set_strip_regions( CELLSTRIP_T* my_strip, uint16_t n_regions, uint16_t* regions_ptr )
{
    my_strip->n_regions = n_regions;
    my_strip->region_size = regions_ptr;
}

