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


	static int precedence(char op) {
		if (op == '+' || op == '-') {
			return 1;
		}
		if (op == '*' || op == '/') {
			return 2;
		}
		if (op == '^') {
			return 3;
		}
		if (op == '#') {
			return 4;
		}
		return 0; 
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

	static bool isExpresion(char c) {
		return  c == '^' || c == '#';
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

	static float scanNum(char ch) {
		int value;
		value = ch;
		return float(value - '0');
	}

};


class Stack {

private:
	float* stack = nullptr;
	int topStack = -1;
	int counterStack = 0;

public:


	Stack(int size = 100) {
		counterStack = size;
		stack = new float[counterStack];
		topStack = -1;
	}

	~Stack() {
		if (this->stack != nullptr) {
			delete[] stack;
			stack = nullptr;
		}
	}

	bool full() {
		return topStack >= counterStack - 1;
	}

	bool empty() {
		return topStack < 0;
	}

	bool push(float value) {
		if (full()) {
			return false;
		}
		
		stack[++topStack] = value;
		return true;
	}

	 float pop() {
		 if (empty()) {
			 cout << "Stack underflow" << endl;
			 return 0;
		 }

		return stack[topStack--];
	}

	 float peek() {
		 if (empty()) {
			 cout << "Stack is empty" << endl;
			 return 0;
		 }
		 return stack[topStack];
	 }

	 float top(){
		 return peek();
	 }

	 bool isEmpty() {
		 return topStack == -1;
	 }

};


class Expressions {
	char* input = nullptr;
	double* numericValues = nullptr;
	char* operators = nullptr;

	int contorOperators = 0;
	int contorNumValues = 0;

	int* priority = nullptr;

	Stack stack;

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

	int* findPriority(const char* op) {

		op = getOperators(input);
		priority = new int[contorOperators];


		for (int i = 0; i < contorOperators; i++) {

			if (op[i] == '*' || op[i] == '/') {
				priority[i] = 1;
			}
			else {
				priority[i] = 0;
			}

		}
		
		/*cout << endl<<"Priority ";
		for (int i = 0; i < contorOperators; i++) {
			cout << priority[i] << " ";
		}*/
		return priority;
	}




	int* findPriorityTEST() {

		int counterBrackets = 0;
		priority = new int[contorOperators];

		for (int i = 0; i < contorOperators; i++) {


			if (operators[i] == '*' || operators[i] == '/') {
				priority[i] = 2;
			}
			else if(Util::isRoundedBrackets(operators[i])) {
				priority[i] = 0;
			}
			else {
				priority[i] = 1;

			}

		}

		for (int i = contorOperators; i > 0; i--) {
			if (operators[i] == ')') {
				counterBrackets++;
			}
		}

		for (int i = 0; i < contorOperators; i++) {
			if (operators[i] == '(') {
				for (int j = 0; j < contorOperators; j++) {
					if (operators[j] == ')') {
						for (int k = i + 1; k < j - 1; k++) {

							//priority[k]++;

							if (operators[k] == '*' || operators[k] == '/') {
								priority[k] = priority[k] + counterBrackets;
							}
							else if (Util::isRoundedBrackets(operators[k])) {
								priority[k] = 0;
							}
							else if(operators[k] == '+' || operators[k] == '-') {
								priority[k] = priority[k]+counterBrackets;

							}
						}
					}
				}
				counterBrackets--;
				cout << endl;
				//for (int i = 0; i < contorOperators; i++) {
				//	cout << priority[i] << " ";
				//}
				break;
			}

			
		}

		//for (int i = 0; i < contorOperators; i++) {
		//	if (operators[i] == '(') {
		//		for (int j = contorOperators; j > 0; j--) {
		//			if (operators[j] == ')') {
		//				int counterBrackets = 0;
		//				counterBrackets++;
		//				for (int k = i + 1; k < j - 1; k++) {
		//					/*if (Util::isOperator(operators[k])) {
		//						priority[k]++;
		//					}*/

		//					if (operators[k] == '*' || operators[k] == '/') {
		//						priority[k] = priority[k] + 2 + counterBrackets;
		//					}
		//					else if (Util::isRoundedBrackets(operators[k])) {
		//						priority[k] = 0;
		//					}
		//					else if (operators[k] == '+' || operators[k] == '-') {
		//						priority[k] = priority[k] +1+counterBrackets;

		//					}
		//				}
		//			}
		//		}
		//	}
		//}

		cout << endl;
		for (int i = 0; i < contorOperators; i++) {
			cout << priority[i] << " ";
		}

		return priority;

	}

	char* parseOperatorsTEST(const char* input) {

		char* extractedOperators = nullptr;
		int extractedOperatorsContor = 0;

		for (int i = 0; i <= strlen(input); i++) {
			if (Util::isOperator(input[i]) || Util::isRoundedBrackets(input[i])) {
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

	char* getOperatorsTEST() {
		return this->operators = parseOperatorsTEST(input);
	}

	double* getNumericValuesTEST() {
		return this->numericValues = parseNumericValues(input);
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

	//double findResult(double* numVal, const char* op, int* priority) { //PT TESTE //momentan imi ia operatiile pe rand => 12+9/5 il va lua ca 12+9=21/5=4.2

	//	numVal = getNumericValues(input);
	//	op = getOperators(input);
	//	priority = findPriority(op);

	//	for (int i = 0; i < sizeof(priority) / sizeof(priority[0]); i++) {

	//		int maxPriority = Util::maxPriority(priority);
	//		int contorDefaultMaxPriority = 0;

	//		if (maxPriority == priority[i]) {
	//			contorDefaultMaxPriority++;
	//		}

	//		cout << endl << "MAX: " << maxPriority << endl;

	//	}


	//	double result = 0.0;

	//	for (int i = 0; i < contorOperators; i++) {




	//		//double nextNumber = numericValues[i + 1];
	//		//char nextOperator = operators[i];

	//		//if (priority[i] == '1') {
	//		//	double result2 = numVal[i];
	//		//	double oldResult = numVal[i];

	//		//	cout << "Old Res " << oldResult << endl;

	//		//		result2 = performOperation(result2, numVal[i + 1], op[i]);
	//		//		cout << endl << "Result -> " << result2;
	//		//		cout << endl << "Num Val " <<i<< " -> " << numVal[i];

	//		//		int oldNumValSize = contorNumValues;
	//		//		contorNumValues--;


	//		//		double* newNumVal = new double[contorNumValues]; //cu newNumVal vreau sa copiez valorile care au ramas(inclusiv rezultatul nou) din numVal 
	//		//		priority[i] = '0';


	//		//		numVal[i+1] = result2;
	//		//		numVal[i] = NULL;



	//		//		cout << endl << "Num val i+1" << i+1 << " ->" << numVal[i+1] << endl;

	//		//		int contorNewVal = 0;

	//		//		for (int j = 0; j < oldNumValSize+1; j++) {
	//		//			if (numVal[j] != NULL) {
	//		//				newNumVal[contorNewVal] = numVal[j];
	//		//				contorNewVal++;
	//		//			}
	//		//		}

	//		//		int priorityCheck = 0;
	//		//		for (int k = 0; k < contorOperators; k++) {
	//		//			if (priority[i] != '1') {
	//		//				priorityCheck++;
	//		//			}
	//		//		}

	//		//		if (priorityCheck == contorOperators) {
	//		//			delete[] numVal;
	//		//		numVal = new double[contorNumValues];

	//		//		for (int k = 0; k < contorNumValues; k++) {
	//		//			numVal[k] = newNumVal[k];
	//		//		}

	//		//		}
	//		//		//delete[] numVal;
	//		//		//numVal = new double[contorNumValues];
	//		//		//numVal = newNumVal;

	//		//		cout << endl << "NumVal: ";
	//		//		for (int l = 0; l < contorNumValues; l++) {
	//		//			cout << numVal[l] << " ";
	//		//		}


	//		//		cout <<endl <<"NewNumVal: ";
	//		//		for (int l = 0; l < contorNumValues; l++) {
	//		//			cout << newNumVal[l] << " ";
	//		//		}
	//		//		cout <<endl <<"Fin" << endl;

	//		//		cout <<endl <<"ContorNUm " << contorNumValues << endl;

	//		//}
	//		//cout << endl;
	//	}




	//	cout << endl << result;
	//	return result;
	//}


	//Reverse Polish Notation

	double RPN(string expression) {
		int i = 0;
		float v1, v2, result;
		v1 = result = v2 = 0.0;

		string tok = "";

		while (i < expression.length()) {
			//Skip white space
			while (isspace(expression[i])) {
				i++;
			}
			//Check for digits and .
			if (Util::isDigit(expression[i]) || expression[i] == '.') {
				while (Util::isDigit(expression[i]) || expression[i] == '.') {
					tok += expression[i];
					i++;
				}
				//Push on stack number.
				stack.push(atof(tok.c_str()));
				tok = "";
			}
			//Check for operator
			else if (Util::isOperator(expression[i])) {
				if (expression[i] == '+') {
					v1 = stack.pop();
					v2 = stack.pop();
					result = (v1 + v2);
				}
				if (expression[i] == '-') {
					v1 = stack.pop();
					v2 = stack.pop();
					result = v2 - v1;
				}
				if (expression[i] == '*') {
					v1 = stack.pop();
					v2 = stack.pop();
					result = (v1 * v2);
				}
				if (expression[i] == '/') {
					v1 = stack.pop();
					v2 = stack.pop();
					result = (v2 / v1);
				}
				//INC Counter
				i++;
				//Push result onto stack
				stack.push(result);
			}
			else {
				cout << "Invaild Expression." << endl;
				break;
			}
		}
		//Return answer
		return stack.pop();
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



class Expr4 {
	char* input = nullptr;
	Stack stack;

public:


	Expr4() {

	}

	~Expr4() {
		delete[] this->input;
	}

	char* getInput() {
		if (input == nullptr) {
			return nullptr;
		}
		cout << this->input << endl;
		return Util::copiereString(this->input);

	}

	void setInput(const char* input) {
		delete[] this->input;
		this->input = Util::copiereString(input);
	}

	float performOp(double a, double b, char op) { //GOOD
		switch (op) {
		case '+':
			return a + b;
		case '-':
			return b - a;
		case '*':
			return a * b;
		case '/':
			if (a == 0)
				cout << "Division by 0 is impossible.";
			return b / a;
		case '^':
			float pow = b;
			for (int i = 1; i < a; i++) {
				pow = pow*b;
			}
			return pow;
		}

		return 0.0;
	}



	char* infixToPostfixTEST(const char* infix) //TEST TO CHAR*
	{
		string result;

		for (int i = 0; i < strlen(infix) + 1; i++) {
			char c = infix[i];

			//e nou de la || in colo
			if (Util::isDigit(c) || (Util::isSemicolumn(c) && Util::isDigit(infix[i + 1]))) {
				//e nou de la while la i--;
				while (Util::isDigit(c) || Util::isSemicolumn(c)) {
					if (c == ',') {
						c = '.';
					}
					result += c;
					c = infix[++i];
				}
				i--;

				if (Util::isOperator(infix[i + 1]) || Util::isExpresion(infix[i + 1])) {
					result += ' ';
				}
			}
			else if (c == '(') {
				stack.push('(');
			}
			else if (c == ')') {
				while (stack.top() != '(') {
					result += stack.pop();
				}
				stack.pop();
			}
			else {
				while (!stack.empty()
					&& Util::precedence(c) <= Util::precedence(stack.top())) {
					result += stack.pop();
				}
				stack.push(c);
			}
		}

		while (!stack.empty()) {
			result += stack.pop();
		}

		
		char* charResult = new char(result.length() + 1);

		for (int i = 0; i < result.length(); i++) {
			charResult[i] = result[i];
		}


		/*for (int i = 0; i < result.length(); i++) {
			cout << charResult[i];
		}*/
		return charResult;

	}

	float evaluatePostfixTEST(const char* infix) { //TEST

		char* postfix = infixToPostfixTEST(infix);

		Stack s(strlen(infix));

		//cout << endl << "OK";


		for (int i = 0; i < strlen(postfix); i++) {
			char c = postfix[i];

			if (c == ' ') continue;
			else if (Util::isDigit(c)) {
				float num = 0;

				while (Util::isDigit(c)) {
					num = num * 10 + (c - '0');
					i++;
					c = postfix[i];
				}
				i--;

				s.push(num);
			}
			else {
				float val1 = s.top();
				s.pop();
				float val2 = s.top();
				s.pop();

				s.push(performOp(val1, val2, c));

			}
		}

		float result = s.pop();
		//cout << "AICI " << result << endl;
		return result;

	}



	string infixToPostfix() //GOOD
	{
		string result;

		for (int i = 0; i < strlen(input)+1; i++) {
			char c = input[i];

			//e nou de la || in colo
			if (Util::isDigit(c) || (Util::isSemicolumn(c) && Util::isDigit(input[i+1]))) {
				//e nou de la while la i--;
				while (Util::isDigit(c) || Util::isSemicolumn(c)) {
					if (c == ',') {
						c = '.';
					}
					result += c;
					c = input[++i];
				}
				i--;
				
				if (Util::isOperator(input[i + 1]) || Util::isExpresion(input[i+1])) {
					result += ' ';
				}
			}
			else if (c == '(') {
				stack.push('(');
			}
			else if (c == ')') {
				while (stack.top() != '(') {
					result += stack.pop();
				}
				stack.pop();
			}
			else {
				while (!stack.empty()
					&& Util::precedence(c) <= Util::precedence(stack.top())) {
					result += stack.pop();
				}
				stack.push(c);
			}
		}

		while (!stack.empty()) {
			result += stack.pop();
		}

		cout << result << endl;
		return result;

	}

	float evaluatePostfix(string postfix) { //GOOD

		postfix = infixToPostfix();
		Stack s(postfix.length());

		cout << endl<<"OK";


		for (int i = 0; i < postfix.length(); i++) {
			char c = postfix[i];

			if (c == ' ') continue;
			else if (Util::isDigit(c)) {
				float num = 0;

				while (Util::isDigit(c)) {
					num = num * 10 + (c - '0');
					i++;
					c = postfix[i];
				}
				i--;

				s.push(num);
			}
			else {
				float val1 = s.top();
				s.pop();
				float val2 = s.top();
				s.pop();

				s.push(performOp(val1, val2, c));
				
			}
		}

		float result = s.pop();
		cout <<"AICI "<< result << endl;
		return result;
		
	}


};



class Calculator: public Expr4 {

	char* input = nullptr;
	//string input;

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

			cout<<endl <<"Introdu ecuatia: ";
			char inputUser[100];
			cin >> inputUser;

			if (strcmp(inputUser, "exit") == 0) {
				break;
			}

			Expr4::setInput(inputUser);
			//Expr4::getInput();
			cout << "Result: " << Expr4::evaluatePostfixTEST(inputUser) << endl;
			cout<<endl <<"___________"<< endl;
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



int main() {

	Calculator c1;
	c1.afisareInserare();

	//"40+(5-1)*2"

	//Expr4 exp1;
	//exp1.setInput("(3*2)^2"); //40+4*2 = 48   9.4 10.0
	//exp1.getInput();
	//exp1.evaluatePostfix("(3*2)^2");
	//exp1.infixToPostfixTEST();

/*	Expr4 exp2;
	exp2.setInput("40.5+(5-1.1)*2");*/ //40+4*2 = 48
	//exp2.getInput();
	//exp1.evaluatePostfix("40.5+(5-1.1)*2");


	//while (true) {
	//	cout << "Introdu ecuatia: ";
	//	string input;
	//	cin >> input;

	//	if (input == "exit") {
	//		break;
	//	}
	//}

	return 0;
}