#pragma once
#include "Camera.h"
#include "glm\gtc\quaternion.hpp"

namespace Engine {

	class PerspectiveCamera3D : public Camera
	{
	private:
		glm::vec3 m_position = glm::vec3(0.f);
		glm::quat m_orientation;
		void updateView() override;

	public:
		PerspectiveCamera3D(float fov, float aspectRatio, float nearClip, float farClip);
		void reset(float fov, float aspectRatio, float nearClip, float farClip);
		inline glm::vec3 getPosition() override { return m_position; }
		inline glm::quat getOrientation() { return m_orientation; }
		void setView(const glm::mat4& view) { m_view = view, m_viewProjection = m_projection * m_view; }
		void setPosition(const glm::vec3& position) { m_position = position; updateView(); }
		void setOrientation(const glm::quat& orientation) { m_orientation = orientation; updateView(); }
		void setPositionAndOrientation(const glm::vec3& position, const glm::quat& orientation) { m_position = position; m_orientation = orientation; updateView(); }
	};

	class FPSCameraControllerEuler : public CameraController
	{
	private:
		std::shared_ptr<PerspectiveCamera3D> m_camera;
		glm::mat4 m_view;
		glm::vec3 m_position;
		glm::vec3 m_forward;
		glm::vec3 m_up;
		glm::vec3 m_right;
		glm::vec3 m_worldUp;
		
		float m_yaw;
		float m_pitch;
		float m_translationSpeed = 2.0f;
		float m_rotationSpeed = 2.0f;
		glm::vec2 m_lastMousePosition;
		void updateView();

	public:
		FPSCameraControllerEuler();
		void init(float fov = 45.f, float aspectRatio = 4.0f / 3.0f, float nearClip = 0.1f, float farClip = 100.f) override;
		std::shared_ptr<Camera> getCamera() override { return m_camera; }
		void onUpdate(float timestep) override;
		void onEvent(Event& e) override;
		void onResize() override {};
		bool onMouseButton(MouseButtonPressedEvent& e);
		
	};


}