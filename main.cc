#include <iostream>
#include "AVLTree.h"
using namespace std;

int main(int argc, char *argv[]) {
    AVLTree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.delete_(3);
    cout << tree.find(3)->getData() << endl;

    return 0;
}

