/*! \file OpenGLRenderer.h
* Using the Renderer class this is specifically for OpenGL
*/
#pragma once
#include "Renderer\Renderer.h"
#include "Renderer\Material.h"

namespace Engine {
	/*! \class OpenGLSuperSimpleRenderer
	* Renderer class for OpenGL inherits from Renderer class
	*/
	class OpenGLSuperSimpleRenderer : public Renderer
	{
	private:
	public:
		void actionCommand(RenderCommand* command) override; //!< void function ActionCommand
		void beginScene(const SceneData& sceneData) {}; //!< void function begin Scene
		void endScene() override {}; //!< void function end Scene
		void submit(const std::shared_ptr<Material>& material) override; //!< void function for submit
		void flush() override {}; //!< void function for flush
	};

	/*! \class OpenGLSetClearColourCommand
	* SetClearColourCommmand class for OpenGL inherits from RenderCommand class
	*/
	class OpenGLSetClearColourCommand : public RenderCommand
	{
	private:
		float m_r, m_g, m_b, m_a; //!< float variables for RGBA
	public:
		OpenGLSetClearColourCommand(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {}; //!< constructor
		void action() override; //!< void function for action
	};
	/*! \class OpenGLClearDepthColourBufferCommand
	*ClearDepthColourBufferCommand class for OpenGL inherits from RenderCommand class
	*/
	class OpenGLClearDepthColourBufferCommand : public RenderCommand
	{
	private:
	public:
		OpenGLClearDepthColourBufferCommand() {};//!< constructor
		void action() override; //!< void function for action
	};
	/*! \class OpenGLSetDepthTestLessCommand
	* setDepthTestLessCommmand class for OpenGL inherits from RenderCommand class
	*/
	class OpenGLsetDepthTestLessCommand : public RenderCommand
	{
	private:
		bool m_enabled; //!< boolean variable for m_enabled
	public:
		OpenGLsetDepthTestLessCommand(bool enabled) : m_enabled(enabled) {}; //!< constructor
		void action() override; //!< void function action
	};

	/*! \class OpenGLSetBackfaceCullingCommand
	* SetBackfaceCullingCommmand class for OpenGL inherits from RenderCommand class
	*/
	class OpenGLsetBackfaceCullingCommand : public RenderCommand
	{
	private:
		bool m_enabled; //!< boolean variable for m_enabled
	public:
		OpenGLsetBackfaceCullingCommand(bool enabled) : m_enabled(enabled) {}; //!< constructor
		void action() override; //!< void function action
	};

	/*! \class OpenGLMaterial 
	* OpenGLMaterial class, inherits from an existing Material Class
	*/
	class OpenGLMaterial : public Material
	{
	public:
		OpenGLMaterial(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO); //!< constructor
		void init(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO); //!< vvoid function for initilisation
		void setShader(const std::shared_ptr<Shader>& shader) override; //!< void function for setting shader
		void setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry) override; //!< void function for setting geometry
		void setDataBlock(const std::map<std::string, void *>& data) override; //!< void function setting data block
		void setDataElement(const std::string& dataName, void * data) override; //!< void function for setting data element
		
		inline std::shared_ptr<Shader> getShader() override { return m_shader; } //!< shared pointer to getShader
		inline std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>> getGeometry() override //!< shared pointer to vertex array and vertex buffer to get Geometry 
		{
			return std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>(m_geometry);
		}
		inline std::map<std::string, void *> getData() override { return m_data; } //!< maps the data from m_data
	private:
		std::shared_ptr<Shader> m_shader; //!< shared pointer to m_shader
		std::shared_ptr<VertexArray> m_geometry; //!< shared pointer to m_geometry 
		std::map<std::string, void *> m_data; //!< map for m_data
	};
}