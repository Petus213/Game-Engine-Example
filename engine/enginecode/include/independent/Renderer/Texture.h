/*! \file Texture.h
*\brief This file contains all information regarding the Buffers
* This includes OpenGL.
*/
#pragma once

namespace Engine {

	/*! \class Texture
	* This class handles the textures for objects within the scene.
	* Other renderers will make use of this class, in this engine it is OpenGL
	*/
	class Texture
	{
	public: 
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;
		virtual unsigned int getChannels() const = 0;
		virtual unsigned int getSlot() const = 0;

		static Texture * createFromFile(const std::string& filepath);
		static Texture * createFromRawData(unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData);
	};

}