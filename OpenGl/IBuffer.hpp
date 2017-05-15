#pragma once

#include "BufferDataPointer.hpp"

#include <BufferTargetEnum.hpp>
#include <BufferUsageEnum.hpp>

namespace OpenGL {

	class Handle;
	class IBufferDataUpdateStrategy;
	class BufferDataLayout;

	class IBuffer {
	public:
		virtual ~IBuffer() { };

		/// <summary>
		/// Gets the OpenGL reference to the buffer
		/// </summary>
		/// <returns>An Object containing the OpenGL handle to the buffer</returns>
		virtual const Handle& Handle() = 0;

		/// <summary>
		///	The target for the buffer
		/// </summary>
		/// <returns>The buffer's target</returns>
		virtual BufferTarget Target() = 0;

		/// <summary>
		///	The usage of the buffer
		/// </summary>
		/// <returns>The buffer's usage</returns>
		virtual BufferUsage Usage() = 0;

		/// <summary>
		///	Binds the buffer to the OpenGL context
		/// </summary>
		virtual void Bind() = 0;

		/// <summary>
		///	Unbinds the buffer to the OpenGL context
		/// </summary>
		virtual void Unbind() = 0;
				
		/// <summary>
		/// Initializes the buffer's data store
		/// </summary>
		/// <param name="data">The data to be stored in the buffer</param>
		virtual void Data(const std::vector<unsigned char>& data, const BufferDataLayout layout) = 0;

		/// <summary>
		/// Gets the layout of the current buffer data
		/// </summary>
		/// <returns>The buffers current data layout</returns>
		virtual const BufferDataLayout & Layout() = 0;

		/// <summary>
		/// Updates the buffers data to new values according to the supplied strategy
		/// </summary>
		/// <param name="data">The data to store in the buffer</param>
		/// <param name="pointer">The pointer describing the position of the data within the buffer</param>
		/// <param name="updateStrategy">The strategy to follow when updating the data</param>
		virtual void Update(const std::vector<unsigned char>& data, const BufferDataPointer& pointer, IBufferDataUpdateStrategy& updateStrategy) = 0;
	};

}