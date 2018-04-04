//
// Created by Brandon Chung, Ryhane Roberts, Phillip Drummond on 3/30/2018.
//

#ifndef DATASTRUCTURESPROJECTREDO_NODE_H
#define DATASTRUCTURESPROJECTREDO_NODE_H


class Node {
private:
	double data;
	Node * nextNode;

public:


	Node(double data) : data(data) {
		/*	Initializes variables	*/
		nextNode = nullptr;
	}


	double getData() const {
		/*	Returns current data	*/
		return data;
	}


	void setData(double data) {
		/*	Sets received double to data	*/
		Node::data = data;
	}


	Node * getNextNode() const {
		/*	Returns current node pointer	*/
		return nextNode;
	}


	void setNextNode(Node *nextNode) {
		/*	Sets received node pointer to nextNode	*/
		Node::nextNode = nextNode;
	}


};

#endif //DATASTRUCTURESPROJECTREDO_NODE_H
