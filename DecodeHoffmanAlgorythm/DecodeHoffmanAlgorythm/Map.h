#pragma once
#define COLOR_RED 1
#define COLOR_BLACK 0
#include"List.h"
#include"Pair.h"
using namespace std;
template<class T, class T1>
class Map {
public:
	class Node
	{
	public:
		Node(bool color = COLOR_RED, T key = T(), Node* parent = NULL, Node* left = NULL, Node* right = NULL, T1 value = T1()) :color(color), key(key), parent(parent), left(left), right(right), value(value) {}
		T key;
		T1 value;
		bool color;
		Node* parent;
		Node* left;
		Node* right;
	};
	~Map() {
		if (this->Top != NULL)
			this->clear();
		Top = NULL;
		delete TNULL;
		TNULL = NULL;
	}
	Map(Node* Top = NULL, Node* TNULL = new Node(0)) :Top(TNULL), TNULL(TNULL) {}
	void increment_value(T key) {
		Node* cur = this->find_value(key);
		cur->value++;
	}
	void printTree()
	{
		if (Top)
		{
			print_Helper(this->Top, "", true);
		}
		else throw std::out_of_range("Tree is empty!");
	}
	
	void insert(T key, T1 value)
	{

		if (this->Top != TNULL) {
			Node* node = NULL;
			Node* parent=NULL;
			/* Search leaf for new element */
			for (node = this->Top; node != TNULL; )
			{
				parent = node;
				if (key < node->key)
					node = node->left;
				else if (key > node->key)
					node = node->right;
				else if (key == node->key)
					throw std::out_of_range("key is repeated");
			}

			node = new Node(COLOR_RED, key, TNULL, TNULL, TNULL, value);
			node->parent = parent;


			if (parent != TNULL) {
				if (key < parent->key)
					parent->left = node;
				else
					parent->right = node;
			}
			rbtree_fixup_add(node);
		}
		else {
			this->Top = new Node(COLOR_BLACK, key, TNULL, TNULL, TNULL, value);
		}
	}
	List<T>* getKeys() {
		List<T>* list = new List<T>();
		this->ListKey(Top,list);
		return list;
	}
	List<T1>* getValues() {
		List<T1>* list = new List<T1>();
		this->ListValue(Top, list);
		return list;
	}
	List<Pair<T, T1>>* getPairs() {
		List<Pair<T, T1>>* list = new List<Pair<T,T1>>();
		this->ListPairs(Top, list);
		return list;
	}
	T1 find(T key) {
		Node* node = Top;

		while (node != TNULL && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != TNULL)
			return node->value;
		else
			throw std::out_of_range("Key is missing");
	}
	bool contains(T key) {
		Node* node = Top;

		while (node != TNULL && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != TNULL)
			return true;
		else
			return false;
	}
	void remove(T key) {
		this->deleteNodeHelper(this->find_key(key));
	}
	
	void clear() {
		this->clear_tree(this->Top);
		this->Top = NULL;
	}
private:
	Node* Top;
	Node* TNULL;
	Node* find_value(T key) {
		Node* node = Top;

		while (node != TNULL && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != TNULL)
			return node;
		
	}
/////////////////////////////////////////////////////////////////////////
	//delete functions
////////////////////////////////////////////////////////////////////////
	void deleteNodeHelper(Node* find_node)
	{
		Node* node_with_fix, * cur_for_change;
		cur_for_change = find_node;
		bool cur_for_change_original_color = cur_for_change->color;
		if (find_node->left == TNULL)
		{
			node_with_fix = find_node->right;
			Transplant(find_node, find_node->right);
		}
		else if (find_node->right == TNULL)
		{
			node_with_fix = find_node->left;
			Transplant(find_node, find_node->left);
		}
		else

		{
			cur_for_change = minimum(find_node->right);
			cur_for_change_original_color = cur_for_change->color;
			node_with_fix = cur_for_change->right;
			if (cur_for_change->parent == find_node)
			{
				node_with_fix->parent = cur_for_change;
			}
			else
			{
				Transplant(cur_for_change, cur_for_change->right);
				cur_for_change->right = find_node->right;
				cur_for_change->right->parent = cur_for_change;
			}
			Transplant(find_node, cur_for_change);
			cur_for_change->left = find_node->left;
			cur_for_change->left->parent = cur_for_change;
			cur_for_change->color = find_node->color;
		}
		delete find_node;
		if (cur_for_change_original_color == COLOR_BLACK)
		{
			this->rbtree_fixup_add(node_with_fix);
		}
	}
	void Transplant(Node* cur, Node* cur1)
	{
		if (cur->parent == TNULL)
		{
			Top = cur1;
		}
		else if (cur == cur->parent->left)
		{
			cur->parent->left = cur1;
		}
		else
		{
			cur->parent->right = cur1;
		}
		cur1->parent = cur->parent;
	}


	void clear_tree(Node* tree) {
		if (tree != TNULL) {
			clear_tree(tree->left);
			clear_tree(tree->right);
			delete tree;
		}
	}

	Node* minimum(Node* node)
	{
		while (node->left != TNULL)
		{
			node = node->left;
		}
		return node;
	}
	Node* maximum(Node* node)
	{
		while (node->right != TNULL)
		{
			node = node->right;
		}
		return node;
	}
	Node* grandparent(Node* cur)
	{
		if ((cur != TNULL) && (cur->parent != TNULL))
			return cur->parent->parent;
		else
			return TNULL;
	}
	Node* uncle(Node* cur)
	{
		Node* cur1 = grandparent(cur);
		if (cur1 == TNULL)
			return TNULL;
		if (cur->parent == cur1->left)
			return cur1->right;
		else
			return cur1->left;
	}
	Node* sibling(Node* n)
	{
		if (n == n->parent->left)
			return n->parent->right;
		else
			return n->parent->left;
	}
	Node* find_key(T key) {
		Node* node = this->Top;
		while (node != TNULL && node->key != key) {
			if (node->key > key)
				node = node->left;
			else
				if (node->key < key)
					node = node->right;
		}
		if (node != TNULL)
			return node;
		else
			throw std::out_of_range("Key is missing");
	}
	void print_Helper(Node* root, string indent, bool last)
	{
		if (root != TNULL)
		{
			cout << indent;
			if (last)
			{
				cout << "R----";
				indent += "   ";
			}
			else
			{
				cout << "L----";
				indent += "|  ";
			}
			string sColor = !root->color ? "BLACK" : "RED";
			cout << root->key << "(" << sColor << ")" << endl;
			print_Helper(root->left, indent, false);
			print_Helper(root->right, indent, true);
		}
	}
void ListValue(Node* tree, List<T1>* list){
	if (tree != TNULL) {
		ListValue(tree->left, list);
		list->push_back(tree->value);
		ListValue(tree->right, list);
	}
}
void ListKey(Node* tree, List<T>* list) {
	if (tree != TNULL) {
		ListKey(tree->left, list);
		list->push_back(tree->key);
		ListKey(tree->right, list);
	}
}
void ListPairs(Node* tree, List<Pair<T,T1>>* list) {
	if (tree != TNULL) {
		ListPairs(tree->left, list);
		Pair<T, T1> cur(tree->key, tree->value);
		list->push_back(cur);
		ListPairs(tree->right, list);
	}
}

	void rbtree_fixup_add(Node* node)
	{
		Node* uncle;
		while (node != this->Top && node->parent->color == COLOR_RED)
		{
			if (node->parent == this->grandparent(node)->left)
			{
				uncle = this->uncle(node);
				if (uncle->color == COLOR_RED) {
					node->parent->color = COLOR_BLACK;
					uncle->color = COLOR_BLACK;
					this->grandparent(node)->color = COLOR_RED;
					node = this->grandparent(node);
				}
				else {
					if (node == node->parent->right) {
						node = node->parent;
						this->left_rotate(node);
					}
					node->parent->color = COLOR_BLACK;
					this->grandparent(node)->color = COLOR_RED;
					this->right_rotate(this->grandparent(node));
				}
			}
			else {
				uncle = this->uncle(node);
				if (uncle->color == COLOR_RED) {
					node->parent->color = COLOR_BLACK;
					uncle->color = COLOR_BLACK;
					this->grandparent(node)->color = COLOR_RED;
					node = this->grandparent(node);
				}
				else {
					if (node == node->parent->left) {
						node = node->parent;
						this->right_rotate(node);
					}
					node->parent->color = COLOR_BLACK;
					this->grandparent(node)->color = COLOR_RED;
					this->left_rotate(this->grandparent(node));
				}
			}
		}
		this->Top->color = COLOR_BLACK;
	}
	void left_rotate(Node* node)
	{
		Node* right = node->right;
		node->right = right->left;
		if (right->left != TNULL)
			right->left->parent = node;
		if (right != TNULL)
			right->parent = node->parent;
		if (node->parent != TNULL) {
			if (node == node->parent->left)
				node->parent->left = right;
			else
				node->parent->right = right;
		}
		else {
			this->Top = right;
		}
		right->left = node;
		if (node != TNULL)
			node->parent = right;
	}
	void right_rotate(Node* node)
	{
		Node* left = node->left;
		node->left = left->right;
		if (left->right != TNULL)
			left->right->parent = node;
		if (left != TNULL)
			left->parent = node->parent;
		if (node->parent != TNULL) {
			if (node == node->parent->right)
				node->parent->right = left;
			else
				node->parent->left = left;
		}
		else {
			this->Top = left;
		}
		left->right = node;
		if (node != TNULL)
			node->parent = left;
	}
}; 
