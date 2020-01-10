/*! \file OrthographicCamera2D.h
* This file will create a 2D camera for the scene. 
*/
#pragma once
#include "windows\Camera.h"

namespace Engine {

	class OrthographicCamera2D : public Camera
	{
	private:
		glm::vec2 m_position = glm::vec2(0.f);
		float m_rotation = 0.f;
		void updateView() override;
	public:
		OrthographicCamera2D(float left, float right, float bottom, float top);

		void reset(float left, float right, float bottom, float top);
		inline glm::vec3 getPosition() override { return glm::vec3(m_position, 0.f)  ; }
		inline float getRotation() const { return m_rotation; }
		void setPosition(const glm::vec2& position) { m_position = position; updateView(); }
		void setRotation(float rotation) { m_rotation = rotation; updateView(); }
		void setPositionRotation(const glm::vec2& position, float rotation) { m_position = position; m_rotation = rotation; updateView(); }
	};

	class FreeOrthoCameraController2D : public CameraController
	{
	private:
		std::shared_ptr<OrthographicCamera2D> m_camera;
		glm::vec2 m_position = glm::vec3(0.f);
		float m_rotation = 0.f;
		float m_translationSpeed = 100.f;
		float m_rotationSpeed = 10.f;
	public:
		FreeOrthoCameraController2D();
		void init(float left, float top, float width, float height) override;
		std::shared_ptr<Camera> getCamera() override { return m_camera; }
		void onUpdate(float timestep) override;
		void onEvent(Event& e) override {};
		void onResize() override {};
	};
}