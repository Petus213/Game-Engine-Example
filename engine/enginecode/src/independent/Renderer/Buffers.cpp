#include "engine_pch.h"

#include "Renderer\renderAPI.h"
#include "Renderer\Buffers.h"
#include "include\platform\OpenGL\OpenGLBuffers.h"
#include "systems\log.h"

namespace Engine {

	VertexBuffer* VertexBuffer::create(float* vertices, unsigned int size)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			NG_ERROR("Lack of graphics API not supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
			break;
		case RenderAPI::API::Direct3D:
			NG_ERROR("Direct3D not supported");
			break;
		default:
			NG_ERROR("Unknown graphics API");
		}
	}





	IndexBuffer* IndexBuffer::create(unsigned int* indices, unsigned int count)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			NG_ERROR("Lack of graphics API not supported");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
			break;
		case RenderAPI::API::Direct3D:
			NG_ERROR("Direct3D not supported");
			break;
		default:
			NG_ERROR("Unknown grpahics API");
		}
	}
	void BufferLayout::addElement(BufferElement element)
	{
		m_Elements.push_back(element);
		CalculateOffsetsAndStride();
	}
}