#include "AVLNode.h"


AVLNode::AVLNode(int data, AVLNode*left, AVLNode*right){
    this->data = data;
    this->left = left;
    this->right = right;
}

AVLNode::~AVLNode() {}

int AVLNode::getData() const{
    return this->data;
}

AVLNode* AVLNode::getLeft() const{
    return this->left;
}

AVLNode* AVLNode::getRight() const{
    return this->right;
}

void AVLNode::setData(int data){
    this->data = data;
}

void AVLNode::setLeft(AVLNode * left){
    this->left = left;
}

void AVLNode::setRight(AVLNode * right){
    this->right = right;
}

AVLNode::Comparison AVLNode::compare(int data) const {
    if (this->data < data) {
        return LESS;
    } else if (this->data > data) {
        return GREATER;
    } else {
        return EQUAL;
    }
}