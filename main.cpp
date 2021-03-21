#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Dictionary.h"
using namespace std;

bool choice = false;
void Print(int matrix[4][4], char board[4][4],Dictionary& d, string word, bool choice, int number);
void solveBoardHelper(int row, int col, int matrix[4][4],char board[4][4], Dictionary dict, Dictionary D, string word, bool choice, int number);
void SolveBoard(char board[4][4], Dictionary& dict, Dictionary& D, bool verbose, int number);

int main()
{
	char board[4][4];
	int number = 0;
	Dictionary dict("Dictionary.txt");							// loading up the words from the Dictionary.txt
	cout << "Enter board " << endl
		<< "-------------" << endl;
	for (int row = 0; row < 4; row++)
	{
		cout << "Row " << row << ": ";
		for (int column = 0; column < 4; column++)			// for inputing the characters to the board
		{
			char character;							
			cin >> character;
			board[row][column] = character;
		}
	}

	for (int row = 0; row < 4; row++)							// 'printing' the entire board to the console
	{
		cout << "\n Row " << row << " : ";
		for (int col = 0; col < 4; col++)
		{
			cout << board[row][col] << " ";
		}
		cout << endl;
	}
	char a;													// see if the user wants to see the board with the path, or not
	cout << "\nWould you like to see the board ('y' or 'n' )" << endl;
	cin >> a;
	if (a == 'y' || a == 'Y')
	{
		choice = true;
	}

	Dictionary wordsFound;
	SolveBoard(board, dict, wordsFound, choice, number);
}

	// Passes in every single character within the matrix
void SolveBoard(char board[4][4], Dictionary& dict, Dictionary& D, bool choice, int number)	// Serves as the 'wrapper' for solveBoadrdHelper
{
	string word;
	int matrix[4][4];
	for (int row = 0; row < 4; row++)								// Initialize the board with one character at a time, and see if there is a word that exist
	{
		for (int col = 0; col < 4; col++)
		{
			word = board[row][col];
			for (int r = 0; r < 4; r++)								// Before calling the SolveBoardHelper function, initialize the matrix, and pass it on 
			{
				for (int c = 0; c < 4; c++)
				{
					matrix[r][c] = 0;
				}
			}
			//cout << "We are now passing is " << board[row][col] << endl;
			solveBoardHelper(row, col, matrix, board, dict, D, word, choice, number);			// Will return to this function after all the words are found
		}
	}
}

void solveBoardHelper(int row, int col, int matrix[4][4], char board[4][4], Dictionary dict, Dictionary D, string word, bool choice, int number)
{
	// We cant go out of bound in the matrix
	if (row > 4 || row < 0 || col > 4 || col < 0)
	{
		return;
	}

	// if it is not a prefix, then return
	if (!dict.isPrefix(word))
	{
		return;
	}
	
	if (matrix[row][col] == 0)							// To make sure we are not repeating the same position twice in one word
	{
		matrix[row][col] = ++number;
	}
	else
		return;											// IF we are, then return

	if (!D.isWord(word) && dict.isWord(word))			// Make ksure we are not repeating the same words in the dictionary
	{
		D.addWord(word);
		Print(matrix, board, D, word, choice, number);	// Print the board with the new formulated word
	}

				// Heavy recucursion, goes through every position before retruning to SolveBoard function


	solveBoardHelper(row + 1, col, matrix, board, dict, D, word + board[row + 1][col], choice, number);
	solveBoardHelper(row - 1, col, matrix, board, dict, D, word + board[row - 1][col], choice, number);

	solveBoardHelper(row, col - 1, matrix, board, dict, D, word + board[row][col - 1], choice, number);
	solveBoardHelper(row, col + 1, matrix, board, dict, D, word + board[row][col + 1], choice, number);

	solveBoardHelper(row + 1, col + 1, matrix, board, dict, D, word + board[row + 1][col + 1], choice, number);
	solveBoardHelper(row - 1, col - 1,matrix,  board, dict, D, word + board[row - 1][col - 1], choice, number);

	solveBoardHelper(row + 1, col - 1, matrix, board, dict, D, word + board[row + 1][col - 1], choice, number);
	solveBoardHelper(row - 1, col + 1, matrix, board, dict, D, word + board[row - 1][col + 1], choice, number);
	matrix[row][col] = 0;


	return;
}

void Print(int matrix[4][4],char Board[4][4], Dictionary& D, string word, bool choice, int number)
{
	ofstream outFile;
	if (choice)														// If choice is true, then print out the word with the matrix
	{
		cout << endl << endl;
		// cout << number << endl;
		cout << " Here is the word " << word << endl;

		for (int r = 0; r < 4; r++)
		{
			for (int col = 0; col < 4; col++)					// Print out the original board
			{
				cout << Board[r][col] << " ";
			}
			cout << setw(12);
			for (int col = 0; col < 4; col++)					// for printing out the entire matrix 
			{
				
				cout << matrix[r][col] << " ";
			}
			cout << endl;
		}
	}
	else
	{
		cout << word << endl;										// or else, just print out the entire word
	}

	outFile.open("output.txt", ios::app);
	if (choice)														// If choice is true, then print out the word with the matrix
	{
		outFile << endl << endl;
		// cout << number << endl;
		outFile << " Here is the word " << word << endl;

		for (int r = 0; r < 4; r++)
		{
			for (int col = 0; col < 4; col++)					// Print out the original board
			{
				outFile << Board[r][col] << " ";
			}
			outFile << setw(12);
			for (int col = 0; col < 4; col++)					// for printing out the entire matrix 
			{

				outFile << matrix[r][col] << " ";
			}
			outFile  << endl;
		}
		outFile.close();
		return;
	}

		outFile << word << endl;										// or else, just print out the entire word
		outFile.close();
			return;

}