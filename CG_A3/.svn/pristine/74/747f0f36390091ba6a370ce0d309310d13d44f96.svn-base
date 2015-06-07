#include "Axes.h"
#include "../../Monitor_GL.h"

using namespace Rendering;
using namespace Models;
using namespace std;

#define VALS_PER_VERT 3
#define VALS_PER_COLOUR 4

Axes::Axes()
{
}


Axes::~Axes()
{
}

void Axes::Create()
{
	GLuint shaderHandle = m_shader;
	unsigned int vao;
	unsigned int vbo[2];

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Triangle's Verticies //
	std::vector<glm::vec3> vertices;
	vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
	vertices.push_back(glm::vec3(100, 0.0, 0.0));
	vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
	vertices.push_back(glm::vec3(0.0, 100, 0.0));
	vertices.push_back(glm::vec3(0.0, 0.0, 0.0));
	vertices.push_back(glm::vec3(0.0, 0.0, 100));

	// Vertex colours //
	std::vector<glm::vec4> colours;
	colours.push_back(glm::vec4(1, 0, 0, 1));
	colours.push_back(glm::vec4(1, 0, 0, 1));
	colours.push_back(glm::vec4(0, 0, 1, 1));
	colours.push_back(glm::vec4(0, 0, 1, 1));
	colours.push_back(glm::vec4(0, 1, 0, 1));
	colours.push_back(glm::vec4(0, 1, 0, 1));

	// Allocate memory and copy vertex values to GPU // 
	glGenBuffers(2, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	int vertLoc = glGetAttribLocation(shaderHandle, "a_vertex");
	glEnableVertexAttribArray(vertLoc); // Turn on the state machine
	glVertexAttribPointer(vertLoc, VALS_PER_VERT, GL_FLOAT, GL_FALSE, 0, 0);

	// Allocate memory and copy colour values to GPU // 
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, colours.size()*sizeof(glm::vec4), &colours[0], GL_STATIC_DRAW);
	int colourLoc = glGetAttribLocation(shaderHandle, "a_colour");
	glEnableVertexAttribArray(colourLoc); // Turn on the state machine
	glVertexAttribPointer(colourLoc, VALS_PER_COLOUR, GL_FLOAT, GL_FALSE, 0, 0);

	// Unbind the VAOs and buffers //
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Save Model Data //
	m_vao.push_back(vao);
	m_vbos.push_back(vbo[0]);
	m_vbos.push_back(vbo[1]);
}

void Axes::Update(unsigned int flags)
{
	// Grab the latest version of the camera matrix // 
	m_cameraMat = m_cameraManager->getCameraPos();


	// Grab the latest version of the projection matrix // 
	m_projMat = m_cameraManager->getProjectionMat();
	

	int m_scaleFactor = 10;
	// Scale the object to fill the view //
	m_mvMat = glm::mat4(1);
	m_mvMat = glm::scale(m_mvMat, glm::vec3(m_scaleFactor, m_scaleFactor, m_scaleFactor));
	
}

void Axes::Draw()
{
	//glLineWidth(3);
	m_glUseProgram(m_shader);

	//----------//
	// UNIFORMS //
	//----------//

	//
	// View Matrices
	//
	GLuint cameraMatHandle = glGetUniformLocation(m_shader, "camera_matrix");
	if (cameraMatHandle == -1)
	{
		exit(1);
	}
	glUniformMatrix4fv(cameraMatHandle, 1, false, glm::value_ptr(m_cameraMat));

	GLuint projMatHandle = glGetUniformLocation(m_shader, "projection_matrix");
	if (projMatHandle == -1)
	{
		exit(1);
	}
	glUniformMatrix4fv(projMatHandle, 1, false, glm::value_ptr(m_projMat));

	GLuint scaleMatHandle = glGetUniformLocation(m_shader, "scale_matrix");
	if (scaleMatHandle == -1)
	{
		exit(1);
	}
	glUniformMatrix4fv(scaleMatHandle, 1, false, glm::value_ptr(m_mvMat));

	//
	// Draw Lines
	//

	m_glDisable(GL_DEPTH_TEST);
	m_glBindVertexArray(m_vao[0]);
	m_glDrawArrays(GL_LINES, 0, 6);
	//glLineWidth(1.0);
	m_glBindVertexArray(0);
	m_glEnable(GL_DEPTH_TEST);
}
