#ifndef TEXTURE_MANAGER
#define TEXTURE_MANAGER


#include "raylib.h"

class TextureManager
{
public:	
	void PrepareGameplayTextures();
	Texture2D GetSoldierTexture();
	Texture2D GetHelicopterLeftTexture();
	Texture2D GetHelicopterRightTexture();
	Texture2D GetDeadTexture();
	Texture2D GetPlayerBaseTexture();
	Texture2D GetPlayerCannonTexture();
	void UnloadGameplayTextures();
private:	
	Texture2D helicopterLeftTexture;
	Texture2D helicopterRightTexture;
	Texture2D soldierTexture;
	Texture2D deadTexture;
	Texture2D playerBaseTexture;
	Texture2D playerCannonTexture;
};

#endif // !TEXTURE_MANAGER