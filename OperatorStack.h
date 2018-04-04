//
// Created by Brandon Chung, Ryhane Roberts, Phillip Drummond on 3/30/2018.
//

#ifndef DATASTRUCTURESPROJECTREDO_OPERATORSTACK_H
#define DATASTRUCTURESPROJECTREDO_OPERATORSTACK_H

#include "OperatorNode.h"

class OperatorStack {
private:
	OperatorNode * top;

public:

	OperatorStack(){
		top = nullptr;
	}

	char stackTop(){
		if(top){
			return top -> getData();
		} else {
			throw -1;
		}
	}

	void pop(){
		if(top){
			OperatorNode * temp = top;
			top = top -> getNextNode();
			delete temp;
		} else {
			throw -2;
		}
	}

	void push(char data){
		if(OperatorNode * temp = new OperatorNode(data)){
			temp -> setNextNode(top);
			top = temp;
		}
	}

	int count(){
		if(!top){
			return 0;
		}
		int count = 0;
		OperatorStack * tempOperatorStack = new OperatorStack();
		while(top){
			count++;
			tempOperatorStack -> push(this -> stackTop());
			this -> pop();
		}

		for(int x = 0; x < count; x++){
			this -> push(tempOperatorStack -> stackTop());
			tempOperatorStack -> pop();
		}

		return count;
	}

	void empty(){
		while(top){
			OperatorNode * temp = top;
			top = top -> getNextNode();
			delete temp;
		}
	}
};


#endif //DATASTRUCTURESPROJECTREDO_OPERATORSTACK_H
