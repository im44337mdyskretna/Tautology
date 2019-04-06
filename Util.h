#include <iostream>
#include <fstream>
#include <string>
#include <stack>

namespace Util {
	std::string readFile(const std::string& path);
	std::string infixToRPN(const std::string& infix);
	int priority(char c);
	bool pop(std::stack<bool>& valueStack);
}
