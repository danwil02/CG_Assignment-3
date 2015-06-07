#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>


#include "../OpenGL_headers.h"

namespace Managers
{

	class ShaderManager
	{
	public:
		ShaderManager();
		~ShaderManager();
		void createShader(const std::string& shaderName,
						  const std::string& vertexShaderFilename,
						  const std::string& fragmentShaderFilename);

		const GLuint getShaderHandle(const std::string& shaderName);
		

	private:
		GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
		int CompileShader(const char *ShaderPath, const GLuint ShaderID);

		std::map<std::string, GLuint> m_programs;


	};
};
#endif