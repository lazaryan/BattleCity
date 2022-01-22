#ifndef __RESOURCE_MANAGER__
#define __RESOURCE_MANAGER__

#include <string>
#include <memory>
#include <map>

namespace Renderer {
	class ShaderPropgram;
}

namespace Resources {
	class ResourceManager {
	public:
		//atr ecacutablePath - path to bin (.exe) file
		ResourceManager(const std::string& executablePath);
		~ResourceManager() = default;

		// this class is Singlton
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;

		std::shared_ptr<Renderer::ShaderPropgram> loadShaderProgram(
			const std::string& shaderName,
			const std::string& pathToVertexShader,
			const std::string& pathToFragmentShader
		);
		std::shared_ptr<Renderer::ShaderPropgram> getShaderProgram(const std::string& shaderName);
	private:
		typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderPropgram>> t_shaderProgramsMap;

		std::string getFileData(const std::string& relativePathToFile) const;

		t_shaderProgramsMap _shaderPropgrams;
		std::string _ecacutablePath;
	};
}

#endif // !__RESOURCE_MANAGER__
