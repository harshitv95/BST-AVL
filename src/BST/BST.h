#include <iostream>
using namespace std;  

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

class BST
{
 public:
     /***** Function Members *****/
    BST();
    bool empty() const;j
    bool search(const int & item) const;
    void insert(const int & item);

    int nodeCount() const;
    void preOrder() const;
    void inOrder() const;
    void postOrder() const;
    virtual void deleteNode(int value);

    /***** Others *****/
    typedef enum {PRE_ORDER, IN_ORDER, POST_ORDER} traversal_order;
    typedef enum {LEAF_NODE, ONE_CHILD, TWO_CHILDREN} delete_mode;

 protected:
     /***** Node class *****/
    class BinNode
    {
    public:
    int data;
    BinNode * left;
    BinNode * right;

    // BinNode constructors
    // Default -- data part is default int value; both links are null.
    BinNode()
    : left(0), right(0)
    {}

    // Explicit Value -- data part contains item; both links are null.
    BinNode(int item)
    : data(item), left(0), right(0)
    {}

    };// end of class BinNode declaration

    /***** Data Members *****/
    BinNode * myRoot;


    /***** Private Function Members *****/
    int nodeCount(BinNode * node) const;
    void traverse(BinNode *node, traversal_order order) const;
    BinNode *searchNode(BinNode *startNode, int data, BinNode *&parentNode);
    void deleteNode(BinNode *node, BinNode *parentNode, delete_mode mode);
    BinNode *smallest(BinNode *rootNode, BinNode *& parentNode, int &status);
    BinNode *largest(BinNode *rootNode, BinNode *& parentNode, int &status);
    virtual void postInsert(BinNode *node, BinNode *parentNode);

}; // end of class declaration

#endif
