/*! \file OpenGLTextures.h
* Using the Texture class, this is specifically for OpenGL.
*/
#pragma once
#include "Renderer\Texture.h"


namespace Engine {

	/*! \class OpenGLShader
	* This class inherits from the Texture class
	* It is used only for the OpenGL renderer.
	*/
	class OpenGLTexture : public Texture
	{
	private:
		std::string m_Path;
		static unsigned int s_TextureSlot;
		unsigned int m_Width;
		unsigned int m_Height;
		unsigned int m_Channels;
		unsigned int m_TextureSlot[2];
		unsigned int m_numberTexture;
		unsigned int m_letterTexture;
		unsigned int m_Opengl_ID;
	public:

		OpenGLTexture(const std::string& path);
		OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData);
		virtual ~OpenGLTexture();

		virtual unsigned int getWidth() const override { return m_Width; }
		virtual unsigned int getHeight() const override { return m_Height; }
		virtual unsigned int getChannels() const override { return m_Channels; }
		virtual unsigned int getSlot() const override { return m_TextureSlot[2]; }
	};


}