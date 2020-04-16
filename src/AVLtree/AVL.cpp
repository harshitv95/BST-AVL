#include <iostream>

using namespace std;

#include "AVL.h"

//--- Definition of constructor
AVL::AVL():BST() {}

// Private methods
void AVL::AVLNode::print() {
    cout << this->data
         << " (height: " << this->height
         << ", balance: " << this->balance
         << ", " << (
            this->childType == ROOT_NODE ? "ROOT" : (
                 this->childType == LEFT_NODE ? "LEFT" : "RIGHT"
                 ) )
         << " child of: " << (!this->parent ? -999 : this->parent->data)
         << ")" << endl;
}

void AVL::postInsert(BinNode *node, BinNode *parentNode) {
    AVLNode *avlNode = ((AVLNode*) node);
    avlNode->parent = ((AVLNode*) parentNode);

    if (!parentNode)
        avlNode->childType = ROOT_NODE;
    else if (parentNode->left == node)
        avlNode->childType = LEFT_NODE;
    else if (parentNode->right == node)
        avlNode->childType = RIGHT_NODE;

    this->calcHeight((AVLNode*) this->myRoot);
    if (avlNode->parent && avlNode->parent->parent)
        this->balance(avlNode);
}

void AVL::postDelete(BinNode *parentNode) {
    this->calcHeight((AVLNode*) this->myRoot);
    if (!parentNode) return;

    AVLNode *parentAVLNode = (AVLNode*) parentNode;
    while (parentAVLNode && IS_BALANCED(parentAVLNode)) {
        switch (BALANCE_TYPE(parentAVLNode)) {
            case BALANCED:
                return;
            case RIGHT_HEAVY:
                parentAVLNode = (AVLNode*) parentAVLNode->right;
                break;
            case LEFT_HEAVY:
                parentAVLNode = (AVLNode*) parentAVLNode->left;
                break;
        }
    }

    if (!parentAVLNode) return;
    switch (BALANCE_TYPE(parentAVLNode)) {
        case BALANCED:
        case LEFT_HEAVY:
            parentAVLNode = (AVLNode*) (parentAVLNode->left);
            break;
        case RIGHT_HEAVY:
            parentAVLNode = (AVLNode*) (parentAVLNode->right);
            break;
    }
    if (parentAVLNode->left)
        parentAVLNode = (AVLNode*) parentAVLNode->left;
    else if (parentAVLNode->right)
        parentAVLNode = (AVLNode*) parentAVLNode->right;

    this->balance(parentAVLNode);
}

AVL::BinNode* AVL::initNode() {
    AVLNode *node = new AVL::AVLNode();
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

AVL::BinNode* AVL::initNode(int data) {
    AVLNode *node = new AVLNode(data);
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

static int max(int a, int b) {
    return a > b ? a : b;
}

int AVL::calcBalance(AVLNode *node) {
    if (node->left && node->right)
        node->balance =
                ((AVL::AVLNode *) node->left)->height -
                ((AVL::AVLNode *) node->right)->height;
    else if (!node->left && !node->right)
        node->balance = 0;
    else if (!node->left)
        node->balance = -1 - ((AVL::AVLNode *) node->right)->height;
    else
        node->balance = ((AVL::AVLNode *) node->left)->height + 1;
}

int AVL::calcHeight(AVL::AVLNode *node) {
    if (node == NULL) return -1;
    ((AVLNode*) node)->parent = NULL;
    ((AVLNode*) node)->childType = ROOT_NODE;

    int leftHeight = calcHeight((AVL::AVLNode*) node->left);
    int rightHeight = calcHeight((AVL::AVLNode*) node->right);

    if (node->left) {
        ((AVLNode *) node->left)->parent = node;
        ((AVLNode *) node->left)->childType = LEFT_NODE;
    }
    if (node->right) {
        ((AVLNode *) node->right)->parent = node;
        ((AVLNode *) node->right)->childType = RIGHT_NODE;
    }

    node->height = 1 + max(leftHeight, rightHeight);
    calcBalance(node);
    return node->height;
}

void AVL::balance(AVL::AVLNode *node) {
    rotation_type rotationType;

    AVLNode *balanceNode = node, *parent, *grandParent, *rotateNode;
    while (
            balanceNode &&
            (parent = balanceNode->parent) &&
            (grandParent = balanceNode->parent->parent)
    )
    {
        if (!IS_BALANCED(grandParent)) {
            if (parent->childType == LEFT_NODE) {
                if (balanceNode->childType == LEFT_NODE) {
                    rotationType = RIGHT_ROTATE;
                    rotateNode = parent;
                } else if (balanceNode->childType == RIGHT_NODE) {
                    rotationType = LEFT_RIGHT_ROTATE;
                    rotateNode = balanceNode;
                }
            } else if (parent->childType == RIGHT_NODE) {
                if (balanceNode->childType == LEFT_NODE) {
                    rotationType = RIGHT_LEFT_ROTATE;
                    rotateNode = balanceNode;
                } else if (balanceNode->childType == RIGHT_NODE) {
                    rotationType = LEFT_ROTATE;
                    rotateNode = parent;
                }
            }
            this->rotate(rotateNode, rotationType);
            this->calcHeight((AVLNode *) this->myRoot);
            return;
        } else
            balanceNode = balanceNode->parent;
    }
}

void AVL::rotate(
        AVL::AVLNode *rotateNode,
        AVL::rotation_type rotationType
    ) {
//    AVLNode *grandParent = rotateNode->parent->parent;
    if (!rotateNode || !rotateNode->parent || rotateNode->childType == ROOT_NODE)
        return;
    bool isRoot;
    AVLNode *parentOfRotated = NULL, *rotated;
    rotated = rotateNode->parent;
    isRoot = rotated->childType == ROOT_NODE;
    parentOfRotated = rotated->parent;

    switch (rotationType) {
        case LEFT_ROTATE:
            rotateNode->parent->right = rotateNode->left;
            rotateNode->left = rotateNode->parent;
            break;
        case RIGHT_ROTATE:
            rotateNode->parent->left = rotateNode->right;
            rotateNode->right = rotateNode->parent;
            break;
        case LEFT_RIGHT_ROTATE: {
            this->rotate(rotateNode, LEFT_ROTATE);
            this->rotate(rotateNode, RIGHT_ROTATE);
            return;
        }
        case RIGHT_LEFT_ROTATE: {
            this->rotate(rotateNode, RIGHT_ROTATE);
            this->rotate(rotateNode, LEFT_ROTATE);
            return;
        }
    }

    if (isRoot || parentOfRotated == NULL) // Is parent Root
        this->myRoot = rotateNode;
    else {
        if (rotated->childType == LEFT_NODE) {
            parentOfRotated->left = rotateNode;
            rotateNode->parent = parentOfRotated;
        }
        else if (rotated->childType == RIGHT_NODE) {
            parentOfRotated->right = rotateNode;
            rotateNode->parent = parentOfRotated;
        }
    }
}