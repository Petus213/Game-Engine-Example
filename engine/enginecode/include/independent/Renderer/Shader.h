/*! \file Shaders.h
*\brief This file contains all information for shaders
* 3D rendering software will use this in their own shader classes.
*/
#pragma once
#include "Buffers.h"
#include <glm\glm.hpp>
#include <map>

namespace Engine {
	
	using UniformLayout = std::map<std::string, void *>;

	/*! \class Shader
	* The shader class is fundimental in 3D graphics
	* It will be used by the OpenGL Shader class
	* It could also be used by other shader classes for other renderers.
	*/
	class Shader
	{
	public: 
		virtual unsigned int id() = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual bool uploadData(const std::string& name, void* data) = 0;
		virtual bool uploadData(const UniformLayout& uniforms) = 0;
		virtual BufferLayout getBufferLayout() const = 0;
		virtual UniformLayout getUniformLayout() const = 0;

		static Shader * create(const std::string& filepath);
		static Shader * create(const std::string& vertexFilepath, const std::string& fragmentFilepath);
	};
	
}