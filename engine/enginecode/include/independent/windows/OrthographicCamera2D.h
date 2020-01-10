/*! \file OrthographicCamera2D.h
* This file will create a 2D camera for the scene. 
*/
#pragma once
#include "windows\Camera.h"

namespace Engine {

	/*! \class OrthographicCamera 2D
	* This class for a 2D camera inherits from Camera class
	*/
	class OrthographicCamera2D : public Camera
	{
	private:
		glm::vec2 m_position = glm::vec2(0.f); //!< vec2 for position
		float m_rotation = 0.f; //!< float value for rotation
		void updateView() override; //!< void function for updating view
	public:
		OrthographicCamera2D(float left, float right, float bottom, float top); //!< Constructor

		void reset(float left, float right, float bottom, float top); //!< void function for resetting the camera
		inline glm::vec3 getPosition() override { return glm::vec3(m_position, 0.f)  ; } //!< vec3 getPosition will retrun m_position
		inline float getRotation() const { return m_rotation; } //!< float getRotation will return rotation
		void setPosition(const glm::vec2& position) { m_position = position; updateView(); } //!< void function for setting position
		void setRotation(float rotation) { m_rotation = rotation; updateView(); } //!< void function for setting rotation
		void setPositionRotation(const glm::vec2& position, float rotation) { m_position = position; m_rotation = rotation; updateView(); } //!< void function for setting position and rotation
	};


	/*! \class FreeOrthoCameraController2D
	* This class controls the 2D camera, it inherits from the Camera Controller class
	*/
	class FreeOrthoCameraController2D : public CameraController
	{
	private:
		std::shared_ptr<OrthographicCamera2D> m_camera; //!< Shared Pointer to m_camera
		glm::vec2 m_position = glm::vec3(0.f); //!< vec2 for position
		float m_rotation = 0.f; //!< float value for rotation
		float m_translationSpeed = 100.f; //!< float value for translation speed
		float m_rotationSpeed = 10.f; //!< float value for rotation speed
	public:
		FreeOrthoCameraController2D(); //!< Constructor
		void init(float left, float top, float width, float height) override; //!< void function for initilisation
		std::shared_ptr<Camera> getCamera() override { return m_camera; } //!< shared pointer to camera
		void onUpdate(float timestep) override; //!< void function for onUpdate
		void onEvent(Event& e) override {}; //!< void function for onEvent
		void onResize() override {}; //!< void function for onResize
	};
}