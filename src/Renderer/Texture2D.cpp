#include "Texture2D.hpp"

namespace Renderer {
	Texture2D::Texture2D(
		const GLuint width,
		const GLuint height,
		const unsigned char* data,
		const unsigned int channels,
		const GLenum filter,
		const GLenum wrapMode
	) : texture_width(width), texture_height(height)
	{
		this->mode = channels == 3 ? GL_RGB : GL_RGBA;

		glGenTextures(1, &this->textureID);
		glBindTexture(GL_TEXTURE_2D, this->textureID);

		glTexImage2D(GL_TEXTURE_2D, 0, this->mode, this->texture_width, this->texture_height, 0, this->mode, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D::Texture2D(Texture2D&& texture2d)
	{
		this->textureID = texture2d.textureID;
		this->mode = texture2d.mode;
		this->texture_height = texture2d.texture_height;
		this->texture_width = texture2d.texture_width;

		texture2d.textureID = 0;
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &this->textureID);
	}

	Texture2D& Texture2D::operator=(Texture2D&& texture2d)
	{
		glDeleteTextures(1, &this->textureID);

		this->textureID = texture2d.textureID;
		this->mode = texture2d.mode;
		this->texture_height = texture2d.texture_height;
		this->texture_width = texture2d.texture_width;

		texture2d.textureID = 0;

		return *this;
	}

	void Texture2D::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, this->textureID);
	}
}