#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "nonogram.h"
#include "nonogram_create.h"
#include "nonogram_output.h"

int main( void )
{
    GAME_T* my_game = create_game();

    compute_regions(my_game);

    output_game( my_game );

    return 0;
}


