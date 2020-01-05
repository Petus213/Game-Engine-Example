#include "engine_pch.h"

#include "Renderer\VertexArray.h"
#include "Renderer\renderAPI.h"
#include "OpenGL\OpenGLVertexArray.h"

namespace Engine {

	VertexArray* VertexArray::create()
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			NG_ERROR("Lack of graphics API not supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLVertexArray();
			break;
		case RenderAPI::API::Direct3D:
			NG_ERROR("Direct3D is not supported");
			break;
		default:
			NG_ERROR("Unknown Graphics API");
		}
		return nullptr;
	}
}