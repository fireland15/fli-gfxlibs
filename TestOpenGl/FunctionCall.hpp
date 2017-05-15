#pragma once

#include <string>
#include <map>

class FunctionCall {
public:
	FunctionCall(std::string name) :_name(name) { }

	template <typename T>
	void AddParameter(std::string param, T value) {
		if (_params.count(param) != 0) {
			throw std::exception("cannot set multiple expectations for a single paramater");
		}

		std::stringstream ss;
		ss << value;
		_params.emplace(param, ss.str());
	}

private:
	std::string _name;
	std::map<std::string, std::string> _params;
};