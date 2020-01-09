#include "engine_pch.h"
#include "Renderer\Shader.h"
#include "Renderer\renderAPI.h"
#include "OpenGL\OpenGLRendering\OpenGLShaders.h"

namespace Engine {

	Shader * Engine::Shader::create(const std::string & filepath)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			return nullptr;
		case RenderAPI::API::OpenGL:
			return new OpenGLShader(filepath);
		}
		return nullptr;
	}


	Shader * Shader::create(const std::string & vertexFilepath, const std::string & fragmentFilepath)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			return nullptr;
		case RenderAPI::API::OpenGL:
			return new OpenGLShader(vertexFilepath);
		}
		return nullptr;
	}
	
}