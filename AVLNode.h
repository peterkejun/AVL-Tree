
template<typename T> class AVLNode
{
private:
    T data;
    AVLNode * left;
    AVLNode * right;
public:
    AVLNode(T data, AVLNode*left, AVLNode*right);
    ~AVLNode();
    T getData();
    void setData(int newData);
};

template<typename T> 
AVLNode<T>::AVLNode(T data, AVLNode*left, AVLNode*right){
    this->data = data;
    this->left = left;
    this->right = right;
}

template<typename T> 
T AVLNode<T>::getData(){
    return this->data;
}

template<typename T> 
void AVLNode<T>::setData(int data){
    this->data = data;
}