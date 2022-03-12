#ifndef __RENDERER_TEXTURE2D__
#define __RENDERER_TEXTURE2D__

#include <string>

#include <glad/glad.h>

namespace Renderer {
	class Texture2D {
	public:
		Texture2D(
			const GLuint width,
			const GLuint height,
			const unsigned char* data,
			const unsigned int channels = 4,
			const GLenum filter = GL_LINEAR,
			const GLenum wrapMode = GL_CLAMP_TO_EDGE
		);
		Texture2D(Texture2D&& texture2d);

		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;

		Texture2D& operator=(Texture2D&& texture2d);

		~Texture2D();

		void bind() const;
	private:
		GLuint textureID;
		GLenum mode;
		unsigned int texture_width;
		unsigned int texture_height;
	};
}

#endif // !__RENDERER_TEXTURE2D__
