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

	static bool isSemicolumn(char c) {
		return c == '.' || c == ',';
	}

	static bool isOperator(char c) {
		return c == '+' || c == '-' || c == '/' || c == '*';
	}

	static bool isSpace(char c) {
		return c == ' ';
	}

	static bool isRoundedBrackets(char c) {
		return c == '(' || c == ')';
	}

	static bool isSqareBrackets(char c) {
		return c == '[' || c == ']';
	}

	static double* micsorareVector() {

	}
};


class Expressions {
	char* input = nullptr;
	double* numericValues = nullptr;
	int contorNumValues = 0;
	char* operators = nullptr;
	int contorOperators = 0;

	char* priority = nullptr;

public:

	char* getInput() {
		if (input == nullptr) {
			return nullptr;
		}
		cout << this->input << endl;
		return Util::copiereString(this->input);

	}

	double* getNumericValues(char* input) {
		return this->numericValues = parseNumericValues(input);
	}

	char* getOperators(char* input) {
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
			else if (Util::isSemicolumn(input[i])) {
				tempNum[tempContor] = input[i];
				tempContor++;
				//cout << endl << "Hi " << tempNum;
			}
			else if (tempContor > 0) {   // daca input[i] nu mai e cifra atunci ceea ce e in tempContor va fi transformat in int si va fi pus extractedNum
				tempNum[tempContor] = '\0';
				double num = stod(tempNum);
				//cout << endl << "Hello " << num;
				contor++;

				double* newExtractedNum = new double[extractedNumContor + 1]; // newExtractedNum se mareste odata cu gasirea unui numar

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

	char* findPriority(const char* op) {

		op = getOperators(input);
		priority = new char[contorOperators];


		for (int i = 0; i < contorOperators; i++) {

			if (op[i] == '*' || op[i] == '/') {
				priority[i] = '1';
			}
			else {
				priority[i] = '0';
			}

		}
		
		/*cout << endl<<"Priority ";
		for (int i = 0; i < contorOperators; i++) {
			cout << priority[i] << " ";
		}*/
		return priority;
	}


	int test() {
		cout << endl << (contorOperators);
		return contorNumValues + 1 / sizeof(numericValues[0]);
	}



	double performOperation(double num1, double num2, char op) {

		switch (op) {
		case '+':
			return num1 + num2;
		case '-':
			return num1 - num2;
		case '*':
			return num1 * num2;
		case '/':
			if (num2 != 0) {
				return num1 / num2;
			}
			else {
				throw invalid_argument("Nu se poate efectua impartirea la 0!");
			}
		default:
			throw invalid_argument("Operator invalid!");
		}
	}

	double findResult(char* userInput) {  //PT CLASA CALCULATOR   //momentan imi ia operatiile pe rand => 12+9/5 il va lua ca 12+9=21/5=4.2
		
		numericValues = getNumericValues(userInput);
		operators = getOperators(userInput);

		double result = numericValues[0];

		for (int i = 0; i < contorOperators; i++) {
			double nextNumber = numericValues[i + 1];
			char nextOperator = operators[i];

			result = performOperation(result, nextNumber, nextOperator);
		}

		cout << endl << result;
		return result;
	}

	double findResult(double* numVal, const char* op, const char* priority) { //PT TESTE //momentan imi ia operatiile pe rand => 12+9/5 il va lua ca 12+9=21/5=4.2

		numVal = getNumericValues(input);
		op = getOperators(input);
		priority = findPriority(op);

		double result = 0;

		for (int i = 0; i < contorOperators; i++) {
			double nextNumber = numericValues[i + 1];
			char nextOperator = operators[i];

			char oldNextOperator = nextOperator;
			/*cout << endl << nextNumber;
			cout << endl << endl;*/

			if (priority[i] == '1') {
				for(int j = 0; j< contorNumValues; j++){ 
					double result = numVal[j];
					double oldResult = result; 
					double oldNextNum = nextNumber;


					result = performOperation(result, nextNumber, nextOperator);
					cout << endl << "Next Op" << nextOperator;


					cout <<endl <<"Rezultat " << result;
					//cout << endl << "contorNumValues " << contorNumValues;


					//AM MICSORAT VECTORUL numVal SI ADAUGAT VALORILE NOI
					int oldContorNumValues = contorNumValues;
					contorNumValues -= 1;


					double* newNumVal = nullptr;
					delete[] newNumVal;
					newNumVal = new double[contorNumValues];

					int contorNewVal = 0;

						for (int i = 0; i < contorNumValues+1; ++i) {
							//cout << endl<<"NumVAL I" << numVal[i]<<endl;

							if (numVal[i] != oldResult) {
								if (numVal[i] == oldNextNum) {
									numVal[i] = result;
								}
								newNumVal[contorNewVal] = numVal[i];
								++contorNewVal;
							}


							if (contorNewVal > contorNumValues) {
								contorNewVal--;
							}
						}

					delete[] numVal;
					numVal = new double[oldContorNumValues];
					numVal = newNumVal;
					

					cout << endl << "vector vechi ";
					for (int i = 0; i < contorNumValues; i++) {
						cout << numVal[i] << " ";
					}
				}

				// AICI VREAU SA MICSOREZ VECTORUL CU OPERATORI momentan nu merge bine
				// DUPA ASTA TREBUIE SA VAD PRIORITATEA DIN NOII VECTORI IAR DACA NU MAI EXISTA VREO PRIORITATE = 1 SE VA FACE CALCULUL NORMAL
				int oldContorOperators = contorOperators;
				contorOperators -= 1;

				char* newOp = nullptr;
				delete[] newOp;
				newOp = new char[contorOperators];

				int contorNewOp = 0;

				for (int k = 0; k < contorOperators + 1; ++k) {

					if (op[k] != oldNextOperator) {
						newOp[contorNewOp] = op[k];
						++contorNewOp;

					}


					if (contorNewOp > contorOperators) {
						contorNewOp--;
					}
				}

				delete[] op;
				numVal = new double[oldContorOperators];
				op = newOp;
			
				cout << endl << "op vechi ";
				for (int i = 0; i < contorOperators; i++) {
					cout << op[i] << " ";
				}
				
			}
			
		}

		cout << endl << result;
		return result;
	}


	Expressions() {

	}

	Expressions(const char* userInput) {
		this->setInput(userInput);
	}

	~Expressions() {
		delete[] this->input;
		//cout<<endl << "deleted";
	}

	friend class OperatoriMatematici;

};

class Calculator: public Expressions {

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
			cout<<endl <<"Introdu ecuatia: "<<endl;
			char inputUser[100];
			cin >> inputUser;
			setInput(inputUser);
			Expressions::findResult(input);
			cout<<endl <<"___________"<< endl;

			//cout << getInput()<<endl;

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




class OperatoriMatematici : public Expressions, public Calculator {
	
};


int main() {

	//Calculator c1;
	//c1.afisareInserare();

	const char* input = "12.5+3-5";
	double* numVal = new double[3] {12, 3, 5};
	char* op = new char[2] {'+', '-'};

	const char* input2 = "12*9+10/2";
	double* numVal2 = new double[4] {12, 9, 10, 2};
	char* op2 = new char[3] {'*', '+', '/'};
	char* priority = new char[3] {'1', '0', '1'};

	/*Expressions exp3(input);
	exp3.parseNumericValues("12.1+3-5");*/


	/*Expressions exp1("12+9/5");
	exp1.getInput();
	exp1.getNumericValues();
	exp1.getOperators();
	exp1.test();*/

	Expressions exp2(input2);
	//exp2.getInput();
	//exp2.getNumericValues();
	//exp2.getOperators();
	exp2.findResult(numVal2, op2, priority);
	//exp2.findPriority(op2);

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