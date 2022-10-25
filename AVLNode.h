
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

void AVLNode::setData(int data){
    this->data = data;
}