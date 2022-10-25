driver: main.cc AVLTree.cc AVLNode.cc
	g++ -std=c++11 -o driver main.cc AVLTree.cc AVLNode.cc

clean:
	rm driver