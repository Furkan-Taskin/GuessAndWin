#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

class Dictionary {
private:
	bool testIfWordSecret(string word);
	set <string> words;
	vector <string> secrets;

public:
	Dictionary();
	~Dictionary();
	Dictionary(char* filename) {
		fstream dataFile;
		string temp;
		dataFile.open(filename, ios::in);
		dataFile >> temp;
		while (!dataFile.eof()) {
			words.insert(temp);
			dataFile >> temp;
		}
	}
	string takeRandValWord() { // this brings random valid words
		string word;
		int flag = 0;
		srand(time(NULL));
		for (set<string>::iterator it = words.begin(); it != words.end(); it++) {
			word = *it;
			if (testIfWordSecret(word) == false) {
				secrets.push_back(word);
			}
		}
		int randomNum = rand() % secrets.size();
		cout << "The secret word: "<< secrets[randomNum] << endl << "-----------------------" << endl;
		word = secrets[randomNum];
		return word;
	}
	bool isWordValid(string word) {
		string temp;
		int flag = 0;
		for (set<string>::iterator it = words.begin(); it != words.end(); it++) {
			temp = *it;
			if (temp == word) {
				flag = 1;
				break;
			}
			else
				flag = 0;
		}
		return flag;
	}
};
Dictionary::Dictionary() {
	bool testIfWordSecret(string word = NULL);
}
bool Dictionary::testIfWordSecret(string word) {
	int flag = 0;
	for (int i = 0; i < word.size(); i++) {
		for (int j = i + 1; j < word.size(); j++) {
			if (word[i] == word[j])
				flag = 1;
		}
	}
	return flag;
}
class Words : public Dictionary {
private:
	int countOfMatchLetters(string); // compare letters and just one time	
	int countOfTruePlaceLetters(string);
	int numOfGuesses;
	bool cheated;
	string secret;

public:
	Words();
	~Words();
	void playgame(Words&);
};
Words::Words() {
	numOfGuesses = 0;
	cheated = false;
	secret = '\0';
}
int Words::countOfMatchLetters(string guess) {
	int counter = 0;
	for (int i = 0; i < guess.size(); i++) {
		for (int j = 0; j < guess.size(); j++) {
			if (secret[i] == guess[j]) {
				counter++;
				break;
			}
		}
	}
	return counter;
}
int Words::countOfTruePlaceLetters(string guess) {
	int counter = 0;
	for (int i = 0; i < guess.size(); i++) {
		if (secret[i] == guess[i]) {
			counter++;
		}
	}
	return counter;
}
void Words::playgame(Words& a) {
	char filename[] = "words.txt";
	Dictionary d1(filename);
	secret = d1.takeRandValWord();;
	string guess;
	cout << "\t\t~~~ Welcome to Guess & Win game! ~~~" << endl;
	cout << "\t  I kept a word with 5 letters. Try to guess it!" << endl;
	while (1) {
		cout << endl << "What is your guess? ";
		getline(cin, guess);
		if (guess == "xxxxx") {
			cout << "Hint: The Secret Word: " << secret << endl;
			numOfGuesses++;
			cheated = true;
		}
		else if (d1.isWordValid(guess) == false) {
			cout << "The word is not in the dictionary!" << endl;
		}
		else {
			numOfGuesses++;
			if (d1.isWordValid(guess) == true) {
				if (guess == secret) {
					cout << "You knew it with " << numOfGuesses << " tries! ";
					if (cheated == true)
						cout << "(with the hint)" << endl;
					break;
				}
			}
			cout << "Number of matching letters: " << countOfMatchLetters(guess) << endl;
			cout << "The correct position of the matching letters: " << countOfTruePlaceLetters(guess) << endl;
		}
	}
}
Dictionary::~Dictionary() {}
Words::~Words() {}
int main() {
	Words w1;
	w1.playgame(w1);
	cout << endl << endl;
	system("pause");
	return 0;
}