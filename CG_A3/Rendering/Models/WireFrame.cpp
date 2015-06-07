#include "WireFrame.h"

using namespace Rendering;
using namespace Models;
using namespace std;

WireFrame::WireFrame()
{
}

WireFrame::~WireFrame()
{
}

void WireFrame::Create(std::string inputfile)
{
	//string inputfile = "./Rendering/Models/TestObjs/cube-simple.obj";
	//string inputfile = "./Rendering/Models/TestObjs/dodec-sub.obj";
	//string inputfile = "./Rendering/Models/TestObjs/car/car-n.obj";
	//string inputfile = "./Rendering/Models/TestObjs/Lambo/Avent.obj";

	vector<tinyobj::shape_t> shapes;
	vector<tinyobj::material_t> materials;
	GLuint vao;
	GLuint vbo[2];

	cout << "Loading " << inputfile << " . . . ";
	std::string err = tinyobj::LoadObj(shapes, materials, inputfile.c_str());
	cout << "DONE!\n";
	if (!err.empty())
	{
		cout << err << endl;
		getchar();
		exit(1);
	}
	m_numShapes = shapes.size();

	for (int i = 0; i < m_numShapes; i++)
	{
		m_indiciesLength.push_back(shapes[i].mesh.positions.size());
		
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(2, vbo);

		// Vertices // 
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, shapes[i].mesh.positions.size()*sizeof(float),
			&shapes[i].mesh.positions[0], GL_STATIC_DRAW);
		int vertLoc = glGetAttribLocation(m_shader, "a_vertex");
		glEnableVertexAttribArray(vertLoc);
		glVertexAttribPointer(vertLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		// Indices //
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapes[i].mesh.indices.size()*sizeof(float),
			&shapes[i].mesh.indices[0], GL_STATIC_DRAW);

		// Unbind VAO and buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_vao.push_back(vao);
		m_vbos.push_back(vbo[0]);
		m_vbos.push_back(vbo[1]);
		m_indiciesLength[i] = shapes[i].mesh.indices.size();
	}
	
	//
	// Default View is 5 units away from object with 70deg fov. This gives approx y range of +10.6
	// So here we will scale each object with respect to coord with largest magnitude up to 10 
	//
	float maxCoord = 0;
	float nextCoord = 0;
	for (int i = 0; i < m_numShapes; i++)
	{
		for (size_t v = 0; v < shapes[i].mesh.positions.size(); v++) 
		{
			nextCoord = abs(shapes[i].mesh.positions[v]);
			if (nextCoord > maxCoord)
			{
				maxCoord = nextCoord;
			}
		}
	}
	
	m_scaleFactor = 7.3f / maxCoord;
	
	cout << "Scale factor = " << m_scaleFactor << endl;
	cout << "Max Coord = " << maxCoord << endl;

}

void WireFrame::Update(unsigned int flags)
{

}

void WireFrame::Draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Fill mode
	glUseProgram(m_shader);
	
	// Grab the latest version of the camera matrix // 
	glm::mat4 cameraMat = m_cameraManager->getCameraPos();
	GLuint cameraMatHandle = glGetUniformLocation(m_shader, "camera_matrix");
	if (cameraMatHandle == -1)
	{
		exit(1);
	}
	glUniformMatrix4fv(cameraMatHandle, 1, false, glm::value_ptr(cameraMat));

	// Grab the latest version of the projection matrix // 
	glm::mat4 projMat = m_cameraManager->getProjectionMat();
	GLuint projMatHandle = glGetUniformLocation(m_shader, "projection_matrix");
	if (projMatHandle == -1)
	{
		exit(1);
	}
	glUniformMatrix4fv(projMatHandle, 1, false, glm::value_ptr(projMat));

	// Scale the object to fill the view //
	glm::mat4 scaleMat(1);
	scaleMat = glm::scale(scaleMat, glm::vec3(m_scaleFactor, m_scaleFactor, m_scaleFactor));
	GLuint scaleMatHandle = glGetUniformLocation(m_shader, "scale_matrix");
	if (scaleMatHandle == -1)
	{
		exit(1);
	}
	glUniformMatrix4fv(scaleMatHandle, 1, false, glm::value_ptr(scaleMat));

	for (int i = 0; i < m_vao.size(); i++)
	{
		glBindVertexArray(m_vao[i]);
		glDrawElements(GL_TRIANGLES,
			m_indiciesLength[i],
			GL_UNSIGNED_INT,
			(void*)0);
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Fill mode
}