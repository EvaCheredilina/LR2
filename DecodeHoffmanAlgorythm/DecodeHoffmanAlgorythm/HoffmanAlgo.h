#pragma once
#include"List.h"
#include"Map.h"
#include"Pair.h"
#include<string>

class Node {
public:
	Node(Pair<char, int> value = Pair<char, int>(), Node* left = NULL, Node* right = NULL)
		:value(value), left(left), right(right) {}
	Pair<char, int> value;
	Node* left;
	Node* right;
};

class HoffmanCodingAlgorythm
{
private:
	Node* treeRoot;
	List<Pair<char, int>>* frequencyList;
	friend class Node;


	void commitDecoding(Node* root, string& codingString, string& decoding_str, int& position) {
		if (codingString.size() > position) {
			while (root->right != NULL && root->left != NULL) {
				if (codingString[position] == '0')
					root = root->left;
				else
					root = root->right;
				position++;
			}
			decoding_str += root->value.first;
			if (treeRoot->left == NULL && treeRoot->right == NULL)
				position++;
			commitDecoding(treeRoot, codingString, decoding_str, position);
		}
	}

	void constructTree(List<Node>* treeNodesList) {
		treeRoot = NULL;
		if (treeNodesList->get_size() <= 1)
		{
			treeRoot = new Node(
				Pair<char, int>(treeNodesList->at(0).value.first, treeNodesList->at(0).value.second)
			);
		}
		else
		{
			while (treeNodesList->get_size() != 0) {
				Node* currentNode = new Node();
				currentNode->left = new Node(treeNodesList->at(0));
				currentNode->right = new Node(treeNodesList->at(1));
				currentNode->value.second = treeNodesList->at(0).value.second + treeNodesList->at(1).value.second;
				treeNodesList->pop_front();
				treeNodesList->pop_front();

				int i = 0;
				for (; i < treeNodesList->get_size() && treeNodesList->at(i).value.second < currentNode->value.second; i++);

				if (treeNodesList->get_size() != 0 && treeNodesList->get_size() != i)
					treeNodesList->insert(*currentNode, i);
				else if (treeNodesList->get_size() == i && treeNodesList->get_size() != 0)
					treeNodesList->push_back(*currentNode);

				if (treeNodesList->get_size() == 0) {
					treeRoot = currentNode;
				}
			}
		}
	}

	void codeGen(Map<char, string>* hoffman, Node* root, string cur) {
		if (treeRoot->left != NULL && treeRoot->right != NULL) {
			if (root->left != NULL && root->right != NULL) {
				codeGen(hoffman, root->left, cur + '0');
				codeGen(hoffman, root->right, cur + '1');
			}
			else
			{
				hoffman->insert(root->value.first, cur);
			}
		}
		else {
			hoffman->insert(root->value.first, cur + '0');
		}
	}

public:
	HoffmanCodingAlgorythm(string str) {
		Map<char, int>* frequencyMap = new Map<char, int>();

		for (int i = 0; i < str.size(); i++) {
			if(frequencyMap->contains(str[i]) == false) frequencyMap->insert(str[i], 1);
			else frequencyMap->increment_value(str[i]);
		}
		
		frequencyList = frequencyMap->getPairs();

		frequencyList->sort();

		List<Node>* treeNodesList = new List<Node>();
		for (int i = 0; i < frequencyList->get_size(); i++)
			treeNodesList->push_back(Node(frequencyList->at(i)));

		constructTree(treeNodesList);
	}
	List<Pair<char, int>>* get_list_symbol() {
		return frequencyList;
	}
	Map<char, string>*& getTreeAsCode() {
		Map<char, string>* hoffman = new Map<char, string>();
		string currentString;
		codeGen(hoffman, treeRoot, currentString);
		return hoffman;
	}
	string decode(string& coding_str) {
		string decoding_str;
		int pos = 0;
		commitDecoding(treeRoot, coding_str, decoding_str, pos);
		return decoding_str;
	}
};