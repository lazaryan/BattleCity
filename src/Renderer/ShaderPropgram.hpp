#ifndef __SHADER_PROGRAM__
#define __SHADER_PROGRAM__

#include <string>
#include <iostream>

#include <glad/glad.h>

namespace Renderer {
	/*
	* ����� ��� ������� � ���������
	* �� ����� ��������� 2 ������ � ������� �� ���� ��������� ���������
	*/
	class ShaderPropgram {
	public:
		ShaderPropgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderPropgram();

		void use() const;

		// ������� ����������� �������� ������ ��� ���������
		ShaderPropgram() = delete;
		// ������ ��������� ����� �� ������, �.�. � ��� ����� ���������� _propgramID
		ShaderPropgram(ShaderPropgram&) = delete;
		// ����� �� ���� ������ ������� �������� ����������
		ShaderPropgram& operator=(const ShaderPropgram&) = delete;

		//� ������ �� ���� ���������
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
