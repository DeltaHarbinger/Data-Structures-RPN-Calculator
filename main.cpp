#include <iostream>
#include <conio.h>
#include <sstream>
#include <fstream>
#include "Stack.h"

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
	std::cout << "\t|  " << divideSymbol << "  |\t\t\t|  0  |\t\t\t\t|  .  |\t\t\t\t|  3  |" << std::endl;
	std::cout << "\t-------\t\t\t-------\t\t\t\t-------\t\t\t\t-------" << std::endl;

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

void loadAnswer(){
	std::ifstream reader;
	reader.open("memory.txt", std::ios::in);
	std::string temp;
	reader >> temp;
	calculatorFace = trimStringZeroes(temp);
	reader.close();
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
			calculatorFace = "";

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
			}
		}
	}

	return 0;
}