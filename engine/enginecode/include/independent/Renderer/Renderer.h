#pragma once
#include "Material.h"
namespace Engine {

	class RenderCommand
	{
	public:
		virtual void action() = 0;
	public:
		static RenderCommand * ClearDepthColourBufferCommand();
		static RenderCommand * setClearColourCommand(float r, float g, float b, float a);
		static RenderCommand * setDepthTestLessCommand(bool enabled);
		static RenderCommand * setBackfaceCullingCommand(bool enabled);
	};

	class Renderer
	{
	public:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		virtual void actionCommand(RenderCommand* command) = 0;
		virtual void beginScene(const SceneData& sceneData) = 0;
		virtual void endScene() = 0;
		virtual void submit(const std::shared_ptr<Material>& material) = 0;
		virtual void flush() = 0;

		static Renderer* createBasic3D();
	};
}