//
// Created by Brandon Chung, Ryhane Roberts, Phillip Drummond on 3/30/2018.
//

#include <iostream>
#include <conio.h>
#include <sstream>
#include <fstream>
#include "Stack.h"
#include "OperatorStack.h"

Stack * numberStack = new Stack();
std::string calculatorFace = "";
double memory = 0.0f;
static const unsigned char divideSymbol = 246;

double solveEquation(double a, double b, char operation){
	/* Receives two doubles and an operator, returns an evaluated value. Throws integer if invalid */
	switch(operation){
		case '+':
			return b + a;
		case '-':
			return b - a;
		case '*':
			return b * a;
		case '/':
			return b / a;
		default:
			throw -3;
	}
}

void calculateOnStack(char operation){
	/*	Receives operation and executes on two variables removed from stack.	*/
	double a = numberStack -> stackTop();
	numberStack -> pop();
	double b = numberStack -> stackTop();
	numberStack -> pop();
	numberStack -> push(solveEquation(a, b, operation));
}

bool checkInput(char input){
	/*	Validates which characters a user may enter.	*/
	std::string validCharacters = "0123456789+-*/ .";
	return validCharacters.find(input) != std::string::npos;
}

bool isNumber(std::string s){
	/*	Validates whether or not value entered is a number.	*/
	return s.find_first_not_of( "0123456789." ) == std::string::npos;
}

bool isOperator(std::string s){
	/*	Validates whether or not value entered is an operator.	*/
	return s.find_first_not_of( "+-*/" ) == std::string::npos;
}

bool isSpecialCharacter(std::string input){
	return input.find_first_not_of(("=mcfx" + char(8))) == std::string::npos;
}

void solveFace(std::string face){
	while(face.back() == ' '){
		face = face.substr(0, face.size() - 1);
	}
	std::stringstream buffer;
	buffer << face;
	while(buffer.rdbuf() -> in_avail()){
		std::string currentValue;
		buffer >> currentValue;

		if(isNumber(currentValue)){
			numberStack -> push(std::stod(currentValue));
		} else if(isOperator(currentValue) && currentValue.length() == 1){
			calculateOnStack(currentValue[0]);
		} else{
			numberStack -> empty();
			return;
		}
	}
}

std::string trimStringZeroes(std::string s){
	/*	Deletes characters until a number other than zero or period is found.	*/
	while(s.back() == '0' && s.size() > 0){
		s = s.substr(0, s.size() - 1);
		if(s.back() == '.'){
			return s.substr(0, s.size() - 1);
		}
	}
	return s;
}

void paintCalculator(){
	/*	Creates Calculator's interface.	*/
	system("cls");
	std::cout << "-----------------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << calculatorFace << std::endl;
	std::cout << "-----------------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "\t-------" << std::endl;
	std::cout << "\t|  f  |" << std::endl;
	std::cout << "\t-------" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "\t-------\t\t\t-------\t\t\t\t-------\t\t\t\t-------" << std::endl;
	std::cout << "\t|  x  |\t\t\t|  m  |\t\t\t\t|  c  |\t\t\t\t|  b  |" << std::endl;
	std::cout << "\t-------\t\t\t-------\t\t\t\t-------\t\t\t\t-------" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "\t-------\t\t\t-------\t\t\t\t-------\t\t\t\t-------" << std::endl;
	std::cout << "\t|  -  |\t\t\t|  7  |\t\t\t\t|  8  |\t\t\t\t|  9  |" << std::endl;
	std::cout << "\t-------\t\t\t-------\t\t\t\t-------\t\t\t\t-------" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "\t-------\t\t\t-------\t\t\t\t-------\t\t\t\t-------" << std::endl;
	std::cout << "\t|  +  |\t\t\t|  4  |\t\t\t\t|  5  |\t\t\t\t|  6  |" << std::endl;
	std::cout << "\t-------\t\t\t-------\t\t\t\t-------\t\t\t\t-------" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "\t-------\t\t\t-------\t\t\t\t-------\t\t\t\t-------" << std::endl;
	std::cout << "\t|  *  |\t\t\t|  1  |\t\t\t\t|  2  |\t\t\t\t|  3  |" << std::endl;
	std::cout << "\t-------\t\t\t-------\t\t\t\t-------\t\t\t\t-------" << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "\t-------\t\t\t-------\t\t\t\t-------\t\t\t\t-------" << std::endl;
	std::cout << "\t|  /  |\t\t\t|  0  |\t\t\t\t|  .  |\t\t\t\t|  =  |" << std::endl;
	std::cout << "\t-------\t\t\t-------\t\t\t\t-------\t\t\t\t-------" << std::endl;

}

void clearFace(){
	calculatorFace = "";
}

void overwriteMemory(){
	memory = numberStack -> stackTop();
}

void loadMemory(){
	calculatorFace = trimStringZeroes(std::to_string(memory));
}

void storeAnswer(){
	std::ofstream writer;
	writer.open("memory.txt", std::ios::out | std::ios::app);
	std::string answer = trimStringZeroes(std::to_string(memory)) + "\n";
	writer << answer << std::endl;
	writer.close();
}

//void loadAnswer(){
//	std::ifstream reader;
//	reader.open("memory.txt", std::ios::in);
//	std::string temp;
//	reader >> temp;
//	calculatorFace = trimStringZeroes(temp);
//	reader.close();
//}

int operatorPriority(char c){
	if(c == '+' || c == '-'){
		return 1;
	} else {
		return 2;
	}
}

std::string convertInfixToPostfix(std::string infix){
	OperatorStack * operatorStack = new OperatorStack();
	std::string postfix = "";
	std::stringstream source;
	source << infix;
	while(source.rdbuf() -> in_avail()){
		std::string data;
		source >> data;
		if(isNumber(data)){
			postfix = postfix + data + " ";
		} else if(isOperator(data) && data.length() == 1){
			if(operatorStack -> count() == 0){
				operatorStack -> push(data[0]);
			} else {
				if(operatorPriority(data[0]) < operatorPriority(operatorStack -> stackTop())) {
					while (operatorStack->count() > 0 && operatorPriority(data[0]) < operatorPriority(operatorStack->stackTop())) {
						postfix = postfix + (operatorStack->stackTop()) + " ";
						std::cout << "ddd" << std::endl;
						operatorStack->pop();
					}
				}
				operatorStack -> push(data[0]);
			}
		} else {
			operatorStack -> empty();
			throw -5;
		}
	}
	while(operatorStack -> count() > 0){
		postfix = postfix + (operatorStack -> stackTop()) + " ";
		operatorStack -> pop();
	}
	delete operatorStack;
	return postfix;
}

int main() {
	char input = 0;
	while(input != 'x') { /*	Entering x exits calculator.	*/
		while (input != 'x' && input != '=') {
			paintCalculator();
			input = getch();	/*	Receives user input	*/
			if (checkInput(input)) {
				calculatorFace = calculatorFace + input;
			} else if (input == 8) {
				calculatorFace = calculatorFace.substr(0, calculatorFace.size() - 1);
			} else if (input == 'm'){
				loadMemory();
			} else if(input == 'f'){
				storeAnswer();
			} else if(input == 'c'){
				clearFace();
			} else if(input == 'p'){
				try {
					calculatorFace = convertInfixToPostfix(calculatorFace);
				} catch (int i){
					calculatorFace = "";
				}
			}
		}
		if(input == '=') {
			try {
				solveFace(calculatorFace);

				if (numberStack->count() == 1) {
					overwriteMemory();
					calculatorFace =  calculatorFace + "\n" + std::to_string(numberStack->stackTop());
				} else {
					throw -4;
				}
			} catch (int i) {
				if (i == -1 || i == -2) {
					calculatorFace = "Syntax error";
				} else if (i == -3) {
					calculatorFace = "Invalid symbol entered";
				} else if (i == -4) {
					calculatorFace = "Invalid expression";
				}
			} catch (const std::out_of_range& oor) {	/*	Validates whether or not entered double is too large.	*/
				calculatorFace = "Number too large\n";
			}

			calculatorFace = trimStringZeroes(calculatorFace);

			paintCalculator();
			clearFace();

			numberStack->empty();

			input = getch();
			if (checkInput(input)) {
				calculatorFace = calculatorFace + input;
			} else if (input == 8) {
				calculatorFace = calculatorFace.substr(0, calculatorFace.size() - 1);
			} else if (input == 'm'){
				loadMemory();
			} else if(input == 'f'){
				storeAnswer();
			} else if(input == 'c'){
				clearFace();
			}
		}
	}

	return 0;
}