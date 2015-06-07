#include "Triangle.h"

using namespace Rendering;
using namespace Models;

Triangle::Triangle()
{
}


Triangle::~Triangle()
{
}

void Triangle::Create()
{
	GLuint shaderHandle = m_shader;
	unsigned int vao;
	unsigned int vbo[2];

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Triangle's Verticies //
	std::vector<glm::vec3> vertices;
	vertices.push_back(glm::vec3(0.25, -0.25, 0.0));
	vertices.push_back(glm::vec3(-0.25, -0.25, 0.0));
	vertices.push_back(glm::vec3(0.25, 0.25, 0.0));

	// Vertex colours //
	std::vector<glm::vec4> colours;
	colours.push_back(glm::vec4(1, 0, 0, 1));
	colours.push_back(glm::vec4(0, 1, 0, 1));
	colours.push_back(glm::vec4(0, 0, 1, 1));

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

void Triangle::Update(unsigned int flags)
{
	//for triangle there is nothing to update for now
}

void Triangle::Draw()
{
	glUseProgram(m_shader);
	glBindVertexArray(m_vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}