#include "engine_pch.h"
#include "..\..\..\include\independent\Renderer\Texture.h"
#include "Renderer\renderAPI.h"
#include "OpenGL\OpenGLRendering\OpenGLTextures.h"

namespace Engine {
	Texture * Engine::Texture::createFromFile(const std::string & filepath)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			return nullptr;
		case RenderAPI::API::OpenGL:
			return new OpenGLTexture(filepath);
		}
		return nullptr;
	}

	Texture * Engine::Texture::createFromRawData(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData)
	{
		return nullptr;
	}
}