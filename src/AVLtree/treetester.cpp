/*----- treetester.cpp -----------------------------------------------------
                Program for testing AVL Tree.
 ------------------------------------------------------------------------*/
#include <iostream>
using namespace std;

#include "AVL.h"

void actions(AVL*, int);
void traverse(AVL*, int);

enum mainOptions { INSERT=1, SEARCH, TRAVERSE, DELETE, COUNT, EXIT };
enum traversalMethods { PREORDER=1, INORDER, POSTORDER, BACK_FROM_TRAVERSAL };

int main()
{
    // Testing Constructor and empty()
    AVL intAVL;            // test the class constructor
    cout << "Constructing empty AVL Tree\n";
    cout << "AVL Tree " << (intAVL.empty() ? "is" : "is not") << " empty\n";

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
        actions(&intAVL, number);
    }

}

void actions(AVL *intAVL, int option) {
    switch (option) {
        case INSERT: {
            int number;
            // Testing insert
            cout << "\nNow insert a bunch of integers into the AVL Tree."
                    "\nTry items not in the AVL Tree and some that are in it:\n";
            for (;;) {
                cout << "Item to insert (-999 to stop): ";
                cin >> number;
                if (number == -999) break;
                intAVL->insert(number);
            }
            cout << "AVL Tree " << (intAVL->empty() ? "is" : "is not") << " empty\n";
            break;
        }
        case SEARCH: {
            int number;
            // Testing search()
            cout << "\n\nNow testing the search() operation."
                    "\nTry both items in the AVL Tree and some not in it:\n";
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
                    "\nSelect a traversal method:";
            while (true) {
                cout << "\n1. PreOrder\n2. InOrder\n3. PostOrder\n4. Back" << endl;
                cin >> number;
                if (number > BACK_FROM_TRAVERSAL || number < 1) {
                    cout << "Select a valid option between 1 and 4" << endl;
                    continue;
                } else {
                    if (number == BACK_FROM_TRAVERSAL) break;
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
                cout << "\nEnter a number to delete (-999 to go back):";
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
        case COUNT:
            cout << "\nSize of tree:" << endl;
            cout << "There are [" << intAVL->nodeCount() << "] elements in the tree" << endl;
            return;
    }
}

void traverse(AVL *intAVL, int traversalMethod) {
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