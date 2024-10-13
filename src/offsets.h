#pragma once
#include <iostream>
#include <Windows.h>
//constexpr ::std::ptrdiff_t
namespace offsets {
	constexpr int entityLocal = 0x18AC00;
	constexpr int entityList = 0x18AC04;
	constexpr int ViewMatrix = 0x57DFD0;
}

namespace entityOffsets {
	constexpr int posX = 0x28;//just get this one for full position
	constexpr int poxY = 0x30;
	constexpr int posZ = 0x2C;

	constexpr int health = 0xEC;
}