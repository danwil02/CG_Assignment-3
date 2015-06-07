#include "GenericObj.h"

using namespace Rendering;
using namespace Models;
using namespace std;

GenericObj::GenericObj()
{
}


GenericObj::~GenericObj()
{
}


void GenericObj::Create(std::string inputfile)
{
	vector<tinyobj::shape_t> shapes;
	vector<tinyobj::material_t> materials;
	vector<glm::vec4> colours;
	string basepath;
	string shapeCheck;

	GLuint vao;
	GLuint vbo[4];
	GLuint texId;

	if (WINDOWS)
	{
		basepath = inputfile.substr(0, inputfile.rfind('\\') + 1); // WINDOWS
	}
	else
	{
		basepath = inputfile.substr(0, inputfile.rfind('/') + 1);;
	}

	cout << "Loading " << inputfile << " . . . ";
	std::string err = tinyobj::LoadObj(shapes, materials, inputfile.c_str(), basepath.c_str());
	cout << "DONE!\n";

	cout << "Shapes " << shapes.size() << endl;
	cout << "Materials " << materials.size() << endl;

	//	for(int i = 0; i < shapes[i].mesh.positions.size())
	//	{
	//colours.push_back(glm::vec4(1, 1, 1, 1));

	if (!err.empty())
	{
		cout << err << endl;
		exit(10);
	}
	m_numShapes = shapes.size();
	//unsigned int num_textures = m_numShapes;
	//m_texId = std::vector<GLuint>(num_textures);

	for (unsigned int i = 0; i < m_numShapes; i++)
	{
		m_indiciesLength.push_back(shapes[i].mesh.positions.size());

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(4, vbo);

		// Vertices // 
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, shapes[i].mesh.positions.size()*sizeof(float),
			&shapes[i].mesh.positions[0], GL_STATIC_DRAW);
		int vertLoc = glGetAttribLocation(m_shader, "a_vertex");
		glEnableVertexAttribArray(vertLoc);
		glVertexAttribPointer(vertLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Indices //
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapes[i].mesh.indices.size()*sizeof(int),
			&shapes[i].mesh.indices[0], GL_STATIC_DRAW);

		// Normals //
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, shapes[i].mesh.normals.size()*sizeof(float),
			&shapes[i].mesh.normals[0], GL_STATIC_DRAW);
		int normLoc = glGetAttribLocation(m_shader, "a_normal");
		glEnableVertexAttribArray(normLoc);
		glVertexAttribPointer(normLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

		if (i < materials.size())
		{
			setupLightingProperties(materials[i]);
		}

		// Unbind VAO and buffers //
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		m_vao.push_back(vao);
		m_vbos.push_back(vbo[0]);
		m_vbos.push_back(vbo[1]);
		m_vbos.push_back(vbo[2]);
		m_indiciesLength[i] = shapes[i].mesh.indices.size();
	}

	//
	// Default View is 5 units away from object with 70deg fov. This gives approx y range of +10.6
	// So here we will scale each object with respect to coord with largest magnitude up to 10 
	//
	float maxCoord = 0;
	float nextCoord = 0;
	for (unsigned int i = 0; i < m_numShapes; i++)
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

	m_scaleFactor = 7.5f / maxCoord;

	cout << "Scale factor = " << m_scaleFactor << endl;
	cout << "Max Coord = " << maxCoord << endl;

	createLight(m_scaleFactor*maxCoord);
}

void GenericObj::Update(unsigned int flags)
{

	if (flags == UPDATE_LIGHTING_OVERHEAD ||
		flags == UPDATE_LIGHTING_HEADLIGHT ||
		flags == UPDATE_LIGHTING_NONE)
	{
		m_lightingState = flags;
	}
}

void GenericObj::Draw()
{
	glUseProgram(m_shader);

	// Grab the latest version of the camera matrix // 
	glm::mat4 cameraMat = m_cameraManager->getCameraPos();
	GLuint cameraMatHandle = glGetUniformLocation(m_shader, "camera_matrix");
	if (cameraMatHandle == -1)
	{
		exit(13);
	}
	glUniformMatrix4fv(cameraMatHandle, 1, false, glm::value_ptr(cameraMat));

	// Grab the latest version of the projection matrix // 
	glm::mat4 projMat = m_cameraManager->getProjectionMat();
	GLuint projMatHandle = glGetUniformLocation(m_shader, "projection_matrix");
	if (projMatHandle == -1)
	{
		exit(14);
	}
	glUniformMatrix4fv(projMatHandle, 1, false, glm::value_ptr(projMat));

	// Scale the object to fill the view //
	glm::mat4 scaleMat(1);
	scaleMat = glm::scale(scaleMat, glm::vec3(m_scaleFactor, m_scaleFactor, m_scaleFactor));
	GLuint scaleMatHandle = glGetUniformLocation(m_shader, "scale_matrix");
	if (scaleMatHandle == -1)
	{
		exit(15);
	}
	glUniformMatrix4fv(scaleMatHandle, 1, false, glm::value_ptr(scaleMat));


	// Normal Matrix //
	glm::mat3 normalMat(1);
	normalMat = glm::mat3(cameraMat*scaleMat);
	int normHandle = glGetUniformLocation(m_shader, "normal_matrix");
	if (normHandle == -1)
	{
		exit(16);
	}
	glUniformMatrix3fv(normHandle, 1, false, glm::value_ptr(normalMat));

	pushLightingPropsToShader(m_lightingState);

	for (unsigned int i = 0; i < m_vao.size(); i++)
	{
		pushMaterialPropsToShader(i);

		glBindVertexArray(m_vao[i]);
		glDrawElements(GL_TRIANGLES,
			m_indiciesLength[i],
			GL_UNSIGNED_INT,
			(void*)0);
	}
	glBindVertexArray(0);
}

void GenericObj::setupLightingProperties(tinyobj::material_t material)
{
	// Lighting Variables //
	// Uniform lighting variables //
	int mtlambientHandle = glGetUniformLocation(m_shader, "mtl_ambient");
	int mtldiffuseHandle = glGetUniformLocation(m_shader, "mtl_diffuse");
	int mtlspecularHandle = glGetUniformLocation(m_shader, "mtl_specular");
	if (mtlambientHandle == -1 ||
		mtldiffuseHandle == -1 ||
		mtlspecularHandle == -1) {
		cerr << "Error: can't find material uniform variables." << endl;
		cerr << "Shader " << m_shader << endl;
		cerr << "mtlambientHandle " << mtlambientHandle << endl;
		cerr << "mtldiffuseHandle " << mtldiffuseHandle << endl;
		cerr << "mtlspecularHandle " << mtlspecularHandle << endl;
		exit(11);
	}

	glUniform3fv(mtlambientHandle, 1, material.ambient);
	glUniform3fv(mtldiffuseHandle, 1, material.diffuse);
	glUniform3fv(mtlspecularHandle, 1, material.specular);

	cout << "\nLighting Properties \"" << material.name << "\""<< endl;
	cout << "mtlambientHandle\t" << mtlambientHandle << " ";
	cout << material.ambient[0] << "\t" << material.ambient[1] << "\t" << material.ambient[3] << endl;
	cout << "mtldiffuseHandle\t" << mtldiffuseHandle << " ";
	cout << material.diffuse[0] << "\t" << material.diffuse[1] << "\t" << material.diffuse[3] << endl;
	cout << "mtlspecularHandle\t" << mtlspecularHandle << " ";
	cout << material.specular[0] << "\t" << material.specular[1] << "\t" << material.specular[3] << endl;
	cout << "============================================" << endl;

	MaterialProperties in_props;
	for (int i = 0; i < 3; i++)
	{
		in_props.ambient[i] = material.ambient[i];
		in_props.diffuse[i] = material.diffuse[i];
		in_props.specular[i] = material.specular[i];
	}

	m_materialProperties.push_back(in_props);
}

void GenericObj::pushMaterialPropsToShader(int idx)
{
	if (idx > m_materialProperties.size())
	{
		cerr << "Index " << idx << " out of range pushMaterialPropsToShader(int idx)" << endl;
		return;
	}
	// Lighting Variables //
	// Uniform lighting variables //
	int mtlambientHandle = glGetUniformLocation(m_shader, "mtl_ambient");
	int mtldiffuseHandle = glGetUniformLocation(m_shader, "mtl_diffuse");
	int mtlspecularHandle = glGetUniformLocation(m_shader, "mtl_specular");
	if (mtlambientHandle == -1 ||
		mtldiffuseHandle == -1 ||
		mtlspecularHandle == -1) {
		cerr << "Error: can't find material uniform variables." << endl;
		cerr << "Shader " << m_shader << endl;
		cerr << "mtlambientHandle " << mtlambientHandle << endl;
		cerr << "mtldiffuseHandle " << mtldiffuseHandle << endl;
		cerr << "mtlspecularHandle " << mtlspecularHandle << endl;
		exit(11);
	}

	glUniform3fv(mtlambientHandle, 1, m_materialProperties[idx].ambient);
	glUniform3fv(mtldiffuseHandle, 1, m_materialProperties[idx].diffuse);
	glUniform3fv(mtlspecularHandle, 1, m_materialProperties[idx].specular);
}

void GenericObj::createLight(float objMaxCoord)
{
	// Uniform lighting variables //
	int lightambientHandle = glGetUniformLocation(m_shader, "light_ambient");
	int lightdiffuseHandle = glGetUniformLocation(m_shader, "light_diffuse");
	int lightspecularHandle = glGetUniformLocation(m_shader, "light_specular");
	int lightposHandle = glGetUniformLocation(m_shader, "light_pos");
	if (lightambientHandle == -1 ||
		lightdiffuseHandle == -1 ||
		lightspecularHandle == -1)
	{
		fprintf(stderr, "Error: can't find light uniform variables\n");
		exit(12);
	}
	else
	{
		cout << "\nLight Created " << endl;
		cout << "Ambient handle\t" << lightambientHandle << endl;
		cout << "Diffuse handle\t" << lightdiffuseHandle << endl;
		cout << "Specular handle\t" << lightspecularHandle << endl;
		cout << "Lightpos handle\t" << lightposHandle << endl;
	}

	// Light 1 overhead, blue //
	float lightambient[3] = { 0.5f, 0.5f, 0.5f };	// ambient light components
	float lightdiffuse[3] = { 0.7f, 0.7f, 1.0f };	// diffuse light components
	float lightspecular[3] = { 1.0f, 1.0f, 1.0f };	// specular light components
	float lightPos[4] = { 0.0f, static_cast<float>(objMaxCoord*0.3), 0.0f, 1.0f };

	LightProperties in_props;
	for (int i = 0; i < 3; i++)
	{
		in_props.ambient[i] = lightambient[i];
		in_props.diffuse[i] = lightdiffuse[i];
		in_props.specular[i] = lightspecular[i];
	}
	for (int i = 0; i < 4; i++)
	{
		in_props.lightPos[i] = lightPos[i];
	}
	m_lightProperties.push_back(in_props);

	// Light 2 - headlight, white // 
	float lightambient2[3] = { 0.5f, 0.5f, 0.5f };	// ambient light components
	float lightdiffuse2[3] = { 0.9f, 0.9f, 0.9f };	// diffuse light components
	float lightspecular2[3] = { 1.0f, 1.0f, 1.0f };	// specular light components
	glm::vec4 lightPos2 = m_cameraManager->getCameraPos()*glm::vec4(0, 0, 0, 1);
	lightPos2.z = -lightPos2.z;
	//glm::vec4 lightPos2 = glm::vec4(0, 0, 20, 1);

	LightProperties in_props2;

	for (int i = 0; i < 3; i++)
	{
		in_props2.ambient[i] = lightambient2[i];
		in_props2.diffuse[i] = lightdiffuse2[i];
		in_props2.specular[i] = lightspecular2[i];
	}
	for (int i = 0; i < 4; i++)
	{
		in_props2.lightPos[i] = lightPos2[i];
	}

	m_lightProperties.push_back(in_props2);

	// Light 3 - none // 
	float lightambient3[3] = { 0.0f, 0.0f, 0.0f };	// ambient light components
	float lightdiffuse3[3] = { 0.0f, 0.0f, 0.0f };	// diffuse light components
	float lightspecular3[3] = { 0.0f, 0.0f, 0.0f };	// specular light components
	glm::vec4 lightPos3 = m_cameraManager->getCameraPos()*glm::vec4(0, 0, 0, 1);
	lightPos3.z = -lightPos3.z;
	//glm::vec4 lightPos2 = glm::vec4(0, 0, 20, 1);

	LightProperties in_props3;

	for (int i = 0; i < 3; i++)
	{
		in_props3.ambient[i] = lightambient3[i];
		in_props3.diffuse[i] = lightdiffuse3[i];
		in_props3.specular[i] = lightspecular3[i];
	}
	for (int i = 0; i < 4; i++)
	{
		in_props3.lightPos[i] = lightPos3[i];
	}

	m_lightProperties.push_back(in_props3);

	cout << "============================================" << endl;
}

void GenericObj::pushLightingPropsToShader(int idx)
{
	if (idx > m_lightProperties.size())
	{
		cerr << "Index " << idx << " out of range pushLightingPropsToShader(int idx)" << endl;
		return;
	}
	// Uniform lighting variables //
	int lightambientHandle = glGetUniformLocation(m_shader, "light_ambient");
	int lightdiffuseHandle = glGetUniformLocation(m_shader, "light_diffuse");
	int lightspecularHandle = glGetUniformLocation(m_shader, "light_specular");
	int lightposHandle = glGetUniformLocation(m_shader, "light_pos");
	if (lightambientHandle == -1 ||
		lightdiffuseHandle == -1 ||
		lightspecularHandle == -1)
	{
		fprintf(stderr, "Error: can't find light uniform variables\n");
		exit(12);
	}

	glUniform3fv(lightambientHandle, 1, m_lightProperties[idx].ambient);
	glUniform3fv(lightdiffuseHandle, 1, m_lightProperties[idx].diffuse);
	glUniform3fv(lightspecularHandle, 1, m_lightProperties[idx].specular);
	glUniform4fv(lightposHandle, 1, m_lightProperties[idx].lightPos);
}
