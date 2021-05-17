#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "nonogram.h"
#include "nonogram_strip.h"

static void calculate_potential( const CELLSTRIP_T* cellstrip_data_ptr, struct POSSIBLE_T** next_poss_ptr, const uint16_t top_region, bool* pattern, uint16_t mod_length );
//static void print_potential( bool* pattern, uint16_t length );
static void add_potential( struct POSSIBLE_T** next_poss_ptr, bool* pattern, uint16_t length );

void nonogram_strip_init_all( GAME_T* my_game )
{
    const uint16_t n_strips = my_game->rows + my_game->columns;

    for( uint16_t n=0; n<n_strips; n++ )
    {
        printf("Calculating strip %d\n", n );
        nonogram_strip_init( my_game->strips + n );
    }
}

void nonogram_strip_init( CELLSTRIP_T* cellstrip )
{
    // Reinitialise the pointer to list of potential solutions (TODO: possble future enhancement
    // to 'free' any memory that is currently here if not a NULL pointer)
    cellstrip->possible_list = NULL;
    struct POSSIBLE_T** list_start = &cellstrip->possible_list;
    
    // Set up a working area for generating these strips. The concept here is we have a recursive
    // function call that will move bits around this memory, but when we add them to the linked
    // list we will take a copy and add that to the end of the list.
    bool* pattern = malloc( cellstrip->length * sizeof(bool) );
    if( pattern == NULL )
    {
        printf("Unable to allocate pattern memory.\n");
        exit( EXIT_FAILURE );
    }

    // Set all pattern elements to false
    for( uint16_t n=0; n<cellstrip->length; n++ )
    {
        pattern[n] = false;
    }

    // Begin calculations
    calculate_potential( cellstrip, list_start, cellstrip->n_regions, pattern, cellstrip->length );

    // Free up memory
    free( pattern );
}

/*
    This is a recursive function that calculates the potential cellstrip patterns.
*/
static void calculate_potential( const CELLSTRIP_T* cellstrip_data_ptr, struct POSSIBLE_T** list_start, const uint16_t top_region, bool* pattern, uint16_t mod_length )
{
    // printf("Calculate potential, top_region %u, mod_length %u \n", top_region, mod_length );

    if( top_region>0 )
    {
        // Variable first_start represents the cell index where our current region will
        // be positioned. It is calculated as the sum of the sizes of all regions before
        // it, plus one for a space.
        uint16_t first_start = 0;
        for( uint16_t n=0; n<top_region-1; n++ )
        {
            first_start += cellstrip_data_ptr->region_size[n];
            first_start++;
        }

        // Variable last_start is the final cell index where our current region could
        // possibly start. It is calculated as the mod_length minus the size of the region.
        uint16_t last_start = mod_length - cellstrip_data_ptr->region_size[top_region-1];

        // We now loop round placing the region at each start point.
        for( uint16_t start=first_start; start<=last_start; start++ )
        {
            // Place the region at the start point.
            for( uint16_t i=start; i<start+cellstrip_data_ptr->region_size[top_region-1]; i++ )
            {
                pattern[i] = true;
            }

            // Recursive call to position all regions before it.
            calculate_potential( cellstrip_data_ptr, list_start, top_region-1, pattern, start-1 );

            // Clear the region for the next iteration.
            for( uint16_t i=start; i<start+cellstrip_data_ptr->region_size[top_region-1]; i++ )
            {
                pattern[i] = false;
            }
        }
    }
    else
    {
        //print_potential( pattern, cellstrip_data_ptr->length );
        add_potential( list_start, pattern, cellstrip_data_ptr->length );
    }

}

#if 0
static void print_potential( bool* pattern, uint16_t length )
{
    for( uint16_t n=0; n<length; n++ )
    {
        if( pattern[n] )
        {
            printf("#");
        }
        else
        {
            printf("-");
        }        
    }
    printf("\n");
}
#endif

static void add_potential( struct POSSIBLE_T** list_start, bool* pattern, uint16_t length )
{
    // First allocate memory for our POSSIBLE_T structure, next to be added to the linked list.
    struct POSSIBLE_T* new_possible = malloc( sizeof( struct POSSIBLE_T ) );
    if( new_possible == NULL )
    {
        printf("Memory allocation failure 1 in add_potential\n");
        exit( EXIT_FAILURE );
    }

    // Now allocate memory for the cell states
    new_possible->candidate = malloc( sizeof( new_possible->candidate ) * length );
    if( new_possible->candidate == NULL )
    {
        printf("Memory allocation failure 2 in add_potential\n");
        exit( EXIT_FAILURE );
    }

    // Copy the cell pattern into the new candidate structure
    for( uint16_t l=0; l<length; l++ )
    {
        if( pattern[l] )
        {
            new_possible->candidate[l] = DEFF_FILL;
        }
        else
        {
            new_possible->candidate[l] = DEFF_BLANK;
        }        
    }

    // Update pointers for linked list
    new_possible->next = NULL;
    while( *list_start != NULL )
    {
        list_start = &((*list_start)->next);
    }
    *list_start = new_possible;
}

