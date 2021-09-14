/*
 *
 * Implementation of the sliding blocks game
 * 
 * Author: @Rajan
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue.c"
#include "list.c"

//----------------------------------global variables-----------------------------

//user inputs
int rowSize, colSize;
int input[6][6];

//input matrix in form of string
char *initialState;

//Direction to move to block
int dirX[4] = {0, 0, 1, -1};
int dirY[4] = {1, -1, 0, 0};

//To store ending node of the path
queueNode *endNode;

//------------------------------------End-----------------------------------------

//------------------------To swap the value of two characters---------------------
void swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

//-------------------------To take the user input initially------------------------
void takeInput()
{
    printf("\nEnter the number of rows: ");
    scanf("%d", &rowSize);
    printf("\nEnter the number of columns: ");
    scanf("%d", &colSize);

    if (rowSize * colSize > 9)
    {
        printf("\nGrid size is too big\n");
        exit(0); //To end the program
    }

    //array to check if any number is visited greater than once
    int countOccurence[rowSize * colSize];
    memset(countOccurence, 0, sizeof(countOccurence));

    printf("\nEnter the initial grid with %d rowSize and %d colSize\n", rowSize, colSize);
    printf("(Only distinct numbers between 1-%d and a 0 to represent an empty space)\n\n", rowSize * colSize - 1);

    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
            scanf("%d", &input[i][j]);

            //if any invalid value is added to grid
            if (input[i][j] >= rowSize * colSize)
            {
                printf("\nInvalid Number\n");
                exit(0);
            }

            countOccurence[input[i][j]]++;
        }
    }

    //if any character is repeated in the grid
    for (int i = 0; i < rowSize * colSize; i++)
    {
        if (countOccurence[i] != 1)
        {
            printf("\n\nInvalid grid");
            exit(0);
        }
    }
}

//-------------------------Converts a matrix to string format------------------------
void convertMatrixToString()
{
    initialState = (char *)malloc(sizeof(char) * (rowSize * colSize + 1));
    int index = 0;
    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
            initialState[index++] = (char)(input[i][j] + '0');
        }
    }
    initialState[index] = '\0';
}

//----------------------prints a matrix of rowSize rows and colSize columns from a string------------------
void printMatrixFromString(char *string)
{
    printf("\n");
    for (int i = 0; string[i] != '\0'; i++)
    {
        printf("%c", string[i]);
        if (((i + 1) % colSize) == 0)
        {
            printf("\n");
            for (int j = 0; j < colSize; j++)
                printf("---");
            printf("\n");
        }
        else
        {
            printf(" | ");
        }
    }
    printf("\n");
}

//------------------------Returns 1 if solution state is reached, else 0-----------------------------------
int reachedAnswerState(char *toCheck)
{
    for (int i = 0; i + 1 < rowSize * colSize; i++)
    {
        if ((toCheck[i] - '0') != (i + 1))
            return 0;
    }

    return toCheck[rowSize * colSize - 1] == '0';
}

//---------------------pushes all the reachable states from a given state----------------------------------
//-----------------------------------Time Complexity : O((N*M)!)---------------------------------------------
void pushReachableStates(queueNode *parent, char *initialState)
{
    //Finding the index at which empty space or 0 is present
    int indexOfZero = -1;
    for (int i = 0; i < rowSize * colSize; i++)
    {
        if (initialState[i] == '0')
        {
            indexOfZero = i;
            break;
        }
    }

    //Computing the x and y coordinate of 0 in grid
    int xCoordinate = indexOfZero / colSize;
    int yCoordinate = indexOfZero % colSize;

    //moving in all four directions
    for (int i = 0; i < 4; i++)
    {
        int newX = xCoordinate + dirX[i];
        int newY = yCoordinate + dirY[i];

        //if new cell is inside the matrix
        if (newX >= 0 && newX < rowSize && newY >= 0 && newY < colSize)
        {
            //moving the empty space
            swap(&initialState[newX * colSize + newY], &initialState[indexOfZero]);

            //checking if we have reached this state initially or not
            if (isPresent(initialState) == 0)
            {
                insert(initialState);
                enqueue(initialState, initialState[indexOfZero] - '0', parent);
            }

            //moving the empty space back to it's original position
            swap(&initialState[newX * colSize + newY], &initialState[indexOfZero]);
        }
    }
}

//---------------------Returns the number of minimum moves to solve the input grid---------------------------
//-----------------------------------Time Complexity : O((N*M)!)---------------------------------------------
int minimumMoves()
{
    //initializing queue and adding the initialState
    initializeQueue();

    enqueue(initialState, -1, NULL);
    insert(initialState);

    //denotes moves until we find solution state
    int movesTillNow = 0;

    //while there are more states to explore
    while (!is_empty())
    {
        int size = queueSize();

        //exploring all the states within one move
        while (size--)
        {
            char *currentState = (char *)malloc(sizeof(char) * 10);
            queueNode *currentNode = frontNode();
            strcpy(currentState, frontVal());

            dequeue();

            if (reachedAnswerState(currentState))
            {
                endNode = currentNode;
                return movesTillNow;
            }

            pushReachableStates(currentNode, currentState);
        }

        //incrementing number of moves to reach the solution state
        movesTillNow++;
    }

    //there is no solution for the input grid
    return -1;
}

int main()
{
    takeInput();
    convertMatrixToString();

    int result = minimumMoves();

    //if there is no possible solution
    if (result == -1)
    {
        printf("\nNot Possible");
    }
    else
    {
        //shortest number of moves
        printf("\nShortest number of moves = %d\n", result);

        //reversing the path of parents to print from front
        queueNode *startNode = reversePath(endNode);

        //until the end of the path
        while (startNode != NULL)
        {
            printMatrixFromString(startNode->val);
            int toMove = startNode->valMoved;
            startNode = startNode->parent;

            if (startNode)
            {
                printf("Press any key to continue\n");
                getch();
                printf("\nMoving %d to reach next state:\n", startNode->valMoved);
            }
        }

        printf("Press any key to end the program\n");
        getch();
    }
}