#include <stack>
#include "AVLNode.h"

using namespace std;

#ifndef __AVL_TREE_ITERATOR__
#define __AVL_TREE_ITERATOR__

template<class T>
class AVLTree;

template<class T>
class AVLTreeIterator {
private:
    AVLTree<T> *tree;
    stack<AVLNode<T> *> traversal;

    AVLNode<T>* left(AVLNode<T> *);

public:
    AVLTreeIterator(AVLTree<T> *tree);
    AVLNode<T>* next() const;
    bool hasNext() const;
};

template<class T>
AVLTreeIterator<T>::AVLTreeIterator(AVLTree<T> *tree): tree(tree) {}

template<class T>
AVLNode<T> *AVLTreeIterator<T>::next() const {
    if (!hasNext()) {
        return nullptr;
    }
    AVLNode<T> *current = traversal.pop();
    if (current->getRight() != nullptr) {
        left(current->getRight());
    }
    return current;
}

template<class T>
AVLNode<T>* AVLTreeIterator<T>::left(AVLNode<T> *current) {
    while (current != nullptr) {
        traversal.push(current);
        current = current->getLeft();
    }
}

template<class T>
bool AVLTreeIterator<T>::hasNext() const {
    return !traversal.empty();
}

#endif
