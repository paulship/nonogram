#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "nonogram_output.h"
#include "nonogram_solve.h"

static bool check_strip( CELLSTRIP_T* strip_ptr );
static bool apply_strip_possibilities( CELLSTRIP_T* strip_ptr );
static bool update_cells( CELLSTRIP_T* strip_ptr );
static bool update_cell_possibility( CELLSTATE_T* candidate, CELLSTATE_T* actual );

void nonogram_solve( GAME_T* game_ptr )
{
    /* Precalculate number of strips. */
    const uint16_t n_strips = game_ptr->rows + game_ptr->columns;

    /*
        This loop will repeatedly check strips to see if their solution can be
        reduced at all. If some improvement can be made in the game somewhere then
        we consider that to be a change. When no more changes can be made then
        we exit the loop.
    */
    bool change_made = false;

    do
    {
        /* Initialise this to false. If any changes are made later then we set it to true and this will cause another loop. */
        change_made = false;

        for( uint16_t ii=0; ii<n_strips; ii++ )
        {
            //printf("Checking strip %d\n",ii);
            if( check_strip( game_ptr->strips + ii ) )
            {
                change_made = true;
            }
            //printf("Checked strip %d and got:\n",ii);
            //nonogram_output( game_ptr );
        }

        printf("\n_________________________\n\n");
        nonogram_output( game_ptr );
        usleep( 50000u );

    } while ( change_made );
    
}


static bool check_strip( CELLSTRIP_T* strip_ptr )
{
    /* First step is to determine possible cell states and prune invalid strips */
    const bool cond_a = apply_strip_possibilities( strip_ptr );

    /* Second step is to update cell status */
    const bool cond_b = update_cells( strip_ptr );

    /* Return true if either made a change. */
    return( cond_a || cond_b );
}

static bool apply_strip_possibilities( CELLSTRIP_T* strip_ptr )
{
    struct POSSIBLE_T** link_ptr = &strip_ptr->possible_list;
    struct POSSIBLE_T* poss_ptr = strip_ptr->possible_list;

    bool change_made = false;

    while( poss_ptr != NULL )
    {
        bool remove_poss = false;

        for( uint16_t jj=0; jj<strip_ptr->length; jj++ )
        {
            bool invalid_found = update_cell_possibility( poss_ptr->candidate + jj, strip_ptr->cells[jj] );
            if( invalid_found )
            {
                remove_poss = true;
                change_made = true;
            }
        }

        if( remove_poss )
        {
            //printf("Possibility removed.\n");
            free( poss_ptr->candidate );
            poss_ptr = poss_ptr->next;
            free( *link_ptr );
            *link_ptr = poss_ptr;
        }
        else
        {
            //printf("Possibility retained.\n");
            link_ptr = &poss_ptr->next;
            poss_ptr = poss_ptr->next;
        }        
    }

    return( change_made );
}

static bool update_cells( CELLSTRIP_T* strip_ptr )
{
    bool change_made = false;

    for( uint16_t kk=0; kk<strip_ptr->length; kk++ )
    {
        CELLSTATE_T state = *(strip_ptr->cells[kk]);

        switch( state )
        {
            case POSS_FILL:
            {
                *(strip_ptr->cells[kk]) = DEFF_FILL;
                change_made = true;
                break;
            }
            case POSS_BLANK:
            {
                *(strip_ptr->cells[kk]) = DEFF_BLANK;
                change_made = true;
                break;
            }
            case INDETERMINATE:
            {
                *(strip_ptr->cells[kk]) = UNKNOWN;                
                break;
            }
            case UNKNOWN:
            case DEFF_FILL:
            case DEFF_BLANK:
            {
                /* Don't need to do anything for these states. */
                break;
            }
        }
    }

    return( change_made );
}

static bool update_cell_possibility( CELLSTATE_T* candidate, CELLSTATE_T* actual )
{
    bool invalid_found = true;

    switch( *candidate )
    {
        case DEFF_FILL:
        {
            switch( *actual )
            {
                case UNKNOWN:
                {
                    *actual = POSS_FILL;
                    invalid_found = false;
                    break;
                }

                case DEFF_FILL:
                {
                    *actual = DEFF_FILL;
                    invalid_found = false;
                    break;
                }

                case DEFF_BLANK:
                {
                    *actual = DEFF_BLANK;
                    invalid_found = true;
                    break;
                }

                case POSS_FILL:
                {
                    *actual = POSS_FILL;
                    invalid_found = false;
                    break;
                }

                case POSS_BLANK:
                {
                    *actual = INDETERMINATE;
                    invalid_found = false;
                    break;
                }

                case INDETERMINATE:
                {
                    *actual = INDETERMINATE;
                    invalid_found = false;
                    break;
                }
            }
            break;
        }

        case DEFF_BLANK:
        {
            switch( *actual )
            {
                case UNKNOWN:
                {
                    *actual = POSS_BLANK;
                    invalid_found = false;
                    break;
                }

                case DEFF_FILL:
                {
                    *actual = DEFF_FILL;
                    invalid_found = true;
                    break;
                }

                case DEFF_BLANK:
                {
                    *actual = DEFF_BLANK;
                    invalid_found = false;
                    break;
                }

                case POSS_FILL:
                {
                    *actual = INDETERMINATE;
                    invalid_found = false;
                    break;
                }

                case POSS_BLANK:
                {
                    *actual = POSS_BLANK;
                    invalid_found = false;
                    break;
                }

                case INDETERMINATE:
                {
                    *actual = INDETERMINATE;
                    invalid_found = false;
                    break;
                }
            }
            break;
        }

        case POSS_FILL:
        case POSS_BLANK:
        case INDETERMINATE:
        case UNKNOWN:
        {
            /* Don't need to do anything for these - these should never appear in a candidate strip. */
            break;
        }
    }

    return( invalid_found );
}
