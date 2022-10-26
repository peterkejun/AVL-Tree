// Binary Search Tree implementation in C++, used for testing comparison against our AVL library
// Original code from https://gist.github.com/harish-r/a7df7ce576dda35c9660, Harish R

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BST {
    
    struct node {
        int data;
        node* left;
        node* right;
    };

    node* root;

    node* makeEmpty(node* t) {
        if(t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }

    node* insert(int x, node* t)
    {
        if(t == NULL)
        {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
        }
        else if(x < t->data)
            t->left = insert(x, t->left);
        else if(x > t->data)
            t->right = insert(x, t->right);
        return t;
    }

    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t) {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    node* remove(int x, node* t) {
        node* temp;
        if(t == NULL)
            return NULL;
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
            t->right = remove(x, t->right);
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }

        return t;
    }

    void inorder(node* t) {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

    node* find(node* t, int x) {
        if(t == NULL)
            return NULL;
        else if(x < t->data)
            return find(t->left, x);
        else if(x > t->data)
            return find(t->right, x);
        else
            return t;
    }

public:
    BST() {
        root = NULL;
    }

    ~BST() {
        root = makeEmpty(root);
    }

    void insert(int x) {
        root = insert(x, root);
    }

    void remove(int x) {
        root = remove(x, root);
    }

    void display() {
        inorder(root);
        cout << endl;
    }

    void search(int x) {
        find(root, x);
    }
};

static intmax_t convert( const char * str ) {			
	char * endptr;
	errno = 0;											
	intmax_t val = strtoll( str, &endptr, 10 );			
	if ( errno == ERANGE ) throw std::out_of_range("");
	if ( endptr == str ||								
		 *endptr != '\0' ) throw std::invalid_argument(""); 
	return val;
}

int main(int argc, char *argv[]) {
    long long int testSize = 100000;
    //0=>insert, 1=>delete, 2=>find
    int mode = 0;
    if(argc > 2){
        testSize = convert(argv[1]);
        mode = convert(argv[2]);
    }

    vector<int> testVector;
    cout << "GENERATING " << testSize << " ELEMENTS" << endl;
    for(long long int i = 0; i < testSize; i++){
        testVector.push_back(rand() % testSize);
    }

    BST tree;
    //Interate through the tests
    cout << "INSERTING " << testSize << " ELEMENTS" << endl;
    for(long long int i = 0; i < testSize; i++){
        tree.insert(testVector.at(i));
    }

    if(mode == 1){
        cout << "DELETING " << testSize << " ELEMENTS" << endl;
        for(long long int i = 0; i < testSize; i++){
            tree.remove(testVector.at(i));
        }
    }

    if(mode == 2){
        cout << "FINDING" << endl;
        for(long long int i = 0; i < testSize; i++){
            int element = testVector.at(i);
            tree.search(element);
        }
    }
    
    return 0;
}