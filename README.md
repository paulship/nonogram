# Nonogram Solver

## So what's going on here then?
After playing around with various nonogram apps, I realised that I was starting to follow a common set of rules to arrive at a solution. This project is my attempt to implement these rules so that, given an initial set of clues, the program would output a matching solution.

### What's an nonogram?

https://en.wikipedia.org/wiki/Nonogram

## Data Structures and Algorithm

Some basic things that you should know first:
* At the core of this is a 2-dimensional array of cells. The state of each cell can be one of the ones described below.
* There is also an array of strips. Each strip contains an array of pointers to the cells that make up the strips. Strips will cross the array of cells both horizontally and vertically, but it is the same structure used for both. Thus, each cell in the grid will be pointed at from two strips. This means that, for example, if a cell is confirmed as filled when analysing the horizontal script, it will automatically be confirmed as filled in the vertical strip since they point at the same data.
* Each strip also contains a pointer to a linked list of possible solutions. Possible solutions are tested on each iteration, and we continue this until no further eliminations are possible. If all goes well, then this should leave only a single solution. (This doesn't always happen though, there are some limits to the algorithm.)

The algorithm is:

1. Initialisation of a blank grid, and constructing strips. Each strip contains an array of pointers into the grid. Remember, strips go both horizontally and vertically, and pointers are aliased such that each cell in the grid is pointed to by both the horizontal and vertical strip.
2. Creating linked lists containing each valid combination of "filled" and "empty" squares, based on the clue included with the strip. The means by which this is done is explained below.
3. For each strip, eliminate any combinations that are not possible, based on the current state of the grid. Also, update the grid based on the remaining combinations.

The final step is repeated until the grid is no longer being updated. At this point, the grid is printed to stdout, hopefully revealing a solution.

## Generating Strip Possibilities

For a given strip, we know the length of the strip, and we have a clue. The clue defines the number of consecutive filled squares. We do not know how many empty squares are between them.

For example, let the length of our strip be 10, and the clue be "1,2,2". The possibilities are:

- ■□■■□■■□□□
- ■□■■□□■■□□
- ■□■■□□□■■□
- ■□■■□□□□■■
- ■□□■■□■■□□
- ■□□■■□□■■□
- ■□□■■□□□■■
- ■□□□■■□■■□
- ■□□□■■□□■■
- ■□□□□■■□■■
- □■□■■□■■□□
- □■□■■□□■■□
- □■□■■□□□■■
- □■□□■■□□■■
- □■□□□■■□■■
- □□■□■■□■■□
- □□■□■■□□■■
- □□■□□■■□■■
- □□□■□■■□■■

So there is kind of a pattern here. It's possible to see how the strip possibilities can be built up recursively. Starting with the initial run of 1 filled square, the remaining spaces can be filled by populating with the clue "2,2". The square is then moved along, and the process repeated until the square can be moved along no further. This works for any number of consecutive runs in the clue, and they are added to the strip's linked list of possibities as they are generated.

## Updating the Grid



