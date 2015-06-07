#pragma once

#include "../OpenGL_headers.h"
#include "CameraManager.h"
#include "../Utils/tiny_obj_loader.h"
#include "../Utils/glm/glm.hpp"
#include "../Utils/glm/gtc/matrix_transform.hpp"
#include "../Utils/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>

#define NUM_LIGHT_STATES 3
#define NO_LIGHTING 2

using namespace std;

namespace Managers
{
	class LightingManager
	{
	public:
		LightingManager(CameraManager* cam);
		~LightingManager();
		void setupLightingProperties(tinyobj::material_t material, int shader, string objName);
		void pushMaterialPropsToShader(int idx, int shader, string objName);
		void createLight(float objMaxCoord, int shader, string objName);
		void pushLightingPropsToShader(int shader, string objName);

		void switchLighting();

	private:
		map<string, vector<MaterialProperties>> m_materialProperties;
		map<string, vector<LightProperties>> m_lightProperties;

		int m_lightState;

		CameraManager* m_cameraManager;
	};
}