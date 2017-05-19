#pragma once

#include <string>
#include <memory>

namespace Auxili {

	class VertexAttributes;

	class IMeshLoader {
	public:
		virtual ~IMeshLoader() { }
		virtual std::unique_ptr<ObjFIleData> Load(std::string filename) = 0;
	};

}