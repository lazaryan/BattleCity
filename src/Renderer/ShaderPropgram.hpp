#ifndef __SHADER_PROGRAM__
#define __SHADER_PROGRAM__

#include <string>
#include <iostream>

#include <glad/glad.h>

namespace Renderer {
	/*
	* Class for working with shaders
	* Takes 2 shaders (vertex and fragment) as input and creates a shader program for them 
	*/
	class ShaderPropgram {
	public:
		ShaderPropgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderPropgram();

		void use() const;

		// remove the ability to create a class without parameters 
		ShaderPropgram() = delete;
		// you cannot create a class from a class, because they will have the same _propgramID 
		ShaderPropgram(ShaderPropgram&) = delete;
		// Also for this reason, we remove the assignment operator 
		ShaderPropgram& operator=(const ShaderPropgram&) = delete;

		// and now we implement them ourselves 
		ShaderPropgram(ShaderPropgram&& shaderProgram) noexcept;
		ShaderPropgram& operator=(const ShaderPropgram&& shaderProgram) noexcept;

		// getters
		bool isCompiled() const { return this->_isCompiled; };
	private:
		bool compileShader(const std::string& sourceShader, GLenum shaderType, GLuint& shaderID);
		bool createPropgram(const GLuint shaderVertexID, const GLuint shaderFragmentID, GLuint& propgramID);

		// set default state
		bool _isCompiled = false;
		GLuint _propgramID = 0;
	};
}

#endif // !__SHADER_PROGRAM__
