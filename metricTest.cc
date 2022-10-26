#include <iostream>
#include <string>
#include <vector>
#include "AVLTree.h"
using namespace std;

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
    int testSize = 100000;
    //0=>insert, 1=>delete, 2=>find
    int mode = 0;
    if(argc > 2){
        testSize = convert(argv[1]);
        mode = convert(argv[2]);
    }

    vector<int> testVector;
    cout << "GENERATING " << testSize << "ELEMENTS" << endl;
    for(int i = 0; i < testSize; i++){
        testVector.push_back(rand() % testSize);
    }

    AVLTree<int> tree;
    //Interate through the tests
    cout << "INSERTING " << testSize << " ELEMENTS" << endl;
    for(int i = 0; i < testSize; i++){
        tree.insert(testVector.at(i));
        if(mode == 2 && rand() % 10 == 0){
            int element = testVector.at(i);
            cout << "FINDING " << element << endl;
            tree.find(element);
        }
    }

    if(mode == 1){
        cout << "DELETING " << testSize << " ELEMENTS" << endl;
        for(int i = 0; i < testSize; i++){
            tree.delete_(testVector.at(i));
        }
    }
    
    return 0;
}

