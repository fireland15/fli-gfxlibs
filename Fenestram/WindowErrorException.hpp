#pragma once

#include <string>

namespace Fenestram {

	class WindowErrorException {
	public:
		WindowErrorException();
		WindowErrorException(std::string & description);
		virtual std::string Message();
	private:
		std::string _message;
	};

}