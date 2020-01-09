/*! \file OpenGLShaders.h
* Using the Shaders class, this class is specifically for OpenGL
*/
#pragma once
#include "Renderer\Shader.h"
#include <glad\glad.h>

namespace Engine {
	
	/*! \class OpenGLShader
	* This class inherits from the Shader class
	* It is used only for the OpenGL renderer. 
	*/
	class OpenGLShader : public Shader
	{
	private: 
		unsigned int m_OpenGL_ID;
		void compileAndLink(std::string vertexShaderSrc, const std::string& fragmentShaderSrc);
		void parseSource(const std::string& filepath);
		void dispatchUniformUpload(ShaderDataType type, GLuint location, void * data);
		BufferLayout m_BufferLayout;
		UniformLayout m_UniformLayout;

	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
		
		inline unsigned int id() override { return m_OpenGL_ID; }
		virtual void bind() override;
		virtual void unbind() override;
		
		virtual bool uploadData(const std::string& name, void* data) override;
		virtual bool uploadData(const UniformLayout& uniforms) override;
		virtual BufferLayout getBufferLayout() const override { return m_BufferLayout; }
		virtual UniformLayout getUniformLayout() const override { return m_UniformLayout; }

	};
	
}