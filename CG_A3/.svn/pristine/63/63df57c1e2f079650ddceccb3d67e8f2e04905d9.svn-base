#ifndef IGAMEOBJECT_H
#define IGAMEOBJECT_H

#include <vector>
#include "../OpenGL_headers.h"
#include "../Utils/glm/glm.hpp"

//
// Interface which all types of models or game objects must conform to //
//
namespace Rendering
{
	class IGameObject
	{
	public:
		virtual ~IGameObject() = 0;

		virtual void Draw() = 0;
		virtual void Update(unsigned int flags) = 0;
		virtual void SetShader(GLuint shaderName) = 0;
		virtual void Destroy() = 0;

		virtual GLuint GetVao() const = 0;
		virtual const std::vector<GLuint>& GetVbos() const = 0;
	};

	inline IGameObject::~IGameObject()
	{//blank
	}
 }

#endif