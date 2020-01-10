#include "engine_pch.h"
#include "windows\PerspectiveCamera3D.h"
#include "systems\inputPoller.h"
#include "windows\GLFWCodes.h"
#include "glm\gtx\transform.hpp"

namespace Engine {

	void PerspectiveCamera3D::updateView()
	{
		m_viewProjection = m_projection * m_view;
	}

	PerspectiveCamera3D::PerspectiveCamera3D(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
		m_view = glm::mat4(1.0f);
		m_viewProjection = m_projection * m_view;
	}

	void PerspectiveCamera3D::reset(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_projection = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
		m_view = glm::mat4(1.0f);
		m_viewProjection = m_projection * m_view;
	}

	void FPSCameraControllerEuler::updateView()
	{
		glm::vec3 forward;
		forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		forward.y = sin(glm::radians(m_pitch));
		forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_forward = glm::normalize(forward);

		m_right = glm::normalize(glm::cross(m_forward, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_forward));

		m_view = glm::lookAt(m_position, m_position + m_forward, m_up);
		m_camera->setView(m_view);
	}

	FPSCameraControllerEuler::FPSCameraControllerEuler()
	{
	}

	void FPSCameraControllerEuler::init(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_camera = std::shared_ptr<PerspectiveCamera3D>(new PerspectiveCamera3D(fov, aspectRatio, nearClip, farClip));
		m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
		m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		m_view = m_camera->getView();
		m_position = m_camera->getPosition();
		m_yaw = -90.0f;
		m_pitch = 0;
		updateView();

	}

	void FPSCameraControllerEuler::onUpdate(float timestep)
	{
		if (InputPoller::isKeyPressed(KEY_W))
		{
			m_position += m_forward * m_translationSpeed * timestep;
		}
		if (InputPoller::isKeyPressed(KEY_S))
		{
			m_position -= m_forward * m_translationSpeed * timestep;
		}
		if (InputPoller::isKeyPressed(KEY_A))
		{
			m_position -= m_right * m_translationSpeed * timestep;
		}
		if (InputPoller::isKeyPressed(KEY_D))
		{
			m_position += m_right * m_translationSpeed * timestep;
		}
		if (InputPoller::isMousePressed(MOUSE_BUTTON_1))
		{
			glm::vec2 currentMousePosition = InputPoller::getMousePosition();
			glm::vec2 mouseDelta = currentMousePosition - m_lastMousePosition;

			m_yaw += mouseDelta.x * m_rotationSpeed * timestep;
			m_pitch -= mouseDelta.y * m_rotationSpeed * timestep;

			if (m_pitch > 89.0f)
				m_pitch = 89.0f;
			if (m_pitch < -89.0f)
				m_pitch = -89.0f;
			m_lastMousePosition = currentMousePosition;
		}
		m_lastMousePosition = InputPoller::getMousePosition();
		updateView();
		m_camera->setPosition(m_position);
	}

	void FPSCameraControllerEuler::onEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseButtonPressedEvent>(std::bind(&FPSCameraControllerEuler::onMouseButton, this, std::placeholders::_1));
	}

	bool FPSCameraControllerEuler::onMouseButton(MouseButtonPressedEvent & e)
	{
		if (e.getMouseButton() == MOUSE_BUTTON_1)
			m_lastMousePosition = InputPoller::getMousePosition();
		return true;
	}

}