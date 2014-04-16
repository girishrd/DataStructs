#include <iostream>
#define DEBUG
using namespace std;
/*Original source: http://www.sourcetricks.com/2011/06/binary-search-trees-in-c.html
Comments: Templatized version 
*/

// A generic tree node class
template<typename T>
class Node {
   
    
public:
	 T key;
	Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
	//def ctor
	Node() {
	cout<<"In def ctor for Node()"<<endl;	
	left=NULL; right=NULL; parent = NULL;
	key=0;
	
	}//{ key=-1; };
    void setKey(T aKey) { key = aKey; };
    void setLeft(Node* aLeft) { left = aLeft; };
    void setRight(Node* aRight) { right = aRight; };
    void setParent(Node* aParent) { parent = aParent; };
    T Key() { return key; };
    Node* Left() { return left; };
    Node* Right() { return right; };
    Node* Parent() { return parent; };
};

// Binary Search Tree class
template<typename T>
class Tree {
    Node<T>* root;
public:
    Tree();
    ~Tree();
    Node<T>* Root() { return root; };
    void addNode(T key);
    Node<T>* findNode( T key, Node<T>* parent);
    void walk(Node<T>* node);
	void postOrderWalk(Node<T>* node);
	void preOrderWalk(Node<T>* node);
	void inOrderWalk(Node<T>* node);
    void deleteNode(T key);
    Node<T>* min(Node<T>* node);
    Node<T>* max(Node<T>* node);
    Node<T>* successor(T key, Node<T>* parent);
    Node<T>* predecessor(T key, Node<T>* parent);
private:
    void addNode(T key, Node<T>* leaf);
    void freeNode(Node<T>* leaf);
};

// Constructor
template<typename T>
Tree<T>::Tree() {
	cout<<"In ctor"<<endl;
    root = NULL;
}

// Destructor
template<typename T>
Tree<T>::~Tree() {
	cout<<"Dtor"<<endl;
    freeNode(root);
	cout<<"Cleaned up ..."<<endl;
}

// Free the node
template<typename T>
void Tree<T>::freeNode(Node<T>* leaf)
{
    if ( leaf != NULL ) 
    {
        freeNode(leaf->Left());
        freeNode(leaf->Right());
        delete leaf;
    }
}

// Add a node [O(height of tree) on average]
template<typename T>
void Tree<T>::addNode(T key)
{
    // No elements. Add the root
    if ( root == NULL ) {
        cout << "No root exists creating root ... " << key << endl;
        Node<T>* n = new Node<T>();
        n->setKey(key);
		root = n;
    }
    else {
		cout << "Root exists adding leaf... " << key << endl;
		addNode(key, root);
    }
}

// Add a node (private)
template<typename T>
void Tree<T>::addNode(T key, Node<T>* leaf) {
    //if new key is <<less than or equal to>> parent, add to the left 
	if ( key <= leaf->Key() )
    {
	#ifdef DEBUG
		cout<<"Moving left..."<<endl;
	#endif

        if ( leaf->Left() != NULL ){//if there is already a left leaf call again 
            addNode(key, leaf->Left());
		}
        else{
				Node<T>* n = new Node<T>();
				//n->setKey(key);
				n->key = key;
				//n->setParent(leaf);
				n->parent=leaf;
				//leaf->setLeft(n); 
				leaf->left = n;
				
        }
    }
    else
    {
		#ifdef DEBUG
			cout<<"Moving right..."<<endl;
		#endif
        if ( leaf->Right() != NULL )
            addNode(key, leaf->Right());
        else {
				Node<T>* n = new Node<T>();
				n->setKey(key);
				n->setParent(leaf);
				leaf->setRight(n);
        }
    }
}

// Find a node [O(height of tree) on average]
template<typename T>
Node<T>* Tree<T>::findNode(T key, Node<T>* node)
{
    if ( node == NULL )
        return NULL;
    else if ( node->Key() == key )
        return node;
    else if ( key <= node->Key() )
        findNode(key, node->Left());
    else if ( key > node->Key() )
        findNode(key, node->Right());
    else
        return NULL;
}

// Print the tree
template<typename T>
void Tree<T>::walk(Node<T>* node)
{
    if ( node )
    {
        cout << node->Key() << "--> ";
        walk(node->Left());
        walk(node->Right());
    }
}

template<typename T>
void Tree<T>::preOrderWalk(Node<T>* node)
{

    if ( node )
    {
		cout << node->Key() << "--> ";
		if(node->left) {
			preOrderWalk(node->Left());
		}
		if(node->right){
			preOrderWalk(node->Right());
		}
    }
	
}

template<typename T>
void Tree<T>::inOrderWalk(Node<T>* node)
{

    if ( node )
    {
		if(node->left) {
			inOrderWalk(node->Left());
		}

		cout << node->Key() << "--> ";
        inOrderWalk(node->Right());
    }
	
}

template<typename T>
void Tree<T>::postOrderWalk(Node<T>* node)
{

    if ( node )
    {
		if(node->left) 
			postOrderWalk(node->Left());
		if(node->right)
			postOrderWalk(node->Right());
		cout << node->Key() << "--> ";
    }
	
}


// Find the node with min key
// Traverse the left sub-tree recursively
// till left sub-tree is empty to get min
template<typename T>
Node<T>* Tree<T>::min(Node<T>* node)
{
    if ( node == NULL )
        return NULL;

    if ( node->Left() )
        min(node->Left());
    else
        return node;
}

// Find the node with max key
// Traverse the right sub-tree recursively
// till right sub-tree is empty to get max
template<typename T>
Node<T>* Tree<T>::max(Node<T>* node)
{
    if ( node == NULL )
        return NULL;

    if ( node->Right() )
        max(node->Right());
    else
        return node;
}

// Find successor to a node
// Find the node, get the node with max value
// for the right sub-tree to get the successor
template<typename T>
Node<T>* Tree<T>::successor(T key, Node<T> *node)
{
    Node<T>* thisKey = findNode(key, node);
    if ( thisKey )
        return max(thisKey->Right());
}

// Find predecessor to a node
// Find the node, get the node with max value
// for the left sub-tree to get the predecessor
template<typename T>
Node<T>* Tree<T>::predecessor(T key, Node<T> *node)
{
    Node<T>* thisKey = findNode(key, node);
    if ( thisKey )
        return max(thisKey->Left());
}

// Delete a node
// (1) If leaf just delete
// (2) If only one child delete this node and replace
// with the child
// (3) If 2 children. Find the predecessor (or successor).
// Delete the predecessor (or successor). Replace the
// node to be deleted with the predecessor (or successor).

template<typename T>
void Tree<T>::deleteNode(T key)
{
    // Find the node.
    Node<T>* thisKey = findNode(key, root);

    // (1)
    if ( thisKey->Left() == NULL && thisKey->Right() == NULL )
    {
        if ( thisKey->Key() > thisKey->Parent()->Key() )
            thisKey->Parent()->setRight(NULL);
        else
            thisKey->Parent()->setLeft(NULL);

        delete thisKey;
    }

    // (2)
    if ( thisKey->Left() == NULL && thisKey->Right() != NULL )
    {
        if ( thisKey->Key() > thisKey->Parent()->Key() )
            thisKey->Parent()->setRight(thisKey->Right());
        else
            thisKey->Parent()->setLeft(thisKey->Right());

        delete thisKey;
    }
    if ( thisKey->Left() != NULL && thisKey->Right() == NULL )
    {
        if ( thisKey->Key() > thisKey->Parent()->Key() )
            thisKey->Parent()->setRight(thisKey->Left());
        else
            thisKey->Parent()->setLeft(thisKey->Left());

        delete thisKey;
    }

    // (3)
    if ( thisKey->Left() != NULL && thisKey->Right() != NULL )
    {
        Node* sub = predecessor(thisKey->Key(), thisKey);
        if ( sub == NULL )
            sub = successor(thisKey->Key(), thisKey);        

        if ( sub->Parent()->Key() <= sub->Key() )
            sub->Parent()->setRight(sub->Right());
        else
            sub->Parent()->setLeft(sub->Left());

        thisKey->setKey(sub->Key());
        delete sub;
    }
}