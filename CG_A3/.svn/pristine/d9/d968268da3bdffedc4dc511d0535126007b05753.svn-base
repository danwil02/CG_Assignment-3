#include "CameraManager.h"

using namespace Managers;

CameraManager::CameraManager(int windowWidth, int windowHeight)
{
	/*
	m_position = glm::vec3(0, 0, 15);
	m_direction = glm::vec3(0, 0, 0);
	m_up = glm::vec3(0, 1, 0);
	m_speed = 0.2;
	
	m_cameraMatrix = glm::lookAt(m_position, m_direction, m_up);
	*/
	// Set initial camera position //
	m_cameraMatrix = glm::translate(m_cameraMatrix, glm::vec3(0.0f, 0.0f, -15.0f));
//	m_cameraMatrix = glm::rotate(m_cameraMatrix, 20.0f, glm::vec3(1.0f, 0.0f, 0.0f));
//	m_cameraMatrix = glm::rotate(m_cameraMatrix, 20.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	m_original_cameraMatrix = m_cameraMatrix;
	/*m_projectionMatrix = glm::ortho(-5.0f, 5.0f, // left, right
									-5.0f, 5.0f, // bottom, top
									0.0f, 10.0f);// near, far*/
	// NOTE!!!!!!! Near must be set to 1.0 for this to work //
	m_aspectRatio = ((float)windowWidth) / ((float)windowHeight);
	m_fov = 45.0f;
	m_farDist = 10000.0f;
	m_projectionMatrix = glm::perspective(m_fov, m_aspectRatio, 1.0f, m_farDist); 

	input = new Input();
	m_verticalAngle = 3.14/6;
	m_horizontalAngle = 3.125;
	m_mouseSpeed = 0.005;
	m_mvSpeed = 30;
	m_position = glm::vec3(31.7, 3, 61.4);
}


CameraManager::~CameraManager()
{
}

void CameraManager::Update()
{
	//m_cameraMatrix = glm::lookAt(m_position, m_position + m_direction, m_up);
}

void CameraManager::calcNewCameraPos(float dx, float dy, float dz,
	float d_rot_x, float d_rot_y, float d_rot_z)
{
	m_cameraMatrix = glm::translate(m_cameraMatrix, glm::vec3(dx,dy,dz));
	m_cameraMatrix = glm::rotate(m_cameraMatrix, d_rot_x, glm::vec3(1.0f, 0.0f, 0.0f));
	m_cameraMatrix = glm::rotate(m_cameraMatrix, d_rot_y, glm::vec3(0.0f, 1.0f, 0.0f));
	m_cameraMatrix = glm::rotate(m_cameraMatrix, d_rot_z, glm::vec3(0.0f, 0.0f, 1.0f));
}

void CameraManager::upDateProjection(float width, float height)
{
	m_aspectRatio = width/height;
	glViewport(0, 0, width, height);
	m_projectionMatrix = glm::perspective(m_fov, m_aspectRatio, 1.0f, m_farDist);
}

void CameraManager::upDateProjectionFov(float fov)
{
	m_fov = fov;
	m_projectionMatrix = glm::perspective(m_fov, m_aspectRatio, 1.0f, m_farDist);
}

void CameraManager::upDateProjectionFarDist(float far_dist)
{
	m_farDist = far_dist;
	m_projectionMatrix = glm::perspective(m_fov, m_aspectRatio, 1.0f, m_farDist);
}

void CameraManager::resetCamera()
{
	m_cameraMatrix = m_original_cameraMatrix;
}

void CameraManager::calcCameraFromInput()
{
	// Reset mouse position for next frame
	int windowHeight = 100;//glutGet(GLUT_WINDOW_HEIGHT);
	int windowWidth = 100; //glutGet(GLUT_WINDOW_WIDTH);
	glutWarpPointer(windowWidth, windowHeight);

	// Compute new orientation
	m_horizontalAngle += m_mouseSpeed * float(windowWidth - input->x);
	m_verticalAngle += m_mouseSpeed * float(windowHeight - input->y);


	if (m_verticalAngle > 0.5)
	{
		m_verticalAngle = 0.5;
	}
	if (m_verticalAngle < -0.5)
	{
		m_verticalAngle = -.5;
	}

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(m_verticalAngle) * sin(m_horizontalAngle),
		sin(m_verticalAngle),
		cos(m_verticalAngle) * cos(m_horizontalAngle)
		);

	// Right vector
	glm::vec3 right = glm::vec3(
		sin(m_horizontalAngle - 3.14f / 2.0f),
		0,
		cos(m_horizontalAngle - 3.14f / 2.0f)
		);

	// Up vector
	glm::vec3 up = glm::cross(right, direction);
	up = glm::vec3(0, 1, 0);

	// Move forward
	if (input->forward)
	{
		m_position += direction * input->difftime * m_mvSpeed;
	}
	// Move backward
	if (input->backward)
	{
		m_position -= direction * input->difftime * m_mvSpeed;
	}
	// Strafe right
	if (input->right)
	{
		m_position += right * input->difftime * m_mvSpeed;
	}
	// Strafe left
	if (input->left)
	{
		m_position -= right * input->difftime * m_mvSpeed;
	}
	// Move Up
	if (input->up)
	{
		m_position += up * input->difftime * m_mvSpeed;
	}
	// Move down
	if (input->down)
	{
		m_position -= up * input->difftime * m_mvSpeed;
	}

	m_cameraMatrix = glm::lookAt(
		m_position,           // Camera is here
		m_position + direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up (set to 0,-1,0 to look upside-down)
		);

	//std::cout << "Camera horizontal = " << m_horizontalAngle <<  " vertical = "<< m_verticalAngle << std::endl;
}