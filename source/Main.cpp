#include <iostream>
#include "Chip-8.h"
#include <chrono>
#include "SdlClass.h"
#include <Windows.h> // for FreeConsole function.


int main(int argc, char *argv[]) {
	SdlClass* platform = new SdlClass("Alpay's Chip-8 Emulator (AC-8)", VIDEO_WIDTH * 10, VIDEO_HEIGHT * 10, VIDEO_WIDTH, VIDEO_HEIGHT);
	Chip8* chip8 = new Chip8;
	ASKGAME:
	std::cout << "Type the file name you wish to load" << std::endl;
	char gameName[64];
	std::cin.getline(gameName, 64);
	if (!chip8->loadRom(gameName))
	{
		std::cout << "Cannot find the game" << std::endl;
		Sleep(3000);
		goto ASKGAME;
	}
	else FreeConsole(); chip8->paused = false;
	int videoPitch = sizeof(chip8->video[0]) * VIDEO_WIDTH;

	auto lastCycleTime = std::chrono::high_resolution_clock::now();
	bool quit = false;

	while (!quit)
	{
		quit = platform->Input(chip8->keypad, chip8);

		auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();
		if (dt > 5) // Decrease the number to make games faster
		{
			lastCycleTime = currentTime;

			chip8->cycles();

			platform->Update(chip8->video, videoPitch);
		}
	}
	delete platform;
	delete chip8;
	return 0;
}
