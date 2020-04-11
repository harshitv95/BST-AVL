#include <iostream>
using namespace std;  

#ifndef AVL_TREE
#define AVL_TREE

#include "../BST/BST.h"

class AVL: public BST
{
 public:
     /***** Function Members *****/
    AVL();
  
 private:
    /***** Private Function Members *****/
    virtual void postInsert(BinNode *node, BinNode *parentNode);

}; // end of class declaration

#endif
