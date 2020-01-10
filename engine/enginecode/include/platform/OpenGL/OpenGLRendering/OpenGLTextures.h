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
		std::string m_Path; //!< string named m_Path
		static unsigned int s_TextureSlot; //!< integer value for s_TextureSLot
		unsigned int m_Width; //!< integer value for Width
		unsigned int m_Height; //!< integer value for height
		unsigned int m_Channels; //!< integer value for channels
		unsigned int m_TextureSlot[2]; //!< integer value for texture slots
		unsigned int m_numberTexture; //!< integer value for NumberTexture
		unsigned int m_letterTexture; //!< integer value for LetterTexture
		unsigned int m_Opengl_ID; //!< integer value for ID of texture
	public:

		OpenGLTexture(const std::string& path); //!< constructor
		OpenGLTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData); //!< constructor
		virtual ~OpenGLTexture(); //!< destructor

		virtual unsigned int getWidth() const override { return m_Width; } //!< gets width and returns m_width
		virtual unsigned int getHeight() const override { return m_Height; } //!< gets height and return m_height
		virtual unsigned int getChannels() const override { return m_Channels; } //!< gets channels and returns m_channels
		virtual unsigned int getSlot() const override { return m_TextureSlot[2]; } //!< gets slots and returns m_TextureSlot
	};


}