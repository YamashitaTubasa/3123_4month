#include "RideLight.h"

// windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
	RLFramework* game = new RideLight();

	game->Run();

	delete game;

	return 0;
}