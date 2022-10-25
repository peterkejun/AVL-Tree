
class AVLNode
{
private:
    int data;
    AVLNode * left;
    AVLNode * right;
public:
    AVLNode(int data, AVLNode*left, AVLNode*right);
    ~AVLNode();
    int getData();
    AVLNode* getLeft();
    AVLNode* getRight();
    void setData(int newData);
};

AVLNode::AVLNode(int data, AVLNode*left, AVLNode*right){
    this->data = data;
    this->left = left;
    this->right = right;
}

int AVLNode::getData(){
    return this->data;
}

AVLNode* AVLNode::getLeft(){
    return this->left;
}

AVLNode* AVLNode::getRight(){
    return this->right;
}

void AVLNode::setData(int data){
    this->data = data;
}