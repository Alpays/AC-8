#pragma once

#ifndef CHIP8_H
#define CHIP8_H

#include <cstdint>
#include <fstream>
#include <chrono>
#include <random>

typedef uint8_t uint8;
typedef uint16_t uint16;

const unsigned int VIDEO_HEIGHT = 32;
const unsigned int VIDEO_WIDTH = 64;

class Chip8
{	
public: // Functions
	Chip8();
	~Chip8();
	bool loadRom(const char* fileName);
	void cycles();
	bool isRunning();
public: // Variables
	uint8 registers[16]{};
	uint8 memory[4096];
	uint16 index{};
	uint16 pc{};
	uint16 stack[16]{};
	uint8 stackPointer{};
	uint8 delayTimer{};
	uint8 soundTimer{};
	uint8 keypad[16]{};
	uint32_t video[64 * 32]{}; 
	uint16 opcode{};
	bool running{};
	std::default_random_engine randGen;
	std::uniform_int_distribution<uint16_t> randByte;
public: // Instructions
	void OP_00E0();
	void OP_00EE();
	void OP_1nnn();
	void OP_2nnn();
	void OP_3xkk();
	void OP_4xkk();
	void OP_5xy0();
	void OP_6xkk();
	void OP_7xkk();
	void OP_8xy0();
	void OP_8xy1();
	void OP_8xy2();
	void OP_8xy3();
	void OP_8xy4();
	void OP_8xy5();
	void OP_8xy6();
	void OP_8xy7();
	void OP_8xyE();
	void OP_9xy0();
	void OP_Annn();
	void OP_Bnnn();
	void OP_Cxkk();
	void OP_Dxyn();
	void OP_Ex9E();
	void OP_ExA1();
	void OP_Fx07();
	void OP_Fx0A();
	void OP_Fx15();
	void OP_Fx18();
	void OP_Fx1E();
	void OP_Fx29();
	void OP_Fx33();
	void OP_Fx55();
	void OP_Fx65();
public:
	void Table0()
	{
		((*this).*(table0[opcode & 0x000Fu]))();
	}

	void Table8()
	{
		((*this).*(table8[opcode & 0x000Fu]))();
	}

	void TableE()
	{
		((*this).*(tableE[opcode & 0x000Fu]))();
	}

	void TableF()
	{
		((*this).*(tableF[opcode & 0x00FFu]))();
	}

	void OP_NULL()
	{}
	typedef void (Chip8::* Chip8Func)();
	Chip8Func table[0xF + 1]{ &Chip8::OP_NULL };
	Chip8Func table0[0xE + 1]{ &Chip8::OP_NULL };
	Chip8Func table8[0xE + 1]{ &Chip8::OP_NULL };
	Chip8Func tableE[0xE + 1]{ &Chip8::OP_NULL };
	Chip8Func tableF[0x65 + 1]{ &Chip8::OP_NULL };
};


#endif 
