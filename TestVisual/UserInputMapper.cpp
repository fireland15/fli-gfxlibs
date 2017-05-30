#include "UserInputMapper.hpp"

#include <list>
#include <cctype>
#include <sstream>
#include <fstream>

UserInputMapper::UserInputMapper(std::string & file)
{
	std::ifstream f(file);
	Tokenizer tokenizer;
	auto list = tokenizer.Tokenize(f);
	
}
