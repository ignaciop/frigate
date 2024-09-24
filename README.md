# frigate
This C programming project focuses on dynamic memory allocation, pointers, file I/O, and string manipulation. Based on a lab from ECPE 170 (https://ecs-network.serv.pacific.edu/ecpe-170/lab/lab-c-programming-project).

The game is named Frigate, which is a one-sided game of Battleship in which the computer hides the ships, and the player must destroy them before s/he runs out of ammunition (the player has a limited number of shells per game).

The user specifies at the beginning of the game the size of the grid; it will always be square and any size between 5 and 20. The player gets n shells, where n is 1/2 the grid size squared.  The number of shells is rounded down to the next smallest integer value.

The computer next randomly places four ships (one carrier of 5 squares, one battleship of 4 squares, and two frigates of 2 squares) randomly inside the grid.  Ships must fit inside the grid and cannot be placed on top of one another (there are no submarines in frigate. )

Coordinates are noted by row/column, where row is a number and column a letter. A player can enter coordinates either row or column first (i.e., 1a or A1). Upper or lower case letters are allowed. White space is not allowed. Coordinates are checked for validity; they must lie within the grid and a player can enter a coordinate only once per game. 

A ship is "destroyed" when all of its structure has been hit.

Usage: ***make release && build/release/frigate***
