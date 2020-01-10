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
		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::mat4 m_viewProjection;

	public:
		virtual void updateView() = 0;
		const glm::mat4& getProjection() { return m_projection; }
		const glm::mat4& getView() { return m_view; }
		const glm::mat4& getViewProjection() { return m_viewProjection; }

		virtual glm::vec3 getPosition() = 0;
	};

	class CameraController
	{
	public:
		virtual void init(float, float, float, float) = 0;
		virtual std::shared_ptr<Camera> getCamera() = 0;
		virtual void onUpdate(float timestep) = 0;
		virtual void onEvent(Event& e) = 0;
		virtual void onResize() = 0;

	};
}
