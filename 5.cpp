// C++ implementation of of K-Knight problem
#include <iostream>
using namespace std;

int m, k;
int count = 0;

//To create an empty m*m board
void makeBoard(char** board)
{
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			board[i][j] = '_';
		}
	}
}

// To display our board
void displayBoard(char** board)
{
	cout << endl
		<< endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			cout << " " << board[i][j] << " ";
		}
		cout << endl;
	}
}

// To mark all the attacking positions of a knight placed at board[i][j] position
void attack(int i, int j, char a, char** board)
{

	// To ensure that the block to be checked is inside the board
	if ((i + 2) < m && (j - 1) >= 0) {
		board[i + 2][j - 1] = a;
	}
	if ((i - 2) >= 0 && (j - 1) >= 0) {
		board[i - 2][j - 1] = a;
	}
	if ((i + 2) < m && (j + 1) < m) {
		board[i + 2][j + 1] = a;
	}
	if ((i - 2) >= 0 && (j + 1) < m) {
		board[i - 2][j + 1] = a;
	}
	if ((i + 1) < m && (j + 2) < m) {
		board[i + 1][j + 2] = a;
	}
	if ((i - 1) >= 0 && (j + 2) < m) {
		board[i - 1][j + 2] = a;
	}
	if ((i + 1) < m && (j - 2) >= 0) {
		board[i + 1][j - 2] = a;
	}
	if ((i - 1) >= 0 && (j - 2) >= 0) {
		board[i - 1][j - 2] = a;
	}
}

// If the position is empty, place the knight
bool canPlace(int i, int j, char** board)
{
	if (board[i][j] == '_')
		return true;
	else
		return false;
}

// To place the knight at [i][j] position
void place(int i, int j, char k, char a, char** board, char** new_board)
{

	for (int y = 0; y < m; y++) {
		for (int z = 0; z < m; z++) {
			new_board[y][z] = board[y][z];
		}
	}

	new_board[i][j] = k;

	attack(i, j, a, new_board);
}

// Function for placing knights on board such that they don't attack each other
void kkn(int k, int sti, int stj, char** board)
{

	if (k == 0) {
		displayBoard(board);
		count++;
	}
	else {

		for (int i = sti; i < m; i++) {
			for (int j = stj; j < m; j++) {

				if (canPlace(i, j, board)) {

					char** new_board = new char*[m];
					for (int x = 0; x < m; x++) {
						new_board[x] = new char[m];
					}
					place(i, j, 'K', 'A', board, new_board);

					kkn(k - 1, i, j, new_board);

					for (int x = 0; x < m; x++) {
						delete[] new_board[x];
					}
					delete[] new_board;
				}
			}
			stj = 0;
		}
	}
}

// Driver code
int main()
{
    cout<<"Enter the dimensions of the board in the format m*m \n\n";
    cout<<"Enter the value of m:";
    cin>>m;
    cout<<"Enter the number of knights:";
    cin>>k;
	//m = 4, n = 3, k = 6;

	// Creation of a m*n board
	char** board = new char*[m];
	for (int i = 0; i < m; i++) {
		board[i] = new char[m];
	}

	// To make all the places empty
	makeBoard(board);

	kkn(k, 0, 0, board);

	cout << endl
		<< "Total number of solutions are: "
		<< count;

	return 0;
}
