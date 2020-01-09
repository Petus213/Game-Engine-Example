#pragma once
#include "Renderer\Renderer.h"
#include "Renderer\Material.h"

namespace Engine {

	class OpenGLSuperSimpleRenderer : public Renderer
	{
	private:
	public:
		void actionCommand(RenderCommand* command) override;
		void beginScene(const SceneData& sceneData) {};
		void endScene() override {};
		void submit(const std::shared_ptr<Material>& material) override;
		void flush() override {};
	};

	class OpenGLSetClearColourCommand : public RenderCommand
	{
	private:
		float m_r, m_g, m_b, m_a;
	public:
		OpenGLSetClearColourCommand(float r, float g, float b, float a) : m_r(r), m_g(g), m_b(b), m_a(a) {};
		void action() override;
	};

	class OpenGLClearDepthColourBufferCommand : public RenderCommand
	{
	private:
	public:
		OpenGLClearDepthColourBufferCommand() {};
		void action() override;
	};

	class OpenGLsetDepthTestLessCommand : public RenderCommand
	{
	private:
		bool m_enabled;
	public:
		OpenGLsetDepthTestLessCommand(bool enabled) : m_enabled(enabled) {};
		void action() override;
	};

	class OpenGLsetBackfaceCullingCommand : public RenderCommand
	{
	private:
		bool m_enabled;
	public:
		OpenGLsetBackfaceCullingCommand(bool enabled) : m_enabled(enabled) {};
		void action() override;
	};

	class OpenGLMaterial : public Material
	{
	public:
		OpenGLMaterial(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO);
		void init(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO);
		void setShader(const std::shared_ptr<Shader>& shader) override;
		void setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry) override;
		void setDataBlock(const std::map<std::string, void *>& data) override;
		void setDataElement(const std::string& dataName, void * data) override;
		
		inline std::shared_ptr<Shader> getShader() override { return m_shader; }
		inline std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>> getGeometry() override 
		{
			return std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>(m_geometry);
		}
		inline std::map<std::string, void *> getData() override { return m_data; }
	private:
		std::shared_ptr<Shader> m_shader;
		std::shared_ptr<VertexArray> m_geometry;
		std::map<std::string, void *> m_data;
	};
}