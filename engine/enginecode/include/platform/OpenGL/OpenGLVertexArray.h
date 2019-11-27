#pragma once

#include "Renderer\VertexArray.h"

namespace Engine {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void bind() const override;
		virtual void unbind() const override;
		
		virtual void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual std::shared_ptr<VertexBuffer> getVertexBuffer() const { return m_vertexBuffer; }
		virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const { return m_indexBuffer; }

	private:
		unsigned int m_rendererID;
		unsigned int m_vertexBufferIndex = 0;
		std::shared_ptr<VertexBuffer> m_vertexBuffer;
		std::shared_ptr<IndexBuffer> m_indexBuffer;

	};

}