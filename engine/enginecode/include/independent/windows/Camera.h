/*! \file Camera.h
* This file contains the camera class
* The camera is used to navigate the scene
*/
#pragma once
#include "Events\events.h"
#include "Events\Mouse_Events.h"
#include "glm\glm.hpp"

namespace Engine {

	/*! \class Camera
	* This class will be inherited by other camera based classes.
	*/
	class Camera
	{
	protected:
		glm::mat4 m_projection; //!< mat4 for projection
		glm::mat4 m_view; //!< mat4 for view
		glm::mat4 m_viewProjection; //!< mat4 for view projection

	public:
		virtual void updateView() = 0; //!< void function for updateView - pure virutal
		const glm::mat4& getProjection() { return m_projection; } //!< mat4 for get projection, returns m_projection
		const glm::mat4& getView() { return m_view; } //!< mat4 for get view, returns m_view
		const glm::mat4& getViewProjection() { return m_viewProjection; } //!< mat4 for get view projection, returns m_viewProjection

		virtual glm::vec3 getPosition() = 0; //!< vec3 for getPosition
	};

	/*! \class Camera
	* This clas will control the camera (both 2D and 3D)
	* it will be inherited by other classes
	*/
	class CameraController
	{
	public:
		virtual void init(float, float, float, float) = 0; //!< void function for initilisation
		virtual std::shared_ptr<Camera> getCamera() = 0; //!< shared pointer to getCamera -pure virtual 
		virtual void onUpdate(float timestep) = 0; //!< void function for onUpdate - pure virtual
		virtual void onEvent(Event& e) = 0; //!< void function for onEvent - pure virtual
		virtual void onResize() = 0; //!< void function for onResize -pure virtual

	};
}
