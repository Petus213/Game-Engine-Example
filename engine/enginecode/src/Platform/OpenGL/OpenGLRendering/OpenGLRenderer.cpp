#include "engine_pch.h"
#include "OpenGL\OpenGLRendering\OpenGLRenderer.h"
#include "glad\glad.h"

namespace Engine {

	void OpenGLSuperSimpleRenderer::actionCommand(RenderCommand * command)
	{
		command->action();
		delete command;
	}

	void OpenGLSuperSimpleRenderer::submit(const std::shared_ptr<Material>& material)
	{
		auto shader = material->getShader();
		shader->bind();

		auto geometry = std::get<std::shared_ptr<VertexArray>>(material->getGeometry());
		geometry->bind();

		auto uniformData = material->getData();
		for (auto dataPair : uniformData)
		{
			shader->uploadData(dataPair.first, dataPair.second);
		}

		glDrawElements(GL_TRIANGLES, geometry->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLSetClearColourCommand::action()
	{
		glClearColor(m_r, m_g, m_b, m_a);
	}

	void OpenGLClearDepthColourBufferCommand::action()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLsetDepthTestLessCommand::action()
	{
		if (m_enabled) {
			glEnable(GL_DEPTH_TEST);
			glCullFace(GL_BACK);
		}
		else {
			glDisable(GL_DEPTH_TEST);
			glCullFace(GL_NONE);
		}
		
	}

	void OpenGLsetBackfaceCullingCommand::action()
	{
		if (m_enabled) {
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
		else {
			glDisable(GL_CULL_FACE);
			glCullFace(GL_NONE);
		}
	}

	OpenGLMaterial::OpenGLMaterial(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO)
	{
		init(shader, VAO);
	}

	void OpenGLMaterial::init(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO)
	{
		m_shader = shader;
		m_geometry = VAO;
	}

	void OpenGLMaterial::setShader(const std::shared_ptr<Shader>& shader)
	{
		m_shader = shader;
	}

	void OpenGLMaterial::setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry)
	{
		m_geometry = std::get<std::shared_ptr<VertexArray>>(geometry);
	}

	void OpenGLMaterial::setDataBlock(const std::map<std::string, void*>& data)
	{
		for (auto dataPair : data)
		{
			m_data[dataPair.first] = dataPair.second;
		}
	}

	void OpenGLMaterial::setDataElement(const std::string & dataName, void * data)
	{
		m_data[dataName] = data;
	}

}