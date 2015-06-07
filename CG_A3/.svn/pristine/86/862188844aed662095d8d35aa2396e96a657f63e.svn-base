#include "ShaderManager.h"

namespace Managers
{
	ShaderManager::ShaderManager()
	{
	}


	ShaderManager::~ShaderManager()
	{
		std::map<std::string, GLuint>::iterator i;
		for (i = m_programs.begin(); i != m_programs.end(); ++i)
		{
			GLuint pr = i->second;
			glDeleteProgram(pr);
		}
		m_programs.clear();
	}
	void ShaderManager::createShader(const std::string& shaderName,
					  const std::string& vertexShaderFilename,
					  const std::string& fragmentShaderFilename)
	{
		m_programs[shaderName] = LoadShaders(vertexShaderFilename.c_str(),
											 fragmentShaderFilename.c_str());
		std::cout << "Shader " << getShaderHandle(shaderName) << " \"" << shaderName << "\" compiled.\n" << std::endl;
	}


	const GLuint ShaderManager::getShaderHandle(const std::string& shaderName)
	{
		return m_programs.at(shaderName);
	}


	int ShaderManager::CompileShader(const char *ShaderPath, const GLuint ShaderID)
	{
		// Read shader code from file
		std::string ShaderCode;
		std::ifstream ShaderStream(ShaderPath, std::ios::in);
		if (ShaderStream.is_open()) {
			std::string Line = "";
			while (getline(ShaderStream, Line)) {
				ShaderCode += "\n" + Line;
			}
			ShaderStream.close();
		}
		else {
			std::cerr << "Cannot open " << ShaderPath << ". Are you in the right directory?" << std::endl;
			return 0;
		}

		// Compile Shader
		char const *SourcePointer = ShaderCode.c_str();
		glShaderSource(ShaderID, 1, &SourcePointer, NULL);
		glCompileShader(ShaderID);

		// Check Shader
		GLint Result = GL_FALSE;
		int InfoLogLength;

		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		printf("Compiled Shader: %d %d ", Result, InfoLogLength);
		std::cout << ShaderPath << std::endl;
		if (InfoLogLength > 1) {
			std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(ShaderID,
				InfoLogLength,
				NULL,
				&ShaderErrorMessage[0]);
			std::cerr << &ShaderErrorMessage[0] << std::endl;
			return 0;
		}
		return 1;
	}

	GLuint ShaderManager::LoadShaders(const char * vertex_file_path,
									  const char * fragment_file_path)
	{
		// Create the shaders
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Compile both shaders. Exit if compile errors.
		if (!CompileShader(vertex_file_path, VertexShaderID)
			|| !CompileShader(fragment_file_path, FragmentShaderID)) {
			return 0;
		}

		// Link the program
		GLuint ProgramID = glCreateProgram();
		glAttachShader(ProgramID, VertexShaderID);
		glAttachShader(ProgramID, FragmentShaderID);
		glLinkProgram(ProgramID);

		// Check the program
		GLint Result = GL_FALSE;
		int InfoLogLength;

		glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			std::cerr << &ProgramErrorMessage[0] << std::endl;
		}

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		return ProgramID;
	}
}