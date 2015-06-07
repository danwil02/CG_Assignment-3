#ifndef INITGLUT_H
#define INITGLUT_H

#include "WindowInfo.h"
#include "FrameBufferInfo.h"
#include "ContextInfo.h"
#include "InitGlew.h"
#include "ListenerInterface.h"
#include <time.h>

#include <iostream>

namespace Init
{
	class InitGLUT{

		public:             //use the structures from Part II
			static void init(const WindowInfo& window,
							 const ContextInfo& context,
							 const FrameBufferInfo& framebufferInfo);

			static void run();//called from outside
			static void close();

			void enterFullscreen();
			void exitFullscreen();

			//used to print info about GL
			static void printOpenGLInfo(const WindowInfo& windowInfo,
										const ContextInfo& context);

			// Scene Manager Interface //
			static void setListener(ListenerInterface*& iListener);
		private:
			static void idleCallback();
			static void displayCallback();
			static void reshapeCallback(int width, int height);
			static void closeCallback();
			static void specialFuncCallBack(int key, int x, int y);
			static void specialKeyReleaseCallBack(int key, int x, int y);
			static void keyBoardCallBack(unsigned char key, int x, int y);
			static void keyBoardReleaseCallBack(unsigned char key, int x, int y);

			static void mouseButtonCallBack(int button, int state, int x, int y);
			static void mouseMovementCallBack(int x, int y);
			static void mousePassiveMovementCallBack(int x, int y);

			// Scene Manager Interface //
			static ListenerInterface* m_listener;
			static WindowInfo m_windowInformation;
	};
}

#endif
