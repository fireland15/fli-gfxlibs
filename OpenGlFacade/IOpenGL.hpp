#pragma once

namespace OpenGL {
	class IOpenGL {
	public:
		virtual ~IOpenGL() { };

		/// <summary>
		/// Generate buffer object names
		/// </summary>
		/// <param name="n">Specifies the number of buffer objects names to be generated</param>
		/// <param name="buffers">Specifies an array in which the generated buffer object names are stored</param>
		virtual void GenBuffers(int n, unsigned int* buffers) = 0;

		/// <summary>
		/// Creates buffer objects
		/// </summary>
		/// <param name="n">Specifies the number of buffer objects to create</param>
		/// <param name="buffers">Specifies an array in which names of the new buffers are stored</param>
		virtual void CreateBuffers(int n, unsigned int* buffers) = 0;

		/// <summary>
		/// Delete named buffer objects
		/// </summary>
		/// <param name="n">Specifies the number of buffer objects to be deleted</param>
		/// <param name="buffers">Specifies an array of buffer objects to be deleted</param>
		virtual void DeleteBuffers(int n, const unsigned int* buffers) = 0;

		/// <summary>
		/// Bind a named buffer object
		/// </summary>
		/// <param name="target">Specifies the target to which the buffer object is bound</param>
		/// <param name="buffer">Specifies the name of a buffer object
		/// </param>
		virtual void BindBuffer(unsigned int target, unsigned int buffer) = 0;

		/// <summary>
		/// Creates and initializes a buffer object's data store
		/// </summary>
		/// <param name="target">Specifies the target to which the buffer object is bound</param>
		/// <param name="size">Specifies the size in bytes of the buffer object's new data store</param>
		/// <param name="data">Specifies a pointer to data that will be copied into the data store for initialization, or NULL if no data is to be copied</param>
		/// <param name="usage">Specifies the expected usage pattern of the data store</param>
		virtual void BufferData(unsigned int target, int size, const void* data, unsigned int usage) = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="buffer">Specifies the name of the buffer object</param>
		/// <param name="size">Specifies the size in bytes of the buffer object's new data store</param>
		/// <param name="data">Specifies a pointer to data that will be copied into the data store for initialization, or NULL if no data is to be copied</param>
		/// <param name="usage">Specifies the expected usage pattern of the data store</param>
		virtual void NamedBufferData(unsigned int buffer, int size, const void* data, unsigned int usage) = 0;

		/// <summary>
		/// Specify clear values for the color buffers. All parameters initially 0
		/// </summary>
		/// <param name="red">Specify the red value used when color buffers are cleared</param>
		/// <param name="green">Specify the green value used when color buffers are cleared</param>
		/// <param name="blue">Specify the blue value used when color buffers are cleared</param>
		/// <param name="alpha">Specify the alpha value used when color buffers are cleared</param>
		virtual void ClearColor(float red, float green, float blue, float alpha) = 0;

		/// <summary>
		/// Clear buffers to preset values
		/// </summary>
		/// <param name="mask">Bitwise OR of masks that indicat the buffers to be cleared</param>
		virtual void Clear(unsigned int mask) = 0;

		/// <summary>
		/// Return error information
		/// </summary>
		/// <returns>Returns the value of the error flag</returns>
		virtual unsigned int GetError() = 0;

		/// <summary>
		/// Return the value of a selected parameter
		/// </summary>
		/// <param name="pname">Specifies the parameter value to be returned</param>
		/// <param name="data">Returns the value or values of the selected paramter</param>
		virtual void GetIntegerv(unsigned int pname, int* data) = 0;

		/// <summary>
		/// Creates a program object
		/// </summary>
		/// <returns>Handle to program object</returns>
		virtual unsigned int CreateProgram() = 0;

		/// <summary>
		/// Deletes a program object
		/// </summary>
		/// <param name="program">Specifies the program object to be deleted</param>
		virtual void DeleteProgram(unsigned int program) = 0;

		/// <summary>
		/// Attaches a shader object to a program object
		/// </summary>
		/// <param name="program">Specifies the program object to which a shader object will be attached</param>
		/// <param name="shader">Specifies the shader object that is to be attached</param>
		virtual void AttachShader(unsigned int program, unsigned int shader) = 0;

		/// <summary>
		/// Detaches a shader object from a program object to which it is attached
		/// </summary>
		/// <param name="program">Specifies the program object from which to detach the shader object</param>
		/// <param name="shader">Specifies the shader object to be detached</param>
		virtual void DetachShader(unsigned int program, unsigned int shader) = 0;

		/// <summary>
		/// Installs a program object as part of current rendering state
		/// </summary>
		/// <param name="program">Specifies the handle of the program object whose executables are to be used as part of current rendering state</param>
		virtual void UseProgram(unsigned int program) = 0;

		/// <summary>
		/// Links a program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program object to be linked</param>
		virtual void LinkProgram(unsigned int program) = 0;

		/// <summary>
		/// Returns a parameter from a program object
		/// </summary>
		/// <param name="program">Specifies the program object to be queried</param>
		/// <param name="pname">Specifies the object paramter</param>
		/// <param name="params">Returns the requested object parameter</param>
		virtual void GetProgramiv(unsigned int program, unsigned int pname, int* params) = 0;

		/// <summary>
		/// Returns the information log for a program object
		/// </summary>
		/// <param name="program">Specifies the program object whose information log is to be queried</param>
		/// <param name="maxLength">Specifies the size of the character buffer for storing the returned information log</param>
		/// <param name="length">Returns the length of the string returned in infoLog (excluding the null terminator)</param>
		/// <param name="infoLog">Specifies an array of characters that is used to return the information log</param>
		virtual void GetProgramInfoLog(unsigned int program, int maxLength, int* length, char* infoLog) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="v0">Specifies the new value to be used for the specified uniform variable</param>
		virtual void ProgramUniform1f(unsigned int program, int location, float v0) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="v0">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v1">Specifies the new value to be used for the specified uniform variable</param>
		virtual void ProgramUniform2f(unsigned int program, int location, float v0, float v1) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="v0">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v1">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v2">Specifies the new value to be used for the specified uniform variable</param>
		virtual void ProgramUniform3f(unsigned int program, int location, float v0, float v1, float v2) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="v0">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v1">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v2">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v3">Specifies the new value to be used for the specified uniform variable</param>
		virtual void ProgramUniform4f(unsigned int program, int location, float v0, float v1, float v2, float v3) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="v0">Specifies the new value to be used for the specified uniform variable</param>
		virtual void ProgramUniform1i(unsigned int program, int location, int v0) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="v0">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v1">Specifies the new value to be used for the specified uniform variable</param>
		virtual void ProgramUniform2i(unsigned int program, int location, int v0, int v1) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="v0">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v1">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v2">Specifies the new value to be used for the specified uniform variable</param>
		virtual void ProgramUniform3i(unsigned int program, int location, int v0, int v1, int v2) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="v0">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v1">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v2">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v3">Specifies the new value to be used for the specified uniform variable</param>
		virtual void ProgramUniform4i(unsigned int program, int location, int v0, int v1, int v2, int v3) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="v0">Specifies the new value to be used for the specified uniform variable</param>
		virtual void ProgramUniform1ui(unsigned int program, int location, unsigned int v0) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="v0">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v1">Specifies the new value to be used for the specified uniform variable</param>
		virtual void ProgramUniform2ui(unsigned int program, int location, unsigned int v0, unsigned int v1) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="v0">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v1">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v2">Specifies the new value to be used for the specified uniform variable</param>
		virtual void ProgramUniform3ui(unsigned int program, int location, unsigned int v0, unsigned int v1, unsigned int v2) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="v0">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v1">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v2">Specifies the new value to be used for the specified uniform variable</param>
		/// <param name="v3">Specifies the new value to be used for the specified uniform variable</param>
		virtual void ProgramUniform4ui(unsigned int program, int location, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniform1fv(unsigned int program, int location, int count, const float* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniform2fv(unsigned int program, int location, int count, const float* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniform3fv(unsigned int program, int location, int count, const float* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniform4fv(unsigned int program, int location, int count, const float* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniform1iv(unsigned int program, int location, int count, const int* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniform2iv(unsigned int program, int location, int count, const int* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniform3iv(unsigned int program, int location, int count, const int* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniform4iv(unsigned int program, int location, int count, const int* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniform1uiv(unsigned int program, int location, int count, const unsigned int* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniform2uiv(unsigned int program, int location, int count, const unsigned int* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniform3uiv(unsigned int program, int location, int count, const unsigned int* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniform4uiv(unsigned int program, int location, int count, const unsigned int* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="transpose">Specifies whether to transpose the matrix as the values are loaded into the uniform variable</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniformMatrix2fv(unsigned int program, int location, int count, unsigned char transpose, const float* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="transpose">Specifies whether to transpose the matrix as the values are loaded into the uniform variable</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniformMatrix3fv(unsigned int program, int location, int count, unsigned char transpose, const float* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="transpose">Specifies whether to transpose the matrix as the values are loaded into the uniform variable</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniformMatrix4fv(unsigned int program, int location, int count, unsigned char transpose, const float* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="transpose">Specifies whether to transpose the matrix as the values are loaded into the uniform variable</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniformMatrix2x3fv(unsigned int program, int location, int count, unsigned char transpose, const float* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="transpose">Specifies whether to transpose the matrix as the values are loaded into the uniform variable</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniformMatrix3x2fv(unsigned int program, int location, int count, unsigned char transpose, const float* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="transpose">Specifies whether to transpose the matrix as the values are loaded into the uniform variable</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniformMatrix2x4fv(unsigned int program, int location, int count, unsigned char transpose, const float* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="transpose">Specifies whether to transpose the matrix as the values are loaded into the uniform variable</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniformMatrix4x2fv(unsigned int program, int location, int count, unsigned char transpose, const float* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="transpose">Specifies whether to transpose the matrix as the values are loaded into the uniform variable</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniformMatrix3x4fv(unsigned int program, int location, int count, unsigned char transpose, const float* value) = 0;

		/// <summary>
		/// Specify the value of a uniform variable for a specified program object
		/// </summary>
		/// <param name="program">Specifies the handle of the program containing the uniform variable to be modified</param>
		/// <param name="location">Specifies the location of the uniform variable to be modified</param>
		/// <param name="count">Specifies the number of elements that are to be modified. This should be 1 if the targeted uniform variable is not an array, and 1 or more if it is an array</param>
		/// <param name="transpose">Specifies whether to transpose the matrix as the values are loaded into the uniform variable</param>
		/// <param name="value">Specifies a pointer to an array of count values that will be used to update the specified uniform variable</param>
		virtual void ProgramUniformMatrix4x3fv(unsigned int program, int location, int count, unsigned char transpose, const float* value) = 0;

		/// <summary>
		/// Query a property of an interface in a program
		/// </summary>
		/// <param name="program">The name of a program object whose interface to query</param>
		/// <param name="programInterface">A token identifying the interface within program to query</param>
		/// <param name="pname">The name of the parameter within programInterface to query</param>
		/// <param name="params">The address of a variable to retrieve the value of pname for the program interface</param>
		virtual void GetProgramInterfaceiv(unsigned int program, unsigned int programInterface, unsigned int pname, int* params) = 0;

		/// <summary>
		/// Retrieve values for multiple properties of a single active resource within a program object
		/// </summary>
		/// <param name="program">The name of a program object whose resources to query</param>
		/// <param name="programInterface">A token identifying the interface within program containing the resourced named name</param>
		/// <param name="index"></param>
		/// <param name="propCount"></param>
		/// <param name="props"></param>
		/// <param name="bufSize"></param>
		/// <param name="length"></param>
		/// <param name="params"></param>
		virtual void GetProgramResourceiv(unsigned int program, unsigned int programInterface, unsigned int index, int propCount, const unsigned int* props, int bufSize, int* length, int* params) = 0;

		/// <summary>
		/// Query the name of an indexed resource within a program
		/// </summary>
		/// <param name="program">The name of a program object whose resources to query</param>
		/// <param name="programInterface">A token identifying the interface within program containing the indexed resource</param>
		/// <param name="index">The index of the resource within programInterface of program</param>
		/// <param name="bufSize">The size of the character array whose address is given by name</param>
		/// <param name="length">The address of a variable which will receive the length of the resource name</param>
		/// <param name="name">The address of a character array into which will be written the name of a resource</param>
		virtual void GetProgramResourceName(unsigned int program, unsigned int programInterface, unsigned int index, int bufSize, int* length, char* name) = 0;
		
		/// <summary>
		/// Query the location of a named resource within a program
		/// </summary>
		/// <param name="program">The name of a program object whose resources to query</param>
		/// <param name="programInterface">A token identifying the interface within program containing the resourced named name</param>
		/// <param name="name">The name of the resource to query the location of</param>
		virtual int GetProgramResourceLocation(unsigned int program, unsigned int programInterface, const char* name) = 0;

		/// <summary>
		/// Replaces the source code in a shader object
		/// </summary>
		/// <param name="shader">Specifies the handle of the shader object whose source code is to be replaced</param>
		/// <param name="count">Specifies the number of elements inthe string and length arrays</param>
		/// <param name="string">Specifies an array of pointers to strings containing the source code to be loaded into the shader</param>
		/// <param name="length">Specifies an array of string lengths</param>
		virtual void ShaderSource(unsigned int shader, int count, const char** string, const int* length) = 0;

		/// <summary>
		/// Creates a shader object
		/// </summary>
		/// <param name="shaderType">Specifies the type of shader to be created</param>
		/// <returns>Handle to the new shader object</returns>
		virtual unsigned int CreateShader(unsigned int shaderType) = 0;

		/// <summary>
		/// Deletes a shader object
		/// </summary>
		/// <param name="shader">Specifies the shader object to be deleted</param>
		virtual void DeleteShader(unsigned int shader) = 0;

		/// <summary>
		/// Compiles a shader object
		/// </summary>
		/// <param name="shader">Specifies the shader object to be compiled</param>
		virtual void CompileShader(unsigned int shader) = 0;

		/// <summary>
		/// Returns a parameter from a shader object
		/// </summary>
		/// <param name="shader">Specifies the shader object to be queried</param>
		/// <param name="param">Specifies the object parameter</param>
		/// <param name="params">Returns the requested object parameter</param>
		virtual void GetShaderiv(unsigned int shader, unsigned int pname, int* params) = 0;

		/// <summary>
		/// Returns the information log for a shader object
		/// </summary>
		/// <param name="shader">Specifies the shader object whose information log is to be queried</param>
		/// <param name="maxLength">Specifies the size of the character buffer for storing the returned information log</param>
		/// <param name="length">Returns the length of the string returned in infoLog (excluding the null terminator)</param>
		/// <param name="infoLog">Specifies an array of characters that is used to return the information log</param>
		virtual void GetShaderInfoLog(unsigned int shader, int maxLength, int* length, char* infoLog) = 0;

		/// <summary>
		/// Draw multiple instances of a range of elements
		/// </summary>
		/// <param name="mode">Specifies what kind of primitives to render</param>
		/// <param name="first">Specifies the starting index in the enabled arrays</param>
		/// <param name="count">Specifies the number of indicies to be rendered</param>
		/// <param name="primcount">Specifies the number of instances of the specified range of indices to be rendered</param>
		virtual void DrawArraysInstanced(unsigned int mode, int first, int count, int primcount) = 0;

		/// <summary>
		/// Render primitives from array data
		/// </summary>
		/// <param name="mode">Specifies what kind of primitives to render</param>
		/// <param name="first">Specifies the starting index in the enabled arrays</param>
		/// <param name="count">Specifies the number of indices to be rendered</param>
		virtual void DrawArrays(unsigned int mode, int first, int count) = 0;

		/// <summary>
		/// Generate vertex array object names
		/// </summary>
		/// <param name="n">Specifies the number of vertex array object names to generate</param>
		/// <param name="arrays">SPecifies an array in which the generated vertex object names are stored</param>
		virtual void GenVertexArrays(int n, unsigned int* arrays) = 0;

		/// <summary>
		/// Delete vertex array objects
		/// </summary>
		/// <param name="n">Specifies the number of vertex array objects to be deleted</param>
		/// <param name="arrays">SPecifies the address of an array containing the n names of the objects to be deleted</param>
		virtual void DeleteVertexArrays(int n, const unsigned int* arrays) = 0;

		/// <summary>
		/// Enable a generic vertex attribute array
		/// </summary>
		/// <param name="index">Specifies the index of the generic vertex attribute to be enabled</param>
		virtual void EnableVertexAttribArray(unsigned int index) = 0;

		/// <summary>
		/// Disable a generic vertex attribute array
		/// </summary>
		/// <param name="index">Specifies the index of the generic vertex attribute to be disabled</param>
		virtual void DisableVertexAttribArray(unsigned int index) = 0;

		/// <summary>
		/// Enable a generic vertex attribute array
		/// </summary>
		/// <param name="vaobj">Specifies the name of the vertex array object</param>
		/// <param name="index">Specifies the index of the generic vertex attribute to be enabled</param>
		virtual void EnableVertexArrayAttrib(unsigned int vaobj, unsigned int index) = 0;

		/// <summary>
		/// Disable a generic vertex attribute array
		/// </summary>
		/// <param name="vaobj">Specifies the name of the vertex array object</param>
		/// <param name="index">Specifies the index of the generic vertex attribute to be disabled</param>
		virtual void DisableVertexArrayAttrib(unsigned int vaobj, unsigned int index) = 0;

		/// <summary>
		/// Define an array of generic vertex attribute data
		/// </summary>
		/// <param name="index">Specifies the index of the generic vertex attribute to be modified</param>
		/// <param name="size">Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, or 4. Initial value is 4</param>
		/// <param name="type">Specifies the data type of each component in the array</param>
		/// <param name="normalized">Specifies whether fixed point data values should be normalized or converted directly as fixed point values when they are accessed</param>
		/// <param name="stride">Specifies the byte offset between consecutive generic verte attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. Initial value is 0</param>
		/// <param name="pointer">Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. Initial value is 0</param>
		virtual void VertexAttribPointer(unsigned int index, int size, unsigned int type, unsigned char normalized, int stride, const void* pointer) = 0;

		/// <summary>
		/// Define an array of generic vertex attribute data
		/// </summary>
		/// <param name="index">Specifies the index of the generic vertex attribute to be modified</param>
		/// <param name="size">Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, or 4. Initial value is 4</param>
		/// <param name="type">Specifies the data type of each component in the array</param>
		/// <param name="stride">Specifies the byte offset between consecutive generic verte attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. Initial value is 0</param>
		/// <param name="pointer">Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. Initial value is 0</param>
		virtual void VertexAttribIPointer(unsigned int index, int size, unsigned int type, int stride, const void* pointer) = 0;

		/// <summary>
		/// Define an array of generic vertex attribute data
		/// </summary>
		/// <param name="index">Specifies the index of the generic vertex attribute to be modified</param>
		/// <param name="size">Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, or 4. Initial value is 4</param>
		/// <param name="type">Specifies the data type of each component in the array</param>
		/// <param name="stride">Specifies the byte offset between consecutive generic verte attributes. If stride is 0, the generic vertex attributes are understood to be tightly packed in the array. Initial value is 0</param>
		/// <param name="pointer">Specifies an offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. Initial value is 0</param>
		virtual void VertexAttribLPointer(unsigned int index, int size, unsigned int type, int stride, const void* pointer) = 0;

		/// <summary>
		/// Modify the rate at which generic vertex attributes advance during instanced rendering
		/// </summary>
		/// <param name="index">Specifies the index of the generic vertex attribute</param>
		/// <param name="divisor">Specify the number of instances that will pass between updates of the generic attribute at slot index</param>
		virtual void VertexAttribDivisor(unsigned int index, unsigned int divisor) = 0;

		/// <summary>
		/// Bind a vertex array object
		/// </summary>
		/// <param name="array">Specifies the name of the vertex array to bind</param>
		virtual void BindVertexArray(unsigned int array) = 0;

		/// <summary>
		/// Set the viewport
		/// </summary>
		/// <param name="x">Specify the lower left corner of the viewport rectangle in pixels. Initial value is 0</param>
		/// <param name="y">Specify the lower left corner of the viewport rectangle in pixels. Initial value is 0</param>
		/// <param name="width">Specify the width of the viewport</param>
		/// <param name="height">Specifies the height of the viewport</param>
		virtual void Viewport(int x, int y, int width, int height) = 0;

		virtual void VertexArrayBindVertexBuffer() = 0;

		virtual void VertexArrayVertexAttribBinding() = 0;

		virtual void VertexArrayVertexAttribDivisor() = 0;

		/// <summary>
		/// Generate texture names. See <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenTextures.xhtml">glGenTextures</a>
		/// </summary>
		/// <param name="n">Specifies the number of texture names to be generated</param>
		/// <param name="textures">Specifies an array in which the generated texture names are stored</param>
		virtual void GenTextures(int n, unsigned int * textures) = 0;

		/// <summary>
		/// Bind a named texture to a texturing target. See <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindTexture.xhtml">glBindTexture</a>
		/// </summary>
		/// <param name="target">Specifies the target to which the texture is bound</param>
		/// <param name="texture">Specifies the name of a texture</param>
		virtual void BindTexture(unsigned int target, unsigned int texture) = 0;

		/// <summary>
		/// Specify a two dimensional texture image. See <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml">glTexImage2d</a>
		/// </summary>
		/// <param name="target">Specifies the target texture</param>
		/// <param name="level">Specifies the level of detail number. 0 is the base image, n is the nth mipmap reduction</param>
		/// <param name="internalFormat">Specifies the number of color components in the texture</param>
		/// <param name="width">Specifies the width of the texture image</param>
		/// <param name="height">Specifies the height of the texture image</param>
		/// <param name="border">Must be 0</param>
		/// <param name="format">Specifies the format of the pixel data</param>
		/// <param name="type">Specifies the data type of the pixel data</param>
		/// <param name="data">Specifies a pointer to the image data in memory</param>
		virtual void TexImage2D(unsigned int target, int level, int internalFormat, int width, int height, int border, unsigned int format, unsigned int type, const void * data) = 0;

		/// <summary>
		/// Select active texture unit. See <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glActiveTexture.xhtml">glActiveTexture</a>
		/// </summary>
		/// <param name="texture">Specifies which texture unit to make active</param>
		virtual void ActiveTexture(unsigned int texture) = 0;

		/// <summary>
		/// Set texture parameters. See <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexParameter.xhtml">glTextureParameter</a>
		/// </summary>
		/// <param name="target">Specifies the target to which the texture is bound</param>
		/// <param name="pname">Specifies the symboloc name of a single valued texture parameter</param>
		/// <param name="param">Specifies the value of pname</param>
		virtual void TexParameteri(unsigned int target, unsigned int pname, int param) = 0;

		/// <summary>
		/// Generate mipmaps for a specified texture object. See <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenerateMipmap.xhtml">glGenerateMipmap</a>
		/// </summary>
		/// <param name="target">Specifies the target to which the texture object is bound</param>
		virtual void GenerateMipmap(unsigned int target) = 0;

		/// <summary>
		/// Generate mipmaps for a specified texture object. See <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGenerateMipmap.xhtml">glGenerateTextureMipmap</a>
		/// </summary>
		/// <param name="texture">Specifies the texture object name</param>
		virtual void GenerateTextureMipmap(unsigned int texture) = 0;

		/// <summary>
		/// Enable server-side GL capabilities. See <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glEnable.xhtml">glEnable</a>
		/// </summary>
		/// <param name="capability">Specifies a symbolic constant indicating GL capability</param>
		virtual void Enable(unsigned int capability) = 0;

		/// <summary>
		/// Disable server-side GL capabilities. See <a href="https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glEnable.xhtml">glEnable</a>
		/// </summary>
		/// <param name="capability">Specifies a symbolic constant indicating GL capability</param>
		virtual void Disable(unsigned int capability) = 0;
	};
}