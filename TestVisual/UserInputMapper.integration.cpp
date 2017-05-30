#include "UserInputMapper.integration.hpp"

#include "UserInputMapper.hpp"
#include <sstream>
#include <list>
#include <iostream>

void TokenizesFile() {
	std::stringstream ss;
	ss << "a --> func();\n";
	ss << "b --> func2(arg);\n";
	ss << "c --> func3(1...0);\n";
	Tokenizer t;
	auto list = t.Tokenize(ss);
	for (auto & l : list) {
		std::cout << l.ToString() << std::endl;
	}
}

void ParsesTokens() {
	std::vector<Token> tokens;
	tokens.emplace_back(Tokens::Identifier);
	tokens.emplace_back(Tokens::MapOperator);
	tokens.emplace_back(Tokens::Identifier);
	tokens.emplace_back(Tokens::OpenParen);
	tokens.emplace_back(Tokens::CloseParen);
	tokens.emplace_back(Tokens::NewLine);

	Parser p;
	p.Parse(tokens);
}
