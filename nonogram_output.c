#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "nonogram.h"
#include "nonogram_output.h"


void output_game( GAME_T* game_ptr )
{
    const uint16_t rows = game_ptr->rows;
    const uint16_t columns = game_ptr->columns;

    CELLSTATE_T* cell_ptr = game_ptr->cells;

    for( uint16_t r=0; r<rows; r++ )
    {
        for( uint16_t c=0; c<columns; c++ )
        {
            switch( *cell_ptr )
            {
                case UNKNOWN:    { printf("-"); break; }
                case DEFF_FILL:  { printf("#"); break; }
                case DEFF_BLANK: { printf(" "); break; }
                default:         { printf("!"); break; }
            }
            cell_ptr++;
        }
        printf("\n");
    }
    printf("Done.");
}
