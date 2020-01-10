/*! \file VertexArray.h
*\brief This file contains all information regarding the Vertex Array
* Other renderers, such as OpenGL, will use this class. 
*/
#pragma once

#include <memory>
#include "Renderer\Buffers.h"

namespace Engine {
	
	/*! \class VertexArray
	* This class is used with the OpenGL Vertex Array
	*/
	class VertexArray
	{
	public:
		virtual ~VertexArray(){} //!< destructor
		 
		virtual void bind() const = 0; //!< void function for bind
		virtual void unbind() const = 0; //!< void function for unbind

		virtual void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0; //!< void function with shared pointer to VertexBuffer
		
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0; //!< void function with shared pointer to IndexBuffer
		virtual std::shared_ptr<VertexBuffer> getVertexBuffer() const = 0; //!< shared pointer to getVertexBuffer
		virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const = 0; //!< shred pointer to getIndexBuffer
		

		static VertexArray * create(); //!< pointer to create
	};
}