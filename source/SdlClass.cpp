#include "SdlClass.h"
#include "SDL.h"

SdlClass::SdlClass(const char* title, int width, int height, int textureW, int textureH)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, textureW, textureH);
}

SdlClass::~SdlClass()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
 
void SdlClass::Update(const void* buffer, int pitch)
{
	SDL_UpdateTexture(texture, nullptr, buffer, pitch);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}

bool SdlClass::Input(uint8_t* key)
{
	bool quit = false;
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
		{
			quit = true;
		} break;
		case SDL_KEYDOWN:
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE: quit = true; break;
			case SDLK_x: key[0] = true; break;
			case SDLK_1: key[1] = true; break;
			case SDLK_2: key[2] = true; break;
			case SDLK_3: key[3] = true; break;
			case SDLK_q: key[4] = true; break;
			case SDLK_w: key[5] = true; break;
			case SDLK_e: key[6] = true; break;
			case SDLK_a: key[7] = true; break;
			case SDLK_s: key[8] = true; break;
			case SDLK_d: key[9] = true; break;
			case SDLK_z: key[0xA] = true; break;
			case SDLK_c: key[0xB] = true; break;
			case SDLK_4: key[0xC] = true; break;
			case SDLK_r: key[0xD] = true; break;
			case SDLK_f: key[0xE] = true; break;
			case SDLK_v: key[0xF] = true; break;
			}
		} break;
		case SDL_KEYUP:
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_x: key[0] = false; break;
			case SDLK_1: key[1] = false; break;
			case SDLK_2: key[2] = false; break;
			case SDLK_3: key[3] = false; break;
			case SDLK_q: key[4] = false; break;
			case SDLK_w: key[5] = false; break;
			case SDLK_e: key[6] = false; break;
			case SDLK_a: key[7] = false; break;
			case SDLK_s: key[8] = false; break;
			case SDLK_d: key[9] = false; break;
			case SDLK_z: key[0xA] = false; break;
			case SDLK_c: key[0xB] = false; break;
			case SDLK_4: key[0xC] = false; break;
			case SDLK_r: key[0xD] = false; break;
			case SDLK_f: key[0xE] = false; break;
			case SDLK_v: key[0xF] = false; break;
			}
		} break;
		}
	}
	return quit;
}
