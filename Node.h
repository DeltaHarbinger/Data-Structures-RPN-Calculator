//
// Created by Brandon Chung on 3/12/2018.
//

#ifndef DATASTRUCTURESPROJECT_NODE_H
#define DATASTRUCTURESPROJECT_NODE_H


class Node {
private:
	double data;
	Node * nextNode;

public:


	Node(double data) : data(data) {
		nextNode = nullptr;
	}

	double getData() const {
		return data;
	}

	void setData(double data) {
		Node::data = data;
	}

	Node * getNextNode() const {
		return nextNode;
	}

	void setNextNode(Node *nextNode) {
		Node::nextNode = nextNode;
	}


};


#endif //DATASTRUCTURESPROJECT_NODE_H
