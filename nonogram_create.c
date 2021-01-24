#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "nonogram.h"
#include "nonogram_strip.h"

static void setup_strip( CELLSTRIP_T* my_strip, CELLSTATE_T* cell_ptr, uint16_t length, uint16_t stepsize );
static void set_strip_regions( CELLSTRIP_T* my_strip, uint16_t n_regions, uint16_t* regions_ptr );

GAME_T* create_game( void )
{
    GAME_T* my_game = malloc( sizeof(GAME_T) );
    if( my_game == NULL )
    {
        return NULL;
    }

    const uint16_t rows = 4;
    const uint16_t columns = 15;

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

    set_strip_regions( &my_game->strips[0], 5, (uint16_t[]){ 3, 1, 1, 1, 1 } );
    set_strip_regions( &my_game->strips[1], 7, (uint16_t[]){ 1, 1, 1, 1, 1, 1, 1 } );
    set_strip_regions( &my_game->strips[2], 5, (uint16_t[]){ 3, 3, 1, 1, 1 } );
    set_strip_regions( &my_game->strips[3], 5, (uint16_t[]){ 1, 1, 1, 3, 3 } );

    set_strip_regions( &my_game->strips[4], 1, (uint16_t[]){ 4 } );
    set_strip_regions( &my_game->strips[5], 2, (uint16_t[]){ 1, 1 } );
    set_strip_regions( &my_game->strips[6], 1, (uint16_t[]){ 3 } );
    set_strip_regions( &my_game->strips[7], 0, (uint16_t[]){ 0 } );
    set_strip_regions( &my_game->strips[8], 1, (uint16_t[]){ 3 } );
    set_strip_regions( &my_game->strips[9], 2, (uint16_t[]){ 1, 1 } );
    set_strip_regions( &my_game->strips[10], 1, (uint16_t[]){ 3 } );
    set_strip_regions( &my_game->strips[11], 0, (uint16_t[]){ 0 } );
    set_strip_regions( &my_game->strips[12], 1, (uint16_t[]){ 4 } );
    set_strip_regions( &my_game->strips[13], 1, (uint16_t[]){ 1 } );
    set_strip_regions( &my_game->strips[14], 1, (uint16_t[]){ 4 } );
    set_strip_regions( &my_game->strips[15], 0, (uint16_t[]){ 0 } );
    set_strip_regions( &my_game->strips[16], 1, (uint16_t[]){ 4 } );
    set_strip_regions( &my_game->strips[17], 1, (uint16_t[]){ 1 } );
    set_strip_regions( &my_game->strips[18], 1, (uint16_t[]){ 1 } );

    /* This call initialises all strips with their potential patterns. */
    nonogram_strip_init_all( my_game );

    return( my_game );
}

static void setup_strip( CELLSTRIP_T* my_strip, CELLSTATE_T* cell_ptr, uint16_t length, uint16_t stepsize )
{
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

