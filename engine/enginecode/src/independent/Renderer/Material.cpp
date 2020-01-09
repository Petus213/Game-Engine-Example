#include "engine_pch.h"
#include "Renderer\Material.h"
#include "Renderer\renderAPI.h"
#include "OpenGL\OpenGLRendering\OpenGLRenderer.h"

namespace Engine {


	Material * Material::create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO)
	{
		switch (RenderAPI::getApi()) {
		case RenderAPI::API::None:
			return nullptr;
		case RenderAPI::API::OpenGL:
			return new OpenGLMaterial(shader, VAO);
		}
		return nullptr;
	}

	Material * Material::create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& VBO)
	{
		return nullptr;
	}

}