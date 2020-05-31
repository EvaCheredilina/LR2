#include<iostream>
#include"Map.h"
#include<string>
#include"HoffmanAlgo.h"
using namespace std;

int main() {

	string inputString;
	cout << "String for coding: ";
	getline(cin, inputString);

	HoffmanCodingAlgorythm* hoffmanAlgo = new HoffmanCodingAlgorythm(inputString);
	Map<char, string>* codedLetters = hoffmanAlgo->getTreeAsCode();

	int counter = 0;
	List<Pair<char, int>>* inputSymbols = hoffmanAlgo->get_list_symbol();


	for (int i = 0; i < inputSymbols->get_size(); i++)
		cout << "Symbol: " << inputSymbols->at(i).first << " "
		<< "Code: " << codedLetters->find(inputSymbols->at(i).first) << " "
		<< "Frequency: " << inputSymbols->at(i).second << endl;

	cout << "Coded string: ";

	string codedString;

	for (int i = 0; i < inputString.size(); i++) {
		codedString += codedLetters->find(inputString[i]);
		cout << codedLetters->find(inputString[i]);
		counter += codedLetters->find(inputString[i]).size();
	}
	cout << endl;

	string decodedString = hoffmanAlgo->decode(codedString);

	cout << "Decoded string: " << decodedString << endl;

	cout << "Compression coefficient is " << (((double)(decodedString.size() * 8) / (codedString.size())));
	delete hoffmanAlgo;
	return 0;
}