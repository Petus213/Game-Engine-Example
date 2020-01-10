/*! \file Buffers.h
*\brief This file contains all information regarding the Buffers
* This includes OpenGL.
*/
#pragma once
#include "systems\log.h"

namespace Engine {
	/*! \class ShaderDataType
	*This class simply provides the type of data the shader could be
	*/
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool, Sampler2D
	};

	//!< This switch statement will return an integer depending on the shader data type.
	static unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:		return 4;
		case ShaderDataType::Float2:	return 4 * 2;
		case ShaderDataType::Float3:	return 4 * 3;
		case ShaderDataType::Float4:	return 4 * 4;
		case ShaderDataType::Mat3:		return 4 * 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4 * 4;
		case ShaderDataType::Int:		return 4;
		case ShaderDataType::Int2:		return 4 * 2;
		case ShaderDataType::Int3:		return 4 * 3;
		case ShaderDataType::Int4:		return 4 * 4;
		case ShaderDataType::Bool:		return 1;
		case ShaderDataType::Sampler2D:	return 1;
		}
		NG_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	struct BufferElement
	{
		std::string Name; //!< string Name
		ShaderDataType Type; //!< returns a Type for the ShaderDataType
		unsigned int Size; //!< integer for size
		size_t Offset; //!< size_t Offset
		bool Normalized; //!< bool value for Normalized

		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

		unsigned int getCompoundCount() const
		{
			switch (Type)
			{
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Mat3:		return 3 * 3;
			case ShaderDataType::Mat4:		return 4 * 4;
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Bool:		return 1;
			case ShaderDataType::Sampler2D:	return 1;
			}
			NG_ASSERT(false, "Unknown ShaderDataType");
			return 0;

		}
	};
	/*! \class BufferLayout
	*
	*/
	class BufferLayout
	{
	public:
		BufferLayout(){} //!< constructor

		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) //!< constructor
		{
			CalculateOffsetsAndStride();
		}

		void addElement(BufferElement element); //!< void add element function
		inline unsigned int GetStride() const { return m_stride; } //!< integer for getStride
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; } //!< Vector for class BufferElement, returns m_Elements

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); } //!< begin function
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); } //!< end function
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); } //!< begin function
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); } //!< end function

	private:
		void CalculateOffsetsAndStride() //!< void function CalculateOffsetsAndStride
		{
			size_t offset = 0;
			m_stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_stride += element.Size;
			}
		}

		std::vector<BufferElement> m_Elements;
		unsigned int m_stride = 0; //!< integer for m_stride
	};
	/*! \class VertexBuffer
	*The vertex buffer will create a vertex buffer
	*/
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default; //!< destructor

		virtual void bind() const = 0; //!< void function bind
		virtual void unbind() const = 0; //!< void function unbind

		virtual const BufferLayout& GetLayout() const = 0; //!< GetLayout from BufferLayout
		virtual void SetLayout(const BufferLayout& layout) = 0; //!< void function SetLayout
		 
		static VertexBuffer * create(float* vertices, unsigned int size); //!< pointer from vertexBuffer to create

	};

	/*! \class IndexBuffer
	*The index buffer will create an index buffer
	*/
	class IndexBuffer
	{
	public:
		virtual void bind() const = 0; //!< void function bind
		virtual void unbind() const = 0; //!< void function unbind
		 
		virtual unsigned int getCount() const = 0; //!< integer variable getCount
		 
		static IndexBuffer * create(unsigned int* indices, unsigned int count); //!< pointer from IndexBuffer to create

		
	};
}