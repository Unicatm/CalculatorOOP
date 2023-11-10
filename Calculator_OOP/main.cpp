#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class Util {
public:
	static char* copiereString(const char* sursa) {
		if (sursa == nullptr) {
			return nullptr;
		}
		char* copie = new char[strlen(sursa) + 1];
		strcpy_s(copie, strlen(sursa) + 1, sursa);
		return copie;
	}

	static char* micsorareOperatorCuUnu(const char* operators, int contorOperators) {
		char* newOperatorVect = new char[contorOperators - 1];

		for (int j = 1; j < contorOperators; j++) {
			newOperatorVect[j-1] = operators[j];
		}

		delete[] operators;
		operators = newOperatorVect;

		return newOperatorVect;

	}

	static bool isDigit(char c) {
		return c >= '0' && c <= '9';
	}

	static bool isOperator(char c) {
		return c == '+' || c == '-' || c == '/' || c == '*';
	}

	static bool isSpace(char c) {
		return c == ' ';
	}

	static bool isRoundBrackets(char c) {
		return c == '(' || c == ')';
	}

	static bool isSqareBrackets(char c) {
		return c == '[' || c == ']';
	}
};


class Calculator {

	char* input = nullptr;

public:

	char* getInput() {

		if (input == nullptr) {
			return nullptr;
		}
		return Util::copiereString(this->input);

	}

	void setInput(const char* inputUser) {
		if (input) {
			delete[] input;
		}
		this->input = Util::copiereString(inputUser);
	}


	void afisareInserare() {

		while (true) {
			cout << "Introdu ecuatia: ";
			char inputUser[100];
			cin >> inputUser;
			setInput(inputUser);
		    

			cout << getInput()<<endl;

			if (strcmp(inputUser, "exit") == 0) {
				break;
			}
		}

	}

	Calculator() {

	}

	Calculator(const char* userInput) {
		this->setInput(userInput);
	}

	~Calculator() {
		delete[] this->input;
	}

};


class Expressions {
	char* input = nullptr;
	double* numericValues = nullptr;
	int contorNumValues = 0;
	char* operators = nullptr;
	int contorOperators = 0;

public:

	char* getInput() {
		if (input == nullptr) {
			return nullptr;
		}
		cout << this->input << endl;
		return Util::copiereString(this->input);
		
	}

	double* getNumericValues() {
		return this->numericValues = parseNumericValues(input);
	}

	char* getOperators() {
		return this->operators = parseOperators(input);
	}

	void setInput(const char* input) {
		delete[] this->input;
		this->input = Util::copiereString(input);
	}

	double* parseNumericValues(const char* input) {
		double* extractedNum = nullptr;  //vectorul ce va retine toate numerele din input
		int tempContor = 0;

		char* tempNum = new char[20];  //un char care va tine minte fiecare numar si o va stoca in extractedNum 

		int extractedNumContor = 0;

		int contor = 0;

 		for (int i = 0; i <= strlen(input); i++) {
			if (Util::isDigit(input[i])) {  //daca e cifra, cifra se stocheaza in tempNum
				tempNum[tempContor] = input[i];
				tempContor++;
			}
			else if (tempContor > 0) {   // daca input[i] nu mai e cifra atunci ceea ce e in tempContor va fi transformat in int si va fi pus extractedNum
				tempNum[tempContor] = '\0';
				int num = atoi(tempNum);
				contor++;

				double* newExtractedNum = new double[extractedNumContor+1]; // newExtractedNum se mareste odata cu gasirea unui numar

				for (int j = 0; j < extractedNumContor; j++) {  //copiez ceea ce e in extractedNum in newExtractedNum
					newExtractedNum[j] = extractedNum[j];
				}
				newExtractedNum[extractedNumContor] = num; //adaug noua valoare la finalul newExtractedNum

				delete[] extractedNum; //dezaloc memoria
				extractedNum = newExtractedNum;

				memset(tempNum, '\0', 20);  //golesc tempNum si tempContor pentru a putea baga in tempNum urmatorul numar: 12+9/5 => se sterge valoarea 12 pt a putea pune valoarea 9 in tempNum
				tempContor = 0;
				extractedNumContor++;
			}
		}


		contorNumValues = extractedNumContor;

		cout << endl;
		for (int i = 0; i < extractedNumContor; i++) {
			cout << extractedNum[i] << " ";
		}

		delete[] tempNum;
		return extractedNum;
	}

	char* parseOperators(const char* input) {
	
		char* extractedOperators = nullptr;  
		int extractedOperatorsContor = 0;

		for (int i = 0; i <= strlen(input); i++) {
			if (Util::isOperator(input[i])) {  
				char* newExtractedOperators = new char[extractedOperatorsContor + 1];

				for (int j = 0; j < extractedOperatorsContor; j++) {
					newExtractedOperators[j] = extractedOperators[j];
				}

				newExtractedOperators[extractedOperatorsContor] = input[i];

				delete[] extractedOperators; //dezaloc memoria
				extractedOperators = newExtractedOperators;

				extractedOperatorsContor++;
				contorOperators++;
			}
		}

		contorOperators = extractedOperatorsContor;

		cout << endl;

		for (int i = 0; i < extractedOperatorsContor; i++) {
			cout << extractedOperators[i] << " ";
		}

		return extractedOperators;
	}



	int test() {
		cout << endl << (contorOperators);
		return contorNumValues + 1 / sizeof(numericValues[0]);
	}



	double performOperation(double operand1, double operand2, char op) {

		switch (op) {
		case '+':
			return operand1 + operand2;
		case '-':
			return operand1 - operand2;
		case '*':
			return operand1 * operand2;
		case '/':
			if (operand2 != 0) {
				return operand1 / operand2;
			}
			else {
				throw invalid_argument("Nu se poate efectua impartirea la 0!");
			}
		default:
			throw invalid_argument("Operator invalid!");
		}
	}

	double findResult(double *numVal,const char* op) {  //momentan imi ia operatiile pe rand => 12+9/5 il va lua ca 12+9=21/5=4.2

		//numVal = numVal.getNumericVal();

		double result = numericValues[0];

		for (int i = 0; i < contorOperators; i++) {
			double nextNumber = numericValues[i + 1];
			char nextOperator = operators[i];

			result = performOperation(result, nextNumber, nextOperator);
		}

		cout << endl<<result;
		return result;
	}

	Expressions() {

	}

	Expressions(const char* userInput) {
		this->setInput(userInput);
	}

	~Expressions(){
		delete[] this->input;
		//cout<<endl << "deleted";
	}

	friend class OperatoriMatematici;

};

class OperatoriMatematici : public Expressions, public Calculator {
	
};


int main() {

	const char* input = "12+9/5";
	double* numVal = new double[3] {12, 9, 5};
	char* op = new char[2] {'+', '/'};


	/*Expressions exp1("12+9/5");
	exp1.getInput();
	exp1.getNumericValues();
	exp1.getOperators();
	exp1.test();*/

	Expressions exp2(input);
	exp2.getInput();
	exp2.getNumericValues();
	exp2.getOperators();
	exp2.findResult(numVal, op);

	cout << endl <<endl;

	/*Expressions exp2("2+9+1");
	exp2.getNumericValues();
	exp2.getOperators();
	exp2.afisare();*/

	//exp2.afisare();

	/*int* extractedNumbers = exp1.setNumericValues(input);
	cout << endl;

	for (int i = 0; extractedNumbers[i]; i++) {
		cout << extractedNumbers[i] << " ";
	}*/


	/*while (true) {
		cout << "Introdu ecuatia: ";
		string input;
		cin >> input;

		if (input == "exit") {
			break;
		}
	}*/

	return 0;
}