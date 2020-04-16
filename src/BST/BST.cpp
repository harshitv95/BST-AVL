#include <iostream>
//#include <iomanip>

using namespace std;

#include "BST.h"

//--- Definition of constructor
BST::BST()
: myRoot(0)
{}

bool BST::empty() const
{ return myRoot == 0; }


bool BST::search(const int & item) const
{
    BinNode * locptr = myRoot;
   bool found = false;
   while (!found && locptr != 0)
   {
      if (item < locptr->data)       // descend left
        locptr = locptr->left;
      else if (locptr->data < item)  // descend right
        locptr = locptr->right;
      else if (locptr->data == item) // item found
        found = true;
   }
   return found;
}


void BST::insert(const int & item)
{
    BinNode * locptr = myRoot;   // search pointer
    BinNode * parent = 0;        // pointer to parent of current node
   bool found = false;     // indicates if item already in BST
   while (!found && locptr != 0)
   {
      parent = locptr;
      if (item < locptr->data)       // descend left
         locptr = locptr->left;
      else if (locptr->data < item)  // descend right
         locptr = locptr->right;
      else                           // item found
         found = true;
   }
   if (!found)
   {                                 // construct node containing item
      locptr = this->initNode(item);
      if (parent == 0) {              // empty tree
          myRoot = locptr;
          this->postInsert(myRoot, NULL);
      }
      else if (item < parent->data ) { // insert to left of parent
          parent->left = locptr;
          this->postInsert(parent->left, parent);
      }
      else {                          // insert to right of parent
          parent->right = locptr;
          this->postInsert(parent->right, parent);
      }
   }
   else
      cout << "Item already in the tree\n";
}

// Public methods to be called from user program
int BST::nodeCount() const {
    return this->nodeCount(this->myRoot);
}

void BST::preOrder() const {
    cout << "PreOrder Traversal:" << endl;
    this->traverse(this->myRoot, PRE_ORDER);
}

void BST::inOrder() const {
    cout << "InOrder Traversal:" << endl;
    this->traverse(this->myRoot, IN_ORDER);
}

void BST::postOrder() const {
    cout << "PostOrder Traversal:" << endl;
    this->traverse(this->myRoot, POST_ORDER);
}

void BST::deleteNode(int value) {
    BinNode *searchNode, *parentNode;
    parentNode = NULL;
    delete_mode mode = LEAF_NODE;
    searchNode = this->searchNode(this->myRoot, value, parentNode);
    if (searchNode->left && searchNode->right)
        mode = TWO_CHILDREN;
    else if (searchNode->left || searchNode->right)
        mode = ONE_CHILD;
    this->deleteNode(searchNode, parentNode, mode);
    cout << "Deleted " << value << " successfully, data in tree:" << endl;
    this->traverse(this->myRoot, IN_ORDER);
}



// Private methods
int BST::nodeCount(BST::BinNode *node) const {
    if (node == NULL || node == 0)
        return 0;
    return 1 + this->nodeCount(node->left) + this->nodeCount(node->right);
}

BST::BinNode *BST::searchNode(BST::BinNode *startNode, int data, BST::BinNode *& parentNode) {
    if (startNode == NULL || startNode == 0) return NULL;
    if (startNode->data == data)
        return startNode;
    else if (data < startNode->data) {
        if (startNode->left && startNode->left->data == data) {
            parentNode = startNode;
            return startNode->left;
        }
        return this->searchNode(startNode->left, data, parentNode);
    } else {
        if (startNode->right && startNode->right->data == data) {
            parentNode = startNode;
            return startNode->right;
        }
        return this->searchNode(startNode->right, data, parentNode);
    }
}

void BST::BinNode::print() {
    cout << this->data << endl;
}

void BST::traverse(BST::BinNode *node, traversal_order order) const {
    if (node == NULL || node == 0)
        return;
    BinNode *left = node->left;
    BinNode *right = node->right;
    switch (order) {
        case PRE_ORDER:
//            printf("%d", node->data);
            node->print();
            traverse(left, order);
            traverse(right, order);
            break;
        case IN_ORDER:
            traverse(left, order);
            node->print();
            traverse(right, order);
            break;
        case POST_ORDER:
            traverse(left, order);
            traverse(right, order);
            node->print();
            break;
    }
}

void BST::deleteNode(BST::BinNode *node, BST::BinNode *parentNode, BST::delete_mode mode) {
    bool isRoot = (node == this->myRoot);
    int data = node->data;
    if (isRoot)
        cout << "Deleting Root element : " << node->data << endl;
    else
        cout << "Deleting element [" << node->data << "] with parent [" << parentNode->data << "]" << endl;
    switch (mode) {
        case LEAF_NODE: {
//            cout << "Deleting Leaf Node " << node->data << endl;
            if (isRoot)
                this->myRoot = NULL;
            else {
                if (parentNode->left == node) {
//                    cout << "Deleting left child of parent: " << parentNode->data << endl;
                    parentNode->left = NULL;
                }
                else if (parentNode->right == node) {
//                    cout << "Deleting right child of parent: " << parentNode->data << endl;
                    parentNode->right = NULL;
                }
            }
            break;
        }
        case ONE_CHILD: {
            BinNode *child = node->left ? node->left : node->right;
            if (isRoot)
                this->myRoot = child;
            else {
                if (parentNode->left == node)
                    parentNode->left = child;
                else if (parentNode->right == node)
                    parentNode->right = child;
            }
            break;
        }
        case TWO_CHILDREN: {
            int status = 0;
            BinNode *parentOfSmallestNode, *smallestNode;
            smallestNode = smallest(node->right, parentOfSmallestNode, status);
            if (parentOfSmallestNode != NULL && status == 1)
                parentOfSmallestNode->left = smallestNode->right;
            else
                node->right = smallestNode->right;

            cout << "Found smallest : [" << smallestNode->data << "] with parent : [" << parentOfSmallestNode->data << "]";

            smallestNode->left = node->left;
            smallestNode->right = node->right;

            if (isRoot) {
                this->myRoot = smallestNode;
            }
            else {
                if (parentNode->left == node)
                    parentNode->left = smallestNode;
                else if (parentNode->right == node)
                    parentNode->right = smallestNode;
            }
            break;
        }
    }
    delete node;
    this->postDelete(data, parentNode);
}

BST::BinNode * BST::smallest(BinNode *rootNode, BinNode *& parentNode, int &status) {
    if (rootNode->left == NULL) return rootNode;
    parentNode = rootNode;
    status = 1;
    return smallest(rootNode->left, parentNode, status);
}

BST::BinNode * BST::largest(BinNode *rootNode, BinNode *& parentNode, int &status) {
    if (rootNode->right == NULL) return rootNode;
    parentNode = rootNode;
    status = 1;
    return largest(rootNode->right, parentNode, status);
}

BST::BinNode * BST::smallest(BinNode *rootNode) {
    if (rootNode->left == NULL) return rootNode;
    return smallest(rootNode->left);
}

BST::BinNode * BST::largest(BinNode *rootNode) {
    if (rootNode->right == NULL) return rootNode;
    return largest(rootNode->right);
}


void BST::postInsert(BST::BinNode *node, BST::BinNode *parentNode) {}

void BST::postDelete(int data, BST::BinNode *parentNode) {}

BST::BinNode* BST::initNode() {
    return new BinNode();
}

BST::BinNode* BST::initNode(int data) {
    return new BinNode(data);
}