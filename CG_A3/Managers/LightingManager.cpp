#include "LightingManager.h"

using namespace Managers;
using namespace std;

LightingManager::LightingManager(CameraManager* cam) : m_cameraManager(cam)
{
}


LightingManager::~LightingManager()
{
}

void LightingManager::setupLightingProperties(tinyobj::material_t material, int shader, string objName)
{
	// Lighting Variables //
	// Uniform lighting variables //
	int mtlambientHandle = glGetUniformLocation(shader, "mtl_ambient");
	int mtldiffuseHandle = glGetUniformLocation(shader, "mtl_diffuse");
	int mtlspecularHandle = glGetUniformLocation(shader, "mtl_specular");
	int shininessHandle = glGetUniformLocation(shader, "shininess");
	if (mtlambientHandle == -1 ||
		mtldiffuseHandle == -1 ||
		mtlspecularHandle == -1 ||
		shininessHandle == -1) {
		cerr << "Error: can't find material uniform variables." << endl;
		cerr << "Shader " << shader << endl;
		cerr << "mtlambientHandle " << mtlambientHandle << endl;
		cerr << "mtldiffuseHandle " << mtldiffuseHandle << endl;
		cerr << "mtlspecularHandle " << mtlspecularHandle << endl;
		cerr << "shininessHandle " << shininessHandle << endl;
		exit(11);
	}

	glUniform3fv(mtlambientHandle, 1, material.ambient);
	glUniform3fv(mtldiffuseHandle, 1, material.diffuse);
	glUniform3fv(mtlspecularHandle, 1, material.specular);
	glUniform1f(shininessHandle, material.shininess);

	cout << "\nLighting Properties \"" << material.name << "\"" << endl;
	cout << "mtlambientHandle\t" << mtlambientHandle << " ";
	cout << material.ambient[0] << "\t" << material.ambient[1] << "\t" << material.ambient[3] << endl;
	cout << "mtldiffuseHandle\t" << mtldiffuseHandle << " ";
	cout << material.diffuse[0] << "\t" << material.diffuse[1] << "\t" << material.diffuse[3] << endl;
	cout << "mtlspecularHandle\t" << mtlspecularHandle << " ";
	cout << material.specular[0] << "\t" << material.specular[1] << "\t" << material.specular[3] << endl;
	cout << "shininessHandle\t" << shininessHandle << " " << material.shininess << endl;
	cout << "============================================" << endl;

	MaterialProperties in_props;
	for (int i = 0; i < 3; i++)
	{
		in_props.ambient[i] = material.ambient[i];
		in_props.diffuse[i] = material.diffuse[i];
		in_props.specular[i] = material.specular[i];
	}
	in_props.shininess = material.shininess;

	m_materialProperties[objName].push_back(in_props);
}

void LightingManager::pushMaterialPropsToShader(int idx, int shader, string objName)
{
	if (idx > m_materialProperties[objName].size())
	{
		cerr << "Index " << idx << " out of range pushMaterialPropsToShader(int idx)" << endl;
		return;
	}
	// Lighting Variables //
	// Uniform lighting variables //
	int mtlambientHandle = glGetUniformLocation(shader, "mtl_ambient");
	int mtldiffuseHandle = glGetUniformLocation(shader, "mtl_diffuse");
	int mtlspecularHandle = glGetUniformLocation(shader, "mtl_specular");
	int shininessHandle = glGetUniformLocation(shader, "shininess");
	if (mtlambientHandle == -1 ||
		mtldiffuseHandle == -1 ||
		mtlspecularHandle == -1 ||
		shininessHandle == -1) {
		cerr << "Error: can't find material uniform variables." << endl;
		cerr << "Shader " << shader << endl;
		cerr << "mtlambientHandle " << mtlambientHandle << endl;
		cerr << "mtldiffuseHandle " << mtldiffuseHandle << endl;
		cerr << "mtlspecularHandle " << mtlspecularHandle << endl;
		cerr << "shininessHandle " << shininessHandle << endl;
		exit(11);
	}
	glUniform3fv(mtlambientHandle, 1, m_materialProperties[objName][idx].ambient);
	glUniform3fv(mtldiffuseHandle, 1, m_materialProperties[objName][idx].diffuse);
	glUniform3fv(mtlspecularHandle, 1, m_materialProperties[objName][idx].specular);
	glUniform1f(shininessHandle, m_materialProperties[objName][idx].shininess);
}

void LightingManager::createLight(float objMaxCoord, int shader, string objName)
{
	// Uniform lighting variables //
	int lightambientHandle = glGetUniformLocation(shader, "light_ambient");
	int lightdiffuseHandle = glGetUniformLocation(shader, "light_diffuse");
	int lightspecularHandle = glGetUniformLocation(shader, "light_specular");
	int lightposHandle = glGetUniformLocation(shader, "light_pos");
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
	float lightPos[4] = { 0.0f, objMaxCoord*0.3, 0.0f, 1.0f };

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
	m_lightProperties[objName].push_back(in_props);

	// Light 2 - headlight, white // 
	float lightambient2[3] = { 0.0f, 0.0f, 0.0f };	// ambient light components
	float lightdiffuse2[3] = { 0.0f, 0.0f, 0.0f };	// diffuse light components
	float lightspecular2[3] = { 0.0f, 0.0f, 0.0f };	// specular light components
	glm::mat4 camerapos = m_cameraManager->getCameraPos();
	glm::vec4 lightPos2 = glm::vec4(1)*camerapos;
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

	m_lightProperties[objName].push_back(in_props2);

	cout << "============================================" << endl;
}

void LightingManager::pushLightingPropsToShader(int shader, string objName)
{	
	/*
	if (idx > m_lightProperties[objName].size())
	{
		cerr << "Index " << idx << " out of range pushLightingPropsToShader(int idx)" << endl;
		return;
	}*/
	// Uniform lighting variables //
	int lightambientHandle = glGetUniformLocation(shader, "light_ambient");
	int lightdiffuseHandle = glGetUniformLocation(shader, "light_diffuse");
	int lightspecularHandle = glGetUniformLocation(shader, "light_specular");
	int lightposHandle = glGetUniformLocation(shader, "light_pos");
	int enableLightingHandle = glGetUniformLocation(shader, "lighting_enabled");
	if (lightambientHandle == -1 ||
		lightdiffuseHandle == -1 ||
		lightspecularHandle == -1 ||
		lightposHandle == -1 ||
		enableLightingHandle == -1)
	{
		fprintf(stderr, "Error: can't find light uniform variables\n");
		exit(12);
	}
	int idx = m_lightState;

	if (idx == NO_LIGHTING)
	{
		glUniform1i(lightambientHandle, 0); // Lighting off
		return;
	}
	glUniform1i(lightambientHandle, 1); // Lighting on

	glUniform3fv(lightambientHandle, 1, m_lightProperties[objName][idx].ambient);
	glUniform3fv(lightdiffuseHandle, 1, m_lightProperties[objName][idx].diffuse);
	glUniform3fv(lightspecularHandle, 1, m_lightProperties[objName][idx].specular);
	glUniform4fv(lightposHandle, 1, m_lightProperties[objName][idx].lightPos);
}

void LightingManager::switchLighting()
{
	m_lightState = (m_lightState + 1) % NUM_LIGHT_STATES;
	cout << "m_lightState = " << m_lightState << endl;
}