#ifndef MODELSMANAGER_H
#define MODELSMANAGER_H

#include <map>
#include "ShaderManager.h"
#include "CameraManager.h"
#include "LightingManager.h"
#include "../Rendering/IGameObject.h"
#include "../Rendering/Models/Triangle.h"
#include "../Rendering/Models/WireFrame.h"
#include "../Rendering/Models/Axes.h"
#include "../Rendering/Models/TextureObj.h"
#include "../Rendering/Models/GenericObj.h"
#include "../Rendering/Models/SkyBox.h"
#include "../Rendering/Models/Island.h"
#include "../Rendering/Models/Sun.h"
#include "../Rendering/MultiPass/ShadowMap.h"
#include "../Rendering/Models/Water.h"

using namespace Rendering;

namespace Managers
{
	class ModelsManager
	{
	public:
		ModelsManager(ShaderManager* shaderManager, CameraManager* cameraManager,
			CMD_OPTIONS options, std::string objDir);
		~ModelsManager();

		void Draw();
		void Update(unsigned int flags);
		void DeleteModel(const std::string& gameModelName);
		const IGameObject& GetModel(const std::string& gameModelName) const;

	private:
		std::map<std::string, IGameObject*> m_gameModelList;
		CameraManager* m_cameraManager;

		MultiPass::ShadowMap* m_sMap;
	};
}

#endif