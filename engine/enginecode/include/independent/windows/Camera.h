/*! Camera.h
* This file contains the camera class
* The camera is used to navigate the scene
*/
#pragma once
#include "glm\glm.hpp"

namespace Engine {

	/*! \class Camera
	* This class will be inherited by other camera based classes.
	*/
	class Camera
	{
	protected:
		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::mat4 m_viewProjection;

	public:
		virtual void updateView() = 0;
		const glm::mat4& getProjection() { return m_projection; }
		const glm::mat4& getView() { return m_view; }
		const glm::mat4& getViewProjection() { return m_viewProjection; }
	};

}
