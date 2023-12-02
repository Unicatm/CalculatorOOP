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
			if (a == 0){
				cout << "Division by 0 is impossible.";
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
		infix = Util::removeSpaces(infix);


		for (int i = 0; i < strlen(infix) + 1; i++) {
			char c = infix[i];

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


		//for (int i = 0; i < result.length(); i++) {
		//	cout << charResult[i];
		//}
		return charResult;

	}

	float evaluatePostfix(const char* infix) { 

		char* postfix = infixToPostfix(infix);

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

			cout<<endl <<"Enter an equation: ";
			char inputUser[100];
			cin.getline(inputUser, ' ');

			if (strcmp(inputUser, "exit") == 0) {
				break;
			}

			Expr4::setInput(inputUser);
			//Expr4::getInput();
			cout << "Result: " << Expr4::evaluatePostfix(inputUser) << endl;
			cout<<endl <<"___________"<< endl;
		}

	}

	Calculator() {

	}

	Calculator(const char* userInput) {
		this->setInput(userInput);
	}

	~Calculator() {
		if (this->input != nullptr) {
			delete[] this->input;
			this->input = nullptr;
		}

	}

};



int main() {

	Calculator c1;
	c1.afisareInserare();


	//"40+(5-1)*2"

	//Expr4 exp1;
	//exp1.setInput("1 + 2 * 3"); //40+4*2 = 48   9.4 10.0
	//exp1.getInput();
	//exp1.evaluatePostfixTEST("2+3*(1+2)");
	 //exp1.evaluatePostfixTEST("3/2+3+1/3");
	//exp1.evaluatePostfixTEST("1 + 2 * 3");

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

	//return 0;
}