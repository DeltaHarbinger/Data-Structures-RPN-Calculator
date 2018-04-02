//
// Created by Brandon Chung on 3/30/2018.
//

#ifndef DATASTRUCTURESPROJECTREDO_OPERATORNODE_H
#define DATASTRUCTURESPROJECTREDO_OPERATORNODE_H


class OperatorNode {

private:
	char data;
	OperatorNode * nextNode;

public:
	OperatorNode(char data) : data(data) {
		nextNode = nullptr;
	}

	OperatorNode() {
		data = 0;
	}

	char getData(){
		return data;
	}

	void setData(char data){
		this -> data = data;
	}

	OperatorNode * getNextNode(){
		return nextNode;
	}

	void setNextNode(OperatorNode * nextNode){
		this -> nextNode = nextNode;
	}


};


#endif //DATASTRUCTURESPROJECTREDO_OPERATORNODE_H
