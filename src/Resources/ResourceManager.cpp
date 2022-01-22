#include "ResourceManager.hpp"
#include "../Renderer/ShaderPropgram.hpp"

#include <sstream>
#include <fstream>
#include <iostream>

namespace Resources {
	ResourceManager::ResourceManager(const std::string& executablePath)
	{
		size_t indexLastDirSeparator = executablePath.find_last_of("/\\");

		this->_ecacutablePath = executablePath.substr(0, indexLastDirSeparator);
	}

	std::shared_ptr<Renderer::ShaderPropgram> ResourceManager::loadShaderProgram(
		const std::string& shaderName,
		const std::string& pathToVertexShader,
		const std::string& pathToFragmentShader
	)
	{
		std::string vertexShaderText = this->getFileData(pathToVertexShader);
		if (vertexShaderText.empty())
		{
			std::cerr << "ERROR::RESOURCE_MANAGER::GET_SHADER_TEXT => shader file" << pathToVertexShader << "is empty" << std::endl;
			return nullptr;
		}

		std::string fragmentShaderText = this->getFileData(pathToFragmentShader);
		if (fragmentShaderText.empty())
		{
			std::cerr << "ERROR::RESOURCE_MANAGER::GET_SHADER_TEXT => shader file" << pathToFragmentShader << "is empty" << std::endl;
			return nullptr;
		}

		std::shared_ptr<Renderer::ShaderPropgram> sharedResource = this->_shaderPropgrams.emplace(
			shaderName,
			std::make_shared<Renderer::ShaderPropgram>(vertexShaderText, fragmentShaderText)
		).first->second;

		if (!sharedResource->isCompiled())
		{
			std::cerr << "ERROR::RESOURCE_MANAGER => error create program"
				<< "vertex file:" << pathToVertexShader
				<< "fragment file:" << pathToFragmentShader << std::endl;
			return nullptr;
		}

		return sharedResource;
	}

	std::shared_ptr<Renderer::ShaderPropgram> ResourceManager::getShaderProgram(const std::string& shaderName)
	{
		t_shaderProgramsMap::iterator it = this->_shaderPropgrams.find(shaderName);

		if (it != this->_shaderPropgrams.end())
		{
			return it->second;
		}

		std::cerr << "ERROR::RESOURCE_MANAGER => Can`t find program: " << shaderName << std::endl;
	}

	std::string ResourceManager::getFileData(const std::string& relativePathToFile) const
	{
		std::fstream fileStram;

		fileStram.open(this->_ecacutablePath + "/" + relativePathToFile.c_str(), std::ios::in | std::ios::binary);
		if (!fileStram.is_open())
		{
			std::cerr << "ERROR::RESOURCE_MANAGER => Failed to open file: " << relativePathToFile << std::endl;
			return std::string{};
		}

		std::stringstream buffer;

		buffer << fileStram.rdbuf();

		return buffer.str();
	}
}
