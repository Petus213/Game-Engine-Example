/*! \file PerspectiveCamera3D
* This file is for the 3D scene camera
* it inherits from an existing Camera class
*/
#pragma once
#include "Camera.h"
#include "glm\gtc\quaternion.hpp"

namespace Engine {

	/*! \class PerspectiveCamera3D
	* This class inherits from Camera to provide a 3D camera
	*/
	class PerspectiveCamera3D : public Camera
	{
	private:
		glm::vec3 m_position = glm::vec3(0.f); //!< vec3 Position
		glm::quat m_orientation; //!< Quaternian value for m_orientation
		void updateView() override; //!< void function for updating view

	public:
		PerspectiveCamera3D(float fov, float aspectRatio, float nearClip, float farClip); //!< constructor
		void reset(float fov, float aspectRatio, float nearClip, float farClip); //!< void function for resetting
		inline glm::vec3 getPosition() override { return m_position; } //<! vec3 for getting poistion
		inline glm::quat getOrientation() { return m_orientation; } //!< Quaternian for getting orientation
		void setView(const glm::mat4& view) { m_view = view, m_viewProjection = m_projection * m_view; } //!< void function for setting view
		void setPosition(const glm::vec3& position) { m_position = position; updateView(); } //!< void function for setting position
		void setOrientation(const glm::quat& orientation) { m_orientation = orientation; updateView(); } //!< void function for setting orientation
		void setPositionAndOrientation(const glm::vec3& position, const glm::quat& orientation) { m_position = position; m_orientation = orientation; updateView(); } //!< void function from setting position and orientation
	};

	/*! \class FPSCameraControllerEuler
	* This class inherits from Camera Controller to create controls for the camera
	*/
	class FPSCameraControllerEuler : public CameraController
	{
	private:
		std::shared_ptr<PerspectiveCamera3D> m_camera; //!< Shared pointer to m_camera
		glm::mat4 m_view; //!< mat4 m_view
		glm::vec3 m_position; //!< vec3 m_postition
		glm::vec3 m_forward; //!< vec3 m_forward
		glm::vec3 m_up; //!< vec3 m_up
		glm::vec3 m_right; //!< vec3 m_right
		glm::vec3 m_worldUp; //!< vec3 m_worldUp
		
		float m_yaw; //!< flaot variable m_yaw
		float m_pitch; //!< float variable m_pitch
		float m_translationSpeed = 2.0f; //!< set variable for translation speed
		float m_rotationSpeed = 2.0f; //!< set variable for rotation speed
		glm::vec2 m_lastMousePosition; //!< vec2 for last mouse position
		void updateView(); //!< void function for updating view

	public:
		FPSCameraControllerEuler(); //!< constructor
		void init(float fov = 45.f, float aspectRatio = 4.0f / 3.0f, float nearClip = 0.1f, float farClip = 100.f) override; //!< void function for initilisation
		std::shared_ptr<Camera> getCamera() override { return m_camera; } //!< shared pointer to return m_camera
		void onUpdate(float timestep) override; //!< void function for onUpdate
		void onEvent(Event& e) override; //!< void function for OnEvent
		void onResize() override {}; //!< void function for on Resize
		bool onMouseButton(MouseButtonPressedEvent& e); //!< boolean value for mouse button pressed
		
	};


}