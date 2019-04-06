#include "Util.h"

std::string Util::readFile(const std::string& path) {
    std::fstream file;

    try {
    	file.open(path);
    } catch(std::ifstream::failure e) {
	std::cerr << e.what() << std::endl;
    }

    std::string result;
    std::string line;

    if(file.is_open())
        while(getline(file, line))
            result.append(line + "\n");
    else {
        std::cerr << "ERROR: Blad odczytu pliku: " << path << std::endl;
	exit(2);
    }
    
    return result;
}

std::string Util::infixToRPN(const std::string& infix) {
	
	std::stack<char> operatorStack;
    	std::string output = "";
	operatorStack.push('X');

	for(auto s : infix) {

		//ZMIENNE
		if(s == 'p' || s == 'q' || s == 'r' || s == '~')
			output += s;
		
		//NAWIASY
		else if(s == '(')
			operatorStack.push('(');

		else if(s == ')') {

			while(operatorStack.top() != 'X' && operatorStack.top() != '(') {

				char c = operatorStack.top();
				operatorStack.pop();
				output += c;
			}

			if(operatorStack.top() == '(')
				operatorStack.pop();
		}

		//OPERATORY
		else if(s == 'v' || s == '^' || s == '>' || s == '='){

			while(operatorStack.top() != 'X' && priority(s) <= priority(operatorStack.top())) {

				char c = operatorStack.top();
				operatorStack.pop();
				output += c;
			}

			operatorStack.push(s);
		}
	}

	//DODAJ DO WYJSCIOWEGO STRINGA OPERATORY KTORE ZOSTALY NA STOSIE
	while(operatorStack.top() != 'X') {

		char c = operatorStack.top();
		operatorStack.pop();
		output += c;
	}

	return output;
}

int Util::priority(char a) {
    
	int weight = -1;
    	if (a == '>' || a == '=')
        	weight = 1;
    	else if (a == 'v')
        	weight = 2;
    	else if (a == '^')
        	weight = 3;
    	return weight;
}


bool Util::pop(std::stack<bool>& valueStack) {
	bool result = valueStack.top();
	valueStack.pop();
	return result;
}
