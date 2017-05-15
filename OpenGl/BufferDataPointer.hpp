#pragma once

#include <DataTypesEnum.hpp>

namespace OpenGL {

	class BufferDataPointer {
	public:
		/// <summary>
		/// Initializes information about what the data points to.
		/// </summary>
		/// <param name="count">The number of elements per vertex</param>
		/// <param name="type">The type of each element</param>
		BufferDataPointer(unsigned int count, DataType type);

		/// <summary>
		/// Gets the numberof elements per vertex
		/// </summary>
		/// <returns>The number of elements per vertex</returns>
		unsigned int Count() const;

		/// <summary>
		/// Gets the type of data in the buffer
		/// </summary>
		/// <returns>The type of data this points to</returns>
		DataType Type() const;

		/// <summary>
		/// Sets the offset of the first element into the buffer.
		/// </summary>
		/// <param name="offset"></param>
		void Offset(unsigned int offset);

		/// <summary>
		/// Gets the offset of the first element into the buffer
		/// </summary>
		/// <returns>Returns the offset into the buffer</returns>
		unsigned int Offset() const;

		/// <summary>
		/// Stores the stride of the data
		/// </summary>
		/// <param name="stride">The stride of the data this points to</param>
		void Stride(unsigned int stride);

		/// <summary>
		/// Gets the stride for the data this points to
		/// </summary>
		/// <returns>The stride</returns>
		unsigned int Stride() const;

	private:
		unsigned int _count;
		DataType _type;
		unsigned int _offset;
		unsigned int _stride;
	};

}