#pragma once

#include <vector>

#include "BufferDataFormatter.hpp"
#include "BufferDataLayout.hpp"

typedef unsigned char byte;

namespace OpenGL {

	class IBufferDataBuilder {
	public:
		virtual ~IBufferDataBuilder() { };

		/// <summary>
		/// Should be the first call, adds initial data
		/// </summary>
		/// <param name="data">A pointer to the array of data</param>
		/// <param name="size">The size in bytes of a single element</param>
		/// <param name="count">The number of data elements in the array</param>
		/// <returns>Reference to the builder</returns>
		virtual IBufferDataBuilder& Data(const void* data, unsigned int size, unsigned int count, BufferDataPointer& pointer) = 0;

		/// <summary>
		/// Adds data, and interleaves it with the most recently added data
		/// </summary>
		/// <param name="data">A pointer to the array of data</param>
		/// <param name="size">The size in bytes of a single element</param>
		/// <param name="count">The number of data elements in the array</param>
		/// <returns>Reference to the builder</returns>
		virtual IBufferDataBuilder& InterleavedWith(const void* data, unsigned int size, unsigned int count, BufferDataPointer& pointer) = 0;

		/// <summary>
		/// Adds data and resets the interleave flag
		/// </summary>
		/// <param name="data">A pointer to the array of data</param>
		/// <param name="size">The size in bytes of a single element</param>
		/// <param name="count">The number of data elements in the array</param>
		/// <returns>Reference to the builder</returns>
		virtual IBufferDataBuilder& And(const void* data, unsigned int size, unsigned int count, BufferDataPointer& pointer) = 0;

		/// <summary>
		/// Compiles the data into proper stride offset stuff
		/// </summary>
		/// <typeparam name="unsigned char"></typeparam>
		/// <param name="formatter">An object to format the buffer's data</param>
		/// <returns>Vector of bytes of data</returns>
		virtual std::vector<byte> BuildData(BufferDataFormatter& formatter) = 0;

		/// <summary>
		/// Returns a collection of data pointers containing information about the layout of data within the buffer
		/// </summary>
		/// <typeparam name="BufferDataPointer"></typeparam>
		/// <returns></returns>
		virtual BufferDataLayout Layout() = 0;
	};

}