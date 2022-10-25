#include "AVLNode.h"

class AVLTree {
    
private:
    AVLNode * root;

    AVLNode *rotateRR(AVLNode *);
    AVLNode *rotateLL(AVLNode *);
    AVLNode *rotateLR(AVLNode *);
    AVLNode *rotateRL(AVLNode *);
    AVLNode *balance(AVLNode *);

public:
    AVLTree();
    ~AVLTree();

    void insert(int);
    void delete_(int);
    AVLNode * find(int);
};
