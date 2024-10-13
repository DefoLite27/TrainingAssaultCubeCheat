#pragma once
#include <windows.h>
#include <sstream>
#include <iostream>

#include "maths.h"
#include "gameEntities.h"

class visualClass
{
public:

	HBRUSH hBrushEnemy = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH hBrushTeam = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH hBrushNeutral = CreateSolidBrush(RGB(255, 255, 255));
	COLORREF enemyColor = RGB(255, 0, 0);
	COLORREF teamColor = RGB(0, 0, 255);
	COLORREF neutralColor = RGB(255, 255, 255);

	HDC HDC_Desktop;
	HFONT Font;
	HWND TargetWnd;
	HWND Handle;
	COLORREF TextCOLOR;
	RECT m_Rect;

	void SetupDrawing(HDC hDesktop, HWND handle)
	{
		visualClass::HDC_Desktop = hDesktop;
		visualClass::Handle = handle;
		visualClass::TextCOLOR = RGB(0, 255, 0);
	}
	void DrawFilledRect(int x, int y, int w, int h, HBRUSH brushColor)
	{
		RECT rect = { x,y,x + w,y + h };
		FillRect(visualClass::HDC_Desktop, &rect, brushColor);
	}
	void DrawBorderBox(int x, int y, int w, int h, int thickness, HBRUSH brushColor)
	{
		DrawFilledRect(x, y, w, thickness, brushColor);
		DrawFilledRect(x, y, thickness, h, brushColor);
		DrawFilledRect((x + w), y, thickness, h, brushColor);
		DrawFilledRect(x, y + h, w + thickness, thickness, brushColor);
	}
	void DrawESP(int x, int y, float distance, int health, HBRUSH hBrush, COLORREF Pen)
	{
		int width = 1100 / distance;	//1100

		int height = 2000 / distance;	//2000

		DrawBorderBox(x - (width / 2), y - height, width, height, 1, hBrush);
	}

	DWORD WINAPI posTrack(Vector3 pos, playerEntity player, localData locData, Maths math)
	{
		GetWindowRect(FindWindow(NULL, L"AssaultCube"), &m_Rect);

		while (true)
		{
			locData.updateInfo();
			player.updateInfo();

			//std::cout << player.position_feet.x << " " << pos.x << "\n";
			Vector3 plrPos = player.position_feet;
			//std::cout << plrPos.x << " " << plrPos.y << " " << plrPos.z << " " << pos.x << " " << pos.y << " " << pos.z << "\n";
			if (math.WorldToScreen(pos, math.screen, locData.matrix, 800, 600))
			{
				//std::cout << math.GetDistance3D(player.position_feet, pos) << "\n";
				DrawESP(math.screen.x, math.screen.y, math.GetDistance3D(plrPos, pos), 100, visualClass::hBrushEnemy, visualClass::enemyColor);
			}
			//Sleep(1000);
		}
	}

	DWORD WINAPI esp(std::vector<playerEntity> entities, playerEntity player, localData locData,  Maths math)
	{
		GetWindowRect(FindWindow(NULL, L"AssaultCube"), &m_Rect);

		while (true)
		{
			player.updateInfo();

			for (int i = 0; i < 9; i++)
			{
				playerEntity ent = entities[i];
				ent.updateInfo();

				if (math.WorldToScreen(ent.position_feet, math.screen, locData.matrix, 800, 600) && ent.health > 0)
				{
					DrawESP(math.screen.x, math.screen.y, math.GetDistance3D(player.position_feet, ent.position_feet), ent.health, visualClass::hBrushEnemy, visualClass::enemyColor);
				}
			}
		}
	}

};