
## Project description 

The project is regarding the solution of [Sliding puzzle](https://en.wikipedia.org/wiki/Sliding_puzzle) in which a player have to move the tiles in a grid to reach a solution state of continuous numbers in the grid.
<center><a href="https://imgbb.com/"><img src="https://i.ibb.co/M1VK3Tx/puzzle.gif" alt="puzzle" border="0"></a></center>

## Goals

 - Printing the least number of moves to reach the solution state or printing not possible if there is no solution.
 - Printing the moves to make to reach the solution state in minimum number of moves.

## Specifications

 - Driver.c is the main C language program which takes input from user and finds the the minimum number of moves.
 - list.c is the C file for adding the visited states of game to a singly linked list with a linear seach operation.
 - queue.c is the C file for queue data structure implemented using singly linked list with node of a queue containing information about the parent state.

## Design

 - Used [Breadth-first search(BFS)](https://en.wikipedia.org/wiki/Breadth-first_search) to explore all the states of game until a solution state is reached.
 - Used singly linked list to add the visited states of game.
 - Used a linked list based queue for BFS which also deals with parent state of a state to generate the path to the solution
 - Maintained the grid in from of string of digits.
