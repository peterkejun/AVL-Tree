#ifndef __AVL_NODE_H__
#define __AVL_NODE_H__

class AVLNode
{
private:
    int data;
    AVLNode * left;
    AVLNode * right;
public:
    AVLNode(int data, AVLNode*left, AVLNode*right);
    ~AVLNode();
    int getData() const;
    AVLNode* getLeft() const;
    AVLNode* getRight() const;
    void setData(int newData);
    void setLeft(AVLNode * left);
    void setRight(AVLNode * right);
};
#endif
