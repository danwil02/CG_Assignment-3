#pragma once

#include "../../OpenGL_headers.h"
#include "../../Utils/glm/glm.hpp"
#include "../../Utils/glm/gtc/matrix_transform.hpp"
#include "../../Utils/glm/gtc/type_ptr.hpp"
#include "../../Utils/glm/gtx/quaternion.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

namespace Rendering
{
	namespace MultiPass
	{
		class ShadowMap
		{
		public:
			ShadowMap();
			~ShadowMap();
			bool Create();
			void Draw();

			void addSceneData(vector<GLuint>& vao, vector<unsigned int>& idx_len);

			void setShader(GLuint s){ m_shader = s; }

			void bindDepthTexture(GLuint shader_handle);
			glm::mat4 getDepthBiasMVP() { return m_depthBiasMVP; }

		private:
			GLuint m_shader;
			GLuint m_FramebufferName;
			GLuint m_depthTexture;

			vector< GLuint > m_vao;
			vector<unsigned int > m_indiciesLength;

			glm::mat4 m_depthBiasMVP;
			glm::mat4 m_depthMVP;

			void pushMatrices();
			void getPVLightMatrix(glm::mat4& projection, glm::mat4& viewMatrix);

			unsigned int m_texSz = 4096;
			
			float lightX = 544;
			float lightY = 378;
			float lightZ = -120;
		};
	}
}