#include "ShaderManager.h"
#include "ModelsManager.h"
#include "CameraManager.h"
#include "LightingManager.h"
#include "../Init/ListenerInterface.h"
#include <string>
#include <time.h>

#define NUM_BACKGROUND_STATES 4
#define NUM_LIGHT_STATES 3

struct Input_Movement
{
	// Translation //
	int x_prev = 0;
	int y_prev = 0;
	int z_prev = 0;

	int dx = 0;
	int dy = 0;
	int dz = 0;

	// Rotation //
	float x_rot_prev = 0;
	float y_rot_prev = 0;
	float z_rot_prev = 0;

	float d_rot_x = 0;
	float d_rot_y = 0;
	float d_rot_z = 0;
};

namespace Managers
{
	class SceneManager : public Init::ListenerInterface
	{
	public:
		SceneManager(int windowWidth, int windowHeight, CMD_OPTIONS options, std::string objDir);
		~SceneManager();

		virtual void notifyBeginFrame();
		virtual void notifyDisplayFrame();
		virtual void notifyEndFrame();
		virtual void notifyReshape(int width,
			int height,
			int previous_width,
			int previous_height);
		virtual void notifyKeyboardEvent(unsigned char key, int x, int y);
		virtual void notifyKeyboardReleaseEvent(unsigned char key, int x, int y);
		virtual void notifySpecialKeyEvent(int key, int x, int y);
		virtual void notifySpecialKeyReleaseEvent(int key, int x, int y);
		
		virtual void notifyMouseButton(int button, int state, int x, int y);
		virtual void notifyMouseMovement(int x, int y);
		virtual void notifyPassiveMouseMovement(int x, int y);

	private:
		ShaderManager* m_shaderManager;
		ModelsManager* m_modelsManager;
		CameraManager* m_cameraManager;

		Input_Movement* m_inputMovement;


		bool m_zoom = false;
		bool m_move = false;

		int m_x_origin = 0;
		int m_y_origin = 0;

		float m_d_rot_x_origin = 0;
		float m_d_rot_y_origin = 0;
		float m_d_rot_z_origin = 0;

		bool m_wireFrame;
		int m_backgroundState;
		unsigned int m_updateFlags;
		int m_lightingState;

		float m_FPS = 0;
		float m_deltaTime = 0;
		float m_timePrev = 0;
		float m_fps_disp_counter = 0;

		float m_horizontalAngle = 0;
		float m_verticalAngle = 0;
	};
}
