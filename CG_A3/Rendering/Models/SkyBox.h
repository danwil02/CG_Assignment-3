#ifndef SKYBOX_H
#define SKYBOX_H
#include "Model.h"

#include "../../OpenGL_headers.h"
#include <vector>

using namespace std;

namespace Rendering
{
	namespace Models
	{

		class SkyBox : public Model
		{
		public:
			SkyBox();
			~SkyBox();
			void Create();
			virtual void Update(unsigned int flags) override final;
			virtual void Draw() override final;
		private:

			void vertAndTexData(vector<glm::vec3>& vertices, vector<glm::vec2>& texCoords, int i);

			std::vector<GLuint> m_texture;

			float m_x;
			float m_y;
			float m_z;
			float m_width;
			float m_height;
			float m_length;

			// Matrices //
			glm::mat4 m_cameraMat;
			glm::mat4 m_projMat;
			glm::mat4 m_mvMat;
		};
	}
}

#endif