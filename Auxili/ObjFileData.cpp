#include "ObjFileData.hpp"

Auxili::ObjFileData::ObjFileData() { }

void Auxili::ObjFileData::AddVertex(glm::vec3 & v) {
	_vertices.push_back(v);
}

void Auxili::ObjFileData::AddNormal(glm::vec3 & n) {
	_normals.push_back(n);
}

void Auxili::ObjFileData::AddTexCoord(glm::vec2 & t) {
	_texCoords.push_back(t);
}

void Auxili::ObjFileData::AddFace(Face & f) {
	_faces.push_back(f);
}

std::vector<glm::vec3>& Auxili::ObjFileData::Vertices() {
	return _vertices;
}

std::vector<glm::vec3>& Auxili::ObjFileData::Normals() {
	return _normals;
}

std::vector<glm::vec2>& Auxili::ObjFileData::TexCoords() {
	return _texCoords;
}

std::vector<Auxili::ObjFileData::Face>& Auxili::ObjFileData::Faces() {
	return _faces;
}

Auxili::ObjFileData::VertexIndices & Auxili::ObjFileData::Face::operator[](unsigned int index) {
	return _v[index];
}
