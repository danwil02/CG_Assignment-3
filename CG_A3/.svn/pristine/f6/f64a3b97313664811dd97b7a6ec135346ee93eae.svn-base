#include "InitGlew.h"

#include <stdio.h>
#include <iostream>
#include "../OpenGL_headers.h"

namespace Init
{
	void InitGlew::Init()
	{
		// Initialize GLEW
		glewExperimental = true; // Needed for core profile
		if (glewInit() != GLEW_OK) 
		{
			fprintf(stderr, "GLEW:\tFAILED\n");
		}
		else
		{
			std::cout << "GLEW:\tInitialised\n";
		}
	}
}