#include <iostream>
#include "Chip-8.h"
#include "SDL.h"
#include <chrono>
#include "SdlClass.h"
#include <Windows.h> // for FreeConsole function.


int main(int argc, char *argv[]) {
	SdlClass platform("Alpay's Chip-8 Emulator (AC-8)", VIDEO_WIDTH * 10, VIDEO_HEIGHT * 10, VIDEO_WIDTH, VIDEO_HEIGHT);
	std::cout << "Type the file name you wish to load" << std::endl;
	Chip8 chip8;
	char gameName[32];
	std::cin.getline(gameName, 32);
	if (!chip8.loadRom(gameName))
	{
		std::cout << "Cannot find the game";
		exit(2);
	}
	else FreeConsole();
	int videoPitch = sizeof(chip8.video[0]) * VIDEO_WIDTH;

	auto lastCycleTime = std::chrono::high_resolution_clock::now();
	bool quit = false;

	while (!quit)
	{
		quit = platform.Input(chip8.keypad);

		auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

		if (dt > 10)
		{
			lastCycleTime = currentTime;

			chip8.cycles();

			platform.Update(chip8.video, videoPitch);
		}
	}
	return 0;
}
