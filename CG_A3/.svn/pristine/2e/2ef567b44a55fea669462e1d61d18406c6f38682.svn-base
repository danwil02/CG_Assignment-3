#include "Model.h"
namespace Rendering
{
	namespace Models
	{

		Model::Model(){}

		Model::~Model()
		{
			Destroy();
		}

		void Model::Draw()
		{
			//this will be again overwritten
		}

		void Model::Update(unsigned int flags)
		{
			//this will be again overwritten
		}

		void Model::SetShader(GLuint shaderName)
		{
			this->m_shader = shaderName;
		}

		GLuint Model::GetVao() const
		{
			return m_vao[0];
		}

		const std::vector<GLuint>& Model::GetVbos() const
		{
			return m_vbos;
		}

		void Model::Destroy()
		{
			for (int i = 0; i < m_vao.size(); i++)
			{
				glDeleteVertexArrays(1, &m_vao[i]);
			}
			glDeleteBuffers(m_vbos.size(), &m_vbos[0]);
			m_vbos.clear();
		}
	}
}