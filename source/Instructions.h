#pragma once

#include "Chip-8.h"

void Chip8::OP_00E0() {
	for (int i = 0; i < 2048; i++) video[i] = 0;
	printf("Debug: Display Cleared!");
}

void Chip8::OP_00EE() {
	--stackPointer;
	pc = stack[stackPointer];
}

void Chip8::OP_1nnn() {
	uint16_t addr = opcode & 0x0FFFu;
	pc = addr;
}

void Chip8::OP_2nnn() {
	uint16_t addr = opcode & 0x0FFFu;
	stack[stackPointer] = pc;
	++stackPointer;
	pc = addr;
}

void Chip8::OP_3xkk() {
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t byte = opcode & 0x00FFu;
	if (registers[Vx] == byte) pc += 2;
}

void Chip8::OP_4xkk() {
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t byte = opcode & 0x00FFu;
	if (registers[Vx] != byte) 
	{ 
		pc += 2; 
	}
}

void Chip8::OP_5xy0() {
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (opcode & 0x00F0u) >> 4u;

	if (registers[Vx] == registers[Vy])
	{
		pc += 2;
	}
}

void Chip8::OP_6xkk() {
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t byte = opcode & 0x00FFu;

	registers[Vx] = byte;
}

void Chip8::OP_7xkk() {
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t byte = opcode & 0x00FFu;
	registers[Vx] += byte;
}

void Chip8::OP_8xy0() {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

	registers[vx] = registers[vy];
}

void Chip8::OP_8xy1() {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

	registers[vx] |= registers[vy];
}

void Chip8::OP_8xy2() {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

	registers[vx] &= registers[vy];
}

void Chip8::OP_8xy3() {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x0F0u) >> 4u;

	registers[vx] ^= registers[vy];
}

void Chip8::OP_8xy4() {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

	uint16_t sum = registers[vx] + registers[vy];

	if (sum > 255u) registers[0xF] = 1;
	else registers[0xF] = 0;
	registers[vx] = sum & 0xFFu;
}

void Chip8::OP_8xy5()
{
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (opcode & 0x00F0u) >> 4u;
	if (registers[Vx] > registers[Vy])
	{
		registers[0xF] = 1;
	}
	else
	{
		registers[0xF] = 0;
	}
	registers[Vx] -= registers[Vy];
}

void Chip8::OP_8xy6() {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	registers[0xF] = (registers[vx] & 0x1u);
	registers[vx] >>= 1;
}

void Chip8::OP_8xy7() {
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;
	if (registers[vy] > registers[vx]) registers[0xF] = 1;
	else registers[0xF] = 0;
}

void Chip8::OP_8xyE() {
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	registers[0xF] = (registers[Vx] & 0x80u) >> 7u;
	registers[Vx] <<= 1;
}

void Chip8::OP_9xy0() {
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (opcode & 0x00F0u) >> 4u;
	if (registers[Vx] != registers[Vy]) pc += 2;
}

void Chip8::OP_Annn() {
	uint16_t address = opcode & 0x0FFFu;
	index = address;
}

void Chip8::OP_Bnnn() {
	uint16_t adress = opcode & 0x0FFFu;
	pc = registers[0] + adress;
}

void Chip8::OP_Cxkk()
{
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t byte = opcode & 0x00FFu;

	registers[Vx] = randByte(randGen) & byte;
}

void Chip8::OP_Dxyn() {
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;
	uint8_t Vy = (opcode & 0x00F0u) >> 4u;
	uint8_t height = opcode & 0x000Fu;

	uint8_t xPos = registers[Vx] % VIDEO_WIDTH;
	uint8_t yPos = registers[Vy] % VIDEO_HEIGHT;

	registers[0xF] = 0;
	
	for (unsigned int row = 0; row < height; ++row)
	{
		uint8_t spriteByte = memory[index + row];
		for (unsigned int col = 0; col < 8; col++)
		{
			uint8 spritePixel = spriteByte & (0x80u >> col);
			uint32_t* screenPixel = &video[(yPos + row) * VIDEO_WIDTH + (xPos + col)];
			if (spritePixel)
			{
				if (*screenPixel == 0xFFFFFFFF)
				{
					registers[0xF] = 1;
				}
				*screenPixel ^= 0xFFFFFFFF;
			}
		}
	}
}

void Chip8::OP_Ex9E()
{
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t key = registers[vx];

	if (keypad[key]) pc += 2;
}

void Chip8::OP_ExA1()
{
	uint8 vx = (opcode & 0x0F00u) >> 8u;
	uint8 key = registers[vx];

	if (!keypad[key]) pc += 2;
}

void Chip8::OP_Fx07()
{
	uint8_t vx = (opcode & 0x0F00u) >> 8u;
	registers[vx] = delayTimer;
}

void Chip8::OP_Fx0A()
{
	uint8 vx = (opcode & 0x0F00u) >> 8u;
	if (keypad[0]) registers[vx] = 0;
	else if (keypad[1]) registers[vx] = 1;
	else if (keypad[2]) registers[vx] = 2;
	else if (keypad[3]) registers[vx] = 3;
	else if (keypad[4]) registers[vx] = 4;
	else if (keypad[5]) registers[vx] = 5;
	else if (keypad[6]) registers[vx] = 6;
	else if (keypad[7]) registers[vx] = 7;
	else if (keypad[8]) registers[vx] = 8;
	else if (keypad[9]) registers[vx] = 9;
	else if (keypad[10]) registers[vx] = 10;
	else if (keypad[11]) registers[vx] = 11;
	else if (keypad[12]) registers[vx] = 12;
	else if (keypad[13]) registers[vx] = 13;
	else if (keypad[14]) registers[vx] = 14;
	else if (keypad[15]) registers[vx] = 15;
	else pc -= 2;
}

void Chip8::OP_Fx15()
{
	uint8 vx = (opcode & 0x0F00u) >> 8u;
	delayTimer = registers[vx];
}

void Chip8::OP_Fx18()
{
	uint8 vx = (opcode & 0x0F00u) >> 8u;
	soundTimer = registers[vx];
}

void Chip8::OP_Fx1E()
{
	uint8 vx = (opcode & 0x0F00u) >> 8u;
	index += registers[vx];
}

void Chip8::OP_Fx29()
{
	uint8 vx = (opcode & 0x0F00u) >> 8u;
	uint8 digit = registers[vx];
	index = 80 + (5 * digit); // 80 = Fontset start adress
}

void Chip8::OP_Fx33()
{
	uint8 vx = (opcode & 0x0F00u) >> 8u;
	uint8 value = registers[vx];
	memory[index + 2] = value % 10;
	value /= 10;
	memory[index + 1] = value % 10;
	value /= 10;
	memory[index] = value % 10;
}

void Chip8::OP_Fx55()
{
	uint8 vx = (opcode & 0x0F00u) >> 8u;
	for (uint8 i = 0; i <= vx; ++i)
	{
		memory[index + i] = registers[i];
	}
}

void Chip8::OP_Fx65()
{
	uint8_t Vx = (opcode & 0x0F00u) >> 8u;

	for (uint8_t i = 0; i <= Vx; ++i)
	{
		registers[i] = memory[index + i];
	}
}

