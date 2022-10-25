#include "AVLTree.h"
#include <iostream>
using namespace std;

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

int AVLTree::recursiveHeight(AVLNode * node) const {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = recursiveHeight(node->getLeft());
    int rightHeight = recursiveHeight(node->getRight());
    int max_height = leftHeight > rightHeight ? leftHeight : rightHeight;
    return max_height + 1;
}

int AVLTree::heightDifference(AVLNode * node) const {
    return recursiveHeight(node->getLeft()) - recursiveHeight(node->getRight());
}

AVLNode * AVLTree::balance(AVLNode * node) {
    int heightDifference = this->heightDifference(node);
    if (heightDifference < -1) {
        if (this->heightDifference(node->getRight()) <= 0) {
            node = rotateRR(node);
        } else {
            node = rotateRL(node);
        }
    } else if (heightDifference > 0) {
        if (this->heightDifference(node->getLeft()) <= 0) {
            node = rotateLR(node);
        } else {
            node = rotateLL(node);
        }
    }
    return node;
}

AVLNode *rotateRR(AVLNode * parent){
    AVLNode *temp = parent->getRight();
    parent->setRight(temp->getLeft());
    temp->setLeft(parent);
    return temp;
}

AVLNode *rotateLL(AVLNode * parent){
    AVLNode *temp = parent->getLeft();
    parent->setLeft(temp->getRight());
    temp->setRight(parent);
    return temp;
}

AVLNode *rotateLR(AVLNode * parent){
    AVLNode * temp = parent->getLeft();
    parent->setLeft(rotateRR(temp));
    return rotateLL(parent);
}

AVLNode *rotateRL(AVLNode * parent){
    AVLNode * temp = parent->getRight();
    parent->setRight(rotateRR(temp));
    return rotateRR(parent);
}

AVLNode * AVLTree::recursiveFind(AVLNode *node, int data) const {
    if (node->getData() == data) {
        return node;
    }
    AVLNode *leftFind = recursiveFind(node->getLeft(), data);
    if (leftFind != nullptr) {
        return leftFind;
    }
    AVLNode *rightFind = recursiveFind(node->getRight(), data);
    return rightFind;
}

AVLNode * AVLTree::find(int data) const {
    return recursiveFind(root, data);
}

void AVLTree::printTree(AVLNode * root, int space) {
    if (root == nullptr)
        return;

    space += 10;
    printTree(root->getRight(), space);
    cout << endl;
    for (int i = 10; i < space; i++)
        cout << " ";
    cout << root->getData() << "\n";
    printTree(root->getLeft(), space);
}

AVLNode *AVLTree::recursiveMinimum(AVLNode * node) const {
    if (node == nullptr) {
        return nullptr;
    } else if (node->getLeft() == nullptr) {
        return node;
    } else {
        return recursiveMinimum(node->getLeft());
    }
}

AVLNode *AVLTree::recursiveDelete(AVLNode *node, int data) {
    if (node == nullptr) {
        return nullptr;
    } else if (node->getData() < data) {
        node->setRight(recursiveDelete(node->getRight(), data));
    } else if (node->getData() > data) {
        node->setLeft(recursiveDelete(node->getLeft(), data));
    } else {
        if (node->getLeft() != nullptr && node->getRight() != nullptr) {
            AVLNode *temp = recursiveMinimum(node->getRight());
            node->setData(temp->getData());
            node->setRight(recursiveDelete(node->getRight(), node->getData()));
        } else {
            AVLNode * temp = node;
            if (node->getLeft() == nullptr) {
                node = node->getRight();
            } else if (node->getRight() == nullptr) {
                node = node->getLeft();
            }
            delete temp;
        }
    }

    if (node != nullptr) {
        return balance(node);
    }
    return nullptr;
}

void AVLTree::delete_(int) {

}
