//
// Created by Brandon Chung on 3/12/2018.
//

#ifndef DATASTRUCTURESPROJECT_STACK_H
#define DATASTRUCTURESPROJECT_STACK_H

#include "Node.h"

class Stack {

private:
	Node * top;

public:

	Stack() {
		top = nullptr;
	}

	double stackTop(){
		if(top){
			return top -> getData();
		} else {
			throw -1;
		}
	}

	void pop(){
		if(top) {
			Node *temp = top;
			top = top->getNextNode();
			delete temp;
		} else {
			throw -2;
		}
	}

	void push(double data){

		if(Node * temp = new Node(data)){
			temp -> setNextNode(top);
			top = temp;
		}
	}

	int count(){
		if(!top){
			return 0;
		}

		int count = 0;

		Stack * tempStack = new Stack();



		while(top){
			count++;
			tempStack -> push(this -> stackTop());

			this -> pop();
		}

//		while(!empty){
//			try {
//				push(tempStack->stackTop());
//
//				tempStack->pop();
//			} catch(int i){
//				empty = true;
//			}
//		}

		for(int x = 0; x < count; x++){
			this -> push(tempStack->stackTop());
			std::cout << "Cherry" << std::endl;
			system("pause");
			tempStack->pop();
		}

		return count;
	}

	void empty(){
		while(top){
			Node * temp = top;
			top = top -> getNextNode();
			delete temp;
		}
	}


};


#endif //DATASTRUCTURESPROJECT_STACK_H
