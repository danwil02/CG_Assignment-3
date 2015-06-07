#ifndef LISTENERINTERFACE_H
#define LISTENERINTERFACE_H

namespace Init
{

	class ListenerInterface
	{
	public:
		virtual ~ListenerInterface() = 0;

		// Drawing functions
		virtual void notifyBeginFrame() = 0;
		virtual void notifyDisplayFrame() = 0;
		virtual void notifyEndFrame() = 0;
		virtual void notifyReshape( int width,
									int height,
									int previous_width,
									int previous_height) = 0;
		virtual void notifyKeyboardEvent(unsigned char key, int x, int y) = 0;
		virtual void notifyKeyboardReleaseEvent(unsigned char key, int x, int y) = 0;
		virtual void notifySpecialKeyEvent(int key, int x, int y) = 0;
		virtual void notifySpecialKeyReleaseEvent(int key, int x, int y) = 0;
		virtual void notifyMouseButton(int button, int state, int x, int y) = 0;
		virtual void notifyMouseMovement(int x, int y) = 0;
		virtual void notifyPassiveMouseMovement(int x, int y) = 0;

	};

	inline ListenerInterface::~ListenerInterface()
	{
		//implementation of pure virtual destructor
	}
}

#endif