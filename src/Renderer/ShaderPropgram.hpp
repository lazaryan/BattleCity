#ifndef __SHADER_PROGRAM__
#define __SHADER_PROGRAM__

#include <string>
#include <iostream>

#include <glad/glad.h>

namespace Renderer {
	/*
	* Класс для рабоаты с шейдерами
	* На воход принимает 2 шйдера и создает дл яних шейдерную программу
	*/
	class ShaderPropgram {
	public:
		ShaderPropgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderPropgram();

		void use() const;

		// удаляем возможность создания класса без парамеров
		ShaderPropgram() = delete;
		// нельзя создавать класс из класса, т.к. у них будет одинаковый _propgramID
		ShaderPropgram(ShaderPropgram&) = delete;
		// Также по этой прчине удаляем оператор присваения
		ShaderPropgram& operator=(const ShaderPropgram&) = delete;

		//а теперь их сами реализуем
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
