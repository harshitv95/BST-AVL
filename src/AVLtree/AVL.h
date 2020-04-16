#include <iostream>
using namespace std;  

#ifndef AVL_TREE
#define AVL_TREE

#define IS_BALANCED(node) (node->balance < 2 && node->balance > -2)
#define BALANCE_TYPE(node) (node->balance > 0 ? LEFT_HEAVY : (node->balance < 0 ? RIGHT_HEAVY : BALANCED))

#include "../BST/BST.h"

class AVL: public BST
{
 public:
     /***** Function Members *****/
    AVL();
    /***** Others *****/
    typedef enum { ROOT_NODE, LEFT_NODE, RIGHT_NODE } child_type;
    typedef enum{
        LEFT_ROTATE, RIGHT_ROTATE, LEFT_RIGHT_ROTATE, RIGHT_LEFT_ROTATE
    } rotation_type;
    typedef enum { LEFT_HEAVY, RIGHT_HEAVY, BALANCED } balance_type;

 protected:
    class AVLNode: public BinNode {
    public:
        int height, balance;
        AVLNode *parent;
        child_type childType;

        AVLNode():BST::BinNode(), height(0), balance(0) {}
        AVLNode(int data):BST::BinNode(data), height(0), balance(0) {}

        void print();
    };

    int calcHeight(AVLNode *node);
    int calcBalance(AVLNode *node);
    BinNode* initNode();
    BinNode* initNode(int data);

 private:
    /***** Private Function Members *****/
    void postInsert(BinNode *node, BinNode *parentNode);
    void postDelete(BinNode *parentNode);
    void balance(AVLNode *node);
    void rotate(
            AVLNode *rotateNode, rotation_type rotationType
        );

}; // end of class declaration

#endif
