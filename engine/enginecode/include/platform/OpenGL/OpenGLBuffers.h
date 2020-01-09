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
		OpenGLVertexBuffer(float* vertices, unsigned int size);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_layout = layout; }

	private:
		unsigned int m_rendererID;
		BufferLayout m_layout;
		
	};

	/*! \class OpenGLIndexBuffer
	* This class inherits from the IndexBuffer class
	* It is used only for the OpenGL renderer.
	*/
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const;
		virtual void unbind() const;

		virtual unsigned int getCount() const { return m_count; }

	private:
		unsigned int m_count;
		unsigned int m_rendererID;
	};
}