#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <list>

enum class Tokens {
	Identifier,
	MapOperator,
	NewLine,
	OpenParen,
	CloseParen,
	Comma,
	Whitespace,
	Number
};

class Token {
public:
	Token(Tokens t) : _token(t) { }
	Token(Tokens t, std::string& val) : _token(t), _value(val) { }

	Tokens Type() { return _token; }
	std::string Value() { return _value; }
	std::string ToString() {
		std::stringstream ss;
		switch (_token) {
		case Tokens::Identifier:
			ss << "<IDENTIFIER>";
			break;
		case Tokens::MapOperator:
			ss << "<MAP_OP>";
			break;
		case Tokens::NewLine:
			ss << "<NEW_LINE>";
			break;
		case Tokens::OpenParen:
			ss << "<OPAREN>";
			break;
		case Tokens::CloseParen:
			ss << "<CPAREN>";
			break;
		case Tokens::Comma:
			ss << "<COMMA>";
			break;
		case Tokens::Whitespace:
			ss << "<WHITESPACE>";
			break;
		case Tokens::Number:
			ss << "<NUMBER>";
			break;
		}
		ss << ": " << _value;
		return ss.str();
	}

private:
	Tokens _token;
	std::string _value;
};

class Tokenizer {
public:
	std::vector<Token> Tokenize(std::istream& stream) {
		std::vector<Token> tokens;

		while (stream) {
			char c;
			stream.get(c);
			if (c == '-') {
				stream.get(c);
				if (c == '-') {
					stream.get(c);
					if (c == '>') {
						tokens.emplace_back(Tokens::MapOperator);
					}
				}
			}
			else if (c == '\n') {
				tokens.emplace_back(Tokens::NewLine);
			}
			else if (c == ',') {
				tokens.emplace_back(Tokens::Comma);
			}
			else if (c == '(') {
				tokens.emplace_back(Tokens::OpenParen);
			}
			else if (c == ')') {
				tokens.emplace_back(Tokens::CloseParen);
			}
			else if (std::isalpha(c)) {
				std::stringstream ss;
				ss << c;
				while (std::isalnum(stream.peek())) {
					stream.get(c);
					ss << c;
				}
				tokens.emplace_back(Tokens::Identifier, ss.str());
			}
			else if (std::isdigit(c)) {
				bool hasDecimal = false;
				std::stringstream ss;
				ss << c;
				while (std::isdigit(stream.peek()) || stream.peek() == '.') {
					stream.get(c);
					// check for multiple decimal points
					if (c == '.') {
						if (!hasDecimal) {
							ss << c;
							hasDecimal = true;
						}
						else {
							return tokens;
						}
					}
					else {
						ss << c;
					}
				}
				tokens.emplace_back(Tokens::Number, ss.str());
			}
			else if (std::isblank(c)) {
				//tokens.emplace_back(Tokens::Whitespace);
			}
		}
		return tokens;
	}
};

enum class UserEvents {
	A, a,
	B, b,
	C, c,
	D, d, 
	E, e,
	F, f, 
	G, g,
	H, h,
	I, i,
J, j,
K, k,
L, l,
M, m,
N, n,
O, o,
P, p,
Q, q,
R, r,
S, s,
T, t,
U, u,
V, v,
W, w,
X, x,
Y, y,
Z, z
};

#include <map>
#include <functional>

class UserInputCallbackMap {
public:
	UserInputCallbackMap() {
		_map.insert(std::make_pair(UserEvents::A, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::a, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::B, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::b, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::C, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::c, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::D, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::d, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::E, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::e, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::F, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::f, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::G, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::g, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::H, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::h, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::I, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::i, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::J, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::j, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::K, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::k, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::L, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::l, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::M, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::m, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::N, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::n, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::O, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::o, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::P, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::p, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::Q, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::q, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::R, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::r, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::S, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::s, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::T, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::t, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::U, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::u, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::V, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::v, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::W, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::w, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::X, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::x, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::Y, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::y, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::Z, std::list<std::function<void()>>()));
		_map.insert(std::make_pair(UserEvents::z, std::list<std::function<void()>>()));
	}

private:
	std::map<UserEvents, std::list<std::function<void()>>> _map;
};

class Parser {
public:
	void AddMethod(std::string & name, std::function<void()> func) {
		if (_functionType.count(name) > 0)
			throw std::runtime_error("cannot overload callback functions");
		_functionType.insert(std::make_pair(name, FunctionType::void_void));
		_callback_void.insert(std::make_pair(name, func));
	}

	void AddMethod(std::string & name, std::function<void(std::string)> func) {
		if (_functionType.count(name) > 0)
			throw std::runtime_error("cannot overload callback functions");
		_functionType.insert(std::make_pair(name, FunctionType::void_string));
		_callback_s.insert(std::make_pair(name, func));
	}

	void AddMethod(std::string & name, std::function<void(float)> func) {
		if (_functionType.count(name) > 0)
			throw std::runtime_error("cannot overload callback functions");
		_functionType.insert(std::make_pair(name, FunctionType::void_float));
		_callback_f.insert(std::make_pair(name, func));
	}

	UserInputCallbackMap Parse(std::vector<Token>& tokens) {
		unsigned int i = 0;
		while (i < tokens.size()) {
			if (!MatchAssignment(tokens, i))
				throw std::runtime_error("Syntax Error");
		}
	}

private:
	bool MatchAssignment(std::vector<Token> & tokens, unsigned int& i) {
		unsigned int j = i;
		if (!MatchIdentifier(tokens, j))
			return false;
		if (!MatchMapping(tokens, j))
			return false;
		while (j < tokens.size() && tokens[j].Type() != Tokens::Identifier) {
			if (!MatchMapping(tokens, j))
				return false;
		}
		i = j;
		return true;
	}

	bool MatchMapping(std::vector<Token> & tokens, unsigned int & i) {
		unsigned int j = i;
		if (!MatchMapOperator(tokens, j))
			return false;
		if (!MatchFunction(tokens, j))
			return false;
		if (tokens[j].Type() != Tokens::NewLine)
			return false;
		i = j + 1;
		return true;
	}

	bool MatchIdentifier(std::vector<Token> & tokens, unsigned int & i) {
		if (tokens[i].Type() != Tokens::Identifier)
			return false;
		i++;
		return true;
	}

	bool MatchMapOperator(std::vector<Token> & tokens, unsigned int & i) {
		if (tokens[i].Type() != Tokens::MapOperator)
			return false;
		i++;
		return true;
	}

	bool MatchFunction(std::vector<Token> & tokens, unsigned int & i) {
		unsigned int j = i;
		if (tokens[j].Type() != Tokens::Identifier) 
			return false;
		j++;
		if (tokens[j].Type() != Tokens::OpenParen)
			return false;
		j++;
		if (j < tokens.size() && tokens[j].Type() == Tokens::CloseParen) {
			i = j + 1;
			return true;
		}
		else {
			j++;
			if (!MatchArgument(tokens, j))
				return false;
		}
		j++;
		while (j < tokens.size() && tokens[j].Type() != Tokens::CloseParen) {
			if (tokens[j].Type() != Tokens::Comma)
				return false;
			j++;
			if (!MatchArgument(tokens, j))
				return false;
		}
		if (tokens[j].Type() != Tokens::CloseParen)
			return false;
		i = j + 1;
		return true;
	}

	bool MatchArgument(std::vector<Token> & tokens, unsigned int& i) {
		if (i < tokens.size()) {
			Tokens t = tokens[i].Type();
			if (t == Tokens::Number || t == Tokens::Identifier) {
				i++;
				return true;
			}
		}
		return false;
	}


private:
	enum class FunctionType {
		void_string,
		void_void,
		void_float
	};
	std::map<std::string, FunctionType> _functionType;
	std::map<std::string, std::function<void()>> _callback_void;
	std::map<std::string, std::function<void(std::string)>> _callback_s;
	std::map<std::string, std::function<void(float)>> _callback_f;
};

class UserInputMapper {
public:
	UserInputMapper(std::string& file);
};