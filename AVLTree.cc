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
AVLNode *rotateRR(AVLNode * parent){
    AVLNode *temp = parent->getRight();
    parent->setRight(temp->getLeft());
    temp->setLeft(parent);
    cout<<"ROTATION: RightRight";
    return temp;
}

AVLNode *rotateLL(AVLNode * parent){
    AVLNode *temp = parent->getLeft();
    parent->setLeft(temp->getRight());
    temp->setRight(parent);
    cout<<"ROTATION: LeftLeft";
    return temp;
}

AVLNode *rotateLR(AVLNode * parent){
    AVLNode * temp = parent->getLeft();
    parent->setLeft(rotateRR(temp));
    cout<<"ROTATION: LeftRight";
    return rotateLL(parent);
}

AVLNode *rotateRL(AVLNode * parent){
    AVLNode * temp = parent->getRight();
    parent->setRight(rotateRR(temp));
    cout<<"Right-Left Rotation";
    return rotateRR(parent);
}
