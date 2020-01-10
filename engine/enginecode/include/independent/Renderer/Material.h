/*! \file Material.h
* This file is used for the materials of the objects rendered in the scene
*/

#pragma once
#include "Renderer\Shader.h"
#include "VertexArray.h"
#include <variant>
namespace Engine {

	/*!\class Material
	* This class will set the various elements needed for a material
	*/
	class Material
	{
	public:
		virtual void setShader(const std::shared_ptr<Shader>& shader) = 0; //!< void function for setting shader, shared pointer to shader
		virtual void setGeometry(const std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>>& geometry) = 0; //!< void function for setting geometry
		virtual void setDataBlock(const std::map<std::string, void *>&data) = 0; //!< void function for setting data block
		virtual void setDataElement(const std::string& dataName, void * data) = 0; //!< void function for setting data elements
		
		virtual std::shared_ptr<Shader> getShader() = 0; //!< shared pointer to shader to getShader
		virtual std::variant<std::shared_ptr<VertexArray>, std::shared_ptr<VertexBuffer>> getGeometry() = 0; //!< shared pointers to Vertex Array and VertexBuffer
		virtual std::map<std::string, void *> getData() = 0; //<! map for getData

		static Material * create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& VAO); //!< pointer to create material
		static Material * create(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexBuffer>& VBO); //!< pointer to create material
	};
}