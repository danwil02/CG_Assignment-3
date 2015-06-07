#pragma once

#include "../OpenGL_headers.h"
#include "../Utils/glm/glm.hpp"
#include "../Utils/glm/gtc/matrix_transform.hpp"
#include "../Utils/glm/gtc/type_ptr.hpp"
#include "../Utils/glm/gtx/quaternion.hpp"
#include "../Init/WindowInfo.h"

#include <iostream>

struct Input
{
	bool left;
	bool right;
	bool forward;
	bool backward;
	bool up;
	bool down;

	int x;
	int y;

	float difftime;
};

namespace Managers
{
	class CameraManager
	{
	public:
		CameraManager(int windowWidth, int windowHeight);
		~CameraManager();
		void calcNewCameraPos(float x, float y, float z,
			float rot_x, float rot_y, float rot_z); 
		
		void Update();
		void glmLookAt(glm::vec3 eye, glm::vec3 centre, glm::vec3 up);

		void upDateProjection(float width, float height);
		void upDateProjectionFov(float fov);
		void upDateProjectionFarDist(float far_dist);
		void upDateProjection();
		void resetCamera();

		// New Code //

		Input* input;
		void calcCameraFromInput();

		float m_horizontalAngle;
		float m_verticalAngle;
		float m_mouseSpeed;
		float m_mvSpeed;
		//glm::vec3 m_position;
		/**/



		glm::mat4 getCameraPos(){ return m_cameraMatrix; }
		glm::vec3 getCameraXYZ(){ return m_position; }
		glm::mat4 getProjectionMat(){ return m_projectionMatrix; }
	private:
		glm::mat4 m_cameraMatrix;
		glm::vec3 m_position;
		glm::vec3 m_direction;
		glm::vec3 m_up;

		glm::mat4 m_projectionMatrix;

		// Original Camera matrix for recentring //
		glm::mat4 m_original_cameraMatrix;

		float m_fov, m_farDist, m_aspectRatio;
		float m_speed;
	};

}