#include <stdlib.h>
#include <stdint.h>

#include "nonogram.h"

static void nonogram_init( GAME_T* my_game )
{
    const uint16_t n_strips = my_game->rows + my_game->columns;

    for( uint16_t n=0; n<n_strips; n++ )
    {
        compute_regions( my_game->strips[n] );
    }
}

void compute_regions( CELLSTRIP_T* cellstrip )
{
    cellstrip->possible_list = NULL;
    struct POSSIBLE_T** next_ptr = &cellstrip->possible_list;
    
    

}


