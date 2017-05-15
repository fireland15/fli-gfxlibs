#pragma once

#include <string>
#include <map>

#include <UniformTypeEnum.hpp>

namespace OpenGL {

	class UniformTypeFormatter {
	public:
		UniformTypeFormatter();

		/// <summary>
		/// Converts the uniform type enum into a string
		/// </summary>
		/// <param name="type">The uniform type to get the string</param>
		/// <returns>The string representatin of the uniform type</returns>
		std::string ToString(UniformType type);

	private:
		static std::map<UniformType, std::string> _strings;
	};

}