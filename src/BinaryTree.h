#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include<iostream>
#include "dictionary.h"

using std::cout;
using std::endl;

//Binary tree node abstract class
template<typename E> class BinNode{
public:
	virtual ~BinNode(){}
	virtual E& element() = 0;
	virtual void setElement(const E&) = 0;
	virtual BinNode* left() const = 0;
	virtual void setLeft(BinNode*) = 0;
	virtual BinNode* right() const = 0;
	virtual void setRight(BinNode*) = 0;
	virtual bool isLeaf() = 0;
};

//Simple binary tree node class
template<typename Key, typename E>
class BSTNode :public BinNode<E>{
private:
	Key k;
	E it;
	BSTNode *lc, *rc;
public:
	BSTNode(){ lc = rc = NULL; }
	BSTNode(Key K, E e, BSTNode* l = NULL, BSTNode* r = NULL){
		k = K;
		it = e;
		lc = l;
		rc = r;
	}
	~BSTNode(){}

	E& element(){ return it; }
	void setElement(const E& e){ it = e; }
	Key& key(){ return k; }
	void setKey(const Key& K){ k = K; }

	inline BSTNode* left() const { return lc; }
	void setLeft(BinNode<E>* b){ lc = (BSTNode*)b; }
	inline BSTNode* right() const{ return rc; }
	void setRight(BinNode<E>* b){ rc = (BSTNode*)b; }

	bool isLeaf(){ return (lc == NULL) && (rc == NULL); }
};

//Binary Search Tree implementation for the Dictionary ADT
template<typename Key, typename E>
class BST : public Dictionary<Key, E> {
private:
	BSTNode<Key, E> *root;
	int nodecount;

	//private "helper" functions
	void clearhelp(BSTNode<Key, E>*);
	BSTNode<Key, E>* inserthelp(BSTNode<Key, E>*, const Key&, const E&);
	BSTNode<Key, E>* deletemin(BSTNode<Key, E>*);
	BSTNode<Key, E>* getmin(BSTNode<Key, E>*);
	BSTNode<Key, E>* removehelp(BSTNode<Key, E>*, const Key&);
	E findhelp(BSTNode<Key, E>*, const Key&) const;
	void printhelp(BSTNode<Key, E>*, int) const;

public:
	BST(){ root = NULL; nodecount = 0; }
	~BST(){ clearhelp(root); }

	void clear(){
		clearhelp(root);
		root = NULL;
		nodecount = 0;
	}
	
	//insert a record into the tree.
	//k Key value of the record.
	//e The value to insert.
	void insert(const Key& k, const E& e){
		root = inserthelp(root, k, e);
		nodecount++;
	}

	//remove a record from the tree.
	//k Key value of record to remove.
	//return: the record removed , or null if there is none.
	E remove(const Key& k){
		E temp = findhelp(root, k);
		if (temp != NULL){
			root = removehelp(root, k);
			nodecount--;
		}
		return temp;
	}

	//remove and return the root node from the dictionary.
	//return : the record removed, null if tree is empty.
	E removeAny(){ //delete min value
		if (root != NULL){
			E temp = root->element();
			root = removehelp(root, root->key());
			nodecount--;
			return temp;
		}
		else return NULL;
	}

	// return record with key value k, NULL if none exist.
	// k: the key value to find.
	// return some record matching "k"
	// return true if such exists, false otherwise.
	// if multiple records match "k", return an arbitrary one.
	E find(const Key& k) const { return findhelp(root, k); }

	//return the number of records in the dictionary.
	int size(){ return nodecount; }
	void print() const {
		if (root == NULL) cout << "The BST is empty.\n";
		else printhelp(root, 0);
	}

	void printRange(BSTNode<Key, E> *rt, int low, int high);

	BSTNode<Key, E>* printRoot(){ return root; }
};

//打印某一范围的数值、
//递归实现，若当前节点值大于最大值则往左找，若小于最小值则往右找
template<typename Key, typename E>
void BST<Key, E>::printRange(BSTNode<Key, E> *rt, int low, int high){ //参数为根节点指针和数值范围

	if (rt == NULL) return;
	if (high < rt->element())
		printRange(rt->left(), low, high);
	else if (low > rt->element())
		printRange(rt->right(), low, high);
	else{
		printRange(rt->left(), low, high);
		cout << rt->element(); 
		printRange(rt->right(), low, high);
	}
}

template<typename Key, typename E>
E BST<Key, E>::findhelp(BSTNode<Key, E>* root, const Key& k) const{
	if (root == NULL) return NULL;
	if (k < root->key())
		return findhelp(root->left(), k);
	else if (k > root->key())
		return findhelp(root->right(), k);
	else return root->element();
}

template<typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::inserthelp(BSTNode<Key, E>* root, const Key& k, const E& it){
	if (root == NULL)	//Empty tree : create node
		return new BSTNode<Key, E>(k, it, NULL, NULL);
	if (k < root->key())
		root->setLeft(inserthelp(root->left(), k, it));
	else root->setRight(inserthelp(root->right(), k, it));
	return root;		//return the tree with node inserted
}

template<typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::deletemin(BSTNode<Key, E>* rt){
	if (rt->left() == NULL)
		return rt->right();
	else {
		rt->setLeft(deletemin(rt->left()));
		return rt;
	}
}

template<typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::getmin(BSTNode<Key, E>* rt){
	if (rt->left() == NULL)
		return rt;
	else return getmin(rt->left());
}

//remove a node with key value k
//return: the tree with the node removed
template<typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::removehelp(BSTNode<Key, E>*rt, const Key& k){
	if (rt == NULL) return NULL;
	else if (k < rt->key())
		rt->setLeft(removehelp(rt->left(), k));
	else if (k > rt->key())
		rt->setRight(removehelp(rt->right(), k));
	else{
		BSTNode<Key, E>* temp = rt;
		if (rt->left() == NULL){
			rt = rt->right();
			delete temp;
		}
		else if(rt->right() == NULL){
			rt = rt->left();
			delete temp;
		}
		else{
			BSTNode<Key, E>* temp = getmin(rt->right());
			rt->setElement(temp->element());
			rt->setKey(temp->key());
			rt->setRight(deletemin(rt->right()));
			delete temp;
		}
	}
	return rt;
}

template<typename Key, typename E>
void BST<Key, E>::clearhelp(BSTNode<Key, E>* root){
	if (root == NULL) return;
	clearhelp(root->left());
	clearhelp(root->right());
	delete root;
}

template<typename Key, typename E>
void BST<Key, E>::printhelp(BSTNode<Key, E>* root, int level) const{
	if (root == NULL) return;
	printhelp(root->left(), level + 1);
	for (int i = 0; i < level; i++) cout << "  ";
	cout << root->key() << endl;
	printhelp(root->right(), level + 1);
}

//Node implementation with simple inheritance

//Node abstract base class 
//class VarBinNode{
//public :
//	virtual ~VarBinNode(){}
//	virtual bool isLeaf() = 0;
//};
//
//class LeafNode : public VarBinNode{
//private:
//	Operand var;
//
//public :
//	LeafNode(const Operand& val){ var = val; }
//	bool isLeaf(){ return true; }
//	Operand value(){ return var; }
//};
//
//class IntlNode : public VarBinNode{
//private:
//	VarBinNode* left;
//	VarBinNode* right;
//	Operator opx;
//
//public:
//	IntlNode(const Operator& op, VarBinNode* l, VarBinNode* r){
//		opx = op;
//		left = l;
//		right = r;
//	}
//
//	bool isLeaf() { return false; }
//	VarBinNode* leftchild(){ return left; }
//	VarBinNode* rightchild() { return right; }
//	Operator value(){ return opx; }
//};
//
//void traverse(VarBinNode *root){
//	if (root == NULL) return;
//	if (root->isLeaf())
//		cout << "Leaf: " << ((LeafNode *)root)->value() << endl;
//	else{
//		cout << "Intenal: " << ((IntlNode *)root)->value() << endl;
//		traverse(((IntlNode *)root)->leftchild());
//		traverse(((IntlNode *)root)->rightchild());
//	}
//}
/*
//Node implementation with the composite design pattern
class VarBinNode{
public :
	virtual ~VarBinNode(){}
	virtual bool isLeaf() = 0;
	virtual void traverse() = 0;
};

class LeafNode : public VarBinNode{
private:
	Operand var;

public:
	LeafNode(const Operand& val){ var = val; }
	bool isLeaf(){ return true; }
	Operand value(){ return var; }
	void traverse(){ cout << "Leaf: " << value() << endl; }
};

class IntlNode : public VarBinNode{
private:
	VarBinNode* lc;
	VarBinNode* rc;
	Operator opx;

public:
	IntlNode(const Operator& op.VarBinNode* l, VarBinNode* r){
		opx = op;
		lc = l;
		rc = r;
	}
	bool isLeaf(){ return false; }
	VarBinNode* left(){ return lc; }
	VarBinNode* right(){ return rc; }
	Operator value(){ return opx; }

	void traverse(){
		cout << "Internal : " << value() << endl;
		if (left() != NULL) left()->traverse();
		if (right() != NULL) right()->traverse();
	}
};

//Do a pre-order traversal
void traverse(VarBinNode* root){
	if (root != NULL) root->traverse();
}
*/
#endif