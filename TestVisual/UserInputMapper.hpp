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

constexpr unsigned int str2int(const char* str, int h = 0) {
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

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

	void AddBinding(std::string event, std::function<void()> func) {
		UserEvents e = ToUserEvent(event);
		if (_map.count(e) == 0) {
			_map.insert(std::make_pair(e, std::list<std::function<void()>>()));
		}
		_map[e].push_back(func);
	}

	void Invoke(UserEvents e) {
		for (auto & func : _map[e]) {
			func();
		}
	}

	static UserEvents ToUserEvent(std::string & s) {
		switch (str2int(s.c_str())) {
		case str2int("A"):
			return UserEvents::A;
		case str2int("a"):
			return UserEvents::a;
		case str2int("B"):
			return UserEvents::B;
		case str2int("b"):
			return UserEvents::b;
		case str2int("C"):
			return UserEvents::C;
		case str2int("c"):
			return UserEvents::c;
		case str2int("D"):
			return UserEvents::D;
		case str2int("d"):
			return UserEvents::d;
		case str2int("E"):
			return UserEvents::E;
		case str2int("e"):
			return UserEvents::e;
		case str2int("F"):
			return UserEvents::F;
		case str2int("f"):
			return UserEvents::f;
		case str2int("G"):
			return UserEvents::G;
		case str2int("g"):
			return UserEvents::g;
		case str2int("H"):
			return UserEvents::H;
		case str2int("h"):
			return UserEvents::h;
		case str2int("I"):
			return UserEvents::I;
		case str2int("i"):
			return UserEvents::i;
		case str2int("J"):
			return UserEvents::J;
		case str2int("j"):
			return UserEvents::j;
		case str2int("K"):
			return UserEvents::K;
		case str2int("k"):
			return UserEvents::k;
		case str2int("L"):
			return UserEvents::L;
		case str2int("l"):
			return UserEvents::l;
		case str2int("M"):
			return UserEvents::M;
		case str2int("m"):
			return UserEvents::m;
		case str2int("N"):
			return UserEvents::N;
		case str2int("n"):
			return UserEvents::n;
		case str2int("O"):
			return UserEvents::O;
		case str2int("o"):
			return UserEvents::o;
		case str2int("P"):
			return UserEvents::P;
		case str2int("p"):
			return UserEvents::p;
		case str2int("Q"):
			return UserEvents::Q;
		case str2int("q"):
			return UserEvents::q;
		case str2int("R"):
			return UserEvents::R;
		case str2int("r"):
			return UserEvents::r;
		case str2int("S"):
			return UserEvents::S;
		case str2int("s"):
			return UserEvents::s;
		case str2int("T"):
			return UserEvents::T;
		case str2int("t"):
			return UserEvents::t;
		case str2int("U"):
			return UserEvents::U;
		case str2int("u"):
			return UserEvents::u;
		case str2int("V"):
			return UserEvents::V;
		case str2int("v"):
			return UserEvents::v;
		case str2int("W"):
			return UserEvents::W;
		case str2int("w"):
			return UserEvents::w;
		case str2int("X"):
			return UserEvents::X;
		case str2int("x"):
			return UserEvents::x;
		case str2int("Y"):
			return UserEvents::Y;
		case str2int("y"):
			return UserEvents::y;
		case str2int("Z"):
			return UserEvents::Z;
		case str2int("z"):
			return UserEvents::z;
		default:
			throw std::runtime_error("Symbol not found");
		}
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

	void AddMethod(std::string & name, std::function<void(float, float)> func) {
		if (_functionType.count(name) > 0)
			throw std::runtime_error("cannot overload callback functions");
		_functionType.insert(std::make_pair(name, FunctionType::void_float2));
		_callback_f2.insert(std::make_pair(name, func));
	}

	UserInputCallbackMap Parse(std::vector<Token>& tokens) {
		UserInputCallbackMap map;
		unsigned int i = 0;
		while (i < tokens.size()) {
			if (tokens[i].Type() == Tokens::NewLine) {
				i++;
				continue;
			}
			auto assignment = MatchAssignment(tokens, i);
			for (auto f : assignment.second) {
				map.AddBinding(assignment.first, f);
			}
		}
		return map;
	}

private:
	std::pair<std::string, std::list<std::function<void()>>> MatchAssignment(std::vector<Token> & tokens, unsigned int& i) {
		unsigned int j = i;
		std::string userEvent = MatchIdentifier(tokens, j);
		std::list<std::function<void()>> funcs;
		funcs.push_back(MatchMapping(tokens, j));
		while (j < tokens.size() && tokens[j].Type() != Tokens::Identifier) {
			if (tokens[j].Type() != Tokens::NewLine)
				throw std::runtime_error("Expected new line");
			j++;
			try {
				funcs.push_back(MatchMapping(tokens, j));
			}
			catch (std::exception ex) {
				i = j;
				return std::make_pair(userEvent, funcs);
			}
		}
		i = j;
		return std::make_pair(userEvent, funcs);
	}

	std::function<void()> MatchMapping(std::vector<Token> & tokens, unsigned int & i) {
		unsigned int j = i;
		MatchMapOperator(tokens, j);
		std::function<void()> func = MatchFunction(tokens, j);
		//if (tokens[j].Type() != Tokens::NewLine)
		//	throw std::runtime_error("Expected a newline");
		//i = j + 1;
		i = j;
		return func;
	}

	std::string MatchIdentifier(std::vector<Token> & tokens, unsigned int & i) {
		if (tokens[i].Type() != Tokens::Identifier)
			throw std::runtime_error("Expected an identifier");
		std::string identifier = tokens[i].Value();
		i++;
		return identifier;
	}

	bool MatchMapOperator(std::vector<Token> & tokens, unsigned int & i) {
		if (tokens[i].Type() != Tokens::MapOperator)
			throw std::runtime_error("Expected a map operator");
		i++;
		return true;
	}

	std::function<void()> MatchFunction(std::vector<Token> & tokens, unsigned int & i) {
		std::string funcName;
		std::vector<std::string> args;


		unsigned int j = i;
		if (tokens[j].Type() != Tokens::Identifier) 
			throw std::runtime_error("Expected an identifier");
		funcName = tokens[j].Value();
		j++;
		if (tokens[j].Type() != Tokens::OpenParen)
			throw std::runtime_error("Expected a Parenthesis");
		j++;
		if (j < tokens.size() && tokens[j].Type() == Tokens::CloseParen) {
			i = j + 1;
		}
		else {
			args.push_back(MatchArgument(tokens, j));
		}
		while (j < tokens.size() && tokens[j].Type() != Tokens::CloseParen) {
			if (tokens[j].Type() != Tokens::Comma)
				throw std::runtime_error("Expected a comma");
			j++;
			args.push_back(MatchArgument(tokens, j));
		}
		if (tokens[j].Type() != Tokens::CloseParen)
			throw std::runtime_error("Expected a closing parenthesis");
		i = j + 1;

		if (_functionType.count(funcName) == 0) {
			throw std::runtime_error("Unidentified function name");
		}
		else {
			switch (_functionType[funcName]) {
			case FunctionType::void_void:
				return _callback_void[funcName];
				break;
			case FunctionType::void_float: {
					std::function<void(float)> func = _callback_f[funcName];
					char* end;
					return std::bind(func, std::strtof(args[0].c_str(), &end));
				}
				break;
			case FunctionType::void_float2: {
					std::function<void(float, float)> func = _callback_f2[funcName];
					char* end;
					return std::bind(func, std::strtof(args[0].c_str(), &end), strtof(args[1].c_str(), &end));
				}
				break;
			case FunctionType::void_string: {
					std::function<void(std::string)> func = _callback_s[funcName];
					return std::bind(func, args[0]);
				}
				break;
			}
		}

		throw std::runtime_error("Invalid function");
	}

	std::string MatchArgument(std::vector<Token> & tokens, unsigned int& i) {
		if (i < tokens.size()) {
			Token t = tokens[i];
			if (t.Type() == Tokens::Number || t.Type() == Tokens::Identifier) {
				i++;
				return t.Value();
			}
		}
		return false;
	}

private:
	enum class FunctionType {
		void_string,
		void_void,
		void_float,
		void_float2
	};
	std::map<std::string, FunctionType> _functionType;
	std::map<std::string, std::function<void()>> _callback_void;
	std::map<std::string, std::function<void(std::string)>> _callback_s;
	std::map<std::string, std::function<void(float)>> _callback_f;
	std::map<std::string, std::function<void(float, float)>> _callback_f2;
};

class UserInputMapper {
public:
	UserInputMapper(std::string& file);
};