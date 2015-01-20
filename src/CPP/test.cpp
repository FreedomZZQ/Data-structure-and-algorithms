#include <iostream>
#include <string>
#include "list.h"
#include "BinaryTree.h"
#include "sort.h"
using namespace std;

int main()
{
	
	/*BST<int, int> *tree = new BST<int, int>;
	for (int i = 0; i < 10; i++){
	tree->insert(i, i + 10);
	}

	BSTNode<int, int> *temp = tree->printRoot();
	tree->printRange(temp, 13, 16);*/

	int a[50];
	for (int i = 0; i < 50; i++){
		a[i] = 50 - i;
		cout << a[i] << endl;
	}
	//bubsort(a, 50);
	//selsort(a, 50);
	qsort(a, 0, 49);
	for (int i = 0; i < 50; i++){
		cout << a[i] << endl;
	}
	return 0;
}
