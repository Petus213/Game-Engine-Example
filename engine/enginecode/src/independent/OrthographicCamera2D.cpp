#include "engine_pch.h"
#include "windows\OrthographicCamera2D.h"
#include "systems\inputPoller.h"
#include "windows\GLFWCodes.h"
#include "glm\gtx\transform.hpp"

namespace Engine {

	//!< Orthographic Camera functions here
	void OrthographicCamera2D::updateView()
	{
		glm::mat4 translate = glm::translate(glm::mat4(1.f), glm::vec3(m_position, 1.f));
		glm::mat4 rotate = glm::rotate(glm::mat4(1.f), glm::radians(m_rotation), glm::vec3(0.f, 0.f, 1.f));
		m_view = translate * rotate;
		m_viewProjection - m_projection * m_view;
	}

	OrthographicCamera2D::OrthographicCamera2D(float left, float right, float bottom, float top)
	{
		m_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_view = glm::mat4(1.0f);
		m_viewProjection - m_projection * m_view;
	}

	void OrthographicCamera2D::reset(float left, float right, float bottom, float top)
	{
		m_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_view = glm::mat4(1.0f);
		m_viewProjection - m_projection * m_view;
		
	}

	//!< Camera Controller (2D) functions here
	FreeOrthoCameraController2D::FreeOrthoCameraController2D()
	{
	}

	void FreeOrthoCameraController2D::init(float left, float top, float width, float height)
	{
		m_camera = std::shared_ptr<OrthographicCamera2D>(new OrthographicCamera2D(left, top, width, top + height));
	}

	void FreeOrthoCameraController2D::onUpdate(float timestep)
	{
		if (InputPoller::isKeyPressed(KEY_Q))
		{
			m_rotation -= timestep * m_rotationSpeed;
			if (m_rotation > 180.0f) m_rotation -= 360.0f;
			else if (m_rotation <= -180.0f) m_rotation += 360.0f;
		}
		if (InputPoller::isKeyPressed(KEY_E))
		{
			m_rotation += timestep * m_rotationSpeed;
			if (m_rotation > 180.0f) m_rotation -= 360.0f;
			else if (m_rotation <= -180.0f) m_rotation += 360.0f;
		}
	}
}