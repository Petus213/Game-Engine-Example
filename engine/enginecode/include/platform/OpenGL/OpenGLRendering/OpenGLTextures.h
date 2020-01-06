#pragma once
#include "Renderer\Texture.h"


namespace Engine {

	class OpenGLTexture : public Texture
	{
	private:
		std::string m_Path;
		static unsigned int s_TextureSlot;
		unsigned int m_Width;
		unsigned int m_Height;
		unsigned int m_Channels;
		unsigned int m_TextureSlot;
		unsigned int m_Opengl_ID;
	public:

		OpenGLTexture(const std::string& path);
		OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData);
		virtual ~OpenGLTexture();

		virtual unsigned int getWidth() const override { return m_Width; }
		virtual unsigned int getHeight() const override { return m_Height; }
		virtual unsigned int getChannels() const override { return m_Channels; }
		virtual unsigned int getSlot() const override { return m_Slot; }
	};


}