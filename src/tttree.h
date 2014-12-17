#ifndef TTTREE_H
#define TTTREE_H

#define EMPTY 0

template <class Elem>
class TTNode {       // 2-3 tree node structure
public:
	Elem lkey;
	Elem rkey;
	TTNode* left;
	TTNode* center;
	TTNode* right;
	TTNode()
	{
		center = left = right = NULL; lkey = rkey = EMPTY;
	}
	~TTNode() { }
	bool isLeaf() { return left == NULL; }
};

template<class Key, class Elem>
class TTTree{
public:
	bool inserthelp(TTNode<Elem>*& subroot, const Elem& e, Elem& retval, TTNode<Elem>*& retptr);
	bool splitnode(TTNode<Elem>* subroot, const Elem& inval, TTNode<Elem>*inptr, Elem& retval, TTNode<Elem>*& retptr);
	bool insert(const Elem& e);
	void bfs(vector<Elem> *res);
	TTTree() { root = NULL; }
private:
	TTNode<Elem> *root;
};

template <class Key, class Elem>
bool TTTree<Key, Elem>::inserthelp(TTNode<Elem>*& subroot, const Elem& e, Elem& retval, TTNode<Elem>*& retptr) {
	Elem myretv;
	TTNode<Elem>* myretp = NULL;
	if (subroot == NULL){                      // Empty tree: make new node
		subroot = new TTNode<Elem>();
		subroot->lkey = e;
	}
	else if (subroot->isLeaf()){                // At leaf node: insert here
		if (subroot->rkey == EMPTY) {    // Easy case: not full
			if (subroot->lkey < e)
				subroot->rkey = e;
			else {
				subroot->rkey = subroot->lkey;
				subroot->lkey = e;
			}
		}
		else splitnode(subroot, e, NULL, retval, retptr);
	}
	else if (e < subroot->lkey) {      // Insert in left child
		inserthelp(subroot->left, e, myretv, myretp);
	}
	else if ((subroot->rkey == EMPTY) || (e < subroot->rkey)){
		inserthelp(subroot->center, e, myretv, myretp);
	}
	else {
		inserthelp(subroot->right, e, myretv, myretp);
	}

	if (myretp != NULL){
		if (subroot->rkey != EMPTY){  // Full: split node
			splitnode(subroot, myretv, myretp, retval, retptr);
		}
		else { // Not full: add to this node
			if (myretv < subroot->lkey) {
				subroot->rkey = subroot->lkey;
				subroot->lkey = myretv;
				subroot->right = subroot->center;
				subroot->center = myretp;
			}
			else{
				subroot->rkey = myretv; subroot->right = myretp;
			}
		}

		return true;
	}
}

template <class Key, class Elem>
bool TTTree<Key, Elem>::splitnode(TTNode<Elem>* subroot, const Elem& inval, TTNode<Elem>*inptr, Elem& retval, TTNode<Elem>*& retptr){
	retptr = new TTNode<Elem>();                 // Node created by split
	if (inval < subroot->lkey) {     // Add at left
		retval = subroot->lkey;                    subroot->lkey = inval;
		retptr->lkey = subroot->rkey;         retptr->left = subroot->center;
		retptr->center = subroot->right;     subroot->center = inptr;
	}
	else if (inval < subroot->rkey) {   // Center
		retval = inval;                      retptr->lkey = subroot->rkey;
		retptr->left = inptr;            retptr->center = subroot->right;
	}
	else {    // Add at right
		retval = subroot->rkey;                retptr->lkey = inval;
		retptr->left = subroot->right;       retptr->center = inptr;
	}
	subroot->rkey = EMPTY;
	return true;
}
template <class Key, class Elem>
bool TTTree<Key, Elem>::insert(const Elem& e) { // Insert node with value val
	Elem retval;               // Smallest value in newly created node
	TTNode<Elem>* retptr = NULL; // Newly created node
	bool inssucc = inserthelp(root, e, retval, retptr);
	if (retptr != NULL) {      // Root overflowed: make new root
		TTNode<Elem>* temp = new TTNode<Elem>;  temp->lkey = retval;
		temp->left = root; temp->center = retptr;
		root = temp;
	}
	return inssucc;
}

template <class Key, class Elem>
void TTTree<Key, Elem>::bfs(vector<Elem> *res)
{
	if (root == NULL) return;
	queue<TTNode<Elem>*> q;

	q.push(root);
	while (!q.empty()){
		if (q.front()->lkey != EMPTY) res->push_back(q.front()->lkey);
		if (q.front()->rkey != EMPTY) res->push_back(q.front()->rkey);
		if (q.front()->left != NULL) q.push(q.front()->left);
		if (q.front()->center != NULL) q.push(q.front()->center);
		if (q.front()->right != NULL) q.push(q.front()->right);
		q.pop();
	}
}


#endif