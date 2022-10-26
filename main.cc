#include <iostream>
#include <string>
#include "AVLTree.h"
using namespace std;

int main(int argc, char *argv[]) {
    AVLTree<string> tree;
    tree.insert("1");
    tree.insert("2");
    // cout << "inserting " << 3 << endl;
    tree.insert("3");
    tree.insert("4");
    tree.insert("5");
    tree.insert("6");
    // tree.delete_(5);
    tree.delete_("4");
    tree.print();
    // cout << tree.find(1) << endl;

    return 0;
}

