#ifndef NODE_BST_H
#define NODE_BST_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <limits.h>

using namespace std;

class Node{
	private:
		int key;
		Node *left, *right, *parent;
	public:
		Node(int key){
			this->key = key;
			left = right = parent = NULL;
		}
		
		Node(){
			key = 0;
			left = right = parent = NULL;
		}
		
		int getKey() const { return key; }
		Node *getLeft() const { return left; }
		Node *getRight() const { return right; }
		Node *getParent() const { return parent; }
		
		void setKey(int key) { this->key = key; }
		void setLeft(Node *left) { this->left = left; }
		void setRight(Node *right) { this->right = right; }
		void setParent(Node *parent) { this->parent = parent; }
};

//<<>>

#endif
