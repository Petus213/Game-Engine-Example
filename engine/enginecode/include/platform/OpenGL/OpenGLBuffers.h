/*! \file OpenGLBuffers.h
* This file uses the Buffers class, but is specifically for OpenGL.
*/
#pragma once
#include "include\independent\Renderer\Buffers.h"

namespace Engine {

	/*! \class OpenGLVertexBuffer
	* This class inherits from the VertexBuffer class
	* It is used only for the OpenGL renderer.
	*/
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size); //!< Constructor
		virtual ~OpenGLVertexBuffer(); //!< destructor

		virtual void bind() const override; //!< void function for bind
		virtual void unbind() const override; //!< void function for unbind

		virtual const BufferLayout& GetLayout() const override { return m_layout; } //!< Gets buffer layout - returns m_layout
		virtual void SetLayout(const BufferLayout& layout) override { m_layout = layout; } //!< void function for setting layout

	private:
		unsigned int m_rendererID; //!< integer value for m_rendererID
		BufferLayout m_layout; //!< m_layout from BuferLayout
		
	};

	/*! \class OpenGLIndexBuffer
	* This class inherits from the IndexBuffer class
	* It is used only for the OpenGL renderer.
	*/
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count); //!< constructor
		virtual ~OpenGLIndexBuffer(); //!< destructor

		virtual void bind() const; //!< void function for bind
		virtual void unbind() const; //!< void function for unbind

		virtual unsigned int getCount() const { return m_count; } //!< integer vlaue for getCount - returns m_count

	private:
		unsigned int m_count; //!< integer value for m_count
		unsigned int m_rendererID; //!< integer value for m_rendererID
	};
}