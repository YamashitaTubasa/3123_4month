#include "RideLight.h"

// windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	RLFramework* game = new RideLight();

	game->Run();

	delete game;

	return 0;
}