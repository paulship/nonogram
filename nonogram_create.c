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

    const uint16_t rows = 30;
    const uint16_t columns = 30;

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

    set_strip_regions( &my_game->strips[0], 3, (uint16_t[]){ 6, 4, 3 } );
    set_strip_regions( &my_game->strips[1], 4, (uint16_t[]){ 8, 6, 2, 2 } );
    set_strip_regions( &my_game->strips[2], 4, (uint16_t[]){ 5, 12, 2, 4 } );
    set_strip_regions( &my_game->strips[3], 5, (uint16_t[]){ 6, 1, 6, 1, 7 } );
    set_strip_regions( &my_game->strips[4], 5, (uint16_t[]){ 4, 2, 5, 2, 7 } );
    set_strip_regions( &my_game->strips[5], 5, (uint16_t[]){ 4, 1, 2, 2, 5 } );
    set_strip_regions( &my_game->strips[6], 6, (uint16_t[]){ 2, 1, 1, 1, 2, 3 } );
    set_strip_regions( &my_game->strips[7], 4, (uint16_t[]){ 2, 1, 1, 1 } );
    set_strip_regions( &my_game->strips[8], 7, (uint16_t[]){ 1, 2, 2, 1, 2, 2, 1 } );
    set_strip_regions( &my_game->strips[9], 9, (uint16_t[]){ 4, 2, 2, 2, 1, 2, 1, 2, 2 } );
    set_strip_regions( &my_game->strips[10], 8, (uint16_t[]){ 2, 2, 1, 1, 1, 1, 1, 1 } );
    set_strip_regions( &my_game->strips[11], 6, (uint16_t[]){ 4, 2, 1, 1, 3, 3 } );
    set_strip_regions( &my_game->strips[12], 5, (uint16_t[]){ 8, 2, 1, 3, 3 } );
    set_strip_regions( &my_game->strips[13], 8, (uint16_t[]){ 1, 4, 1, 1, 1, 1, 1, 1 } );
    set_strip_regions( &my_game->strips[14], 5, (uint16_t[]){ 1, 3, 1, 3, 3 } );
    set_strip_regions( &my_game->strips[15], 5, (uint16_t[]){ 1, 3, 5, 3, 3 } );
    set_strip_regions( &my_game->strips[16], 8, (uint16_t[]){ 4, 2, 5, 2, 1, 1, 1, 1 } );
    set_strip_regions( &my_game->strips[17], 3, (uint16_t[]){ 1, 9, 3 } );
    set_strip_regions( &my_game->strips[18], 5, (uint16_t[]){ 1, 1, 3, 3, 4 } );
    set_strip_regions( &my_game->strips[19], 4, (uint16_t[]){ 4, 4, 2, 5 } );
    set_strip_regions( &my_game->strips[20], 5, (uint16_t[]){ 1, 1, 2, 2, 4 } );
    set_strip_regions( &my_game->strips[21], 5, (uint16_t[]){ 5, 3, 2, 2, 3 } );
    set_strip_regions( &my_game->strips[22], 6, (uint16_t[]){ 6, 1, 2, 1, 2, 2 } );
    set_strip_regions( &my_game->strips[23], 7, (uint16_t[]){ 4, 2, 1, 1, 1, 1, 5 } );
    set_strip_regions( &my_game->strips[24], 6, (uint16_t[]){ 3, 2, 1, 1, 3, 4 } );
    set_strip_regions( &my_game->strips[25], 8, (uint16_t[]){ 2, 1, 1, 1, 1, 3, 2, 4 } );
    set_strip_regions( &my_game->strips[26], 6, (uint16_t[]){ 1, 3, 1, 5, 5, 5 } );
    set_strip_regions( &my_game->strips[27], 7, (uint16_t[]){ 1, 3, 1, 1, 1, 2, 5 } );
    set_strip_regions( &my_game->strips[28], 5, (uint16_t[]){ 8, 1, 1, 3, 2 } );
    set_strip_regions( &my_game->strips[29], 5, (uint16_t[]){ 5, 2, 6, 8, 2 } );
    
    set_strip_regions( &my_game->strips[30], 5, (uint16_t[]){ 5, 2, 2, 5, 2 } );
    set_strip_regions( &my_game->strips[31], 4, (uint16_t[]){ 7, 3, 1, 9 } );
    set_strip_regions( &my_game->strips[32], 6, (uint16_t[]){ 7, 4, 1, 2, 4, 2 } );
    set_strip_regions( &my_game->strips[33], 7, (uint16_t[]){ 6, 1, 3, 3, 1, 3, 4 } );
    set_strip_regions( &my_game->strips[34], 6, (uint16_t[]){ 4, 3, 5, 1, 2, 5 } );
    set_strip_regions( &my_game->strips[35], 8, (uint16_t[]){ 2, 5, 2, 2, 2, 1, 2, 3 } );
    set_strip_regions( &my_game->strips[36], 6, (uint16_t[]){ 2, 1, 4, 3, 2, 1 } );
    set_strip_regions( &my_game->strips[37], 6, (uint16_t[]){ 3, 1, 2, 2, 1, 6 } );
    set_strip_regions( &my_game->strips[38], 5, (uint16_t[]){ 1, 3, 1, 2, 1 } );
    set_strip_regions( &my_game->strips[39], 5, (uint16_t[]){ 1, 1, 1, 2, 3 } );
    set_strip_regions( &my_game->strips[40], 6, (uint16_t[]){ 1, 1, 2, 5, 1, 1 } );
    set_strip_regions( &my_game->strips[41], 4, (uint16_t[]){ 3, 3, 4, 7 } );
    set_strip_regions( &my_game->strips[42], 4, (uint16_t[]){ 5, 7, 1, 1 } );
    set_strip_regions( &my_game->strips[43], 4, (uint16_t[]){ 6, 3, 7, 1 } );
    set_strip_regions( &my_game->strips[44], 3, (uint16_t[]){ 5, 4, 1 } );
    set_strip_regions( &my_game->strips[45], 4, (uint16_t[]){ 5, 4, 5, 2 } );
    set_strip_regions( &my_game->strips[46], 5, (uint16_t[]){ 4, 2, 4, 2, 6 } );
    set_strip_regions( &my_game->strips[47], 4, (uint16_t[]){ 2, 2, 2, 6 } );
    set_strip_regions( &my_game->strips[48], 5, (uint16_t[]){ 3, 6, 2, 4, 1 } );
    set_strip_regions( &my_game->strips[49], 5, (uint16_t[]){ 1, 1, 1, 1, 1 } );
    set_strip_regions( &my_game->strips[50], 4, (uint16_t[]){ 2, 2, 2, 1 } );
    set_strip_regions( &my_game->strips[51], 4, (uint16_t[]){ 8, 1, 1, 1 } );
    set_strip_regions( &my_game->strips[52], 5, (uint16_t[]){ 3, 2, 2, 2, 1 } );
    set_strip_regions( &my_game->strips[53], 4, (uint16_t[]){ 5, 8, 2, 1 } );
    set_strip_regions( &my_game->strips[54], 5, (uint16_t[]){ 2, 4, 1, 2, 3 } );
    set_strip_regions( &my_game->strips[55], 6, (uint16_t[]){ 1, 5, 2, 2, 3, 3 } );
    set_strip_regions( &my_game->strips[56], 4, (uint16_t[]){ 7, 8, 3, 6 } );
    set_strip_regions( &my_game->strips[57], 5, (uint16_t[]){ 5, 2, 2, 4, 5 } );
    set_strip_regions( &my_game->strips[58], 4, (uint16_t[]){ 3, 8, 10, 1 } );
    set_strip_regions( &my_game->strips[59], 3, (uint16_t[]){ 2, 8, 1 } );

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

