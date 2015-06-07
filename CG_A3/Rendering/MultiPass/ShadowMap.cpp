#include "ShadowMap.h"

#define SHADOW 1
#define NO_SHADOW 0

using namespace Rendering;
using namespace MultiPass;
using namespace std;

ShadowMap::ShadowMap()
{
}


ShadowMap::~ShadowMap()
{
}


bool ShadowMap::Create()
{
	glActiveTexture(GL_TEXTURE25);
	// generate namespace for the frame buffer and depthbuffer
	glGenFramebuffers(1, &m_FramebufferName);
	glGenTextures(1, &m_depthTexture);

	//switch to our fbo so we can bind stuff to it
	glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferName);

	// create the depth texture and attach it to the frame buffer.
	glBindTexture(GL_TEXTURE_2D, m_depthTexture);
	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_texSz, m_texSz, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Set "renderedTexture" as our depth attachement
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);


	// Instruct openGL that we won't bind a color texture with the currently binded FBO
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// Always check that our framebuffer is ok
	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		printf("FB error, status: 0x%x\n", Status);
		exit(-1);
	}
}

void ShadowMap::pushMatrices()
{
	int depthBiasMVPHandle = glGetUniformLocation(m_shader, "DepthBiasMVP");
	int shadowHandle = glGetUniformLocation(m_shader, "shadow");
	int lightposHandle = glGetUniformLocation(m_shader, "light_pos");
	int projHandle = glGetUniformLocation(m_shader, "projection_matrix");

	// Update the light position
	float lightPos[4] = { lightX, lightY, lightZ, 0.0f };
	glUniform4fv(lightposHandle, 1, lightPos);

	glm::mat4 viewMatrix = glm::mat4(1.0);
	glm::mat4 projection;
	glm::mat4 depthBiasMVP, projLightMatrix, viewLightMatrix, mvLightMatrix;

	getPVLightMatrix(projLightMatrix, viewLightMatrix);
	mvLightMatrix = viewLightMatrix;

	//mvLightMatrix = glm::mat4(1);
	glm::mat4 biasMatrix(0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0);
	depthBiasMVP = biasMatrix*projLightMatrix*mvLightMatrix;
	glUniformMatrix4fv(depthBiasMVPHandle, 1, false, glm::value_ptr(depthBiasMVP));

	//getPVLightMatrix(&projection, &viewMatrix);
	glUniformMatrix4fv(projHandle, 1, false, glm::value_ptr(projection));
	GLuint projMatHandle = glGetUniformLocation(m_shader, "projection_matrix");
	glUniformMatrix4fv(projMatHandle, 1, false, glm::value_ptr(projLightMatrix));

	GLuint modleview = glGetUniformLocation(m_shader, "modleview_matrix");
	glUniformMatrix4fv(modleview, 1, false, glm::value_ptr(viewLightMatrix));

	glm::mat4 cameraMat = glm::mat4(1);
	//cameraMat = glm::translate(cameraMat, glm::vec3(m_x_offset, 0, 0));
	GLuint cameraMatHandle = glGetUniformLocation(m_shader, "camera_matrix");
	glUniformMatrix4fv(cameraMatHandle, 1, false, glm::value_ptr(cameraMat));
}


void ShadowMap::getPVLightMatrix(glm::mat4& projection, glm::mat4& viewMatrix)
{
	glm::vec3 lightInvDir = glm::vec3(lightX, lightY, lightZ);

	projection = glm::ortho<float>(-1000, 1000, -1000, 1000, 100, 5000);

	viewMatrix = glm::lookAt(lightInvDir, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

void ShadowMap::Draw()
{
	int texHandle = glGetUniformLocation(m_shader, "texMap");
	int gShadowMapHandle = glGetUniformLocation(m_shader, "gShadowMap");
	int applyTexHandle = glGetUniformLocation(m_shader, "apply_tex");
	int winW = glutGet(GLUT_WINDOW_WIDTH);
	int winH = glutGet(GLUT_WINDOW_HEIGHT);

	glUseProgram(m_shader);
	glCullFace(GL_FRONT);

	pushMatrices();

	glActiveTexture(GL_TEXTURE25);
	glBindTexture(GL_TEXTURE_2D, m_depthTexture);
	glUniform1i(gShadowMapHandle, 25);

	glBindFramebuffer(GL_FRAMEBUFFER, m_FramebufferName);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, m_texSz, m_texSz);
	
	int shadowHandle = glGetUniformLocation(m_shader, "shadow");
	glUniform1i(shadowHandle, SHADOW);
	
	// Draw scene
	for (int i = 0; i < m_vao.size(); i++)
	{
		glBindVertexArray(m_vao[i]);
		glDrawElements(GL_TRIANGLES,
			m_indiciesLength[i],
			GL_UNSIGNED_INT,
			(void*)0);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glUniform1i(shadowHandle, NO_SHADOW);

	glDisable(GL_CULL_FACE);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, winW, winH);
}

void ShadowMap::addSceneData(vector<GLuint>& vao, vector<unsigned int>& idx_len)
{
	for (int i = 0; i < vao.size(); i++)
	{
		m_vao.push_back(vao[i]);
	}
	for (int i = 0; i < idx_len.size(); i++)
	{
		m_indiciesLength.push_back(idx_len[i]);
	}
}

void ShadowMap::bindDepthTexture(GLuint shader_handle)
{
	int gShadowMapHandle = glGetUniformLocation(shader_handle, "gShadowMap");
	glActiveTexture(GL_TEXTURE25);
	glBindTexture(GL_TEXTURE_2D, m_depthTexture);
	glUniform1i(gShadowMapHandle, 25);
}