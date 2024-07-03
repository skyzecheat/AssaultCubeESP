#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <gdiplus.h>
#include <math.h>
#include <iostream>
#include <TlHelp32.h>
using namespace std;
typedef struct
{
    float x, y, z, w;
} Vec4;

typedef struct
{
    float x, y, z;
} Vec3;

typedef struct
{
	float x, y;
} Vec2;



Vec2 vScreen, vHead;
Vec3 enemyb, enemyh;
HDC HTDC;
HBRUSH color;



void DrawFilledRect(int x, int y, int w, int h, HBRUSH color);
void DrawBorderBox(int x, int y, int w, int h, int thickness);
DWORD offsetx[1] = { 0x28 };
DWORD offsety[1] = { 0x2C };
DWORD offsetz[1] = { 0x30 };
DWORD headx[1] = { 0x4 };
DWORD heady[1] = { 0x8 };
DWORD headz[1] = { 0xc };
DWORD entitybaseaddress = 0x187C10;
DWORD numberofplayersaddress = 0x187C18;
DWORD viewmatrixaddress= 0x17AFE0;
DWORD GetModuleBaseAddress(DWORD procId, const wchar_t* modName)

{

	DWORD modBaseAddr = 0;

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

	if (hSnap != INVALID_HANDLE_VALUE)

	{

		MODULEENTRY32 modEntry;

		modEntry.dwSize = sizeof(modEntry);

		if (Module32First(hSnap, &modEntry))

		{

			do

			{

				if (!_wcsicmp(modEntry.szModule, modName))

				{

					modBaseAddr = (DWORD)modEntry.modBaseAddr;

					break;

				}

			} while (Module32Next(hSnap, &modEntry));

		}

	}

	CloseHandle(hSnap);

	return modBaseAddr;

}
DWORD pointerveoffset(int PointerLevel, HANDLE hProcHandle, DWORD Offsets[], DWORD BaseAddress)

{

	DWORD pointer = BaseAddress;

	DWORD pTemp;

	DWORD pointerAddr;

	for (int i = 0; i < PointerLevel; i++)

	{

		if (i == 0)

		{

			ReadProcessMemory(hProcHandle, (LPCVOID)pointer, &pTemp, 4, NULL);

		}

		pointerAddr = pTemp + Offsets[i];

		ReadProcessMemory(hProcHandle, (LPCVOID)pointerAddr, &pTemp, 4, NULL);

	}

	return pointerAddr;

}

int WorldToScreen(Vec3 pos, Vec2* screen, float matrix[16], int windowWidth, int windowHeight) 
{
	Vec4 clipCoords;
	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
	clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
	clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
	clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

	if (clipCoords.w < 0.1f)
		return 0;

	Vec3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen->x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen->y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return 1;
}

void ESP(Vec3 EnemyPosition, Vec3 enemyHeadPos, float Matrix[16])
{
	if (WorldToScreen(EnemyPosition, &vScreen, Matrix, 1024, 768))
	{
		if (WorldToScreen(enemyHeadPos, &vHead, Matrix, 1024, 768))
		{
			float height = vHead.y - vScreen.y;
			float width = height / 2.4f;
			DrawBorderBox(vScreen.x - (width / 2), vScreen.y, width, height, 2);
		}
	}
}

void DrawFilledRect(int x, int y, int w, int h, HBRUSH color)
{
	RECT rect = { x, y, x + w, y + h };
	FillRect(HTDC, &rect, color);
}

void DrawBorderBox(int x, int y, int w, int h, int thickness)
{
	DrawFilledRect(x + 2, y, w - 2, thickness, color);
	DrawFilledRect(x, y, thickness, h, color);
	DrawFilledRect((x + w), y, thickness, h, color);
	DrawFilledRect(x, y + h, w + thickness, thickness, color);
}