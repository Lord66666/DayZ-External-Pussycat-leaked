#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <cstdint>

struct _globals
{
	const char* dwProcessName = "DayZ_x64.exe";
	DWORD dwProcessId = NULL;
	uint64_t dwProcess_Base = NULL;

	HANDLE handle;

	HWND OverlayWnd;
	HWND TargetWnd;

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	bool console;

	const char lTargetWindow[256] = "DayZ";
	LPCSTR lWindowName;

	uint64_t Base;
	uint64_t World;

	int timeset;

	bool crosshair;

	int tab_index = 0;
	bool menu;

	bool GrassDisable = true;
	bool SetDay;
	bool NightVision;

	bool DrawFov = true;
	bool SilentAim = false;
	bool LegitSilentAim;
	bool PlayerAim = false;

	const char* bonepos[3] = { "Head", "Body", "Legs" };
	int bone = 0;

	DWORD keys[7] = { VK_LMENU, VK_SHIFT, VK_CONTROL, VK_LBUTTON, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2 };
	const char* keyItems[7] = { "LAlt", "LShift", "LCtrl", "LMouse", "RMouse", "Mouse4", "Mouse5" };
	int AimKey = 0;

	DWORD MENUkeys[7] = { VK_TAB, VK_INSERT, VK_HOME, VK_PRIOR, VK_NEXT, VK_END, VK_RSHIFT };
	const char* keyMENU[7] = { "TAB", "INSERT", "HOME", "PageUP", "PageDown", "END", "RShift" };
	int MENUKey = 0;

	const char* legit[3] = { "Stand", "Sit", "Lay" };
	int legitcheck = 0;

	const char* size[3] = { "Big", "Medium", "Small" };
	int sizecheck = 0;

	const char* box[3] = { "Box", "CornerBox", "FrameBox" };
	int boxcheck = 0;

	const char* boxZ[3] = { "Box", "CornerBox", "FrameBox" };
	int boxcheckZ = 0;

	const char* tracer[3] = { "Top", "Middle", "Bottom" };
	int tracercheck = 0;

	bool weaponinventory;

	bool deadplayer;
	bool ZombieAim;
	bool AnimalsAim;

	bool drawboxz;
	bool drawbox;

	bool weapon;
	bool guns;
	bool shotguns;
	bool pistols;
	bool optics;
	bool magazines;
	bool bayonet;
	bool ammo;
	bool buttstock;
	bool explosives;
	bool melee;
	bool allattachments;

	bool food;

	bool medical;

	bool caritems;

	bool clothing;
	bool gloves;
	bool pants;
	bool shoes;
	bool tops;
	bool vests;
	bool masks;
	bool heads;
	bool headgear;
	bool belts;
	bool allclothings;
	bool backpacks;

	bool inventoryItem;

	bool builditems;

	bool storage;
	bool showstorage;

	bool allitems;

	int itemsdistance = 300;
	int zombiedistance = 100;
	int playerdistance = 1000;

	bool getquality;

	bool compass;
	bool servername;
	bool playerscount;

	bool iteminhands = true;
	bool playersinventory;
	bool playernames;
	bool PlayerEsp = true;
	bool PlayerEspSkeleton;
	bool ZombieEspSkeleton;
	bool playertracer;
	bool carinventory;
	bool carattachments;
	bool ZombieEsp = true;
	bool AnimalsEsp;
	bool CarEsp = true;

	int distancesilent = 500;
	int radius = 180;

	bool City_Esp;
	bool city;
	bool military;
	bool tier3;
	bool tier4;
	bool tier2;
	bool others;

	uint64_t getCamera;
	uint64_t GetLocalPlayer;
	uint64_t localPlayerVisualState;

	uint64_t bskeleton;
	uint64_t bvisual;
	uint64_t banim;
	uint64_t bmatrix;
};


extern LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef struct _player_t
{
	std::uint64_t EntityPtr;
	std::uint64_t TableEntry;
	int NetworkID;
} player_t;

typedef struct _zombie_t
{
	std::uint64_t EntityPtr;
	std::uint64_t TableEntry;
	int NetworkID;
} zombie_t;

typedef struct _player_taim
{
	std::uint64_t EntityPtr;
	std::uint64_t TableEntry;
	int NetworkID;
} _player_taim;

typedef struct _zombie_taim
{
	std::uint64_t EntityPtr;
	std::uint64_t TableEntry;
} _zombie_taim;

typedef struct _item_t
{
	std::uint64_t ItemPtr;
	std::uint64_t ItemTable;
} item_t;

typedef struct _item_tslow
{
	std::uint64_t ItemPtrslow;
	std::uint64_t ItemTableslow;
} item_tslow;

extern _globals globals;