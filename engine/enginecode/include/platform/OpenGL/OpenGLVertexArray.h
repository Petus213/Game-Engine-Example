/*! \file OpenGLVertexArray.h
* This file uses the Vertex Array class, but is used specifically for OpenGL
*/
#pragma once
#include "Renderer\VertexArray.h"

namespace Engine {

	/*! \class OpenGLVertexArray
	* This class inherits from the VertexArray class
	* It is used only for the OpenGL renderer.
	*/
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray(); //!< constructor
		virtual ~OpenGLVertexArray(); //!< destructor

		virtual void bind() const override; //!< void function for bind
		virtual void unbind() const override; //!< void function for unbind
		
		virtual void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override; //!< void function for setting Vertex Buffers
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override; //!< void function for setting Index Buffers

		virtual std::shared_ptr<VertexBuffer> getVertexBuffer() const { return m_vertexBuffer; } //!< shared pointer to get the Vertex Buffer
		virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const { return m_indexBuffer; } //!< shared pointer to get the Index Buffer

	private:
		unsigned int m_rendererID; //!< integer value for m_rendererID
		unsigned int m_vertexBufferIndex = 0; //!< integer value for Vertex Buffer INdex
		std::shared_ptr<VertexBuffer> m_vertexBuffer; //!< shared pointer to m_vertexBuffer
		std::shared_ptr<IndexBuffer> m_indexBuffer; //!< shared pointer to m_indexBuffer

	};

}