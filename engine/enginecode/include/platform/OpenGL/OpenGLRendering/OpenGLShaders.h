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
		unsigned int m_OpenGL_ID; //!< integer value for ID for the openGL shader
		void compileAndLink(std::string vertexShaderSrc, const std::string& fragmentShaderSrc); //!< void function for compile and linking shaders
		void parseSource(const std::string& filepath); //!< void function for parsring source code
		void dispatchUniformUpload(ShaderDataType type, GLuint location, void * data); //!< void function for dispatching uniform upload
		BufferLayout m_BufferLayout; //!< m_BufferLayout from class Buffer Layout
		UniformLayout m_UniformLayout; //!< m_UniformLayout from class Uniform Layout

	public:
		OpenGLShader(const std::string& filepath); //!< constructor
		OpenGLShader(const std::string& vertexFilepath, const std::string& fragmentFilepath); //!< constructor
		
		inline unsigned int id() override { return m_OpenGL_ID; } //!< integer value for ID
		virtual void bind() override; //!< void function for bind
		virtual void unbind() override; //!< void function for unbind
		
		virtual bool uploadData(const std::string& name, void* data) override; //!< boolean value for uploadData
		virtual bool uploadData(const UniformLayout& uniforms) override; //!< boolean value for uploadData
		virtual BufferLayout getBufferLayout() const override { return m_BufferLayout; } //!< get buffer layout, returns m_BufferLayout
		virtual UniformLayout getUniformLayout() const override { return m_UniformLayout; } //!< get uniform layout, returns m_UniformLayout

	};
	
}