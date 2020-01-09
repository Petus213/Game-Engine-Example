/*! \file renderAPI.h
*\brief This file contains the Render API
* This aids with checking what 3D rendering software is being used.
*/
#pragma once

namespace Engine {

	/*! \class RenderAPI
	*This class will check, and give a number to, the current rendering software being used.
	*/
	class RenderAPI {

	public:
		enum class API
		{
			None = 0, OpenGL = 1, Direct3D = 2
		};

		static API getApi() { return s_API; }

	private:
		static API s_API;
	};
}