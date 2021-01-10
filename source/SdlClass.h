#pragma once


#include <cstdint>
#include "Chip-8.h"


struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class SdlClass
{
public:
	SdlClass(const char* title, int width, int height, int textureW, int textureH);
	~SdlClass();
	void Update(const void* buffer, int pitch);
	bool Input(uint8_t* keys, Chip8* ch8 = nullptr);
private:
	SDL_Window* window{};
	SDL_Renderer* renderer{};
	SDL_Texture* texture{};
};


