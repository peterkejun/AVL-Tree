#include "AVLTree.h"

AVLTree::AVLTree() {
    root = nullptr;
}

AVLTree::~AVLTree() {
    recursiveDeallocate(root);
}

void AVLTree::recursiveDeallocate(AVLNode * node) {
    recursiveDeallocate(node->getLeft());
    recursiveDeallocate(node->getRight());
    delete node;
}