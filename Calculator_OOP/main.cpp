#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <string>
#include <cmath>


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

	static char* removeSpaces(const char* input) {

		int counterSpaces = 0;

		for (int i = 0; i < strlen(input); i++) {
			if (input[i] == ' ') {
				counterSpaces++;
			}
		}

		char* newInput = new char[strlen(input) + 1 - counterSpaces];

		int counterNewInput = 0;
		for (int i = 0; i < strlen(input); i++) {
			if (input[i] != ' ') {
				newInput[counterNewInput] = input[i];
				counterNewInput++;
			}
		}
		newInput[counterNewInput] = '\0';
		
		return newInput;
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

	static bool isSemicolon(char c) {
		return c == '.' || c == ',';
	}

	static bool isLetter(char c) {
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
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

};


class Stack {

private:
	float* stack = nullptr;
	int topStack = -1;
	int counterStack = 0;

public:


	Stack(int size = 1000) {
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
			 //cout << "Stack underflow" << endl;
			 return 0;
		 }

		return stack[topStack--];
	}

	 float peek() {
		 if (empty()) {
			 //cout << "Stack is empty" << endl;
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




class Expression {
	char* input = nullptr;
	bool isInvalidInput = false;
	Stack stack;

public:


	Expression() {

	}

	~Expression() {
		if(this->input != nullptr){
			delete[] this->input;
			this->input = nullptr;
		}
		this->isInvalidInput = false;
	}

	char* getInput() {
		if (this->input == nullptr) {
			return nullptr;
		}
		//cout << this->input << endl;
		Util::copiereString(this->input);

	}

	void setInput(const char* input) {
		delete[] this->input;
		this->input = Util::copiereString(input);
	}

	bool getIsInvalidInput() {
		return this->isInvalidInput;
	}

	float performOp(float a, float b, char op) { //GOOD
		switch (op) {
		case '+':
			return a + b;
		case '-':
			return b - a;
		case '*':
			return a * b;
		case '/':
			if (a == 0){
				cout <<endl <<"Division by 0 is impossible."<<endl;
				return 0.0;
			}
			return b / a;
		case '^':
		
			return pow(b,a);
		
		case '#':
			if (b <= 0 || a <= 0) {
				return 0.0;
			}
			return pow(b, 1 / a);
		}

		return 0.0;
	}

	char* infixToPostfix(const char* infix)
	{
		string result;
		Stack s(strlen(infix));

		infix = Util::removeSpaces(infix);


		for (int i = 0; i < strlen(infix) + 1; i++) {
			char c = infix[i];
			
			//Validari input

			if ( (c==')' || c==']') && (Util::isDigit(infix[i + 1]) || Util::isSemicolon(infix[i + 1]))  // )2 ).
				||  (Util::isSemicolon(c) && Util::isSemicolon(infix[i + 1])) // ..
				||   Util::isLetter(c)  //a
				||  (Util::isSemicolon(c) && Util::isOperator(infix[i+1]))  || (Util::isOperator(c) && Util::isSemicolon(infix[i + 1])) // .* *.
				|| (Util::isOperator(c) && Util::isOperator(infix[i + 1])) //**
				|| (Util::isExpresion(c) && Util::isExpresion(infix[i + 1])) //##
				||  ( (c=='(' || c=='[') && Util::isExpresion(infix[i + 1])) //(#
				||  (Util::isExpresion(c) && Util::isSemicolon(infix[i+1])) //#.
				||   (c == '('  && infix[i+1] == ')') || (c == '[' && infix[i + 1] == ']') || (c == '(' && infix[i + 1] == ']') || (c == '[' && infix[i + 1] == ')') // () [] (] [)
	            ||  (Util::isSemicolon(c)  && (Util::isOperator(infix[i+1]) || Util::isExpresion(infix[i + 1]))) // .+ .#
				||  (Util::isOperator(c) && Util::isExpresion(infix[i+1]))  //+#
				|| (Util::isOperator(infix[i+1]) && Util::isExpresion(c))  //#+
				||  ( (Util::isOperator(c) || Util::isDigit(c) || Util::isExpresion(c) || Util::isRoundedBrackets(c) || Util::isSemicolon(c) || Util::isSqareBrackets(c) ) &&
					(infix[i+1] == '`' || infix[i + 1] == '~' || infix[i + 1] == '!' || infix[i + 1] == '@' || infix[i + 1] == '$' || infix[i + 1] == '%' 
					|| infix[i + 1] == '&' || infix[i + 1] == '_' || infix[i + 1] == '`{' || infix[i + 1] == '}' || infix[i + 1] == ';' || infix[i + 1] == ':' 
					|| infix[i + 1] == '"' || infix[i + 1] == '<' || infix[i + 1] == '>' || infix[i + 1] == '?' ))) {
				
				cout <<endl <<"Invalid input! Try again!";
				this->isInvalidInput = true;
			}


			if (Util::isDigit(c) || (Util::isSemicolon(c) && Util::isDigit(infix[i + 1]))) {
				while (Util::isDigit(c) || Util::isSemicolon(c)) {
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
			else if (c == '(' || c == '[') {
				s.push('(');
			}
			else if (c == ')' || c == ']') {
				while (!s.empty() && s.top() != '(' && s.top() != '[') {
					result += s.pop();
				}
				s.pop();
			}
			else {
				while (!s.empty()
					&& Util::precedence(c) <= Util::precedence(s.top())) {
					result += s.pop();
				}
				s.push(c);
			}
		}

		while (!s.empty()) {
			result += s.pop();
		}

		
		char* charResult = new char(result.length() + 1);

		for (int i = 0; i < result.length(); i++) {
			charResult[i] = result[i];
		}


		//for (int i = 0; i < result.length(); i++) {
		//	cout << charResult[i];
		//}
		
		return charResult;

	}

	float evaluatePostfix(const char* infix) { 

		char* postfix = infixToPostfix(infix);

		if (this->isInvalidInput) {
			return 0;
		}

		Stack s(strlen(infix));

		//cout << endl << "OK";
		string tempNum = "";

		bool semicolonFound = false;
		float decimalPart = 1;



		for (int i = 0; i < strlen(postfix); i++) {
			char c = postfix[i];

			if (c == ' ') continue;
			else if (Util::isDigit(c) || Util::isSemicolon(c)) {
				float num = 0;

				if (Util::isSemicolon(c)) {
					semicolonFound = true;
				}

				while (Util::isDigit(c) || Util::isSemicolon(c)) {

					if (semicolonFound) {
						decimalPart *= 0.1;
					}

					tempNum += c;
					//cout << tempNum<<endl;

					//cout << c << " " << "Decimal Part " << decimalPart<<endl;
					//num = num * 10 + (c - '0');

					i++;
					c = postfix[i];
				}
				i--;

				//cout <<"Dupa " << tempNum << endl;
				num = stold(tempNum);
				//cout << "Num " << num;

				s.push(num);

				//cout << num << endl;

				semicolonFound = false;
				decimalPart = 1;
				tempNum = "";
				//cout << endl;

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
		//cout << "Result " << result << endl;
		return result;

	}


	//SUPRAINCARCAREA A 2 OPERATORI

	char operator[](int index) {
		if (index >= 0 && index < strlen(input))
		{
			return input[index];
		}
		else {
			cout << "Nu exista";
		}
	}

	float operator+(const char* val)  //poti adauga dupa ecuatia deja introdusa o continuare a ei
	{

		char* newInput = strcat(this->input, val);


		this->input = new char[strlen(newInput)+1];
		for (int i = 0; i < strlen(newInput); i++) {
			this->input[i] = newInput[i];
		}

		this->input[strlen(newInput)] = '\0';

		cout<<endl<<evaluatePostfix(this->input);
		return evaluatePostfix(this->input);
		
	}


};


class Calculator: public Expression {

	char* input = nullptr;
	float result = 0;
	static int numberOfEquations;

public:

	char* getInput() {

		if (this->input == nullptr) {
			return nullptr;
		}
		char* copie = new char[strlen(this->input) + 1];
		strcpy_s(copie, strlen(this->input) + 1, this->input);
		return copie;

	}

	void setInput(const char* inputUser) {
		if (this->input != nullptr) {
			delete[] this->input;
		}
		this->input = Util::copiereString(inputUser);
		//char* copie = new char[strlen(inputUser) + 1];
		//strcpy_s(copie, strlen(inputUser) + 1, input);
	}

	float getResult() {
		this->result = evaluatePostfix(this->input);
		return this->result;
		
	}



	void afisareInserare() {

		cout<<"      --------------------------------     "<< endl<<"-----| Welcome to Calculations Realm! |-----" << 
		endl << "      --------------------------------     " << endl << endl;
					 
		while (true) {

			cout<<"Enter an equation: ";
			char inputUser[100];
			cin.getline(inputUser, ' ');

			if (strcmp(inputUser, "exit") == 0) {
				break;
			}

			Expression::setInput(inputUser);
			//Expr4::getInput();
			if (Expression::getIsInvalidInput() == false) {
				this->result = Expression::evaluatePostfix(inputUser);
				cout << "Result: " << this->result << endl;
				numberOfEquations++;
				cout << endl << "___________" << endl<<endl;

			}
			else {
				cout << endl << "___________" << endl<<endl;
			}


		}

	}

	Calculator() {

	}

	Calculator(const char* userInput) {
		if (this->input != nullptr) {
			delete[] this->input;
			this->input = nullptr;
		}
		this->input = new char[strlen(userInput) + 1];
		strcpy_s(this->input, strlen(userInput) + 1, userInput);
	}

	~Calculator() {
		if (this->input != nullptr) {
			delete[] this->input;
			this->input = nullptr;
		}

	}

	//SUPRAINCARCAREA A 2 OPERATORI

	void operator()(const char* eq) {  //afiseaza daca rezultatul operatiei este par/impar in caz de rezultatul e int

		float result;
		result = Expression::evaluatePostfix(eq);
		int roundedResult = ceil(result);


		if (roundf(result) == result) {
			
			if (roundedResult % 2 == 0) {
				cout << "The result is even";
			}
			else {
				cout << "The result is odd";
			}
		}
		else {
			cout << "The result is a float";
		}

		//cout << evaluatePostfix(eq);
		//this->result = evaluatePostfix(eq);
		//return this->result;
	}

	float operator +=(float num) {
		this->result += num;
		cout << endl<<this->result;
		return this->result += num;
	}

};

int Calculator::numberOfEquations = 0;


int main() {


	Calculator c1;
	c1.afisareInserare();  //se poate lua input continuu

	//c1("2+2.4");
	//c1.setInput("5+3");
	//cout << c1;
	//cout << endl;
	//c1("5+2");
	//c1 += 3;

	//cout << c1;

	//Expression exp1;
	//exp1.setInput("(1+2)*3");
	//cout << exp1;
	//cout<<endl<<exp1[0];

	//exp1 + "+2^3";

	return 0;
}