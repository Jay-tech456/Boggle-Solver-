#pragma once
#include <string>
using namespace std;

struct Node {
	bool isWord;
	struct Node* letters[26];
	Node()												// For the new nodes
	{
		for (int count = 0; count < 26; count++)			// Every new node needs to have latter[count] = nullptr, and isWord is false
		{
			letters[count] = nullptr;
		}
		isWord = false;
	}

};
class Dictionary
{
public:
	Dictionary();									// Defult constructor (initializing the root and the numWords)
	Dictionary(string);								// for loading up the entire word

	void addWord(string);							// For adding words if it does not already exist
	bool isWord(string);							

	bool isPrefix(string);

	void PrintWords(string);							// This is extra credit 


	int wordCount();
private:
	Node* root;
	int numWords;

};

