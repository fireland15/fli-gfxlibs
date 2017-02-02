#pragma once

#include "opengl.hpp"
#include "attribute_variable.hpp"
#include "buffer.hpp"

namespace opengl {

	class VertexArray {
	public:

		/*************************************************************
		* Constructors
		**************************************************************/

		/// <summary>
		/// Constructor. Requests OpenGL Vertex Array from OpenGL.
		/// </summary>
		VertexArray();

		/// <summary>
		/// Copy Constructor. Deleted.
		/// </summary>
		/// <param name="other"></param>
		VertexArray(const VertexArray& other) = delete;

		/// <summary>
		/// Copy Assignment Operator. Deleted.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		VertexArray& operator=(const VertexArray& other) = delete;

		/// <summary>
		/// Move Constructor. 
		/// </summary>
		/// <param name="other">The Vertex Array to move from.</param>
		VertexArray(VertexArray&& other);

		/// <summary>
		/// Move Assignment Constructor. Moves the Vertex Array into another object leaving the original in an invalid state for rendering.
		/// </summary>
		/// <param name="other">The Vertex Array to move from</param>
		/// <returns>The Vertex Array moved into.</returns>
		VertexArray& operator=(VertexArray&& other);
		
		/*************************************************************
		* Destructor
		**************************************************************/

		/// <summary>
		/// Destructor. Releases the OpenGL Vertex Array.
		/// </summary>
		~VertexArray();

		/*************************************************************
		* OpenGL Vertex Array Functions
		**************************************************************/

		/// <summary>
		/// Enables the vertex attribute for use in the rendering pipeline.
		/// </summary>
		/// <param name="attrib">The attribute to enable.</param>
		void EnableVertexAttribute(const AttributeVariable& attrib);

		/// <summary>
		/// Creates an attribute pointer. Requires a buffer to be currently bound. The buffer must contain the data you wish to reference with the attribute pointer. The description must accurately describe the data within the buffer. Undefined results may occur if it does not.
		/// </summary>
		/// <param name="attrib">The attribute the pointer should reference.</param>
		/// <param name="desc">A description of the data the pointer references.</param>
		void SetVertexAttributePointer(const AttributeVariable& attrib, const Buffer::DataDescriptor& desc);

		/// <summary>
		/// For use when using instanced rendering. The divisor tells OpenGL how many instances to render before switching to the next attribute value.
		/// </summary>
		/// <param name="attrib">The attribute variable to which to apply the divisor.</param>
		/// <param name="divisor">The number of instances render before moving to the next attribute value.</param>
		void SetVertexAttributeDivisor(const AttributeVariable& attrib, unsigned int divisor);

		/// <summary>
		/// Binds the Vertex Array to the context.
		/// </summary>
		void Bind();

		/// <summary>
		/// Unbinds the Vertex Array.
		/// </summary>
		void Unbind();

		/*************************************************************
		* Getter Methods
		**************************************************************/

		/// <summary>
		/// Checks if the buffer is currently bound
		/// </summary>
		/// <returns>True is the buffer is bound. False if the buffer is not bound.</returns>
		bool IsBound();

		/// <summary>
		/// Checks if the current internal OpenGL Vertex Array object is valid for use.
		/// </summary>
		/// <returns>True if the internal Vertex Array is usable; false otherwise.</returns>
		bool IsValid();

	private:
		bool m_isBound;

		GLuint m_obj;
	};

}