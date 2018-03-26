#include <iostream>
#include <conio.h>
#include <sstream>
#include "Stack.h"

Stack * numberStack = new Stack();
std::string calculatorFace = "";
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
	double a = numberStack -> stackTop();
	numberStack -> pop();
	double b = numberStack -> stackTop();
	numberStack -> pop();
	numberStack -> push(solveEquation(a, b, operation));
}

bool checkInput(char input){
	std::string validCharacters = "0123456789+-*/ .";
	return validCharacters.find(input) != std::string::npos;
}

bool isNumber(std::string s){
	return s.find_first_not_of( "0123456789." ) == std::string::npos;
}

bool isOperator(std::string s){
	return s.find_first_not_of( "+-*/" ) == std::string::npos;
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
	while(s.back() == '0' && s.size() > 0){
		s = s.substr(0, s.size() - 1);
		if(s.back() == '.'){
			return s.substr(0, s.size() - 1);
		}
	}
	return s;
}

void paintCalculator(){
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

int main() {



	char input = 0;
	while(input != 'x') {
		while (input != '=' && input != 'x') {
			paintCalculator();
			input = getch();
			if (checkInput(input)) {
				calculatorFace = calculatorFace + input;
			} else if (input == 8) {
				calculatorFace = calculatorFace.substr(0, calculatorFace.size() - 1);
			}
		}
		if(input == '=') {
			try {
				solveFace(calculatorFace);

				if (numberStack->count() == 1) {
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
			} catch (const std::out_of_range& oor) {
				calculatorFace = "Number too large\n";
			}

			calculatorFace = trimStringZeroes(calculatorFace);

			paintCalculator();
			calculatorFace = "";

			numberStack->empty();

			input = getch();
			if (checkInput(input)) {
				calculatorFace = calculatorFace + input;
			}
		}

	}

	return 0;
}