#include "ShaderPropgram.hpp"

namespace Renderer {
	ShaderPropgram::ShaderPropgram(const std::string& vertexShader, const std::string& fragmentShader)
	{
        GLuint idVertexShader;
        GLuint idFragmentShader;
        
        //создаем vertex и fragment шейдеры и компилируем их
        if (!this->compileShader(vertexShader, GL_VERTEX_SHADER, idVertexShader))
        {
            std::cerr << "ERROR::SHADER_COMPILED => Vertex Shader" << std::endl;
            return;
        }
        if (!this->compileShader(fragmentShader, GL_FRAGMENT_SHADER, idFragmentShader))
        {
            std::cerr << "ERROR::SHADER_COMPILED => Fragment Shader" << std::endl;
            return;
        }

        // теперь эти шейдеры линкуем в программу, т.е. последовательное выполнение 2-х этих шейдеров
        if (!this->createPropgram(idVertexShader, idFragmentShader, this->_propgramID))
        {
            return;
        }

        this->_isCompiled = true;
	}

    ShaderPropgram::~ShaderPropgram()
    {
        if (glIsProgram(this->_propgramID))
        {
            glDeleteProgram(this->_propgramID);
        }
    }

    ShaderPropgram::ShaderPropgram(ShaderPropgram&& shaderProgram) noexcept
    {
        this->_propgramID = shaderProgram._propgramID;
        this->_isCompiled = shaderProgram._isCompiled;
    }

    ShaderPropgram& ShaderPropgram::operator=(const ShaderPropgram&& shaderProgram) noexcept
    {
        glDeleteProgram(this->_propgramID);

        this->_propgramID = shaderProgram._propgramID;
        this->_isCompiled = shaderProgram._isCompiled;

        return *this;
    }

    void ShaderPropgram::use() const
    {
        glUseProgram(this->_propgramID);
    }

    bool ShaderPropgram::compileShader(const std::string& sourceShader, const GLenum shaderType, GLuint& shaderID)
    {
        shaderID = glCreateShader(shaderType);
        const char* sourceCode = sourceShader.c_str();

        glShaderSource(shaderID, 1, &sourceCode, nullptr);
        glCompileShader(shaderID);

        // проверяем, что все скопилировалось без ошибок
        GLint isSuccess;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);
        if (!isSuccess)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
            glDeleteShader(shaderID);

            std::cerr << "ERROR::SHADER_COMPILED => Compile time Error: \n" << infoLog << std::endl;

            return false;
        }

        return true;
    }

    bool ShaderPropgram::createPropgram(const GLuint shaderVertexID, const GLuint shaderFragmentID, GLuint& propgramID)
    {
        propgramID = glCreateProgram();

        glAttachShader(propgramID, shaderVertexID);
        glAttachShader(propgramID, shaderFragmentID);

        glLinkProgram(propgramID);

        // их уже прилинковали в программу и шейдеры, как отдельные сущности уже не нужны
        glDeleteShader(shaderVertexID);
        glDeleteShader(shaderFragmentID);

        GLint isSuccess;
        glGetProgramiv(propgramID, GL_LINK_STATUS, &isSuccess);
        if (!isSuccess)
        {
            GLchar infoLog[1024];
            glGetProgramInfoLog(propgramID, 1024, nullptr, infoLog);
            glDeleteProgram(propgramID);

            std::cerr << "ERROR::PROGRAM_LINK => Compile time Error: \n" << infoLog << std::endl;

            return false;
        }

        return true;
    }
}
