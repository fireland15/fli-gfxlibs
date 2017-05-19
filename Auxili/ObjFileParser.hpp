#pragma once

#include <string>
#include <memory>
#include <list>
#include <glm\glm.hpp>

#include "ObjFileData.hpp"

namespace Auxili {

	class ObjFileParser {
	public:
		virtual ~ObjFileParser() { }
		std::unique_ptr<ObjFileData> Parse(std::istream& objFile);
		std::list<std::string>& Errors();

	private:
		std::unique_ptr<Auxili::ObjFileData> _data;
		std::list<std::string> _parseErrors;

		glm::vec3 ExtractVertex(std::string& str, unsigned int line);
		glm::vec3 ExtractNormal(std::string& str, unsigned int line);
		glm::vec2 ExtractTexCoords(std::string& str, unsigned int line);
		ObjFileData::Face ExtractIndices(std::string & str, unsigned int line);
	};

}