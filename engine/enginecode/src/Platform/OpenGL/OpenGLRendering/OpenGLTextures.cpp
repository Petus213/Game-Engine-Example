#include "engine_pch.h"
#include "OpenGL\OpenGLRendering\OpenGLTextures.h"
#include "stb_image.h"
#include <glad\glad.h>
namespace Engine {

	

	OpenGLTexture::OpenGLTexture(const std::string & path)
	{
		int width, height, channels;
		unsigned char * texData;
		m_Width = width;
		m_Height = height;
		m_Channels = channels;

		glGenTextures(1, &m_Opengl_ID);
		m_TextureSlot = s_TextureSlot;
		s_TextureSlot++;

		glActiveTexture(GL_TEXTURE0 + m_TextureSlot);
		glBindTexture(GL_TEXTURE_2D, m_Opengl_ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (texData)
		{
			if (channels == 3) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
			else if (channels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
			else return;
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			return;
		}
		stbi_image_free(texData);
	}

	OpenGLTexture::OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData)
	{
		glGenTextures(1, &m_Opengl_ID);
		m_TextureSlot = s_TextureSlot;
		s_TextureSlot++;

		glActiveTexture(GL_TEXTURE0 + m_TextureSlot);
		glBindTexture(GL_TEXTURE_2D, m_Opengl_ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (channels == 3)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 3);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		}
		else if (channels == 4) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		else if (channels == 1)
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, texData);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		}
		else return;
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_Opengl_ID);
	}

	

}