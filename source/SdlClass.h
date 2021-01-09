#pragma once


#include <cstdint>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class SdlClass
{
public:
	SdlClass(const char* title, int width, int height, int textureW, int textureH);
	~SdlClass();
	void Update(const void* buffer, int pitch);
	bool Input(uint8_t* keys);
private:
	SDL_Window* window{};
	SDL_Renderer* renderer{};
	SDL_Texture* texture{};
};


