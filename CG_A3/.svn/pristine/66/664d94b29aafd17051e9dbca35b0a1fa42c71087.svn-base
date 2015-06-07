#ifndef FRAMEBUFFERINFO_H
#define FRAMEBUFFERINFO_H

#include "../OpenGL_headers.h"

namespace Init
{
	struct FrameBufferInfo
	{
		unsigned int displayFlags;
		bool msaa;

		FrameBufferInfo()
		{
			#ifdef __APPLE__    
				displayFlags = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE;
			#else
				displayFlags = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
			#endif
				msaa = false;
		}

		FrameBufferInfo(bool color, bool alpha, bool depth, bool stencil, bool msaa)
		{
			displayFlags = GLUT_DOUBLE; //this is a must
			if (color)
				displayFlags |= GLUT_RGBA;
			if (alpha)
				displayFlags |= GLUT_ALPHA;
			if (depth)
				displayFlags |= GLUT_DEPTH;
			if (stencil)
				displayFlags |= GLUT_STENCIL;
			if (msaa)
				displayFlags |= GLUT_MULTISAMPLE;
			this->msaa = msaa;
			#ifdef __APPLE__
				displayFlags |= GLUT_3_2_CORE_PROFILE;
			#endif
		}
	};
}

#endif