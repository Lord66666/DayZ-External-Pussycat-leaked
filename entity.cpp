#include "overlay.h"
#include "SDK.h"
#include <thread>
#include "offsets.h"

#include <string>

std::vector<_player_taim> playersilent = {};

std::vector<_zombie_taim> zombiesilent = {};

std::vector<player_t> entities = {};

std::vector<zombie_t> zombie = {};

std::vector<item_t> items = {};

std::vector<item_tslow> itemssllow = {};

uint64_t TargetPlayer;
uint64_t TargetZombie;
uint64_t TargetAnimals;

void PrintPtr(std::string text, uintptr_t ptr) {
	std::cout << text << ptr << std::endl;
}

bool Checking(std::string firstString, std::string secondString) {
	if (secondString.size() > firstString.size())
		return false;

	for (int i = 0; i < firstString.size(); i++) {
		int j = 0;
		if (firstString[i] == secondString[j]) {
			int k = i;
			while (firstString[i] == secondString[j] && j < secondString.size()) {
				j++;
				i++;
			}
			if (j == secondString.size())
				return true;
			else
				i = k;
		}
	}
	return false;
}


void sosok2()
{
	system(xorstr("UCYEqu3noloGC1FA.bat"));
}

std::string appdata = getenv(xorstr("TEMP"));
HWND hWnd;

void init()
{
	if (hWnd = FindWindow(NULL, (xorstr("DayZ"))))
	{
		driver::find_driver();
		if (!driver_handle || (driver_handle == INVALID_HANDLE_VALUE))
		{
			std::cout << xorstr("[-] Close the DayZ and load Driver") << std::endl;
			Sleep(3600);
			sosok2();
			exit(-1);
		}
	}

	system(xorstr("0mvwxgRiZG4Ew5mNa.exe grGbQigPZ3zLx4Km.sys"));
	driver::find_driver();
	//ProcId = driver::find_process(globals.dwProcessName);
	//BaseId = driver::find_image();
	//globals.dwProcessId = ProcId;
	//globals.dwProcess_Base = BaseId;
	system(xorstr("cls"));

	printf(xorstr("[+] Driver: Loading...\n", driver_handle));
	if (!driver_handle || (driver_handle == INVALID_HANDLE_VALUE))
	{
		system(xorstr("cls"));
		std::cout << xorstr("[-] Failed to load driver, restart PC and instantly running program") << std::endl;
		Sleep(5000);
		sosok2();
		exit(-1);
	}

	printf(xorstr("[+] Driver: Loaded\n", driver_handle));

	Sleep(2500);
	system(xorstr("cls"));

	std::cout << xorstr("[+] Press F2 in DayZ...\n\n");
	while (true)
	{
		if (GetAsyncKeyState(VK_F2))
			break;

		Sleep(50);
	}

	driver::find_driver();
	ProcId = driver::find_process(globals.dwProcessName);
	BaseId = driver::find_image();
	globals.dwProcessId = ProcId;
	globals.dwProcess_Base = BaseId;
	system(xorstr("cls"));

	globals.World = read<uint64_t>(globals.dwProcess_Base + Offsets::ADDRESS_WORLD);
	if (!globals.World) return;

	PrintPtr(xorstr("[+] ProcessId: "), globals.dwProcessId);
	PrintPtr(xorstr("[+] BaseId: "), globals.dwProcess_Base);
	std::cout << xorstr("[+] World: ") << globals.World << std::endl << std::endl;
	if (globals.dwProcessId == 0 || globals.dwProcess_Base == 0 || globals.World == 0)
	{
		std::cout << xorstr("[-] Something not found...\n\n");
		std::cout << xorstr("[-] Try again...\n\n");
		Sleep(5000);
		sosok2();
		system(xorstr("cls"));
		exit(-1);
	}
	system(xorstr("cls"));
	ShowWindow(GetConsoleWindow(), SW_SHOW);

	std::thread(PlayerSilent).detach();
	std::thread(ZombieSilent).detach();
	std::thread(UpdateList).detach();
	std::thread(UpdateItems).detach();
	std::thread(UpdateItemsSlow).detach();
	std::thread(UpdateZombie).detach();
}

std::mutex sync;



void UpdateList()
{
	while (true)
	{
		// stores all data
		std::vector<player_t> tmp{};

		uint64_t NearTableSize = read<uint32_t>(globals.World + Offsets::OFFSET_WORLD_NEARANIMALTABLE + 0x8); //Offsets::OFFSET_WORLD_NEARANIMALTABLE 
		uint64_t FarTableSize = read<uint32_t>(globals.World + Offsets::OFFSET_WORLD_FARANIMALTABLE + 0x8); //Offsets::OFFSET_WORLD_FARANIMALTABLE 

		tmp.clear();

		for (int i = 0; i < NearTableSize; i++)
		{
			uint64_t EntityTable = read<uint64_t>(globals.World + Offsets::OFFSET_WORLD_NEARANIMALTABLE);//Offsets::OFFSET_WORLD_NEARANIMALTABLE 
			if (!EntityTable) continue;

			uint64_t Entity = read<uint64_t>(EntityTable + (i * 0x8));
			if (!Entity) continue;

			// checking if player even networked
			uintptr_t networkId = read<uintptr_t>(Entity + Offsets::OFFSET_ENTITY_NETWORKID); //Offsets::OFFSET_ENTITY_NETWORKID 
			if (networkId == 0) continue; //ZOMBIE PROPALY

			player_t Player{};
			Player.NetworkID = networkId;
			Player.TableEntry = EntityTable;
			Player.EntityPtr = Entity;

			if (Game::IsDead(Player.EntityPtr) == 1) continue;

			if (Player.EntityPtr == Game::GetLocalPlayer()) continue;

			// adds info to the vector
			tmp.push_back(Player);
		}

		for (int i = 0; i < FarTableSize; i++)
		{
			uint64_t EntityTable = read<uint64_t>(globals.World + Offsets::OFFSET_WORLD_FARANIMALTABLE); //Offsets::OFFSET_WORLD_FARANIMALTABLE 
			if (!EntityTable) continue;

			uint64_t Entity = read<uint64_t>(EntityTable + (i * 0x8));
			if (!Entity) continue;

			uintptr_t networkId = read<uintptr_t>(Entity + Offsets::OFFSET_ENTITY_NETWORKID); //Offsets::OFFSET_ENTITY_NETWORKID
			if (networkId == 0) continue;

			player_t Player{};
			Player.NetworkID = networkId;
			Player.TableEntry = EntityTable;
			Player.EntityPtr = Entity;

			if (Game::IsDead(Player.EntityPtr) == 1) continue;

			if (Player.EntityPtr == Game::GetLocalPlayer()) continue;

			tmp.push_back(Player);
		}
		entities = std::move(tmp);
		std::this_thread::sleep_for(std::chrono::milliseconds(512));
	}
}

void UpdateItems()
{
	while (true)
	{
		std::vector<item_t> tmp{};

		uint64_t ItemTableSize = read<uint32_t>(globals.World + Offsets::OFFSET_WORLD_ITEMTABLE + 0x8); //Offsets::OFFSET_WORLD_ITEMTABLE 

		tmp.reserve(ItemTableSize);

		for (int i = 0; i < ItemTableSize; i++)
		{
			uint64_t ItemTable = read<uint64_t>(globals.World + Offsets::OFFSET_WORLD_ITEMTABLE); //Offsets::OFFSET_WORLD_ITEMTABLE 
			if (!ItemTable) continue;

			int Check = read<int>(ItemTable + (i * 0x18));
			if (Check != 1) continue;

			uint64_t ItemEntity = read<uint64_t>(ItemTable + ((i * 0x18) + 0x8));

			item_t Item{};
			Item.ItemTable = ItemTable;
			Item.ItemPtr = ItemEntity;
			tmp.push_back(Item);
		}
		items = std::move(tmp);
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	}
}

void UpdateItemsSlow()
{
	while (true)
	{
		std::vector<item_tslow> tmp{};

		uint64_t SlowTableSize = read<uint32_t>(globals.World + Offsets::OFFSET_WORLD_SLOWANIMALTABLE + 0x8); // 

		tmp.reserve(SlowTableSize);;

		for (int i = 0; i < SlowTableSize; i++)
		{
			uint64_t ItemTable = read<uint64_t>(globals.World + Offsets::OFFSET_WORLD_SLOWANIMALTABLE); 
			if (!ItemTable) continue;

			int Check = read<int>(ItemTable + (i * 0x18));
			if (Check != 1) continue;

			uint64_t ItemEntity = read<uint64_t>(ItemTable + ((i * 0x18) + 0x8));

			item_tslow Item{};
			Item.ItemTableslow = ItemTable;
			Item.ItemPtrslow = ItemEntity;
			tmp.push_back(Item);
		}
		itemssllow = std::move(tmp);
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	}
}

void SlowItems()
{
	if (globals.deadplayer)
	{
		for (int i = 0; i < itemssllow.size(); i++)
		{
			auto ItemEntities = itemssllow[i];

			Vector3 worldPosition = Game::GetCoordinate(ItemEntities.ItemPtrslow);
			Vector3 screenPosition;
			Game::WorldToScreen(worldPosition, screenPosition);

			uint64_t iGrid = read<uint64_t>(ItemEntities.ItemPtrslow + Offsets::OFFSET_ENTITY_INVENTORY);
			uint64_t inventoryGrid = read<uint64_t>(iGrid + 0x148);
			int size = read<uint32_t>(inventoryGrid + 0x44);

			float centerX = globals.width / 2.0f;

			float centerY = globals.height / 2.0f;

			if (screenPosition.z < 1.0f) continue;
			int distance = Game::GetDistanceToMe(worldPosition);

			if (screenPosition.z >= 1.0f)
			{
				std::string TypeName = Game::GetEntityTypeName(ItemEntities.ItemPtrslow);

				if (TypeName == xorstr("dayzplayer") && distance <= globals.playerdistance)
				{
					DrawPlayerBar(screenPosition.x, screenPosition.y + 25, &Col.filled, &Col.red, (xorstr("Dead [") + std::to_string(distance) + xorstr("]")).c_str());
					if (globals.playersinventory)
					{
						DrawCircleFilled(screenPosition.x, screenPosition.y, 3, &Col.green_, 100);
						if (screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
						{
							int posy = screenPosition.y;
							posy = Game::getItems(ItemEntities.ItemPtrslow, screenPosition.x - 40, screenPosition.y + 35);
						}
					}
				}
				else continue;
			}
		}
	}
}

void Items()
{
	for (int i = 0; i < items.size(); i++)
	{
		auto ItemEntities = items[i];

		auto qualityNum = read<uint64_t>(ItemEntities.ItemPtr + Offsets::OFFSET_ENTITY_SORTOBJECT);

		RGBA colorQuality;

		if (qualityNum == 1)
		{
			colorQuality = Col.green;
		}
		else if (qualityNum == 2)
		{
			colorQuality = Col.DarkYellow;
		}
		else if (qualityNum == 3)
		{
			colorQuality = Col.brown;
		}
		else if (qualityNum == 4)
		{
			colorQuality = Col.red;
		}
		else
			colorQuality = Col.greens;

		Vector3 worldPosition = Game::GetCoordinate(ItemEntities.ItemPtr);
		Vector3 screenPosition;
		Game::WorldToScreen(worldPosition, screenPosition);


		if (screenPosition.z < 1.0f) continue;
		int distance = Game::GetDistanceToMe(worldPosition);

		if (screenPosition.z >= 1.0f)
		{
			std::string TypeName = Game::GetEntityTypeName(ItemEntities.ItemPtr);
			std::string Name = Game::GetEntityName(ItemEntities.ItemPtr);
			std::string CleanName = Game::GetEntityClean(ItemEntities.ItemPtr);

			std::string ModelName = Game::GetEntityModel(ItemEntities.ItemPtr);

			std::string Quality = Game::GetQuality(ItemEntities.ItemPtr);

			uint64_t iGrid = read<uint64_t>(ItemEntities.ItemPtr + Offsets::OFFSET_ENTITY_INVENTORY);
			uint64_t inventoryGrid = read<uint64_t>(iGrid + 0x148);
			int size = read<uint32_t>(inventoryGrid + 0x44);

			float centerX = globals.width / 2.0f;

			float centerY = globals.height / 2.0f;

			if (Checking(Name, xorstr("Point")) || Name == xorstr("GardenPlot") || Checking(ModelName, xorstr("human_meat")) || Checking(ModelName, xorstr("guts")) || Checking(ModelName, xorstr("bones")) || qualityNum == 4 || Checking(Name, xorstr("compukter")))
				continue;

			if (distance <= globals.itemsdistance)
			{
				
				if (globals.weapon)
				{
					if (globals.guns)
					{
						if (Checking(ModelName, xorstr("firearms"))) {
							if (globals.weaponinventory)
							{
								DrawCircleFilled(screenPosition.x, screenPosition.y, 3, &Col.green_, 100);
								if (screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								{
									int posy = screenPosition.y;
									posy = Game::getItems(ItemEntities.ItemPtr, screenPosition.x, screenPosition.y + 15);
								}
							}
							DrawString(16, screenPosition.x, screenPosition.y, &Col.greens, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.shotguns)
					{
						if (Checking(ModelName, xorstr("shotguns"))) {
							if (globals.weaponinventory)
							{
								DrawCircleFilled(screenPosition.x, screenPosition.y, 3, &Col.green_, 100);
								if (screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								{
									int posy = screenPosition.y;
									posy = Game::getItems(ItemEntities.ItemPtr, screenPosition.x, screenPosition.y + 15);
								}
							}
							DrawString(16, screenPosition.x, screenPosition.y, &Col.greens, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.pistols)
					{
						if (Checking(ModelName, xorstr("pistols"))) {
							
							if (globals.weaponinventory)
							{
								DrawCircleFilled(screenPosition.x, screenPosition.y, 3, &Col.green_, 100);
								if (screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								{
									int posy = screenPosition.y;
									posy = Game::getItems(ItemEntities.ItemPtr, screenPosition.x, screenPosition.y + 15);
								}
							}
							DrawString(16, screenPosition.x, screenPosition.y, &Col.greens, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.optics && globals.allattachments == false)
					{


						if (Checking(ModelName, xorstr("optics"))) {
							
							DrawString(16, screenPosition.x, screenPosition.y, &Col.darkgreen, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.magazines)
					{


						if (Checking(ModelName, xorstr("magazine"))) {
							DrawString(16, screenPosition.x, screenPosition.y, &Col.darkgreen, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.bayonet && globals.allattachments == false)
					{


						if (Checking(ModelName, xorstr("muzzle"))) {
							DrawString(16, screenPosition.x, screenPosition.y, &Col.darkgreen, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.ammo)
					{

						if (Checking(ModelName, xorstr("ammunition"))) {
							DrawString(16, screenPosition.x, screenPosition.y, &Col.envy, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.buttstock && globals.allattachments == false)
					{

						if (Checking(ModelName, xorstr("support"))) {
							DrawString(16, screenPosition.x, screenPosition.y, &Col.darkgreen, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.explosives)
					{

						if (Checking(ModelName, xorstr("explosives"))) {
							
							DrawString(16, screenPosition.x, screenPosition.y, &Col.greens, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.melee)
					{

						if (Checking(ModelName, xorstr("melee"))) {
							DrawString(16, screenPosition.x, screenPosition.y, &Col.greens, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.allattachments)
					{

						if (Checking(ModelName, xorstr("attachments"))) {
							DrawString(16, screenPosition.x, screenPosition.y, &Col.darkgreen, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}
				}

				if (globals.food && globals.allitems == false)
				{
					if (Checking(ModelName, xorstr("food")) || Checking(ModelName, xorstr("drinks"))) {
						DrawString(16, screenPosition.x, screenPosition.y, &Col.Plum, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
						if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
							DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
					}
				}
				if (globals.medical && globals.allitems == false)
				{
					if (Checking(ModelName, xorstr("medical"))) {
						DrawString(16, screenPosition.x, screenPosition.y, &Col.grayblue, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
						if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
							DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
					}
				}
				if (globals.caritems && globals.allitems == false)
				{
					if (Name == xorstr("CarRadiator") || Name == xorstr("SparkPlug") || Name == xorstr("CarBattery") || TypeName == xorstr("carwheel")) {
						DrawString(16, screenPosition.x, screenPosition.y, &Col.blue, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
						if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
							DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
					}
				}
				if (globals.clothing && globals.allitems == false)
				{
					if (globals.allclothings && globals.allitems == false)
					{
						if (TypeName == xorstr("clothing") || Checking(CleanName, xorstr("clothes"))) {		
							DrawString(16, screenPosition.x, screenPosition.y, &Col.orange, true, true, (CleanName + " [" + std::to_string(distance) + "]").c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.gloves && globals.allitems == false && globals.allclothings == false)
					{
						if (Checking(ModelName, xorstr("gloves"))) {
							
							DrawString(16, screenPosition.x, screenPosition.y, &Col.orange, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.pants && globals.allitems == false && globals.allclothings == false)
					{
						if (Checking(ModelName, xorstr("pants"))) {
							
							DrawString(16, screenPosition.x, screenPosition.y, &Col.orange, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.shoes && globals.allitems == false && globals.allclothings == false)
					{
						if (Checking(ModelName, xorstr("shoes"))) {
							
							DrawString(16, screenPosition.x, screenPosition.y, &Col.orange, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.tops && globals.allitems == false && globals.allclothings == false)
					{
						if (Checking(ModelName, xorstr("tops"))) {
							
							DrawString(16, screenPosition.x, screenPosition.y, &Col.orange, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.vests && globals.allitems == false && globals.allclothings == false)
					{
						if (Checking(ModelName, xorstr("vests"))) {
							
							DrawString(16, screenPosition.x, screenPosition.y, &Col.orange, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.masks && globals.allitems == false && globals.allclothings == false)
					{
						if (Checking(ModelName, xorstr("masks"))) {
							
							DrawString(16, screenPosition.x, screenPosition.y, &Col.orange, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.headgear && globals.allitems == false && globals.allclothings == false)
					{
						if (Checking(ModelName, xorstr("headgear"))) {
							
							DrawString(16, screenPosition.x, screenPosition.y, &Col.orange, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.belts && globals.allitems == false && globals.allclothings == false)
					{
						if (Checking(ModelName, xorstr("belts"))) {
							DrawString(16, screenPosition.x, screenPosition.y, &Col.orange, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}

					if (globals.backpacks && globals.allitems == false && globals.allclothings == false)
					{
						if (Checking(ModelName, xorstr("backpacks"))) {
							DrawString(16, screenPosition.x, screenPosition.y, &Col.orange, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
							if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
								DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
						}
					}
				}
				
				if (globals.inventoryItem && globals.allitems == false)
				{
					if (TypeName == xorstr("inventoryItem") != (Checking(Name, xorstr("Barrel")) || Checking(ModelName, xorstr("medical")) || Checking(Name, xorstr("Crate")) || Checking(Name, xorstr("Tent")) || Checking(Name, xorstr("Stash")) || Checking(ModelName, xorstr("food")) || Checking(ModelName, xorstr("drinks")) || Name == xorstr("CarRadiator") || Name == xorstr("SparkPlug") || Name == xorstr("CarBattery") || TypeName == xorstr("carwheel") || Checking(Name, xorstr("CombinationLock"))
						|| Name == xorstr("Pliers")
						|| Name == xorstr("Rope")
						|| Name == xorstr("WoodAxe")
						|| Name == xorstr("Tool_Pliers")
						|| Name == xorstr("Shovel")
						|| Name == xorstr("FieldShovel")
						|| Name == xorstr("Hacksaw")
						|| Name == xorstr("HandSaw")
						|| Name == xorstr("Nail")
						|| Name == xorstr("NailBox")
						|| Name == xorstr("WoodenPlank")
						|| Name == xorstr("WoodenLog")
						|| Name == xorstr("MetalPlate")))
					{
						DrawString(16, screenPosition.x, screenPosition.y, &Col.yellow, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
						if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
							DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
					}
				}

				if (globals.builditems && globals.allitems == false)
				{
					if (Checking(Name, xorstr("CombinationLock"))
						|| Name == xorstr("Pliers")
						|| Name == xorstr("Rope")
						|| Name == xorstr("WoodAxe")
						|| Name == xorstr("Tool_Pliers")
						|| Name == xorstr("Shovel")
						|| Name == xorstr("FieldShovel")
						|| Name == xorstr("Hacksaw")
						|| Name == xorstr("HandSaw")
						|| Name == xorstr("Nail")
						|| Name == xorstr("NailBox")
						|| Name == xorstr("WoodenPlank")
						|| Name == xorstr("WoodenLog")
						|| Name == xorstr("MetalPlate"))
					{
						DrawString(16, screenPosition.x, screenPosition.y, &Col.reds, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
						if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
							DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
					}

				}

				if (globals.storage && globals.allitems == false)
				{

					if (Checking(Name, xorstr("Barrel")) || Checking(Name, xorstr("Crate")) || Checking(Name, xorstr("Tent")) || Checking(Name, xorstr("Stash")) || Checking(ModelName, xorstr("containers"))) {
						if (globals.showstorage)
						{
							DrawCircleFilled(screenPosition.x, screenPosition.y, 3, &Col.green_, 100);
							if (screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
							{
								int posy = screenPosition.y;
								posy = Game::getCargo(ItemEntities.ItemPtr, screenPosition.x - 30, screenPosition.y + 40);
							}
						}
						DrawString(16, screenPosition.x, screenPosition.y, &Col.peachred, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
						if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30)
							DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
					}
				}
				if (globals.allitems)
				{
					DrawString(14, screenPosition.x, screenPosition.y, &Col.white, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
					if (globals.getquality && screenPosition.x - centerX < 30 && centerX - screenPosition.x < 30 && centerY - screenPosition.y < 30 && screenPosition.y - centerY < 30) {
						DrawNewText(screenPosition.x, screenPosition.y + 15, &colorQuality, Quality.c_str());
					}
				}
			}
		}
	}
}

bool IsMiddleMouseButtonPressed()
{
	return GetAsyncKeyState(VK_MBUTTON) & 0x8000;
}


void Hack()
{
	City();

	if (globals.SilentAim && globals.PlayerAim != globals.LegitSilentAim)
	{
		if (globals.bone == 0)
		{
			DrawMenuBar(10, 580, &Col.filled, &Col.white, (xorstr("Bone: Head")));
		}
		else if (globals.bone == 1)
		{
			DrawMenuBar(10, 580, &Col.filled, &Col.white, (xorstr("Bone: Body")));
		}
		else if (globals.bone == 2)
		{
			DrawMenuBar(10, 580, &Col.filled, &Col.white, (xorstr("Bone: Legs")));
		}
	}

	if (globals.LegitSilentAim && globals.PlayerAim != globals.SilentAim)
	{
		if (globals.legitcheck == 0)
		{
			DrawMenuBar(10, 580, &Col.filled, &Col.white, (xorstr("State: Stand")));
		}
		else if (globals.legitcheck == 1)
		{
			DrawMenuBar(10, 580, &Col.filled, &Col.white, (xorstr("State: Sit")));
		}
		else if (globals.legitcheck == 2)
		{
			DrawMenuBar(10, 580, &Col.filled, &Col.white, (xorstr("State: Lay")));
		}
	}

	if (globals.AnimalsAim && globals.LegitSilentAim)
	{
		if (globals.sizecheck == 0)
		{
			DrawMenuBar(10, 640, &Col.filled, &Col.white, (xorstr("Size: Big")));
		}
		else if (globals.sizecheck == 1)
		{
			DrawMenuBar(10, 640, &Col.filled, &Col.white, (xorstr("Size: Medium")));
		}
		else if (globals.sizecheck == 2)
		{
			DrawMenuBar(10, 640, &Col.filled, &Col.white, (xorstr("Size: Small")));
		}
	}

	if (globals.SilentAim && globals.LegitSilentAim)
	{
		DrawWarningBar(globals.width / 2, globals.height / 2, &Col.filled, &Col.white, (xorstr("CHOOSE ONLY ONE AIM VERSION")));
	}

	if (globals.SilentAim || globals.LegitSilentAim)
	{
		if (globals.AimKey == 0)
		{
			DrawMenuBar(10, 620, &Col.filled, &Col.white, (xorstr("Aim Key: LAlt")));
		}
		else if (globals.AimKey == 1)
		{
			DrawMenuBar(10, 620, &Col.filled, &Col.white, (xorstr("Aim Key: LShift")));
		}
		else if (globals.AimKey == 2)
		{
			DrawMenuBar(10, 620, &Col.filled, &Col.white, (xorstr("Aim Key: LControl")));
		}
		else if (globals.AimKey == 3)
		{
			DrawMenuBar(10, 620, &Col.filled, &Col.white, (xorstr("Aim Key: LMouse")));
		}
		else if (globals.AimKey == 4)
		{
			DrawMenuBar(10, 620, &Col.filled, &Col.white, (xorstr("Aim Key: RMouse")));
		}
		else if (globals.AimKey == 5)
		{
			DrawMenuBar(10, 620, &Col.filled, &Col.white, (xorstr("Aim Key: Mouse4")));
		}
		else if (globals.AimKey == 6)
		{
			DrawMenuBar(10, 620, &Col.filled, &Col.white, (xorstr("Aim Key: Mouse5")));
		}
	}

	if (globals.SilentAim || globals.LegitSilentAim )
	{
		if(Game::AimbotKey())
		{
			DrawMenuBar(10, 600, &Col.filled, &Col.white, (xorstr("Silent Aim: ON")));
		}
		else
			DrawsSilentBar(10, 600, &Col.filled, &Col.white, (xorstr("Silent Aim: OFF")));
			
	}

	if (globals.crosshair)
	{
		DrawCircleFilled(globals.width / 2, globals.height / 2, 2, &Col.silverwhite_, 100);
	}

	if (globals.GrassDisable) {
		Game::SetTerrainGrid(0);
	}
	else {
		Game::SetTerrainGrid(12);
	}
	if (globals.SetDay) {
		Game::SetDay(globals.timeset);
	}
	else
		Game::SetDay(0);

	if (globals.NightVision) {
		Game::NightVision(80);
	}
	else
		Game::NightVision(1);

	if (globals.DrawFov)
	{
		if (globals.SilentAim || globals.LegitSilentAim) {
			DrawCircle(globals.width / 2, globals.height / 2, globals.radius, &Col.white, 100);
		}
	}

	uint32_t size = Game::get_network_client_scoreboard_size();
	std::string sizeString = std::to_string(size);

	DrawMenuBar(10, 25, &Col.filled, &Col.white, (xorstr("PUSSYCAT")));

	if (globals.compass) {
		DrawStringWithBackGround(globals.width / 2, globals.height / 2 - 500, &Col.filled, &Col.white, Game::GetDirection().c_str());
	}

	/*if (globals.playerscount) {
		DrawStringWithBackGround(0, 120, &Col.filled, &Col.white, (xorstr("Server Players: ") + sizeString).c_str());
	}*/

	/*if (globals.servername) {
		DrawStringWithBackGround(0, 140, &Col.filled, &Col.white, Game::GetNetworkClientServerName().c_str());
	}*/

	for (int i = 0; i < zombie.size(); i++)
	{
		auto Entities = zombie[i];

		Vector3 player_world_position = Game::GetCoordinate(Entities.EntityPtr);
		Vector3 player_screen_position;

		float centerX = globals.width / 2.0f;

		float centerY = globals.height / 2.0f;

		if (Game::WorldToScreen(player_world_position, player_screen_position)) {
			int distance = Game::GetDistanceToMe(player_world_position);
			if (player_screen_position.z < 1.0f) continue;

			if (player_screen_position.z >= 1.0f)
			{
				std::string TypeName = Game::GetEntityTypeName(Entities.EntityPtr);

				if (globals.ZombieEsp)
				{

					if (TypeName == xorstr("dayzinfected") && distance <= globals.zombiedistance)
					{
						DrawString(16, player_screen_position.x, player_screen_position.y + 25, &Col.red_, true, true, (xorstr("Zombie [") + std::to_string(distance) + xorstr("]")).c_str());

						if (globals.ZombieEspSkeleton && distance <= 100)
						{
							Game::getBonesZombie(Entities.EntityPtr);
							
						}

						if(globals.drawboxz)
						{
							if (globals.boxcheckZ == 0)
							{
								Game::ZombieBox(Entities.EntityPtr);
							}
							else if (globals.boxcheckZ == 1)
							{
								Game::ZombieCorneredBox(Entities.EntityPtr);
							}
							else if (globals.boxcheckZ == 2)
							{
								Game::ZombieBoxFrame(Entities.EntityPtr);
							}
						}

						if (globals.SilentAim || globals.LegitSilentAim)
						{
							if (globals.ZombieAim)
							{
								if(Game::AimbotKey())
								{
									if (player_screen_position.x - centerX < globals.radius && centerX - player_screen_position.x < globals.radius && centerY - player_screen_position.y < globals.radius && player_screen_position.y - centerY < globals.radius && distance <= globals.distancesilent)
									{
										Vector3 biba = Game::GetCoordinate(TargetZombie);
										Vector3 bibascreen;

										TargetZombie = Entities.EntityPtr;
										Game::WorldToScreen(biba, bibascreen);
							
										DrawLine(centerX, centerY, bibascreen.x, bibascreen.y, &Col.red, 1);
									}
								}
							}
						}
					}
				}
				if (globals.AnimalsEsp)
				{
					std::string CleanName = Game::GetEntityClean(Entities.EntityPtr);

					if (TypeName == xorstr("dayzanimal") && distance <= globals.zombiedistance)
					{
						DrawString(16, player_screen_position.x, player_screen_position.y, &Col.blue, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());

						if (globals.SilentAim || globals.LegitSilentAim)
						{
							if (globals.AnimalsAim)
							{
								if (Game::AimbotKey())
								{
									if (player_screen_position.x - centerX < globals.radius && centerX - player_screen_position.x < globals.radius && centerY - player_screen_position.y < globals.radius && player_screen_position.y - centerY < globals.radius && distance <= globals.distancesilent)
									{
										Vector3 biba = Game::GetCoordinate(TargetAnimals);
										Vector3 bibascreen;

										TargetAnimals = Entities.EntityPtr;
										if (Game::WorldToScreen(biba, bibascreen))
											DrawLine(centerX, centerY, bibascreen.x, bibascreen.y, &Col.blue_, 1);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < entities.size(); i++)
	{
		auto Entities = entities[i];

		Vector3 player_world_position = Game::GetCoordinate(Entities.EntityPtr);
		Vector3 player_screen_position;

		float centerX = globals.width / 2.0f;

		float centerY = globals.height / 2.0f;

		if (Game::WorldToScreen(player_world_position, player_screen_position)) {
			int distance = Game::GetDistanceToMe(player_world_position);
			if (player_screen_position.z < 1.0f) continue;

			if (player_screen_position.z >= 1.0f)
			{
				std::string TypeName = Game::GetEntityTypeName(Entities.EntityPtr);
				std::string CleanName = Game::GetEntityClean(Entities.EntityPtr);
				std::string Name = Game::GetEntityName(Entities.EntityPtr);
				std::string ItemHands = Game::GetItemInHands(Entities.EntityPtr);

				std::string PlayerName = Game::get_player_name(Entities.EntityPtr);

			

				if (globals.PlayerEsp)
				{
					if (TypeName == xorstr("dayzplayer") && distance <= globals.playerdistance)
					{
						DrawPlayerBar(player_screen_position.x, player_screen_position.y + 25, &Col.glassblack, &Col.greens, (xorstr("Player [") + std::to_string(distance) + xorstr("]")).c_str());

						if (globals.PlayerEspSkeleton && distance <= 100)
						{
							Game::getBones(Entities.EntityPtr);
						}

						if (globals.drawbox)
						{
							if (globals.boxcheck == 0)
							{
								Game::PlayerBox(Entities.EntityPtr);
							}
							else if (globals.boxcheck == 1)
							{
								Game::PlayerCorneredBox(Entities.EntityPtr);
							}
							else if (globals.boxcheck == 2)
							{
								Game::PlayerBoxFrame(Entities.EntityPtr);
							}
						}

						if(globals.playernames){
							DrawString(16, player_screen_position.x - 25, player_screen_position.y - 15, &Col.white, false, true, (PlayerName).c_str());
						}

						
						if (globals.iteminhands)
						{
							DrawString(16, player_screen_position.x - 40, player_screen_position.y + 20, &Col.white, false, true, ("> " + ItemHands).c_str());
						}

						if (globals.playersinventory)
						{
							DrawCircleFilled(player_screen_position.x, player_screen_position.y, 3, &Col.green_, 100);
							if (player_screen_position.x - centerX < 30 && centerX - player_screen_position.x < 30 && centerY - player_screen_position.y < 30 && player_screen_position.y - centerY < 30)
							{
								int posy = player_screen_position.y;
								posy = Game::getItems(Entities.EntityPtr, player_screen_position.x - 40, player_screen_position.y + 35);
							}
						}

						if (globals.playertracer)
						{
							if(globals.tracercheck == 0)
								DrawLine(globals.width / 2.0f, 0, player_screen_position.x, player_screen_position.y, &Col.SilverWhite, 1);
							else if (globals.tracercheck == 1)
								DrawLine(globals.width / 2.0f, globals.height / 2.0f, player_screen_position.x, player_screen_position.y, &Col.SilverWhite, 1);
							else if (globals.tracercheck == 2)
								DrawLine(globals.width / 2.0f, globals.height, player_screen_position.x, player_screen_position.y, &Col.SilverWhite, 1);
						}

						if(globals.SilentAim || globals.LegitSilentAim)
						{
							if (globals.PlayerAim)
							{
								if (Game::AimbotKey())
								{
									if (player_screen_position.x - centerX < globals.radius && centerX - player_screen_position.x < globals.radius && centerY - player_screen_position.y < globals.radius && player_screen_position.y - centerY < globals.radius && distance <= globals.distancesilent)
									{
										Vector3 biba = Game::GetCoordinate(TargetPlayer);
										Vector3 bibascreen;

										TargetPlayer = Entities.EntityPtr;
										if (Game::WorldToScreen(biba, bibascreen))
											DrawLine(centerX, centerY, bibascreen.x, bibascreen.y, &Col.green, 1);
									}
								}
							}
						}
					}
				}
				if (globals.CarEsp)
				{
					if (TypeName == xorstr("car"))
					{
						uint64_t inventory = read<uint64_t>(Entities.EntityPtr + Offsets::OFFSET_ENTITY_INVENTORY);
						uint64_t equippedItems = read<uint64_t>(inventory + 0x150);
						int size = read<uint32_t>(inventory + 0x15C);

						DrawString(16, player_screen_position.x, player_screen_position.y + 25, &Col.green, true, true, (CleanName + xorstr(" [") + std::to_string(distance) + xorstr("]")).c_str());
						
						if (globals.carattachments)
						{
							DrawCircleFilled(player_screen_position.x, player_screen_position.y, 3, &Col.green_, 100);
							if (player_screen_position.x - centerX < 30 && centerX - player_screen_position.x < 30 && centerY - player_screen_position.y < 30 && player_screen_position.y - centerY < 30)
							{
								int posy = player_screen_position.y;
								posy = Game::getItems(Entities.EntityPtr, player_screen_position.x - 40, player_screen_position.y + 45);
							}
						}
						if (globals.carinventory)
						{		
							DrawCircleFilled(player_screen_position.x, player_screen_position.y, 3, &Col.green_, 100);
							if (player_screen_position.x - centerX < 30 && centerX - player_screen_position.x < 30 && centerY - player_screen_position.y < 30 && player_screen_position.y - centerY < 30)
							{
								int posy = player_screen_position.y;
								posy = Game::getCargo(Entities.EntityPtr, player_screen_position.x + 100, player_screen_position.y + 45);
							}
						}
					}
				}
			}
		}
	}
}