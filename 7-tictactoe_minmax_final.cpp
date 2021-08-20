// A C++ Program to play tic-tac-toe

#include<bits/stdc++.h>
#include<graphics.h> /* header file */
#include<stdio.h>
#include<stdlib.h>
#include "string.h"
#include "time.h"
#define d 70                //d=distance
#define s 60                //s=size
#define f 150               //f=display coordinate factor

using namespace std;

#define COMPUTER 1
#define HUMAN 2
#define SIDE 3
#define COMPUTERMOVE 'X'
#define HUMANMOVE 'O'

struct Move
{
	int row, col;
};

int evaluate(char b[3][3])
{
	// Checking for Rows for X or O victory.
	for (int row = 0; row<3; row++)
	{
		if (b[row][0]==b[row][1] &&
			b[row][1]==b[row][2])
		{
			if (b[row][0]=='O')
				return +10;
			else if (b[row][0]=='X')
				return -10;
		}
	}

	// Checking for Columns for X or O victory.
	for (int col = 0; col<3; col++)
	{
		if (b[0][col]==b[1][col] &&
			b[1][col]==b[2][col])
		{
			if (b[0][col]=='O')
				return +10;

			else if (b[0][col]=='X')
				return -10;
		}
	}

	// Checking for Diagonals for X or O victory.
	if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
	{
		if (b[0][0]=='O')
			return +10;
		else if (b[0][0]=='X')
			return -10;
	}

	if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
	{
		if (b[0][2]=='O')
			return +10;
		else if (b[0][2]=='X')
			return -10;
	}

	// Else if none of them have won then return 0
	return 0;
}

bool isMovesLeft(char board[3][3])
{
	for (int i = 0; i<3; i++)
		for (int j = 0; j<3; j++)
			if (board[i][j]==' ')
				return true;
	return false;
}

int minimax(char board[3][3], int depth, bool isMax)
{
	int score = evaluate(board);
	if (score == 10)
		return score;
	if (score == -10)
		return score;
	if (isMovesLeft(board)==false)
		return 0;

	// If this maximizer's move
	if (isMax)
	{
		int best = -1000;
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				if (board[i][j]==' ')
				{
					board[i][j] = 'O';
					best = max( best, minimax(board, depth+1, !isMax) );
					board[i][j] = ' ';
				}
			}
		}
		return best;
	}

	// If this minimizer's move
	else
	{
		int best = 1000;
		for (int i = 0; i<3; i++)
		{
			for (int j = 0; j<3; j++)
			{
				if (board[i][j]==' ')
				{
					board[i][j] = 'X';
					best = min(best, minimax(board, depth+1, !isMax));
					board[i][j] = ' ';
				}
			}
		}
		return best;
	}
}

Move findBestMove(char board[3][3])
{
	int bestVal = -1000;
	Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;

	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
		{
			if (board[i][j]==' ')
			{
				board[i][j] = 'O';
				int moveVal = minimax(board, 0, false);
				board[i][j] = ' ';
				if (moveVal > bestVal)
				{
					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}
	return bestMove;
}

void display(int sx, int sy, char board[][SIDE])
{
    int i,j;
    char str[2];
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(j==sx&&i==sy)
                setcolor(RED);
            else
                setcolor(BLACK);
            rectangle(j*d+f,i*d+f,j*d+s+f,i*d+s+f);
            sprintf(str,"%c",board[i][j]);               //To print Player's symbol in cell
            outtextxy(j*d+20+f, i*d+20+f, str);
        }
    }
}

// A function to show the instructions
void showInstructions()
{
	printf("\n\nChoose a cell numbered from 1 to 9 as below\n\n");

	printf("\t\t\t 1 | 2 | 3 \n");
	printf("\t\t\t--------------\n");
	printf("\t\t\t 4 | 5 | 6 \n");
	printf("\t\t\t--------------\n");
	printf("\t\t\t 7 | 8 | 9 \n\n");

	printf("-\t-\t-\t-\t-\t-\t-\t-\t-\t-\n\n");

	return;
}

void initialise(char board[][SIDE], int moves[])
{
	srand(time(NULL));

	// Initially the board is empty
	for (int i=0; i<SIDE; i++)
	{
		for (int j=0; j<SIDE; j++)
			board[i][j] = ' ';
	}

	for (int i=0; i<SIDE*SIDE; i++)
		moves[i] = i;

	random_shuffle(moves, moves + SIDE*SIDE);

	return;
}

void declareWinner(int whoseTurn)
{
    char str[25];
	if (whoseTurn == COMPUTER)
    {
		printf("COMPUTER has won\n");
		sprintf(str,"COMPUTER HAS WON!");
        outtextxy(150,400,str);
    }
	else
    {
		printf("USER has won\n");
		sprintf(str,"USER HAS WON!");
        outtextxy(150,400,str);
    }
	return;
}

// returns true if any of the rows crosses the same player's move
bool rowCrossed(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
			return (true);
	}
	return(false);
}

// returns true if any of the columns crosses the same player's move
bool columnCrossed(char board[][SIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
			return (true);
	}
	return(false);
}

// returns true if any of the diagonals crosses the same player's move
bool diagonalCrossed(char board[][SIDE])
{
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
		return(true);

	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
		return(true);

	return(false);
}

// returns true if the game is over, else it returns a false
bool gameOver(char board[][SIDE])
{
	return(rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board) );
}

void playTicTacToe(int whoseTurn)
{
	char board[SIDE][SIDE];
	int moves[SIDE*SIDE];
	char str[25];
	initialise(board, moves);
	showInstructions();
	int moveIndex = 0, x, y, c;
	while (gameOver(board) == false && moveIndex != SIDE*SIDE)
	{
	    cleardevice();
        setcolor(BLACK);
        char aa[]="COMPUTER: X";
        outtextxy(150,40,aa);
        char ab[]="USER: O";
        outtextxy(150,60,ab);
        display(y,x,board);
		if (whoseTurn == COMPUTER)
		{
		    Move bestMove = findBestMove(board);

            /*printf("The Optimal Move is :\n");
            printf("ROW: %d COL: %d\n\n", bestMove.row, bestMove.col );*/
            x=bestMove.row;
            y=bestMove.col;
            if(x==0 && y==0)
            {
                c=1;
                moves[0]=-1;
            }
            else if(x==1 && y==0)
            {
                c=4;
                moves[1]=-1;
            }
            else if(x==2 && y==0)
            {
                c=7;
                moves[2]=-1;
            }
            else if(x==0 && y==1)
            {
                c=2;
                moves[3]=-1;
            }
            else if(x==1 && y==1)
            {
                c=5;
                moves[4]=-1;
            }
            else if(x==2 && y==1)
            {
                c=8;
                moves[5]=-1;
            }
            else if(x==0 && y==2)
            {
                c=3;
                moves[6]=-1;
            }
            else if(x==1 && y==2)
            {
                c=6;
                moves[7]=-1;
            }
            else if(x==2 && y==2)
            {
                c=9;
                moves[8]=-1;
            }
			if(board[x][y]==' ')
			{
			    board[x][y] = COMPUTERMOVE;
                printf("COMPUTER has put an %c in cell %d\n", COMPUTERMOVE, c);
                display(y,x,board);
                moveIndex ++;
                whoseTurn = HUMAN;
			}
			else
            {
                moveIndex ++;
                whoseTurn = COMPUTER;
            }
		}

		else if (whoseTurn == HUMAN)
		{
		    printf("\nEnter your move: ");
			scanf("%d",&c);
			switch(c)
            {
                case 1:
                    x=0; y=0;
                    break;
                case 2:
                    x=0; y=1;
                    break;
                case 3:
                    x=0; y=2;
                    break;
                case 4:
                    x=1; y=0;
                    break;
                case 5:
                    x=1; y=1;
                    break;
                case 6:
                    x=1; y=2;
                    break;
                case 7:
                    x=2; y=0;
                    break;
                case 8:
                    x=2; y=1;
                    break;
                case 9:
                    x=2; y=2;
                    break;
            }
			board[x][y] = HUMANMOVE;
			printf ("USER has put an %c in cell %d\n", HUMANMOVE, c);
			display(y,x,board);
			moveIndex ++;
			whoseTurn = COMPUTER;
		}
	}

	// If the game is draw
	if (gameOver(board) == false && moveIndex == SIDE * SIDE)
    {
        printf("It's a draw\n");
        sprintf(str,"IT IS A DRAW!");
        outtextxy(150,400,str);
    }

	else
	{
		if (whoseTurn == COMPUTER)
			whoseTurn = HUMAN;
		else if (whoseTurn == HUMAN)
			whoseTurn = COMPUTER;

		declareWinner(whoseTurn);
	}
	return;
}

int main()
{
    int gd,gm;
    detectgraph(&gd,&gm);
    initgraph(&gd,&gm,NULL);
    setbkcolor(WHITE);
    cleardevice();
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);

	playTicTacToe(COMPUTER);

	getch();
    closegraph();

	return (0);
}
