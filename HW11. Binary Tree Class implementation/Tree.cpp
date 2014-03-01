
#include <iostream>
using namespace std;
class Node {
public:
	int key;
	Node *left;
	Node *right;
	Node *parent;
	Node()
	{
		parent = NULL;
		left = NULL;
		right = NULL;
	} 
	Node(int KEY)
	{
		parent = NULL;
		left = NULL;
		right = NULL;
		key = KEY;
	}
};

class Tree {
public:
	Node *root;
	Tree() {
		root = NULL;
	}
	void insert(Tree *t, Node *z) {
		Node *y = NULL;
		Node *x = t->root;
		while(x != NULL) {
			y = x;
			if(z->key < x->key) {
				x = x ->left;
			} else {
				x = x->right;
			}
		}
		z->parent = y;
		if(y == NULL) {
			t->root = z;
		} else {
			if(z->key < y->key) {
				y->left = z;
			} else {
				y->right = z;
			}
		}
	}

	void directWalk(Node *x) {
		if(x != NULL ) {
			cout << x->key << " ";
			walkTree(x->left);
			walkTree(x->right);
		}
	}

	void walkTree(Node *x) {
		if( x != NULL) {
			walkTree(x->left);
			cout << x ->key << " ";
			walkTree(x->right);
		}
	}

	void backWalk(Node *x) {
		if(x != NULL) {
			backWalk(x->right);
			cout << x ->key << " ";
			backWalk(x -> left);
		}
	}
	Node* search(Node *x, int KEY) {
		if( x == NULL || KEY == x->key) 
			return x;
		if(KEY != (x -> key)) {
			if(x->key < KEY && x->right != NULL) return search(x->right, KEY); 
			if(x->key > KEY && x->left != NULL) return search(x->left, KEY); 
		}
	}
	Node* minimum(Node *x) 	{
		while (x->left != NULL)
		{
			x = x->left;
		}
		return x;
	}

	Node* maximum(Node *x) 	{
		while (x -> right != NULL)
		{
			x = x->right;
		}
		return x;
	}

	Node* predecessor(Node *x) {
		Node *y = new Node();
		if( x->left != NULL ) {
			return maximum( x->left);
		}
		y = x -> parent;
		while( y!= NULL && x == y ->left) {
			x = y;
			y = y -> parent;
		}
		return y;
	}

	Node* successor(Node *x) {
		Node *y = new Node();
		if (x -> right != NULL)
		{
			return minimum(x->right);
		}
		y = x -> parent;
		while (y != NULL && x == y -> right)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}
	void print(Node* root) {
		if (root != NULL) {
			print(root->left);
			cout<<root->key<<" ";			
			print(root->right);
		}
	}
	Node* remove(Tree *t, Node *z) 	{
		Node *x = t->root;
		Node *y = NULL;
		if (z->left== NULL || z->right== NULL) {
			y = z;
		} else {
			y = successor(z);
		}
		if (y->left != NULL) {
			x = y->left;
		} else {
			x = y->right;
		}
		if (x != NULL) {
			x->parent = y->parent;
		}
		if (y->parent == NULL) {
			t->root= x;
		}
		else if (y == y->parent->left) {
			y->parent->left= x;
		} else {
			y->parent->right= x;
		}
		if (y != z) {
			z->key= y->key;
		}
		return y;
	}
};

void main() {
Tree *t = new Tree();
for(int i = 0; i < 10; i++) {
t->insert(t, new Node(i));
}
t->print(t->root);
system("pause");
cout << endl;
Node *n = new Node(7);
t->insert(t, n);
t->print(t->root);
system("pause");
cout << endl;
t->remove(t,n);
t->print(t->root);
system("pause");
cout << endl;

}