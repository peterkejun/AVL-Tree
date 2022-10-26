#include "AVLNode.h"

class AVLTree {
    
private:
    AVLNode * root;

    AVLNode *rotateRR(AVLNode *);
    AVLNode *rotateLL(AVLNode *);
    AVLNode *rotateLR(AVLNode *);
    AVLNode *rotateRL(AVLNode *);
    AVLNode *balance(AVLNode *);

    int heightDifference(AVLNode *) const;

    void recursiveDeallocate(AVLNode *);
    AVLNode * recursiveInsert(AVLNode *, int);
    int recursiveHeight(AVLNode *) const;
    AVLNode *recursiveFind(AVLNode *, int) const;
    AVLNode *recursiveDelete(AVLNode *, int);
    AVLNode *recursiveMinimum(AVLNode *) const;
    void recursivePrint(AVLNode *, int) const;
public:
    AVLTree();
    ~AVLTree();

    void insert(int);
    void delete_(int);
    AVLNode * find(int) const;
    void print() const;
};
