#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "nonogram.h"
#include "nonogram_create.h"
#include "nonogram_output.h"
#include "nonogram_solve.h"

int main( void )
{
    GAME_T* my_game = nonogram_create();

    nonogram_solve( my_game );

    nonogram_output( my_game );

    return 0;
}


