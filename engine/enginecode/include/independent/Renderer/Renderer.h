/*! \file Renderer.h
* This file contains the base class for all renderers
*/
#pragma once
#include "Material.h"
namespace Engine {

	/*! \class RenderCommand
	* This class contains the base commands the renderer will use
	*/
	class RenderCommand
	{
	public:
		virtual void action() = 0; //!< void function action
	public:
		static RenderCommand * ClearDepthColourBufferCommand(); //!< pointer to ClearDepthColourBufferCommand function
		static RenderCommand * setClearColourCommand(float r, float g, float b, float a); //!< pointer to setClearColourCommand function
		static RenderCommand * setDepthTestLessCommand(bool enabled); //!< pointer to SetDepthTestLessCommand function
		static RenderCommand * setBackfaceCullingCommand(bool enabled); //!< pointer to setBackfaceCullingCommand function
	};

	/*! \class Renderer
	* This class is the basis for the other render classes
	* in this engine it will be used by an OpenGL renderer
	*/
	class Renderer
	{
	public:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		virtual void actionCommand(RenderCommand* command) = 0; //!< void function actionCommand - pure virtual
		virtual void beginScene(const SceneData& sceneData) = 0; //!< void function beginScene - pure virtual
		virtual void endScene() = 0; //!< void function endScene - pure virtual
		virtual void submit(const std::shared_ptr<Material>& material) = 0; //!< void function submit - pure virtual
		virtual void flush() = 0; //!< void function flush - pure virtual

		static Renderer* createBasic3D(); //!< pointer to createBasic3D function
	};
}