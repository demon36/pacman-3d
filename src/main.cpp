#include "Application Manager/ApplicationManager.h"

int main(void)
{
	//Specify OpenGL version as 3.3
	int openGLMajorVersion = 2;
	int openGLMinorVersion = 1;

	//Unique object for the application manager
	std::unique_ptr<ApplicationManager> appManager (new ApplicationManager(openGLMajorVersion,openGLMinorVersion));
	
	// Initialize the window providing its width and height

	HWND desktop = GetDesktopWindow();
	RECT screensize;
	GetWindowRect(desktop, &screensize);

	int WindowSizeWidth = screensize.right;//width;
	int WindowSizeHeight = screensize.bottom;// height;
	if (appManager->InitalizeApplication(WindowSizeWidth, WindowSizeHeight) == true)
	{
		appManager->StartMainLoop();
		appManager->CloseApplication();
	}
	
}