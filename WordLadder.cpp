/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: Bryan
 * This file is the starter project for the Word Ladder problem.
 */

#include <iostream>
#include <fstream>
#include "queue.h"
#include "vector.h"
#include "lexicon.h"
#include "simpio.h"
#include "foreach.h"
using namespace std;

Vector<string> WordLadder(string initWord, string tarWord);

int main() {
	while (true) {
		string startWord = getLine("Enter the starting word: ");
		string endWord = getLine("Enter the ending word: ");
		Vector<string> result = WordLadder(startWord, endWord);
		if (result.isEmpty())
			cout << "Search Failed." << endl;
		else {
			Vector<string>::iterator it;
			cout << "Found ladder: ";
			for (it = result.begin(); it != result.end(); it++)
				cout << *it << " ";
			cout << endl;
		}
	}
    return 0;
}

Vector<string> WordLadder(string initWord, string tarWord) {
	// Create queue containing string vectors for breadth-first search
	Queue<Vector<string> > bfsq;
	// Create string vector for deQ
	Vector<string> vec;
	// Lexicon containing all the used words
	Lexicon lex;
	Lexicon wordlist("EnglishWords.dat");
	vec.add(initWord);
	bfsq.enqueue(vec);
	lex.add(initWord);

	// Keep searching while the queue is not empty
	while (!bfsq.isEmpty()) {
		// DeQ the first vector
		vec = bfsq.dequeue();

		// If the last word in the vector is the target, finish searching
		if (vec.get(vec.size()-1) == tarWord)
			return vec;
		else {
			// Loop every word in the list until find the word or fail
			foreach (string wrd in wordlist) {
				Vector<string> tmp = vec;
				string lastword = vec.get(vec.size()-1);
				// If the length of the word is the same as the given word, and it is not used,
				// make it a new node in the search tree
				if ((wrd.length() == initWord.length()) && (!lex.contains(wrd))) {
					int flag = 0;
					// Count the number of different chars in two words
					for (unsigned i = 0; i < wrd.length(); i++) {
						if (wrd[i] != lastword[i])
							flag++;
					}
					// If only one char is different, add the word to the vector and enQ the vector,
					// also add the word to the used-words lexicon
					if (flag == 1) {
						tmp.add(wrd);
						lex.add(wrd);
						bfsq.enqueue(tmp);
					}
				}
			}
		}
	}
	vec.clear();
	return vec;
}