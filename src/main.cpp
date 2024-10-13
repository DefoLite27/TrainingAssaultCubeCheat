#include "visuals.h"
#include "memoryService.h"
#include "gameEntities.h"
#include "offsets.h"
#include "winFunctions.h"

#include <vector>

int main()
{
	WinFunc win;
	win.GetInfo("AssaultCube");
	win.Print();

	Memory mem = Memory(L"ac_client.exe", L"ac_client.exe");
	Maths math = Maths();
	visualClass visual = visualClass();
	ShowWindow(FindWindowA("ConsoleWindowClass", NULL), true);
	visual.TargetWnd = FindWindow(0, L"AssaultCube");
	visual.HDC_Desktop = GetDC(visual.TargetWnd);
	visual.SetupDrawing(visual.HDC_Desktop, visual.TargetWnd);

	playerEntity player = playerEntity(mem.Read<uintptr_t>(offsets::entityLocal));//mem.Read<uintptr_t>(offsets::entityLocal);
	//std::cout << mem.ReadRaw<int>(mem.Read<int>(offsets::entityLocal) + entityOffsets::health);
	localData locData = localData();
	//std::cout << player.health;

	visual.posTrack(Vector3(150, 0, 150), player, locData, math);
	/*
	std::vector<playerEntity> entList;

	uintptr_t entListPtr = mem.Read<uintptr_t>(offsets::entityList);
	for (int i = 1; i < 10; i++)
	{
		playerEntity ent = mem.Read<uintptr_t>(mem.Read<uintptr_t>(entListPtr) + (i*4));
		entList.push_back(ent);
	}
	playerEntity player = playerEntity(mem.Read<uintptr_t>(offsets::entityLocal));
	localData locData = localData();

	visual.esp(entList, player, locData, math);
	*/
}