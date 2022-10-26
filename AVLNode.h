#include <iostream>
using namespace std;

#ifndef __AVL_NODE_H__
#define __AVL_NODE_H__

template<class T>
class AVLNode
{
private:
    T data;
    AVLNode * left;
    AVLNode * right;
public:
    enum Comparison { LESS, GREATER, EQUAL };
    AVLNode(T data, AVLNode*left, AVLNode*right);
    ~AVLNode();
    T getData() const;
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    void setData(T newData);
    void setLeft(AVLNode * left);
    void setRight(AVLNode * right);
    Comparison compare(T) const;
    AVLNode<T> *clone() const;
};

template<class T>
AVLNode<T>::AVLNode(T data, AVLNode*left, AVLNode*right){
    this->data = data;
    this->left = left;
    this->right = right;
}

template<class T>
AVLNode<T>::~AVLNode() {}

template<class T>
T AVLNode<T>::getData() const{
    return this->data;
}

template<class T>
AVLNode<T>* AVLNode<T>::getLeft() const{
    return this->left;
}

template<class T>
AVLNode<T>* AVLNode<T>::getRight() const{
    return this->right;
}

template<class T>
void AVLNode<T>::setData(T data){
    this->data = data;
}

template<class T>
void AVLNode<T>::setLeft(AVLNode * left){
    this->left = left;
}

template<class T>
void AVLNode<T>::setRight(AVLNode * right){
    this->right = right;
}

template<class T>
typename AVLNode<T>::Comparison AVLNode<T>::compare(T data) const {
    if (this->data < data) {
        return LESS;
    } else if (this->data > data) {
        return GREATER;
    } else {
        return EQUAL;
    }
}

template<class T>
AVLNode<T> *AVLNode<T>::clone() const {
    return new AVLNode<T>(data, nullptr, nullptr);
}

#endif
