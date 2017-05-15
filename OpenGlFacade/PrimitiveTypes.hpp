#pragma once

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLEXT.h>

namespace OpenGL {

	enum class PrimitiveType : unsigned int {
		Points = GL_POINTS,
		LineStrip = GL_LINE_STRIP,
		LineLoop = GL_LINE_LOOP,
		Lines = GL_LINES,
		TriangleStrip = GL_TRIANGLE_STRIP,
		TriangleFan = GL_TRIANGLE_FAN,
		Triangles = GL_TRIANGLES,
		LinesAdjacency = GL_LINES_ADJACENCY,
		LineStripAdjacency = GL_LINE_STRIP_ADJACENCY,
		TrianglesAdjacency = GL_TRIANGLES_ADJACENCY,
		TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY,
		Patches = GL_PATCHES
	};

}