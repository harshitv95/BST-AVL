/*----- treetester.cpp -----------------------------------------------------
                Program for testing BST.
 ------------------------------------------------------------------------*/
#include <iostream>
using namespace std;

#include "AVL.h"

void actions(BST*, int);
void traverse(BST*, int);

enum mainOptions { INSERT=1, SEARCH, TRAVERSE, DELETE, EXIT };
enum traversalMethods { PREORDER=1, INORDER, POSTORDER };

int main()
{
   // Testing Constructor and empty()
   AVL intAVL;            // test the class constructor
   cout << "Constructing empty AVL Tree\n";
   cout << "AVL Tree " << (intAVL.empty() ? "is" : "is not") << " empty\n";

   int number;
   while(true) {
       cout << "\n***********************************" <<endl;
       cout << "Select Action:" << endl << "1. Insert" << endl << "2. Search" << endl << "3. Traverse" << endl << "4. Delete" << endl << "5. Exit" << endl;
       cin >> number;
       if (number < 1 || number > 5) {
           cout << "Select a valid option between 1 and 5" << endl;
           continue;
       } else if (number == EXIT)
           exit(0);
       actions(&intAVL, number);
   }

}

void actions(BST *intAVL, int option) {
    switch (option) {
        case INSERT: {
            int number;
            // Testing insert
            cout << "\nNow insert a bunch of integers into the BST."
                    "\nTry items not in the BST and some that are in it:\n";
            for (;;) {
                cout << "Item to insert (-999 to stop): ";
                cin >> number;
                if (number == -999) break;
                intAVL->insert(number);
            }
            cout << "BST " << (intAVL->empty() ? "is" : "is not") << " empty\n";
            break;
        }
        case SEARCH: {
            int number;
            // Testing search()
            cout << "\n\nNow testing the search() operation."
                    "\nTry both items in the BST and some not in it:\n";
            for (;;) {
                cout << "Item to find (-999 to stop): ";
                cin >> number;
                if (number == -999) break;
                cout << (intAVL->search(number) ? "Found" : "Not found") << endl;
            }
            return;
        }
        case TRAVERSE: {
            int number = 0;
            // Testing tree traversal (inOrder, preOrder, postOrder)
            cout << "\n\nNow testing tree traversal."
                    "\nSelect a traversal method:\n";
            while (true) {
                cout << "1. PreOrder\n2. InOrder\n3. PostOrder\n4. Back" << endl;
                cin >> number;
                if (number > 4 || number < 1) {
                    cout << "Select a valid option between 1 and 3" << endl;
                    continue;
                } else {
                    if (number == 4) break;
                    traverse(intAVL, number);
                }
            }
            return;
        }
        case DELETE: {
            int number = 0;
            // Testing delete number from tree
            cout << "\n\nNow testing delete.";
            while (true) {
                cout << "\nEnter a number to delete (-999 to go back):\n";
                cin >> number;
                if (number == -999) break;
                if (!intAVL->search(number)) {
                    cout << "\nNumber not in tree, please enter a number that exists in the tree, to delete\n";
                    continue;
                } else {
                    intAVL->deleteNode(number);
                }
            }
            return;
        }
    }
}

void traverse(BST *intAVL, int traversalMethod) {
    switch (traversalMethod) {
        case PREORDER:
            intAVL->preOrder();
            break;
        case INORDER:
            intAVL->inOrder();
            break;
        case POSTORDER:
            intAVL->postOrder();
            break;
    }
}