#include "engine_pch.h"
#include "OpenGL\OpenGLRendering\OpenGLShaders.h"
#include "systems\log.h"
#include <glm\gtc\type_ptr.hpp>

namespace Engine {
	
	static ShaderDataType GLSLStrToSDT(const std::string& glslSrc) {
		if (glslSrc == "bool")      return ShaderDataType::Bool;
		if (glslSrc == "int")       return ShaderDataType::Int;
		if (glslSrc == "ivec2")     return ShaderDataType::Int2;
		if (glslSrc == "ivec3")     return ShaderDataType::Int3;
		if (glslSrc == "ivec4")     return ShaderDataType::Int4;
		if (glslSrc == "float")     return ShaderDataType::Float;
		if (glslSrc == "vec2")      return ShaderDataType::Float2;
		if (glslSrc == "vec3")      return ShaderDataType::Float3;
		if (glslSrc == "vec4")      return ShaderDataType::Float4;
		if (glslSrc == "mat3")      return ShaderDataType::Mat3;
		if (glslSrc == "mat4")      return ShaderDataType::Mat4;
		if (glslSrc == "sampler2D") return ShaderDataType::Sampler2D;
	}

	static ShaderDataType OpenGLtoShaderDataType(GLenum type)
	{
		switch (type) {
		case GL_BOOL: 
			return ShaderDataType::Bool;
			break;
		case GL_INT:
			return ShaderDataType::Int;
			break;
		case GL_INT_VEC2:
			return ShaderDataType::Int2;
			break;
		case GL_FLOAT:
			return ShaderDataType::Float;
			break;
		case GL_FLOAT_VEC2:
			return ShaderDataType::Float2;
			break;
		case GL_FLOAT_VEC3:
			return ShaderDataType::Float3;
			break;
		case GL_FLOAT_VEC4:
			return ShaderDataType::Float4;
			break;
		case GL_FLOAT_MAT3:
			return ShaderDataType::Mat3;
			break;
		case GL_FLOAT_MAT4:
			return ShaderDataType::Mat4;
			break;
		case GL_SAMPLER_2D:
			return ShaderDataType::Sampler2D;
			break;
		}


	}

	void OpenGLShader::parseSource(const std::string & filepath)
	{
		std::fstream handle(filepath, std::ios::in);
		enum { NONE = -1, VERTEX = 0, FRAGMENT } region;
		if (!handle.is_open()) NG_ERROR("could not open shader file '{0}' .", filepath);

		std::string line, src[2];
		std::vector<std::string> elementType;
		while (getline(handle, line))
		{
			if (line.find("layout") != std::string::npos) {
				std::string word;
				std::string type;
				std::string name;
				std::istringstream iss(line);
				while (iss) {
					iss >> word;
					if (word == "out") { break; }
					else if (word == "in") {
						iss >> type;
						iss >> name;
						name.pop_back();
						BufferElement element = BufferElement(GLSLStrToSDT(type), name, false);
						m_BufferLayout.addElement(element);
						break;
					}
				}
			}
			if (line.find("#region Vertex") != std::string::npos) { region = VERTEX; continue; }
			if (line.find("#region Fragment") != std::string::npos) { region = FRAGMENT; continue; }
			if (line.find("#region Geometry") != std::string::npos) { region = NONE; continue; }
			if (line.find("#region Tessalation") != std::string::npos) { region = NONE; continue; }

			if (region != NONE) src[region] += (line + "\n");
		}
		handle.close();
		compileAndLink(src[VERTEX], src[FRAGMENT]);

	
	}

	OpenGLShader::OpenGLShader(const std::string & filepath)
	{
		parseSource(filepath);
	}

	OpenGLShader::OpenGLShader(const std::string & vertexFilepath, const std::string & fragmentFilepath)
	{
		std::fstream handle;
		enum { VERTEX = 0, FRAGMENT } region;
		std::string line, src[2];

		handle.open(vertexFilepath, std::ios::in);
		if (!handle.is_open()) NG_ERROR("Could not open shader file '{0}' .", vertexFilepath);

		while (getline(handle, line))
		{
			src[VERTEX] += line;
		}
		handle.close();

		handle.open(fragmentFilepath, std::ios::in);
		if (!handle.is_open()) NG_ERROR("Could not open shader file '{0}' .", fragmentFilepath);

		while (getline(handle, line))
		{
			src[FRAGMENT] += line;
		}
		handle.close();

		compileAndLink(src[VERTEX], src[FRAGMENT]);

		bind();
	}


	void OpenGLShader::compileAndLink(std::string vertexShaderSrc, const std::string & fragmentShaderSrc)
	{
		//Vertex Shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* src = vertexShaderSrc.c_str();
		glShaderSource(vertexShader, 1, &src, 0);
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			NG_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(vertexShader);
			return;
		}

		//Fragment Shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		src = fragmentShaderSrc.c_str();
		glShaderSource(fragmentShader, 1, &src, 0);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
			NG_ERROR("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			return;
		}

		//Link Shaders
		m_OpenGL_ID = glCreateProgram();
		glAttachShader(m_OpenGL_ID, vertexShader);
		glAttachShader(m_OpenGL_ID, fragmentShader);
		glLinkProgram(m_OpenGL_ID);

		GLint isLinked = 0;
		glGetProgramiv(m_OpenGL_ID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_OpenGL_ID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_OpenGL_ID, maxLength, &maxLength, &infoLog[0]);
			NG_ERROR("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(m_OpenGL_ID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return;
		}
		glDetachShader(m_OpenGL_ID, vertexShader);
		glDetachShader(m_OpenGL_ID, fragmentShader);
	}

	void OpenGLShader::bind()
	{
		glUseProgram(m_OpenGL_ID);

	}

	void OpenGLShader::unbind()
	{
		glUseProgram(0);
	}

	bool OpenGLShader::uploadData(const std::string & name, void * data)
	{
		GLint location = glGetUniformLocation(m_OpenGL_ID, name.c_str());
		GLenum Type;
		GLint size;
		GLchar Name[16];
		GLsizei length;
		glGetActiveUniform(m_OpenGL_ID, location, 16, &length, &size, &Type, Name);

		dispatchUniformUpload(OpenGLtoShaderDataType(Type), location, data);
		
		return false;
	}

	bool OpenGLShader::uploadData(const UniformLayout & uniforms)
	{
		for (auto dataPair : uniforms)
		{
			uploadData(dataPair.first, dataPair.second);
		}
		return true;
	}
	
	void OpenGLShader::dispatchUniformUpload(ShaderDataType type, GLuint location, void * data)
	{
		const float * addrf;
		const int * addri;
		GLfloat valueFloat;
		GLint valueInt;

		switch(type)
		{
		case ShaderDataType::Bool:
			valueInt = *(bool*)data;
			glUniform1i(location, valueInt);
			break;
		case ShaderDataType::Int:
			valueInt = *(int*)data;
			glUniform1i(location, valueInt);
			break;
		case ShaderDataType::Int2:
			addri = (const int *)data;
			glUniform2iv(location, 1, addri);
			break;
		case ShaderDataType::Float:
			valueFloat = *(float*)data;
			glUniform1i(location, valueFloat);
			break;
		case ShaderDataType::Float2:
			addrf = (float*)data;
			glUniform2fv(location, 1, addrf);
			break;
		case ShaderDataType::Float3:
			addrf = (float*)data;
			glUniform3fv(location, 1, addrf);
			break;
		case ShaderDataType::Float4:
			addrf = (float*)data;
			glUniform4fv(location, 1, addrf);
			break;
		case ShaderDataType::Mat3:
			addrf = (float*)data;
			glUniformMatrix3fv(location, 1, GL_FALSE, addrf);
			break;
		case ShaderDataType::Mat4:
			addrf = (float*)data;
			glUniformMatrix4fv(location, 1, GL_FALSE, addrf);
			break;
		case ShaderDataType::Sampler2D:
			valueInt = *(int*)data;
			glUniform1i(location, valueInt);
			break;
		}
	}
	
}