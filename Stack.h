//
// Created by Brandon Chung on 3/30/2018.
//

#ifndef DATASTRUCTURESPROJECTREDO_STACK_H
#define DATASTRUCTURESPROJECTREDO_STACK_H



#include "Node.h"

class Stack {

private:
	Node * top;

public:

	Stack() {
		/*	Creates a new stack	*/
		top = nullptr;
	}


	double stackTop(){
		/*	Returns data on top of the stack. If stack empty throws integer	*/
		if(top){
			return top -> getData();
		} else {
			throw -1;
		}
	}


	void pop(){
		/*	Removes data from top of stack. If stack empty throws integer	*/
		if(top) {
			Node *temp = top;
			top = top->getNextNode();
			delete temp;
		} else {
			throw -2;
		}
	}


	void push(double data){
		/*	Enters received data to the stack. */
		if(Node * temp = new Node(data)){
			temp -> setNextNode(top);
			top = temp;
		}
	}


	int count(){
		/*	If no item found in stack exits method. Else creates a temporary stack. Counts each item as removed and places into the new stack. When stack is empty, the temporary stack then pushes all it's content back to the original stack.	*/
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
		for(int x = 0; x < count; x++){
			this -> push(tempStack->stackTop());
			tempStack->pop();
		}

		return count;
	}


	void empty(){
		/*	Removes all data from the stack.	*/
		while(top){
			Node * temp = top;
			top = top -> getNextNode();
			delete temp;
		}
	}


};



#endif //DATASTRUCTURESPROJECTREDO_STACK_H
