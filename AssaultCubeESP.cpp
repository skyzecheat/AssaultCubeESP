#include "Header.h"
#include <iostream>
#include <Windows.h>

int main()
{
    int Players;
    color = CreateSolidBrush(RGB(255, 0, 255));

    HWND hwnd = FindWindowA(NULL, "AssaultCube");

    if (!hwnd) {
        std::cout << "window not found" << std::endl;
    }
    else
    {
        std::cout << "window found" << std::endl;
    }


    HTDC = GetDC(hwnd);

    DWORD pID;
    GetWindowThreadProcessId(hwnd, &pID);
    if (!pID)
    {
        std::cout << "not found pID" << std::endl;
    }
    else
    {
        std::cout << "process id : " << pID << std::endl;
    }

    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, false, pID);

    DWORD baseaddress = GetModuleBaseAddress(pID, L"ac_client.exe");
    std::cout << "base address: " << baseaddress << std::endl;

    DWORD entitybase = baseaddress + entitybaseaddress;
    DWORD playernumberaddress = baseaddress + numberofplayersaddress;


    ReadProcessMemory(handle, (LPVOID)playernumberaddress, &Players, 4, 0);
    float viewmatrix[16];
    DWORD entitytemp;
    DWORD entitylast;

    while (true)
    {
        for (int a = 1; a <= Players; a++)
        {
            ReadProcessMemory(handle, (LPVOID)(baseaddress + viewmatrixaddress), &viewmatrix, sizeof(viewmatrix), 0);
            ReadProcessMemory(handle, (LPVOID)(entitybase), &entitytemp, 4, 0);
            ReadProcessMemory(handle, (LPVOID)(entitytemp + a * 4), &entitylast, 4, 0);
            ReadProcessMemory(handle, (LPVOID)(entitylast + offsetx[0]), &enemyb.x, 4, 0);
            ReadProcessMemory(handle, (LPVOID)(entitylast + offsety[0]), &enemyb.y, 4, 0);
            ReadProcessMemory(handle, (LPVOID)(entitylast + offsetz[0]), &enemyb.z, 4, 0);
            ReadProcessMemory(handle, (LPVOID)(entitylast + headx[0]), &enemyh.x, 4, 0);
            ReadProcessMemory(handle, (LPVOID)(entitylast + heady[0]), &enemyh.y, 4, 0);
            ReadProcessMemory(handle, (LPVOID)(entitylast + headz[0]), &enemyh.z, 4, 0);
            ESP(enemyb, enemyh, viewmatrix);
        }
    }

}

