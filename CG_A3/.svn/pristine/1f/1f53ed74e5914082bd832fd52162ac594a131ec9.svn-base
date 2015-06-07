#include "ModelsManager.h"

using namespace Managers;
using namespace Rendering;

ModelsManager::ModelsManager(ShaderManager* shaderManager, CameraManager* cameraManager,
	CMD_OPTIONS options, std::string objDir)
{
	m_cameraManager = cameraManager;

	Models::Triangle* triangle = new Models::Triangle();
	Models::TextureObj* lambo = new Models::TextureObj();
	Models::Island* island = new Models::Island();
	Models::Sun* sun = new Models::Sun();
	MultiPass::ShadowMap* sMap = new MultiPass::ShadowMap();
	Models::Water* water = new Models::Water();

	//Models::WireFrame* wireFrame = new Models::WireFrame();
	//Models::GenericObj* genericLighting = new Models::GenericObj();

	water->setCameraManager(m_cameraManager);
	water->SetShader(shaderManager->getShaderHandle("water"));
	water->Create("");
	water->setShadowMap(sMap);
	m_gameModelList["04water"] = water;
	
	Models::SkyBox* skybox = new Models::SkyBox();
	skybox->setCameraManager(m_cameraManager);
	skybox->SetShader(shaderManager->getShaderHandle("skybox"));
	skybox->Create();
	skybox->setShadowMap(sMap);
	m_gameModelList["02skybox"] = skybox;
	
	island->setCameraManager(m_cameraManager);
	island->SetShader(shaderManager->getShaderHandle("shaded"));
//	island->setRTTshader(shaderManager->getShaderHandle("shadow_RTT"));
	island->Create("Rendering\\Models\\TestObjs\\Small_Tropical_Island\\Small_Tropical_Island.obj");
	island->setPos(glm::translate(glm::mat4(1), glm::vec3(0, 0, 0)));
	island->setScale(glm::scale(glm::mat4(1), glm::vec3(0.5, 0.5, 0.5)));
	island->setShadowMap(sMap);
	m_gameModelList["01island"] = island;

	sun->setCameraManager(m_cameraManager);
	sun->SetShader(shaderManager->getShaderHandle("sun"));
	sun->Create();
	sun->setShadowMap(sMap);
	m_gameModelList["03Sun"] = sun;
	sun->setPos(glm::translate(glm::mat4(1), glm::vec3(544, 378, -120)));
	sun->setScale(glm::scale(glm::mat4(1), glm::vec3(1, 1, 1)));
	
	lambo->setCameraManager(m_cameraManager);
	lambo->SetShader(shaderManager->getShaderHandle("shaded"));
	lambo->Create("Rendering\\Models\\TestObjs\\Lambo\\Avent.obj");
	lambo->setShadowMap(sMap);
	m_gameModelList["04lambo"] = lambo;
	lambo->setPos(glm::translate(glm::mat4(1), glm::vec3(31, 1.77, 59.09)));
	lambo->setScale(glm::scale(glm::mat4(1), glm::vec3(1, 1, 1)));
	
	vector<GLuint> vao, vao_tmp;
	vector<unsigned int> idx_len, idx_len_tmp;
	
	// Vao data for shadowmap //
	// Island
	vao_tmp = island->getVaoVect();
	idx_len_tmp = island->getVaoIdxLenVect();
	vao.insert(vao.begin(), vao_tmp.begin(), vao_tmp.end());
	idx_len.insert(idx_len.begin(), idx_len_tmp.begin(), idx_len_tmp.end());

	// Water
	//vao_tmp = water->getVaoVect();
	//idx_len_tmp = water->getVaoIdxLenVect();
	//vao.insert(vao.begin(), vao_tmp.begin(), vao_tmp.end());
	//idx_len.insert(idx_len.begin(), idx_len_tmp.begin(), idx_len_tmp.end());

	// Sun
	//vao_tmp = sun->getVaoVect();
	//idx_len_tmp = sun->getVaoIdxLenVect();
	//vao.insert(vao.begin(), vao_tmp.begin(), vao_tmp.end());
	//idx_len.insert(idx_len.begin(), idx_len_tmp.begin(), idx_len_tmp.end());
	/*
	// Lambo
	vao_tmp = lambo->getVaoVect();
	idx_len_tmp = lambo->getVaoIdxLenVect();
	vao.insert(vao.begin(), vao_tmp.begin(), vao_tmp.end());
	idx_len.insert(idx_len.begin(), idx_len_tmp.begin(), idx_len_tmp.end());
	*/

	// Shadow Map Creation //
	sMap->setShader(shaderManager->getShaderHandle("shaded"));
	sMap->Create();
	sMap->addSceneData(vao, idx_len);
	
	m_sMap = sMap;
}

ModelsManager::~ModelsManager()
{
	//auto is a map iterator
	for (auto model : m_gameModelList)
	{
		delete model.second;
	}
	m_gameModelList.clear();
}

void ModelsManager::DeleteModel(const std::string& gameModelName)
{
	IGameObject* model = m_gameModelList[gameModelName];
	model->Destroy();
	m_gameModelList.erase(gameModelName);
}

const IGameObject& ModelsManager::GetModel(const std::string& gameModelName) const
{
	return (*m_gameModelList.at(gameModelName));
}

void ModelsManager::Update(unsigned int flags)
{
	//auto is a map iterator
	for (auto model : m_gameModelList)
	{
		model.second->Update(flags);
	}
}

void ModelsManager::Draw()
{
	m_sMap->Draw();
	//auto is a map iterator
	for (auto model : m_gameModelList)
	{
		model.second->Draw();
	}
}