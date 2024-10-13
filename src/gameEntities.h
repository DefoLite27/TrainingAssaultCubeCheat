#pragma once
#include "maths.h"
#include "memoryService.h"
#include "offsets.h"

class playerEntity
{
public:
	playerEntity(uintptr_t entPointer)
	{
		pointer = entPointer;
		updateInfo();
	}

	int pointer;
	int health = 0;
	Vector3 position_feet;

	void updateInfo()
	{
		Memory mem = Memory(L"ac_client.exe", L"ac_client.exe");
		health = mem.ReadRaw<int>(pointer + entityOffsets::health);
		position_feet = mem.ReadRaw<Vector3>(pointer + entityOffsets::posX);
		float temp = position_feet.z;
		position_feet.z = position_feet.y;
		position_feet.y = temp;
	}
};
class localData
{
public:
	localData()
	{
		updateInfo();
	}

	viewMatrix matrix;

	void updateInfo()
	{
		Memory mem = Memory(L"ac_client.exe", L"ac_client.exe");
		matrix = mem.ReadRaw<viewMatrix>(offsets::ViewMatrix);
	}
};