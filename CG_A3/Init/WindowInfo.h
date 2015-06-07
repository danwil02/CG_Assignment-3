#ifndef WINDOWINFO_H
#define WINDOWINFO_H

#include <string>

namespace Init
{
	struct WindowInfo
	{
		std::string windowName;
		int width, height;
		int posOnScreen_x, posOnScreen_y;
		bool isReshapable;

		WindowInfo()
		{
			windowName = "a1210036";
			width = 800;
			height = 600;
			posOnScreen_x = 300;
			posOnScreen_y = 300;
			isReshapable = true;
		}

		WindowInfo(std::string name,
				   int startPos_x,
				   int startPos_y,
				   int in_width,
				   int in_height,
				   bool reshapable): windowName(name),
									 posOnScreen_x(startPos_x),
									 posOnScreen_y(startPos_y),
									 width(in_width),
									 height(in_height),
									 isReshapable(reshapable){}

	};
}

#endif