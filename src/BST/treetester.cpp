/*----- treetester.cpp -----------------------------------------------------
                Program for testing BST.
 ------------------------------------------------------------------------*/
#include <iostream>
using namespace std;

#include "BST.h"

void actions(BST*, int);
void traverse(BST*, int);

enum mainOptions { INSERT=1, SEARCH, TRAVERSE, DELETE, COUNT, EXIT };
enum traversalMethods { PREORDER=1, INORDER, POSTORDER, BACK_FROM_TRAVERSAL };

int main()
{
   // Testing Constructor and empty()
   BST intBST;            // test the class constructor
   cout << "Constructing empty BST\n";
   cout << "BST " << (intBST.empty() ? "is" : "is not") << " empty\n";

   int number;
   while(true) {
       cout << "\n***********************************" <<endl;
       cout << "Select Action:" << endl
            << "1. Insert" << endl
            << "2. Search" << endl
            << "3. Traverse" << endl
            << "4. Delete" << endl
            << "5. Size of tree (Count of numbers in the tree)" << endl
            << "6. Exit" << endl;
       cin >> number;
       if (number < 1 || number > EXIT) {
           cout << "Select a valid option between 1 and " << EXIT << endl;
           continue;
       } else if (number == EXIT)
           exit(0);
       actions(&intBST, number);
   }

}

void actions(BST *intBST, int option) {
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
                intBST->insert(number);
            }
            cout << "BST " << (intBST->empty() ? "is" : "is not") << " empty\n";
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
                cout << (intBST->search(number) ? "Found" : "Not found") << endl;
            }
            return;
        }
        case TRAVERSE: {
            int number = 0;
            // Testing tree traversal (inOrder, preOrder, postOrder)
            cout << "\n\nNow testing tree traversal."
                    "\nSelect a traversal method:";
            while (true) {
                cout << "\n1. PreOrder\n2. InOrder\n3. PostOrder\n4. Back" << endl;
                cin >> number;
                if (number > BACK_FROM_TRAVERSAL || number < 1) {
                    cout << "Select a valid option between 1 and 4" << endl;
                    continue;
                } else {
                    if (number == BACK_FROM_TRAVERSAL) break;
                    traverse(intBST, number);
                }
            }
            return;
        }
        case DELETE: {
            int number = 0;
            // Testing delete number from tree
            cout << "\n\nNow testing delete.";
            while (true) {
                cout << "\nEnter a number to delete (-999 to go back):";
                cin >> number;
                if (number == -999) break;
                if (!intBST->search(number)) {
                    cout << "\nNumber not in tree, please enter a number that exists in the tree, to delete\n";
                    continue;
                } else {
                    intBST->deleteNode(number);
                }
            }
            return;
        }
        case COUNT:
            cout << "\nSize of tree:" << endl;
            cout << "There are [" << intBST->nodeCount() << "] elements in the tree" << endl;
            return;
    }
}

void traverse(BST *intBST, int traversalMethod) {
    switch (traversalMethod) {
        case PREORDER:
            intBST->preOrder();
            break;
        case INORDER:
            intBST->inOrder();
            break;
        case POSTORDER:
            intBST->postOrder();
            break;
    }
}