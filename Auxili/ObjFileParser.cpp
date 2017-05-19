#include "ObjFileParser.hpp"
#include "ObjFileData.hpp"
#include "ObjParseException.hpp"

#include <fstream>
#include <sstream>

std::string MakeParseErrorMessage(std::string& line, std::string& symbol, unsigned int lineNum);

std::unique_ptr<Auxili::ObjFileData> Auxili::ObjFileParser::Parse(std::istream& objFile) {
	if (!objFile) {
		throw Auxili::ObjParseException(std::string("Error reading file"));
	}

	std::stringstream contents;
	contents << objFile.rdbuf();

	Auxili::ObjFileData* fileData = new Auxili::ObjFileData;
	std::string line;
	line.resize(100);
	unsigned int i = 0;

	while (contents) {
		i++;
		line.clear();
		std::getline(contents, line);

		switch (line[0]) {
		case 'v':
			switch (line[1]) {
			case ' ':
				fileData->AddVertex(ExtractVertex(line, i));
				break;
			case 'n':
				fileData->AddNormal(ExtractNormal(line, i));
				break;
			case 't':
				fileData->AddTexCoord(ExtractTexCoords(line, i));
				break;
			default:
				// next line;
				break;
			}
			break;
		case 'f':
			fileData->AddFace(ExtractIndices(line, i));
			break;
		default:
			// next line;
			break;
		}
	}

	return std::unique_ptr<Auxili::ObjFileData>(fileData);
}

std::list<std::string>& Auxili::ObjFileParser::Errors() {
	return _parseErrors;
}

inline glm::vec3 Auxili::ObjFileParser::ExtractVertex(std::string & str, unsigned int line) {
	glm::vec3 v;
	std::istringstream iss(str);
	iss.ignore(256, ' ');
	bool success = true;
	for (unsigned int i = 0; i < 3; i++) {
		iss >> v[i];
		if (iss.fail()) {
			iss.clear();
			std::string dummy;
			iss >> dummy;
			_parseErrors.emplace_back(MakeParseErrorMessage(str, dummy, line));
			success = false;
			break;
		}
	}

	return success ? v : glm::vec3(0.0f);
}

inline glm::vec3 Auxili::ObjFileParser::ExtractNormal(std::string & str, unsigned int line) {
	glm::vec3 n;
	std::istringstream iss(str);
	iss.ignore(256, ' ');
	bool success = true;
	for (unsigned int i = 0; i < 3; i++) {
		iss >> n[i];
		if (iss.fail()) {
			iss.clear();
			std::string dummy;
			iss >> dummy;
			_parseErrors.emplace_back(MakeParseErrorMessage(str, dummy, line));
			success = false;
			break;
		}
	}

	return success ? n : glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::vec2 Auxili::ObjFileParser::ExtractTexCoords(std::string & str, unsigned int line) {
	glm::vec2 uv;
	std::istringstream iss(str);
	iss.ignore(256, ' ');
	bool success = true;
	for (unsigned int i = 0; i < 2; i++) {
		iss >> uv[i];
		if (iss.fail()) {
			iss.clear();
			std::string dummy;
			iss >> dummy;
			_parseErrors.emplace_back(MakeParseErrorMessage(str, dummy, line));
			success = false;
			break;
		}
	}

	return success ? uv : glm::vec2(0.0f);
}

Auxili::ObjFileData::Face Auxili::ObjFileParser::ExtractIndices(std::string & str, unsigned int line) {
	Auxili::ObjFileData::Face face;
	std::istringstream iss(str);
	iss.ignore(256, ' ');
	bool success = true;
	std::string temp;
	temp.resize(32);
	for (unsigned int i = 0; i < 3; i++) {
		iss >> temp;
		ObjFileData::VertexIndices indices;
		indices.Vertex = -1;
		indices.Normal = -1;
		indices.TexCoord = -1;
		int res;
		if (temp.find("//") != std::string::npos) {
			res = std::sscanf(temp.c_str(), "%d//%d", &indices.Vertex, &indices.Normal);
		}
		else {
			res = std::sscanf(temp.c_str(), "%d/%d/%d", &indices.Vertex, &indices.TexCoord, &indices.Normal);
		}
		if (res == EOF) {
			_parseErrors.emplace_back(MakeParseErrorMessage(str, temp, line));
			success = false;
			break;
		}

		temp.clear();
		face[i] = indices;
	}

	return success ? face : Auxili::ObjFileData::Face();
}

std::string MakeParseErrorMessage(std::string & line, std::string & symbol, unsigned int lineNum) {
	std::ostringstream oss;
	oss << "Unparsable symbol: " << symbol << "\n\tline(" << lineNum << ") \"" << line << "\"\n";
	return oss.str();
}
