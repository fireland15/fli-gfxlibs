#pragma once

#include <string>

namespace Auxili {

	class ObjParseException {
	public:
		ObjParseException(std::string& message);
		virtual std::string& Message();
	private:
		std::string _message;
	};

}