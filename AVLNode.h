
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

AVLNode::AVLNode(int data, AVLNode*left, AVLNode*right){
    this->data = data;
    this->left = left;
    this->right = right;
}

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

void setLeft(AVLNode * left){
    this->left = left;
}

void setRight(AVLNode * right){
    this->right = right;
}