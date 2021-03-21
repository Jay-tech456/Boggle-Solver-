#include "Dictionary.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

Dictionary::Dictionary()							// Defult constuctors 
{
	root = new Node();								// creating the root into a new Node
	numWords = 0;									// numwords is automatically equal to zero.

}

Dictionary::Dictionary(string file)					// Uses the addword function 
{
	ifstream inFile;							// To read inside of the file
	Node* newNode;
	string a;

	newNode = new Node();
	if (!root)									// if the defult constructor fails, create a new node on the spot
												// and set the root
	{
		root = newNode;
	}

	inFile.open(file);							// Open the the file
	if (!inFile)								// If the infile fails
	{
		cout << "\nCannot open the file" << endl;
		return;

	}

	while (!inFile.eof())						// While inile != end of file 
	{
		inFile >> a;
		addWord(a);

	}
	inFile.close();
	cout << "\n" << numWords << " words loaded " << endl;
}


void Dictionary::addWord(string word)								// To add a word to the dictionary
{
	if (isWord(word))												// if the entire words exist in the dictionary, return 
	{																// we cant have duplicate words
		return;
	}
	Node* currNode = root;											// Current is node

	for (int count = 0; count < word.length(); count++)				// for each character in of the word
	{
		Node* newNode = new Node();									// Just in case we need to add a new node in the dictionary
		char c = word[count];										// will store the character of the words to the variable
		int I = (int)c - (int)'a';									// Find the index of the character 
		if (currNode->letters[I] == nullptr)						// If the path of the letter[I] is not pointing to anything
		{
			if (word.length() == 1)
			{
				return;
			}
			currNode->letters[I] = newNode;							// Setting the pointer of letter[I] to a new Node;

		}
		currNode = currNode->letters[I];							// update the currNode


	}
	currNode->isWord = true;										// setting the flag to true
	numWords++;
}


bool Dictionary::isPrefix(string word)
{
	Node* current = root;
	for (int count = 0; count < word.length(); count++)
	{
		char c = word[count];									// saving the character of the word into a character variable
		int I = (int)c - (int)'a';								// turining the character to the index number

		if (current->letters[I] == nullptr)						// if the path is reach to null, word is not in the dictionary														// return false
		{
			return false;
		}
		current = current->letters[I];						// else, update current, and continue
	}
	return true;												// if it goes through the entire list without reaching null,
																// The the word exist 

}


bool Dictionary::isWord(string word)

{
	Node* current = root;										// set the current to the root
	for (int count = 0; count < word.length(); count++)
	{
		char c = word[count];									// store character of the word into a character variable
		int I = (int)c - (int)'a';								// turning the character into index of the alphabet 

		if (current->letters[I] == nullptr)
		{
			return false;										// return false if current->letter[I] is nullptr
		}

		current = current->letters[I];						// update current and continue to the loop

	}
	if (current->isWord == true)
		true;
	else
		false;
}

int Dictionary::wordCount()
{
	return numWords;											// return the number of character in the node 
}
