#pragma once

#include "Model.h"
#include "../../Utils/tiny_obj_loader.h"
#include "../../OpenGL_headers.h"
#include <string>
#include <vector>
#include <iostream>

namespace Rendering
{ 
	namespace Models
	{
		class Axes : public Rendering::Models::Model
		{
		public:
			Axes();
			~Axes();
			void Create();
			virtual void Update(unsigned int flags) override final;
			virtual void Draw() override final;
		private:

			// Matrices //
			glm::mat4 m_cameraMat;
			glm::mat4 m_projMat;
			glm::mat4 m_mvMat;
		};
	}
}