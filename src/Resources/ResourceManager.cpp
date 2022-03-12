#include "ResourceManager.hpp"
#include "../Renderer/ShaderPropgram.hpp"
#include "../Renderer/Texture2D.hpp"

#include <sstream>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

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

		return nullptr;
	}

	std::shared_ptr<Renderer::Texture2D> ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath)
	{
		int channels = 0;
		int width = 0;
		int height = 0;

		stbi_set_flip_vertically_on_load(true);
		unsigned char* pixels = stbi_load(
			std::string(this->_ecacutablePath + "/" + texturePath).c_str(),
			&width,
			&height,
			&channels,
			0
		);

		if (!pixels)
		{
			std::cerr << "ERROR::RESOURCE_MANAGER => can`t find texture for load: " << textureName << std::endl;
			return nullptr;
		}

		std::shared_ptr<Renderer::Texture2D> new_texture = this->_textures.emplace(
			textureName,
			std::make_shared<Renderer::Texture2D>(
				width,
				height,
				pixels,
				channels,
				GL_NEAREST,
				GL_CLAMP_TO_EDGE
			)
		).first->second;

		stbi_image_free(pixels);

		return new_texture;
	}

	std::shared_ptr<Renderer::Texture2D> ResourceManager::getTexture(const std::string& textureName)
	{
		t_texturesMap::iterator it = this->_textures.find(textureName);

		if (it != this->_textures.end())
		{
			return it->second;
		}

		std::cerr << "ERROR::RESOURCE_MANAGER => Can`t find the texture: " << textureName << std::endl;

		return nullptr;
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
