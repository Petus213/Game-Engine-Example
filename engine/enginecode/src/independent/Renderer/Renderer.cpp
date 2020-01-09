#include "engine_pch.h"
#include "Renderer\Renderer.h"
#include "Renderer\renderAPI.h"
#include "systems\log.h"
#include "OpenGL\OpenGLRendering\OpenGLRenderer.h"

namespace Engine {

	RenderCommand * RenderCommand::ClearDepthColourBufferCommand()
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			NG_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLClearDepthColourBufferCommand();
			break;
		case RenderAPI::API::Direct3D:
			NG_ERROR("Direct3D not supported.");
			break;
		default:
			NG_ERROR("Unknown grpahics API");
		}
	}

	RenderCommand * RenderCommand::setClearColourCommand(float r, float g, float b, float a)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			NG_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLSetClearColourCommand(r, g, b, a);
			break;
		case RenderAPI::API::Direct3D:
			NG_ERROR("Direct3D not supported.");
			break;
		default:
			NG_ERROR("Unknown grpahics API");
		}
	}

	RenderCommand * RenderCommand::setDepthTestLessCommand(bool enabled)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			NG_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLsetDepthTestLessCommand(enabled);
			break;
		case RenderAPI::API::Direct3D:
			NG_ERROR("Direct3D not supported.");
			break;
		default:
			NG_ERROR("Unknown grpahics API");
		}
	}

	RenderCommand * RenderCommand::setBackfaceCullingCommand(bool enabled)
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			NG_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLsetBackfaceCullingCommand(enabled);
			break;
		case RenderAPI::API::Direct3D:
			NG_ERROR("Direct3D not supported.");
			break;
		default:
			NG_ERROR("Unknown grpahics API");
		}

	}

	Renderer * Renderer::createBasic3D()
	{
		switch (RenderAPI::getApi())
		{
		case RenderAPI::API::None:
			NG_ERROR("Lack of graphics API not supported.");
			break;
		case RenderAPI::API::OpenGL:
			return new OpenGLSuperSimpleRenderer;
			break;
		case RenderAPI::API::Direct3D:
			NG_ERROR("Direct3D not supported.");
			break;
		default:
			NG_ERROR("Unknown grpahics API");
		}
		return nullptr;
	}

}