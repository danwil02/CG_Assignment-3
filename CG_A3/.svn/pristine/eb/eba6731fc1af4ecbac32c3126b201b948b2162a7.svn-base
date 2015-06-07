/*
Computer Graphics Assignment 2

Will Daniels

a1210036

28/03/2015

NOTE: In glm/core/dummy.cpp the definition of "main" is commented out.
NOTE: OOP Structure based on http://in2gpu.com/opengl-3/ tutorial series.
*/

// Platform Specific OpenGL Includes //
#include "OpenGL_headers.h"

// STL Includes // 
#include <iostream>
#include <fstream>
#include <string>

// Utility Includes //
#include "Utils/glm/glm.hpp"
#include "Utils/glm/gtc/matrix_transform.hpp"
#include "Utils/glm/gtc/type_ptr.hpp"

#include "Monitor_GL.h"

#include "Utils/stb_image.h"
#define STB_IMAGE_IMPLEMENTATION

#include "Managers/ShaderManager.h"
#include "Rendering/Models/Model.h"

#include "Init/ContextInfo.h"
#include "Init/FrameBufferInfo.h"
#include "Init/WindowInfo.h"
#include "Init/InitGlew.h"
#include "Init/InitGlut.h"
#include "Managers/SceneManager.h"

using namespace std;
using namespace Init;
using namespace Rendering;
using namespace Models;


int main(int argc, char** argv)
{
	cout << "CG Assignment 2\nWill Daniels\na1210036\n";
	cout << "Compiled " << __TIMESTAMP__ << endl << endl;

	cout << "\nUsage: ./assign2 [./Path/To/Model/Generic.obj] [Option] " << endl;
	cout << "-t\tFor objects with textures (Note: must have textures to run)" << endl <<
		"-g\tFor generic objects with no texture" << endl << 
		"-w\tFor any object if you only wish to see wireframe\n" << endl;

	string objDir = "";
	string manualTexDir = "";
	CMD_OPTIONS option = GENERIC_WITH_LIGHTING;
	string i_str;

	for (int i = 0; i < argc; i++)
	{
		i_str = argv[i];
		if (i_str.find('-') != string::npos)
		{
			if (i_str == "-w") option = WIREFRAME;
			if (i_str == "-t") option = TEXTURED;
			if (i_str == "-g") option = GENERIC_WITH_LIGHTING;
		}
		if (i_str.find(".obj") != string::npos)
		{
			objDir = i_str;
		}
	}

	WindowInfo window(std::string("a1210036"),
					  300, 300, // Start Pos
					  800, 600, // Dim x*y
					  true);    // Resizable
	ContextInfo context;
	FrameBufferInfo fBInfo;
	InitGLUT::init(window, context, fBInfo);

	ListenerInterface* sceneInterface = new Managers::SceneManager(window.width,
																	window.height,
																	option,
																	objDir);
	Init::InitGLUT::setListener(sceneInterface);

	InitGLUT::run();

	return 0;
}


/*
Models::ObjModels* gameModels;
Managers::ShaderManager* g_shaderManager;
GLuint g_program;
GLint totalm;*/
/*
void render(void) {

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
glBindVertexArray(gameModels->getModel("triangle1"));
glUseProgram(g_program);

glDrawArrays(GL_TRIANGLES, 0, 3);
glutSwapBuffers();
}

void closeFunction(){

std::cout << "GLUT:\t Finished" << std::endl;
glutLeaveMainLoop();
}

void init(){

//glEnable(GL_DEPTH_TEST);

//load and compile shaders
g_shaderManager = new Managers::ShaderManager();
g_shaderManager->createShader("minimal", "Shaders/minimal.vert",
"Shaders/minimal.frag");
g_program = g_shaderManager->getShaderHandle("minimal");

gameModels = new Models::ObjModels();
gameModels->createTriangle("triangle1", g_shaderManager->getShaderHandle("minimal"));
}*/

/* main() ... 
cout << "CG Assignment 2\nWill Daniels\na1210036\n";
cout << "Compiled " << __TIMESTAMP__ << endl;


glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(500, 500);
glutInitWindowSize(800, 600);

#ifdef __APPLE__
glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
#else
glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
#endif

glutCreateWindow("Object Viewer a1210036");
glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);


// Initialize GLEW
glewExperimental = true; // Needed for core profile
if (glewInit() != GLEW_OK) {
fprintf(stderr, "Failed to initialize GLEW\n");
return -1;
}

glEnable(GL_DEPTH_TEST);
glFrontFace(GL_CCW);

init();

// Display Callbacks
glutDisplayFunc(render);
//glutIdleFunc(render);
glutCloseFunc(closeFunction);
glutMainLoop();

delete g_shaderManager;
*/
