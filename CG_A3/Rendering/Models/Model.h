#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "../IGameObject.h"
#include "../../Managers/CameraManager.h"
#include "../MultiPass/ShadowMap.h"

namespace Rendering
{
	namespace Models
	{
		class Model :public IGameObject
		{
		public:
			Model();
			virtual ~Model();
			// methods from interface
			virtual void Draw() override;
			virtual void Update(unsigned int flags) override;
			virtual void SetShader(GLuint shaderName) override;
			virtual void Destroy() override;

			virtual GLuint GetVao() const override;
			virtual const std::vector<GLuint>& GetVbos() const override;

			void setCameraManager(Managers::CameraManager* cam){ m_cameraManager = cam; }
			void setShadowMap(Rendering::MultiPass::ShadowMap* sMap){ m_sMap = sMap; }

			std::vector<GLuint> getVaoVect(){ return m_vao; }
			std::vector<unsigned int> getVaoIdxLenVect(){ return m_indiciesLength; }

		protected:
			std::vector<GLuint> m_vao;
			std::vector<unsigned int> m_indiciesLength;

			GLuint m_shader;
			std::vector<GLuint> m_vbos;

			Managers::CameraManager* m_cameraManager;

			Rendering::MultiPass::ShadowMap* m_sMap;
		};
	}
}
#endif