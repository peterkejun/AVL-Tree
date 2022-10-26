#include "AVLNode.h"
#include <iostream>
using namespace std;

template<class T>
class AVLTree {
    
private:
    AVLNode<T> * root;

    AVLNode<T> *rotateRR(AVLNode<T> *);
    AVLNode<T> *rotateLL(AVLNode<T> *);
    AVLNode<T> *rotateLR(AVLNode<T> *);
    AVLNode<T> *rotateRL(AVLNode<T> *);
    AVLNode<T> *balance(AVLNode<T> *);

    int heightDifference(AVLNode<T> *) const;

    void recursiveDeallocate(AVLNode<T> *);
    AVLNode<T> * recursiveInsert(AVLNode<T> *, T);
    int recursiveHeight(AVLNode<T> *) const;
    AVLNode<T> *recursiveFind(AVLNode<T> *, T) const;
    AVLNode<T> *recursiveDelete(AVLNode<T> *, T);
    AVLNode<T> *recursiveMinimum(AVLNode<T> *) const;
    void recursivePrint(AVLNode<T> *, int) const;
public:
    AVLTree();
    ~AVLTree();

    void insert(T);
    void delete_(T);
    AVLNode<T> * find(T) const;
    void print() const;
};

template<class T>
AVLTree<T>::AVLTree() {
    root = nullptr;
}

template<class T>
AVLTree<T>::~AVLTree() {
    recursiveDeallocate(root);
}

template<class T>
void AVLTree<T>::recursiveDeallocate(AVLNode<T> * node) {
    if (node == nullptr) {
        return;
    }
    recursiveDeallocate(node->getLeft());
    recursiveDeallocate(node->getRight());
    delete node;
}

template<class T>
int AVLTree<T>::recursiveHeight(AVLNode<T> * node) const {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = recursiveHeight(node->getLeft());
    int rightHeight = recursiveHeight(node->getRight());
    int max_height = leftHeight > rightHeight ? leftHeight : rightHeight;
    return max_height + 1;
}

template<class T>
int AVLTree<T>::heightDifference(AVLNode<T> * node) const {
    return recursiveHeight(node->getLeft()) - recursiveHeight(node->getRight());
}

template<class T>
AVLNode<T> * AVLTree<T>::balance(AVLNode<T> * node) {
    int heightDifference = this->heightDifference(node);
    // cout << "balancing " << node->getData() << " " << heightDifference << endl;
    if (heightDifference < -1) {
        if (this->heightDifference(node->getRight()) <= 0) {
            node = rotateRR(node);
        } else {
            node = rotateRL(node);
        }
    } else if (heightDifference > 1) {
        if (this->heightDifference(node->getLeft()) <= 0) {
            node = rotateLR(node);
        } else {
            node = rotateLL(node);
        }
    }
    // recursivePrint(node, 0);
    return node;
}

template<class T>
AVLNode<T> *AVLTree<T>::rotateRR(AVLNode<T> * parent){
    AVLNode<T> *temp = parent->getRight();
    parent->setRight(temp->getLeft());
    temp->setLeft(parent);
    return temp;
}

template<class T>
AVLNode<T> *AVLTree<T>::rotateLL(AVLNode<T> * parent){
    AVLNode<T> *temp = parent->getLeft();
    parent->setLeft(temp->getRight());
    temp->setRight(parent);
    return temp;
}

template<class T>
AVLNode<T> *AVLTree<T>::rotateLR(AVLNode<T> * parent){
    AVLNode<T> * temp = parent->getLeft();
    parent->setLeft(rotateRR(temp));
    return rotateLL(parent);
}

template<class T>
AVLNode<T> *AVLTree<T>::rotateRL(AVLNode<T> * parent){
    AVLNode<T> * temp = parent->getRight();
    parent->setRight(rotateRR(temp));
    return rotateRR(parent);
}

template<class T>
AVLNode<T> * AVLTree<T>::recursiveFind(AVLNode<T> *node, T data) const {
    if (node->compare(data) == AVLNode<T>::EQUAL) {
        return node;
    }
    AVLNode<T> *leftFind = recursiveFind(node->getLeft(), data);
    if (leftFind != nullptr) {
        return leftFind;
    }
    AVLNode<T> *rightFind = recursiveFind(node->getRight(), data);
    return rightFind;
}

template<class T>
AVLNode<T> * AVLTree<T>::find(T data) const {
    return recursiveFind(root, data);
}

template<class T>
void AVLTree<T>::recursivePrint(AVLNode<T> *node, int space) const {
    if (node == nullptr)
        return;

    space += 10;
    recursivePrint(node->getRight(), space);
    cout << endl;
    for (int i = 10; i < space; i++)
        cout << " ";
    cout << node->getData() << "\n";
    recursivePrint(node->getLeft(), space);
}

template<class T>
void AVLTree<T>::print() const {
    recursivePrint(root, 0);
}

template<class T>
AVLNode<T> *AVLTree<T>::recursiveMinimum(AVLNode<T> * node) const {
    if (node == nullptr) {
        return nullptr;
    } else if (node->getLeft() == nullptr) {
        return node;
    } else {
        return recursiveMinimum(node->getLeft());
    }
}

template<class T>
AVLNode<T> *AVLTree<T>::recursiveDelete(AVLNode<T> *node, T data) {
    if (node == nullptr) {
        return nullptr;
    } else if (node->compare(data) == AVLNode<T>::LESS) {
        node->setRight(recursiveDelete(node->getRight(), data));
    } else if (node->compare(data) == AVLNode<T>::GREATER) {
        node->setLeft(recursiveDelete(node->getLeft(), data));
    } else {
        if (node->getLeft() != nullptr && node->getRight() != nullptr) {
            AVLNode<T> *temp = recursiveMinimum(node->getRight());
            node->setData(temp->getData());
            node->setRight(recursiveDelete(node->getRight(), node->getData()));
        } else {
            AVLNode<T> * temp = node;
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

template<class T>
void AVLTree<T>::delete_(T data) {
    root = recursiveDelete(root, data);
}

template<class T>
AVLNode<T>* AVLTree<T>::recursiveInsert(AVLNode<T>* node, T data){
    if (root == nullptr) {
        root = new AVLNode<T>(data, nullptr, nullptr);
        return root;
    } else if (node->compare(data) == AVLNode<T>::GREATER) {
        if (node->getLeft() == nullptr) {
            AVLNode<T> * newNode = new AVLNode<T>(data, nullptr, nullptr);
            node->setLeft(newNode);
            node = balance(node);
            return newNode;
        } else {
            return recursiveInsert(node->getLeft(), data);
        }
   } else {
        if (node->getRight() == nullptr) {
            AVLNode<T> * newNode = new AVLNode<T>(data, nullptr, nullptr);
            node->setRight(newNode);
            // recursivePrint(node, 0);
        } else {
            node->setRight(recursiveInsert(node->getRight(), data));
        }
        // cout << "currently at " << node->getData() << endl;
        node = balance(node);
        return node;
   } 
}

template<class T>
void AVLTree<T>::insert(T data){
    root = recursiveInsert(root, data);
}

