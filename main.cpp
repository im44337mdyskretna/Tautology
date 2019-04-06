#include "Util.h"

typedef unsigned int uint;

bool checkTautologyInRPN(const std::string& textRPN, uint p, uint q, uint r);
bool implication(bool a, bool b);

int main(int argc, char** argv) {

	// sprawdz czy poprawnie przekazano argumenty programu
	if(argc != 2) {
		std::cerr << "Zle uzycie, przyklad: ./tautology [file_path]" << std::endl;
		return 1;
	}

	// wczytaj text z pliku i zamien go na format Reversed Polish Notation
	const char* const filePath = argv[1];
	std::string textInfix = Util::readFile(filePath);
	std::string textRPN = Util::infixToRPN(textInfix);

	// sprawdz czy text jest tautologia
	bool tautology = true;

	for(uint p = 0; p < 2; p++)
		for(uint q = 0; q < 2; q++)
			for(uint r = 0; r < 2; r++) {

				if(!checkTautologyInRPN(textRPN, p, q, r)) {
					std::cout << "Wyrazenie = 0, dla p=" << p << ", q=" << q << ", r=" << r << std::endl; 
					tautology = false;
				}
			}


	std::cout << "Czy wyrazenie jest tautologia? " << (tautology ? "tak" : "nie") << std::endl;;
}

bool checkTautologyInRPN(const std::string& textRPN, uint p, uint q, uint r) {
	
	std::stack<bool> valueStack;

	char previous;

	for(auto s : textRPN) {
		if(s == 'p')
			if(previous == '~')
				valueStack.push(!p);
			else
				valueStack.push(p);
		else if(s == 'q')
			if(previous == '~')
				valueStack.push(!q);
			else
				valueStack.push(q);
		else if(s == 'r')
			if(previous == '~')
				valueStack.push(!r);
			else
				valueStack.push(r);

		//ALTERNATYWA
		else if(s == 'v') {
			
			bool a = Util::pop(valueStack);
			bool b = Util::pop(valueStack);

			bool c = b | a;
			valueStack.push(c);
		}
		//KONIUNKCJA
		else if(s == '^') {

			bool a = Util::pop(valueStack);
			bool b = Util::pop(valueStack);

			bool c = b & a;
			valueStack.push(c);
		}
		//IMPLIKACJA
		else if(s == '>') {

			bool a = Util::pop(valueStack);
			bool b = Util::pop(valueStack);

			bool c = implication(b, a);
			valueStack.push(c);
		}
		//ROWNOWAZNOSC
		else if(s == '=') {

			bool a = Util::pop(valueStack);
			bool b = Util::pop(valueStack);

			bool c = (b == a);
			valueStack.push(c);
		}

		previous = s;
	}

	return valueStack.top();
}

bool implication(bool a, bool b) {
	bool result;

        if(a == 0 && b == 0)
                result = 1;
        else if(a == 0 && b == 1)
                result = 1;
        else if(a == 1 && b == 0)
                result = 0;
        else if(a == 1 && b == 1)
                result = 1;

        return result;
}
