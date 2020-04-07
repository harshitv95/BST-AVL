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
      locptr = new BinNode(item);  
      if (parent == 0)               // empty tree
         myRoot = locptr;
      else if (item < parent->data )  // insert to left of parent
         parent->left = locptr;
      else                           // insert to right of parent
         parent->right = locptr;
   }
   else
      cout << "Item already in the tree\n";
}

// Public methods to be called from user program
int BST::nodeCount() const {
    return this->nodeCount(this->myRoot);
}

void BST::preOrder() const {
    this->traverse(this->myRoot, PRE_ORDER);
}

void BST::inOrder() const {
    this->traverse(this->myRoot, IN_ORDER);
}

void BST::postOrder() const {
    this->traverse(this->myRoot, POST_ORDER);
}

void BST::deleteNode(int value) {
    BinNode *searchNode, *parentNode;
    delete_mode mode = LEAF_NODE;
    searchNode = this->searchNode(this->myRoot, value, parentNode);
    if (searchNode->left && searchNode->right)
        mode = TWO_CHILDREN;
    else if (searchNode->left || searchNode->right)
        mode = ONE_CHILD;
    this->deleteNode(searchNode, parentNode, mode);
}



// Private methods
int BST::nodeCount(BST::BinNode *node) const {
    if (node == NULL || node == 0)
        return 0;
    return 1 + this->nodeCount(node->left) + this->nodeCount(node->right);
}

BST::BinNode *BST::searchNode(BST::BinNode *startNode, int data, BST::BinNode *parentNode) {
    if (startNode == NULL || startNode == 0) return NULL;
    if (startNode->data == data)
        return startNode;
    else if (data < startNode->data) {
        if (startNode->left && startNode->left->data == data) {
            *parentNode = *startNode;
            return startNode->left;
        }
        return this->searchNode(startNode->left, data, parentNode);
    } else {
        if (startNode->right && startNode->right->data == data) {
            *parentNode = *startNode;
            return startNode->right;
        }
        return this->searchNode(startNode->right, data, parentNode);
    }
}

void BST::traverse(BST::BinNode *node, traversal_order order) const {
    if (node == NULL || node == 0)
        return;
    BinNode *left = node->left;
    BinNode *right = node->right;
    switch (order) {
        case PRE_ORDER:
//            printf("%d", node->data);
            cout << node->data << endl;
            traverse(left, order);
            traverse(right, order);
            break;
        case IN_ORDER:
            traverse(left, order);
            cout << node->data << endl;
            traverse(right, order);
            break;
        case POST_ORDER:
            traverse(left, order);
            traverse(right, order);
            cout << node->data << endl;
            break;
    }
}

void BST::deleteNode(BST::BinNode *node, BST::BinNode *parentNode, BST::delete_mode mode) {
    bool isRoot = parentNode == NULL;
    switch (mode) {
        case LEAF_NODE: {
            if (isRoot)
                this->myRoot = NULL;
            else {
                if (parentNode->left == node)
                    parentNode->left = NULL;
                else if (parentNode->right == node)
                    parentNode->right = NULL;
            }
            return;
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
            return;
        }
        case TWO_CHILDREN: {
            BinNode *parentOfSmallestNode, *smallestNode;
            smallestNode = smallest(node->right, parentOfSmallestNode);
            if (parentOfSmallestNode != NULL)
                parentOfSmallestNode->left = NULL;

            smallestNode->left = node->left;
            smallestNode->right = node->right;
            if (isRoot)
                this->myRoot = smallestNode;
            else {
                if (parentNode->left == node)
                    parentNode->left = smallestNode;
                else if (parentNode->right == node)
                    parentNode->right = smallestNode;
            }
            return;
        }
    }
}

BST::BinNode * BST::smallest(BinNode *rootNode, BinNode *parentNode) {
    if (rootNode->left == NULL) return parentNode;
    else if (rootNode->left->left == NULL) {
        *parentNode = *rootNode;
        return rootNode->left;
    }
    return largest(rootNode->left, parentNode);
}

BST::BinNode * BST::largest(BinNode *rootNode, BinNode *parentNode) {
    if (rootNode->right == NULL) return parentNode;
    else if (rootNode->right->right == NULL) {
        *parentNode = *rootNode;
        return rootNode->right;
    }
    return largest(rootNode->right, parentNode);
}