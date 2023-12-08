#pragma once
#include "driver.h"
#include "Vector.h"
#include "globals.h"
#include "xorstr.h"
#include "offsets.h"
  
#define OFF_PVISUAL      0x1D0  //0x1C0
#define OFF_SKELETON_PLAYER     0x830   //0x810
#define OFF_SKELETON_ZOMBIE     0x698   //0x678

namespace Game
{
	bool AimbotKey()
	{
		return GetAsyncKeyState(globals.keys[globals.AimKey]);
	}

	static std::string ReadString(uint64_t address, size_t size)
	{
		if (!address || size > 1024)
			return "";

		char string[1024] = "";
		return read_array(address, string, size) ? std::string(string) : "";
	};

	std::string ReadArmaString(uint64_t address)
	{

		char pBuffer[256];

		int length = read<int>(address + Offsets::OFFSET_LENGTH);

		auto text = ReadString(address + Offsets::OFFSET_TEXT, length);


		return text.c_str();
	}

	void SetTerrainGrid(float value) {
		write<float>(globals.World + Offsets::OFFSET_WORLD_GRASS, value);
	}

	void SetDay(float value) {
		write<float>(globals.World + Offsets::OFFSET_WORLD_DAY, globals.timeset);
	}

	void NightVision(float value)
	{
		write<float>(globals.World + Offsets::OFFSET_WORLD_RENDERER, value);
	}

	uint64_t NearEntityTable()
	{
		return read<uint64_t>(globals.World + Offsets::OFFSET_WORLD_NEARANIMALTABLE); //Offsets::OFFSET_WORLD_NEARANIMALTABLE 
	}

	uint32_t NearEntityTableSize()
	{
		return read<uint32_t>(globals.World + Offsets::OFFSET_WORLD_NEARANIMALTABLE + 0x8); // //Offsets::OFFSET_WORLD_NEARANIMALTABLE 
	}

	uint64_t GetEntity(uint64_t PlayerList, uint64_t SelectedPlayer)
	{
		// Sorted Object
		return read<uint64_t>(PlayerList + SelectedPlayer * Offsets::OFFSET_SORTEDOBJECT_ENTITY);
	}

	std::string GetEntityName(uint64_t Entity)
	{
		return ReadArmaString(read<uint64_t>(read<uint64_t>(Entity + Offsets::OFFSET_ENTITY_RENDERENTITYTYPE) + Offsets::OFFSET_ENTITYTYPE_TYPENAME)).c_str(); //Offsets::OFFSET_ENTITY_RENDERENTITYTYPE + Offsets::OFFSET_ENTITYTYPE_TYPENAME 
	}

	std::string GetEntityTypeName(uint64_t Entity)
	{
		return ReadArmaString(read<uint64_t>(read<uint64_t>(Entity + Offsets::OFFSET_ENTITY_RENDERENTITYTYPE) + Offsets::OFFSET_ENTITYTYPE_CONFIGNAME)).c_str(); //Offsets::OFFSET_ENTITY_RENDERENTITYTYPE + Offsets::OFFSET_ENTITYTYPE_CONFIGNAME 
	}

	std::string GetEntityClean(uint64_t Entity)
	{
		return ReadArmaString(read<uint64_t>(read<uint64_t>(Entity + Offsets::OFFSET_ENTITY_RENDERENTITYTYPE) + Offsets::OFFSET_ENTITYTYPE_CLEANNAME)).c_str(); //Offsets::OFFSET_ENTITY_RENDERENTITYTYPE + Offsets::OFFSET_ENTITYTYPE_CLEANNAME 
	}

	std::string GetEntityModel(uint64_t Entity)
	{
		return ReadArmaString(read<uint64_t>(read<uint64_t>(Entity + Offsets::OFFSET_ENTITY_RENDERENTITYTYPE) + Offsets::OFFSET_ENTITYTYPE_BASETYPE)).c_str(); //Offsets::OFFSET_ENTITY_RENDERENTITYTYPE + Offsets::OFFSET_ENTITYTYPE_MODELNAME  
	}

	uint64_t FarEntityTable()
	{
		return read<uint64_t>(globals.World + Offsets::OFFSET_WORLD_FARANIMALTABLE); //Offsets::OFFSET_WORLD_FARANIMALTABLE 
	}

	uint32_t FarEntityTableSize()
	{
		return read<uint32_t>(globals.World + Offsets::OFFSET_WORLD_FARANIMALTABLE + 0x8);//Offsets::OFFSET_WORLD_FARANIMALTABLE 
	}

	uint64_t GetCameraOn()
	{
		// Camera On 
		return read<uint64_t>(globals.World + Offsets::OFFSET_WORLD_CAMERAON); //Offsets::OFFSET_WORLD_CAMERAON 
	}

	//uint64_t GetLocalPlayer() {
	//	if (globals.GetLocalPlayer == 0) {
	//		uint64_t tmp = read<uint64_t>(read<uint64_t>(globals.World + OFF_WORLD_CAMERA_ON) + 0x8) - 0xA8;
	//		globals.GetLocalPlayer = tmp;
	//		return tmp;
	//	}
	//	else return globals.GetLocalPlayer;

	//}
	//uint64_t GetLocalPlayerVisualState() { // Future Visual State

	//	if (globals.localPlayerVisualState == 0) {
	//		uint64_t tmp = read<uint64_t>(GetLocalPlayer() + OFF_ENTITY_VISUAL_STATE);  //OFF_PLAYER_VISUAL_STATE
	//		globals.localPlayerVisualState = tmp;
	//		return tmp;
	//	}
	//	else return globals.localPlayerVisualState;
	//}

	uint64_t GetLocalPlayer()
	{
		// Sorted Entity Object
		return read<uint64_t>(read<uint64_t>(globals.World + Offsets::OFFSET_WORLD_CAMERAON) + 0x8) - 0xA8; //Offsets::OFFSET_LOCALPLAYER   Offsets::OFFSET_WORLD_PLAYERON
	}

	uint64_t GetLocalPlayerVisualState()
	{
		// Future Visual State
		return read<uint64_t>(GetLocalPlayer() + Offsets::OFFSET_ENTITY_RENDERVISUALSTATE); //Offsets::OFFSET_ENTITY_RENDERVISUALSTATE   Offsets::OFFSET_ENTITY_RENDERVISUALSTATE
	}

	Vector3 GetCoordinate(uint64_t Entity)
	{
		
		if (Entity == GetLocalPlayer())
		{
			return Vector3(read<Vector3>(GetLocalPlayerVisualState() + Offsets::OFFSET_VISUALSTATE_POSITION)); //Offsets::OFFSET_VISUALSTATE_POSITION 
		}

		else
		{
			return  Vector3(read<Vector3>(read<uint64_t>(Entity + Offsets::OFFSET_ENTITY_RENDERVISUALSTATE) + Offsets::OFFSET_VISUALSTATE_POSITION)); //Offsets::OFFSET_ENTITY_RENDERVISUALSTATE  + Offsets::OFFSET_VISUALSTATE_POSITION 
		}
		
	}

	uint64_t GetCamera()
	{

		return read<uint64_t>(globals.World + Offsets::OFFSET_WORLD_CAMERA); //Offsets::OFFSET_WORLD_CAMERA 

	}

	//uint64_t GetCamera() {

	//	if (globals.getCamera == 0) {
	//		uint64_t tmp = read<uint64_t>(globals.World + Offsets::OFFSET_WORLD_CAMERA);
	//		globals.getCamera = tmp;
	//		return tmp;
	//	}
	//	else return globals.getCamera;

	//	//return ReadData<uint64_t>(globals.World + 0x1B8);

	//}

	Vector3 GetInvertedViewTranslation()
	{
		return Vector3(read<Vector3>(GetCamera() + Offsets::OFFSET_CAMERA_VIEWTRANSLATION));
	}
	Vector3 GetInvertedViewRight()
	{
		return Vector3(read<Vector3>(GetCamera() + Offsets::OFFSET_CAMERA_VIEWRIGHT));
	}
	Vector3 GetInvertedViewUp()
	{
		return Vector3(read<Vector3>(GetCamera() + Offsets::OFFSET_CAMERA_VIEWUP));
	}
	Vector3 GetInvertedViewForward()
	{
		return Vector3(read<Vector3>(GetCamera() + Offsets::OFFSET_CAMERA_VIEWFORWARD));
	}

	Vector3 GetViewportSize()
	{
		return Vector3(read<Vector3>(GetCamera() + Offsets::OFFSET_CAMERA_VIEWPORTSIZE));
	}

	Vector3 GetProjectionD1()
	{
		return Vector3(read<Vector3>(GetCamera() + Offsets::OFFSET_CAMERA_PROJECTION_D1));
	}

	Vector3 GetProjectionD2()
	{
		return Vector3(read<Vector3>(GetCamera() + Offsets::OFFSET_CAMERA_PROJECTION_D2));
	}

	std::string GetQuality(uint64_t Entity) {

		auto quality = read<uint64_t>(Entity + Offsets::OFFSET_ENTITY_SORTOBJECT);

		if (quality == 1) return xorstr(" (Worn)");
		if (quality == 2) return xorstr(" (Damaged)");
		if (quality == 3) return xorstr(" (Badly Damaged)");
		if (quality == 4) return xorstr(" (Ruined)");

		else return xorstr(" (Pristine)");
	}

	uint64_t SlowEntityTable()
	{
		return read<uint64_t>(globals.World + Offsets::OFFSET_WORLD_SLOWANIMALTABLE); //Offsets::OFFSET_WORLD_SLOWANIMALTABLE  
	}

	uint32_t SlowEntityTableSize()
	{
		return read<uint32_t>(globals.World + Offsets::OFFSET_WORLD_SLOWANIMALTABLE + 0x8);//Offsets::OFFSET_WORLD_SLOWANIMALTABLE  
	}

	float GetDistanceToMe(Vector3 Entity)
	{
		return Entity.Distance(GetCoordinate(GetLocalPlayer()));
	}

	bool WorldToScreen(Vector3 Position, Vector3& output)
	{
		if (!GetCamera()) return false;

		Vector3 temp = Position - GetInvertedViewTranslation();

		float x = temp.Dot(GetInvertedViewRight());
		float y = temp.Dot(GetInvertedViewUp());
		float z = temp.Dot(GetInvertedViewForward());

		if (z < 0.1f)
			return false;

		Vector3 res(
			GetViewportSize().x * (1 + (x / GetProjectionD1().x / z)),
			GetViewportSize().y * (1 - (y / GetProjectionD2().y / z)),
			z);

		output.x = res.x;
		output.y = res.y;
		output.z = res.z;
		return true;
	}

	bool SetPosition(uint64_t Entity, const Vector3& TargetPosition) 
	{
		if (Entity == Game::GetLocalPlayer()) 
		{
			write<Vector3>(
				read<uint64_t>(
					Entity + Offsets::OFFSET_ENTITY_FUTUREVISUALSTATE) + Offsets::OFFSET_VISUALSTATE_POSITION, TargetPosition);
		}
		else {
			write<Vector3>(
				read<uint64_t>(
					Entity + Offsets::OFFSET_ENTITY_RENDERVISUALSTATE) + Offsets::OFFSET_VISUALSTATE_POSITION, TargetPosition);
		}
		return true;
	};

	uint64_t GetInventory(uint64_t Entity) {
		return read<uint64_t>(Entity + Offsets::OFFSET_ENTITY_INVENTORY); //Offsets::OFFSET_ENTITY_INVENTORY 
	}


	std::string GetItemInventory(uint64_t Entity) {
		return ReadArmaString(read<uint64_t>(
			read<uint64_t>(read<uint64_t>(Game::GetInventory(Entity) + Offsets::OFFSET_INVENTORY_ITEMINHAND) + Offsets::OFFSET_ENTITY_RENDERENTITYTYPE) + Offsets::OFFSET_ENTITYTYPE_CLEANNAME)).c_str(); // Offsets::OFFSET_INVENTORY_ITEMINHAND  + Offsets::OFFSET_ENTITY_RENDERENTITYTYPE + Offsets::OFFSET_ENTITYTYPE_CLEANNAME 
	}

	std::string GetItemInHands(uint64_t Entity) {
		return ReadArmaString(read<uint64_t>(
			read<uint64_t>(read<uint64_t>(Game::GetInventory(Entity) + Offsets::OFFSET_INVENTORY_ITEMINHAND) + Offsets::OFFSET_ENTITY_RENDERENTITYTYPE) + Offsets::OFFSET_ENTITYTYPE_CLEANNAME)).c_str(); // Offsets::OFFSET_INVENTORY_ITEMINHAND  + Offsets::OFFSET_ENTITY_RENDERENTITYTYPE + Offsets::OFFSET_ENTITYTYPE_TYPENAME 
	}

	std::string GetItemInHandsClean(uint64_t Entity) {
		return ReadArmaString(read<uint64_t>(
			read<uint64_t>(read<uint64_t>(Game::GetInventory(Entity) + Offsets::OFFSET_INVENTORY_ITEMINHAND) + Offsets::OFFSET_ENTITY_RENDERENTITYTYPE) + Offsets::OFFSET_ENTITYTYPE_CLEANNAME)).c_str(); // Offsets::OFFSET_INVENTORY_ITEMINHAND  + Offsets::OFFSET_ENTITY_RENDERENTITYTYPE + Offsets::OFFSET_ENTITYTYPE_CLEANNAME 
	}

	uint64_t BulletTable() {
		return read<uint64_t>(globals.World + Offsets::OFFSET_WORLD_BULLETTABLE); //Offsets::OFFSET_WORLD_BULLETTABLE 
	}

	uint64_t BulletTableSize() {
		return sizeof(BulletTable());
	}


	uint64_t GetCameraEntry() {
		return read<uint64_t>(
			GetLocalPlayer() + Offsets::OFFSET_ENTITY_CAMERAENTRY); //Offsets::OFFSET_ENTITY_CAMERAENTRY 
	}

	float RadiansToDegrees(float radians) {
		float degrees;
		degrees = ((radians * 180) / 3.14159265358979323846f);
		return degrees;
	};

	bool IsDead(uintptr_t Entity)//0 = alive, 1 = dead
	{
		return	read<bool>((uintptr_t)Entity + Offsets::OFFSET_IS_DEAD);
	}
	std::string GetDirection() {
		Vector3 viewAnglesRadians, viewAngle;
		viewAnglesRadians.x = atan2(GetInvertedViewRight().z, GetInvertedViewRight().x);
		viewAngle.x = RadiansToDegrees(viewAnglesRadians.x);
		viewAnglesRadians.y = atan2(GetInvertedViewForward().y, GetInvertedViewUp().y);
		viewAngle.y = RadiansToDegrees(viewAnglesRadians.y);

		int angle = static_cast<int>(viewAngle.x);
		if (angle < 0) {
			angle += 360;
		}

		std::string direction;
		if ((angle >= 337.5 && angle < 360) || (angle >= 0 && angle < 22.5)) {
			direction = xorstr("NORTH");
		}
		else if (angle >= 22.5 && angle < 67.5) {
			direction = xorstr("NORTHEAST");
		}
		else if (angle >= 67.5 && angle < 112.5) {
			direction = xorstr("EAST");
		}
		else if (angle >= 112.5 && angle < 157.5) {
			direction = xorstr("SOUTHEAST");
		}
		else if (angle >= 157.5 && angle < 202.5) {
			direction = xorstr("SOUTH");
		}
		else if (angle >= 202.5 && angle < 247.5) {
			direction = xorstr("SOUTHWEST");
		}
		else if (angle >= 247.5 && angle < 292.5) {
			direction = xorstr("WEST");
		}
		else if (angle >= 292.5 && angle < 337.5) {
			direction = xorstr("NORTHWEST");
		}



		return direction + " [" + std::to_string(angle) + "]";
	}

	inline uint64_t GetSkeleton(uint64_t Entity)
	{
		return read<uint64_t>(Entity + OFF_SKELETON_PLAYER);
	}

	inline uint64_t GetSkeletonZombie(uint64_t Entity)
	{
		return read<uint64_t>(Entity + OFF_SKELETON_ZOMBIE);
	}

	struct matrix4x4f {
		float m[12];
	};

	Vector3 BoneAim(uint64_t Entity, uint32_t index)
	{

		Vector3 out;

		if(!Entity) return out;

		uint64_t animClass = read<uintptr_t>(GetSkeleton(Entity) + 0x98);
		if (!animClass) return out;
		//if (!animClass) Vector3 out(0, 0, 0);

		uint64_t matrixClass = read<uint64_t>(animClass + 0xBF0);
		if (!matrixClass) return out;
		//if (!matrixClass) Vector3 out(0, 0, 0);

		matrix4x4f matrix_a = read<matrix4x4f>((read<uint64_t>(Entity + OFF_PVISUAL)) + 0x8);
		Vector3 matrix_b = read<Vector3>(matrixClass + 0x54 + index * sizeof(matrix4x4f));

		out.x = (matrix_a.m[0] * matrix_b.x) + (matrix_a.m[3] * matrix_b.y) + (matrix_a.m[6] * matrix_b.z) + matrix_a.m[9];
		out.y = (matrix_a.m[1] * matrix_b.x) + (matrix_a.m[4] * matrix_b.y) + (matrix_a.m[7] * matrix_b.z) + matrix_a.m[10];
		out.z = (matrix_a.m[2] * matrix_b.x) + (matrix_a.m[5] * matrix_b.y) + (matrix_a.m[8] * matrix_b.z) + matrix_a.m[11];
		return out;
	}

	Vector3 BoneAimZombie(uint64_t Entity, uint32_t index)
	{
		Vector3 out;

		uint64_t animClass = read<uintptr_t>(GetSkeletonZombie(Entity) + 0x98);
		if (!animClass) Vector3 out;

		uint64_t matrixClass = read<uint64_t>(animClass + 0xBF0);
		if (!matrixClass) Vector3 out;

		matrix4x4f matrix_a = read<matrix4x4f>((read<uint64_t>(Entity + OFF_PVISUAL)) + 0x8);
		Vector3 matrix_b = read<Vector3>(matrixClass + 0x54 + index * sizeof(matrix4x4f));

		out.x = (matrix_a.m[0] * matrix_b.x) + (matrix_a.m[3] * matrix_b.y) + (matrix_a.m[6] * matrix_b.z) + matrix_a.m[9];
		out.y = (matrix_a.m[1] * matrix_b.x) + (matrix_a.m[4] * matrix_b.y) + (matrix_a.m[7] * matrix_b.z) + matrix_a.m[10];
		out.z = (matrix_a.m[2] * matrix_b.x) + (matrix_a.m[5] * matrix_b.y) + (matrix_a.m[8] * matrix_b.z) + matrix_a.m[11];
		return out;
	}

	void getBones(uint64_t Entity)
	{
		Vector3 head = BoneAim(Entity, 24);
		Vector3 headscreen;
		Game::WorldToScreen(head, headscreen);

		Vector3 somebody = BoneAim(Entity, 21);
		Vector3 somebodyscreen;
		Game::WorldToScreen(somebody, somebodyscreen);

		Vector3 body = BoneAim(Entity, 20);
		Vector3 bodyscreen;
		Game::WorldToScreen(body, bodyscreen);

		Vector3 downbody = BoneAim(Entity, 0);
		Vector3 downbodyscreen;
		Game::WorldToScreen(downbody, downbodyscreen);

		Vector3 llegup = BoneAim(Entity, 1);
		Vector3 llegupscreen;
		Game::WorldToScreen(llegup, llegupscreen);

		Vector3 rlegup = BoneAim(Entity, 9);
		Vector3 rlegupscreen;
		Game::WorldToScreen(rlegup, rlegupscreen);

		Vector3 llegmid = BoneAim(Entity, 4);
		Vector3 llegmidscreen;
		Game::WorldToScreen(llegmid, llegmidscreen);

		Vector3 rlegmid = BoneAim(Entity, 12);
		Vector3 rlegmidscreen;
		Game::WorldToScreen(rlegmid, rlegmidscreen);

		Vector3 llegdown = BoneAim(Entity, 6);
		Vector3 llegdownscreen;
		Game::WorldToScreen(llegdown, llegdownscreen);

		Vector3 rlegdown = BoneAim(Entity, 14);
		Vector3 rlegdownscreen;
		Game::WorldToScreen(rlegdown, rlegdownscreen);

		Vector3 larmup = BoneAim(Entity, 61);
		Vector3 larmupscreen;
		Game::WorldToScreen(larmup, larmupscreen);

		Vector3 rarmup = BoneAim(Entity, 94);
		Vector3 rarmupscreen;
		Game::WorldToScreen(rarmup, rarmupscreen);

		Vector3 larmmid = BoneAim(Entity, 91);
		Vector3 larmmidscreen;
		Game::WorldToScreen(larmmid, larmmidscreen);

		Vector3 rarmmid = BoneAim(Entity, 97);
		Vector3 rarmmidscreen;
		Game::WorldToScreen(rarmmid, rarmmidscreen);

		Vector3 larmdown = BoneAim(Entity, 66);
		Vector3 larmdownscreen;
		Game::WorldToScreen(larmdown, larmdownscreen);

		Vector3 rarmdown = BoneAim(Entity, 100);
		Vector3 rarmdownscreen;
		Game::WorldToScreen(rarmdown, rarmdownscreen);

		std::vector<std::pair<Vector3, Vector3>> lines = {
			{headscreen, somebodyscreen},
			{somebodyscreen, bodyscreen},
			{bodyscreen, downbodyscreen},
			{downbodyscreen, llegupscreen},
			{downbodyscreen, rlegupscreen},
			{llegupscreen, llegmidscreen},
			{rlegupscreen, rlegmidscreen},
			{llegmidscreen, llegdownscreen},
			{rlegmidscreen, rlegdownscreen},
			{somebodyscreen, larmupscreen},
			{somebodyscreen, rarmupscreen},
			{larmupscreen, larmmidscreen},
			{rarmupscreen, rarmmidscreen},
			{larmmidscreen, larmdownscreen},
			{rarmmidscreen, rarmdownscreen}
		};

		for (const auto& line : lines) {
			DrawLine(line.first.x, line.first.y, line.second.x, line.second.y, &Col.purple_, 2);
		}

		/*for (int i = 0; i < 115; i++) {
			Vector3 zOnScreen;
			Vector3 aboba = BoneAim(Entity, i);
			Game::WorldToScreen(aboba, zOnScreen);
			DrawString(10, zOnScreen.x, zOnScreen.y, &Col.white, false, false, (std::to_string(i)).c_str());
		}*/
		
	}

	void PlayerCorneredBox(uint64_t Entity)
	{
		Vector3 head = BoneAim(Entity, 49); // голова
		Vector3 llegdown = BoneAim(Entity, 6); // лева€ нога
		Vector3 rlegdown = BoneAim(Entity, 14); // права€ нога
		Vector3 larmdown = BoneAim(Entity, 66); // лева€ крайн€€ точка бокса
		Vector3 rarmdown = BoneAim(Entity, 100); // права€ крайн€€ точка бокса

		Vector3 headScreen, llegDownScreen, rlegDownScreen, larmDownScreen, rarmDownScreen;
		Game::WorldToScreen(head, headScreen);
		Game::WorldToScreen(llegdown, llegDownScreen);
		Game::WorldToScreen(rlegdown, rlegDownScreen);
		Game::WorldToScreen(larmdown, larmDownScreen);
		Game::WorldToScreen(rarmdown, rarmDownScreen);

		int boxLeft = min(min(min(headScreen.x, llegDownScreen.x), rlegDownScreen.x), min(larmDownScreen.x, rarmDownScreen.x));
		int boxTop = min(min(min(headScreen.y, llegDownScreen.y), rlegDownScreen.y), min(larmDownScreen.y, rarmDownScreen.y));
		int boxRight = max(max(max(headScreen.x, llegDownScreen.x), rlegDownScreen.x), max(larmDownScreen.x, rarmDownScreen.x));
		int boxBottom = max(max(max(headScreen.y, llegDownScreen.y), rlegDownScreen.y), max(larmDownScreen.y, rarmDownScreen.y));

		int boxWidth = boxRight - boxLeft;
		int boxHeight = boxBottom - boxTop;

		DrawCorneredBox(boxLeft, boxTop, boxWidth, boxHeight, ImColor(128, 255, 0), 2);
	}
	void PlayerBox(uint64_t Entity)
	{
		Vector3 head = BoneAim(Entity, 49); // голова
		Vector3 llegdown = BoneAim(Entity, 6); // лева€ нога
		Vector3 rlegdown = BoneAim(Entity, 14); // права€ нога
		Vector3 larmdown = BoneAim(Entity, 66); // лева€ крайн€€ точка бокса
		Vector3 rarmdown = BoneAim(Entity, 100); // права€ крайн€€ точка бокса

		Vector3 headScreen, llegDownScreen, rlegDownScreen, larmDownScreen, rarmDownScreen;
		Game::WorldToScreen(head, headScreen);
		Game::WorldToScreen(llegdown, llegDownScreen);
		Game::WorldToScreen(rlegdown, rlegDownScreen);
		Game::WorldToScreen(larmdown, larmDownScreen);
		Game::WorldToScreen(rarmdown, rarmDownScreen);

		int boxLeft = min(min(min(headScreen.x, llegDownScreen.x), rlegDownScreen.x), min(larmDownScreen.x, rarmDownScreen.x));
		int boxTop = min(min(min(headScreen.y, llegDownScreen.y), rlegDownScreen.y), min(larmDownScreen.y, rarmDownScreen.y));
		int boxRight = max(max(max(headScreen.x, llegDownScreen.x), rlegDownScreen.x), max(larmDownScreen.x, rarmDownScreen.x));
		int boxBottom = max(max(max(headScreen.y, llegDownScreen.y), rlegDownScreen.y), max(larmDownScreen.y, rarmDownScreen.y));

		RGBA boxColor = { 128, 255, 0, 255 }; // цвет бокса

		// –исование верхней грани квадрата
		DrawLine(boxLeft, boxTop, boxRight, boxTop, &boxColor, 2);
		// –исование нижней грани квадрата
		DrawLine(boxLeft, boxBottom, boxRight, boxBottom, &boxColor, 2);
		// –исование левой грани квадрата
		DrawLine(boxLeft, boxTop, boxLeft, boxBottom, &boxColor, 2);
		// –исование правой грани квадрата
		DrawLine(boxRight, boxTop, boxRight, boxBottom, &boxColor, 2);
	}

	void PlayerBoxFrame(uint64_t Entity)
	{
		Vector3 head = BoneAim(Entity, 49); // голова
		Vector3 llegdown = BoneAim(Entity, 6); // лева€ нога
		Vector3 rlegdown = BoneAim(Entity, 14); // права€ нога
		Vector3 larmdown = BoneAim(Entity, 66); // лева€ крайн€€ точка бокса
		Vector3 rarmdown = BoneAim(Entity, 100); // права€ крайн€€ точка бокса

		Vector3 headScreen, llegDownScreen, rlegDownScreen, larmDownScreen, rarmDownScreen;
		Game::WorldToScreen(head, headScreen);
		Game::WorldToScreen(llegdown, llegDownScreen);
		Game::WorldToScreen(rlegdown, rlegDownScreen);
		Game::WorldToScreen(larmdown, larmDownScreen);
		Game::WorldToScreen(rarmdown, rarmDownScreen);

		int boxLeft = min(min(min(headScreen.x, llegDownScreen.x), rlegDownScreen.x), min(larmDownScreen.x, rarmDownScreen.x));
		int boxTop = min(min(min(headScreen.y, llegDownScreen.y), rlegDownScreen.y), min(larmDownScreen.y, rarmDownScreen.y));
		int boxRight = max(max(max(headScreen.x, llegDownScreen.x), rlegDownScreen.x), max(larmDownScreen.x, rarmDownScreen.x));
		int boxBottom = max(max(max(headScreen.y, llegDownScreen.y), rlegDownScreen.y), max(larmDownScreen.y, rarmDownScreen.y));

		RGBA boxColor = { 128, 255, 0, 255 }; // цвет бокса

		// –исование верхней грани квадрата
		DrawLine(boxLeft, boxTop, boxRight, boxTop, &boxColor, 2);
		// –исование нижней грани квадрата
		DrawLine(boxLeft, boxBottom, boxRight, boxBottom, &boxColor, 2);
		// –исование левой грани квадрата
		DrawLine(boxLeft, boxTop, boxLeft, boxBottom, &boxColor, 2);
		// –исование правой грани квадрата
		DrawLine(boxRight, boxTop, boxRight, boxBottom, &boxColor, 2);

		// —оединение углов квадрата
		DrawLine(boxLeft, boxTop, boxLeft - 5, boxTop - 5, &boxColor, 2);
		DrawLine(boxRight, boxTop, boxRight + 5, boxTop - 5, &boxColor, 2);
		DrawLine(boxLeft, boxBottom, boxLeft - 5, boxBottom + 5, &boxColor, 2);
		DrawLine(boxRight, boxBottom, boxRight + 5, boxBottom + 5, &boxColor, 2);
	}

	void ZombieCorneredBox(uint64_t Entity)
	{
		Vector3 zombieHead = BoneAimZombie(Entity, 22); // голова
		Vector3 zombieLlegdown = BoneAimZombie(Entity, 6); // лева€ нога
		Vector3 zombieRlegdown = BoneAimZombie(Entity, 13); // права€ нога
		Vector3 zombieLarmdown = BoneAimZombie(Entity, 29); // лева€ крайн€€ точка бокса
		Vector3 zombieRarmdown = BoneAimZombie(Entity, 62); // права€ крайн€€ точка бокса

		Vector3 zombieHeadScreen, zombieLlegDownScreen, zombieRlegDownScreen, zombieLarmDownScreen, zombieRarmDownScreen;
		Game::WorldToScreen(zombieHead, zombieHeadScreen);
		Game::WorldToScreen(zombieLlegdown, zombieLlegDownScreen);
		Game::WorldToScreen(zombieRlegdown, zombieRlegDownScreen);
		Game::WorldToScreen(zombieLarmdown, zombieLarmDownScreen);
		Game::WorldToScreen(zombieRarmdown, zombieRarmDownScreen);

		int boxLeft = min(min(min(zombieHeadScreen.x, zombieLlegDownScreen.x), zombieRlegDownScreen.x), min(zombieLarmDownScreen.x, zombieRarmDownScreen.x));
		int boxTop = min(min(min(zombieHeadScreen.y, zombieLlegDownScreen.y), zombieRlegDownScreen.y), min(zombieLarmDownScreen.y, zombieRarmDownScreen.y));
		int boxRight = max(max(max(zombieHeadScreen.x, zombieLlegDownScreen.x), zombieRlegDownScreen.x), max(zombieLarmDownScreen.x, zombieRarmDownScreen.x));
		int boxBottom = max(max(max(zombieHeadScreen.y, zombieLlegDownScreen.y), zombieRlegDownScreen.y), max(zombieLarmDownScreen.y, zombieRarmDownScreen.y));

		int boxWidth = boxRight - boxLeft;
		int boxHeight = boxBottom - boxTop;

		DrawCorneredBox(boxLeft, boxTop, boxWidth, boxHeight, ImColor(255, 0, 0), 2);
	}

	void ZombieBox(uint64_t Entity)
	{
		Vector3 zombieHead = BoneAimZombie(Entity, 22); // голова
		Vector3 zombieLlegdown = BoneAimZombie(Entity, 6); // лева€ нога
		Vector3 zombieRlegdown = BoneAimZombie(Entity, 13); // права€ нога
		Vector3 zombieLarmdown = BoneAimZombie(Entity, 29); // лева€ крайн€€ точка бокса
		Vector3 zombieRarmdown = BoneAimZombie(Entity, 62); // права€ крайн€€ точка бокса

		Vector3 zombieHeadScreen, zombieLlegDownScreen, zombieRlegDownScreen, zombieLarmDownScreen, zombieRarmDownScreen;
		Game::WorldToScreen(zombieHead, zombieHeadScreen);
		Game::WorldToScreen(zombieLlegdown, zombieLlegDownScreen);
		Game::WorldToScreen(zombieRlegdown, zombieRlegDownScreen);
		Game::WorldToScreen(zombieLarmdown, zombieLarmDownScreen);
		Game::WorldToScreen(zombieRarmdown, zombieRarmDownScreen);

		int boxLeft = min(min(min(zombieHeadScreen.x, zombieLlegDownScreen.x), zombieRlegDownScreen.x), min(zombieLarmDownScreen.x, zombieRarmDownScreen.x));
		int boxTop = min(min(min(zombieHeadScreen.y, zombieLlegDownScreen.y), zombieRlegDownScreen.y), min(zombieLarmDownScreen.y, zombieRarmDownScreen.y));
		int boxRight = max(max(max(zombieHeadScreen.x, zombieLlegDownScreen.x), zombieRlegDownScreen.x), max(zombieLarmDownScreen.x, zombieRarmDownScreen.x));
		int boxBottom = max(max(max(zombieHeadScreen.y, zombieLlegDownScreen.y), zombieRlegDownScreen.y), max(zombieLarmDownScreen.y, zombieRarmDownScreen.y));

		RGBA boxColor = { 255, 0, 0, 255 }; // цвет бокса

		// –исование верхней грани квадрата
		DrawLine(boxLeft, boxTop, boxRight, boxTop, &boxColor, 2);
		// –исование нижней грани квадрата
		DrawLine(boxLeft, boxBottom, boxRight, boxBottom, &boxColor, 2);
		// –исование левой грани квадрата
		DrawLine(boxLeft, boxTop, boxLeft, boxBottom, &boxColor, 2);
		// –исование правой грани квадрата
		DrawLine(boxRight, boxTop, boxRight, boxBottom, &boxColor, 2);
	}

	void ZombieBoxFrame(uint64_t Entity)
	{
		Vector3 zombieHead = BoneAimZombie(Entity, 22); // голова
		Vector3 zombieLlegdown = BoneAimZombie(Entity, 6); // лева€ нога
		Vector3 zombieRlegdown = BoneAimZombie(Entity, 13); // права€ нога
		Vector3 zombieLarmdown = BoneAimZombie(Entity, 29); // лева€ крайн€€ точка бокса
		Vector3 zombieRarmdown = BoneAimZombie(Entity, 62); // права€ крайн€€ точка бокса

		Vector3 zombieHeadScreen, zombieLlegDownScreen, zombieRlegDownScreen, zombieLarmDownScreen, zombieRarmDownScreen;
		Game::WorldToScreen(zombieHead, zombieHeadScreen);
		Game::WorldToScreen(zombieLlegdown, zombieLlegDownScreen);
		Game::WorldToScreen(zombieRlegdown, zombieRlegDownScreen);
		Game::WorldToScreen(zombieLarmdown, zombieLarmDownScreen);
		Game::WorldToScreen(zombieRarmdown, zombieRarmDownScreen);

		int boxLeft = min(min(min(zombieHeadScreen.x, zombieLlegDownScreen.x), zombieRlegDownScreen.x), min(zombieLarmDownScreen.x, zombieRarmDownScreen.x));
		int boxTop = min(min(min(zombieHeadScreen.y, zombieLlegDownScreen.y), zombieRlegDownScreen.y), min(zombieLarmDownScreen.y, zombieRarmDownScreen.y));
		int boxRight = max(max(max(zombieHeadScreen.x, zombieLlegDownScreen.x), zombieRlegDownScreen.x), max(zombieLarmDownScreen.x, zombieRarmDownScreen.x));
		int boxBottom = max(max(max(zombieHeadScreen.y, zombieLlegDownScreen.y), zombieRlegDownScreen.y), max(zombieLarmDownScreen.y, zombieRarmDownScreen.y));

		RGBA boxColor = { 255, 0, 0, 255 }; // цвет бокса

		// –исование верхней грани квадрата
		DrawLine(boxLeft, boxTop, boxRight, boxTop, &boxColor, 2);
		// –исование нижней грани квадрата
		DrawLine(boxLeft, boxBottom, boxRight, boxBottom, &boxColor, 2);
		// –исование левой грани квадрата
		DrawLine(boxLeft, boxTop, boxLeft, boxBottom, &boxColor, 2);
		// –исование правой грани квадрата
		DrawLine(boxRight, boxTop, boxRight, boxBottom, &boxColor, 2);

		// —оединение углов квадрата
		DrawLine(boxLeft, boxTop, boxLeft - 5, boxTop - 5, &boxColor, 2);
		DrawLine(boxRight, boxTop, boxRight + 5, boxTop - 5, &boxColor, 2);
		DrawLine(boxLeft, boxBottom, boxLeft - 5, boxBottom + 5, &boxColor, 2);
		DrawLine(boxRight, boxBottom, boxRight + 5, boxBottom + 5, &boxColor, 2);
	}

	void getBonesZombie(uint64_t Entity) 
	{
		Vector3 head = BoneAimZombie(Entity, 21);
		Vector3 headscreen;
		Game::WorldToScreen(head, headscreen);

		Vector3 somebody = BoneAimZombie(Entity, 19);
		Vector3 somebodyscreen;
		Game::WorldToScreen(somebody, somebodyscreen);

		Vector3 body = BoneAimZombie(Entity, 17);
		Vector3 bodyscreen;
		Game::WorldToScreen(body, bodyscreen);

		Vector3 downbody = BoneAimZombie(Entity, 15);
		Vector3 downbodyscreen;
		Game::WorldToScreen(downbody, downbodyscreen);

		Vector3 llegup = BoneAimZombie(Entity, 89);
		Vector3 llegupscreen;
		Game::WorldToScreen(llegup, llegupscreen);

		Vector3 rlegup = BoneAimZombie(Entity, 90);
		Vector3 rlegupscreen;
		Game::WorldToScreen(rlegup, rlegupscreen);

		Vector3 llegmid = BoneAimZombie(Entity, 4);
		Vector3 llegmidscreen;
		Game::WorldToScreen(llegmid, llegmidscreen);

		Vector3 rlegmid = BoneAimZombie(Entity, 10);
		Vector3 rlegmidscreen;
		Game::WorldToScreen(rlegmid, rlegmidscreen);

		Vector3 llegdown = BoneAimZombie(Entity, 6);
		Vector3 llegdownscreen;
		Game::WorldToScreen(llegdown, llegdownscreen);

		Vector3 rlegdown = BoneAimZombie(Entity, 13);
		Vector3 rlegdownscreen;
		Game::WorldToScreen(rlegdown, rlegdownscreen);

		DrawLine(headscreen.x, headscreen.y, somebodyscreen.x, somebodyscreen.y, &Col.red_, 2);
		DrawLine(somebodyscreen.x, somebodyscreen.y, bodyscreen.x, bodyscreen.y, &Col.red_, 2);
		DrawLine(bodyscreen.x, bodyscreen.y, downbodyscreen.x, downbodyscreen.y, &Col.red_, 2);

		DrawLine(downbodyscreen.x, downbodyscreen.y, llegupscreen.x, llegupscreen.y, &Col.red_, 2);
		DrawLine(downbodyscreen.x, downbodyscreen.y, rlegupscreen.x, rlegupscreen.y, &Col.red_, 2);

		DrawLine(llegupscreen.x, llegupscreen.y, llegmidscreen.x, llegmidscreen.y, &Col.red_, 2);
		DrawLine(rlegupscreen.x, rlegupscreen.y, rlegmidscreen.x, rlegmidscreen.y, &Col.red_, 2);

		DrawLine(llegmidscreen.x, llegmidscreen.y, llegdownscreen.x, llegdownscreen.y, &Col.red_, 2);
		DrawLine(rlegmidscreen.x, rlegmidscreen.y, rlegdownscreen.x, rlegdownscreen.y, &Col.red_, 2);

		Vector3 larmup = BoneAimZombie(Entity, 24);
		Vector3 larmupscreen;
		Game::WorldToScreen(larmup, larmupscreen);

		Vector3 rarmup = BoneAimZombie(Entity, 56);
		Vector3 rarmupscreen;
		Game::WorldToScreen(rarmup, rarmupscreen);

		Vector3 larmmid = BoneAimZombie(Entity, 53);
		Vector3 larmmidscreen;
		Game::WorldToScreen(larmmid, larmmidscreen);

		Vector3 rarmmid = BoneAimZombie(Entity, 59);
		Vector3 rarmmidscreen;
		Game::WorldToScreen(rarmmid, rarmmidscreen);

		Vector3 larmdown = BoneAimZombie(Entity, 29);
		Vector3 larmdownscreen;
		Game::WorldToScreen(larmdown, larmdownscreen);

		Vector3 rarmdown = BoneAimZombie(Entity, 62);
		Vector3 rarmdownscreen;
		Game::WorldToScreen(rarmdown, rarmdownscreen);

		DrawLine(somebodyscreen.x, somebodyscreen.y, larmupscreen.x, larmupscreen.y, &Col.red_, 2);
		DrawLine(somebodyscreen.x, somebodyscreen.y, rarmupscreen.x, rarmupscreen.y, &Col.red_, 2);

		DrawLine(larmupscreen.x, larmupscreen.y, larmmidscreen.x, larmmidscreen.y, &Col.red_, 2);
		DrawLine(rarmupscreen.x, rarmupscreen.y, rarmmidscreen.x, rarmmidscreen.y, &Col.red_, 2);

		DrawLine(larmmidscreen.x, larmmidscreen.y, larmdownscreen.x, larmdownscreen.y, &Col.red_, 2);
		DrawLine(rarmmidscreen.x, rarmmidscreen.y, rarmdownscreen.x, rarmdownscreen.y, &Col.red_, 2);

		//for (int i = 0; i < 115; i++) {
		//	//Vector3 bone_tmp;
		//	Vector3 zPosition;
		//	Vector3 zOnScreen;
		//	Vector3 aboba = BoneAimZombie(Entity, i);
		//	Game::WorldToScreen(aboba, zOnScreen);
		//	DrawString(10, zOnScreen.x, zOnScreen.y, &Col.white, false, false, (std::to_string(i)).c_str());
		//}
	}

	bool SilentAimHead(uint64_t Entity)
	{
		uint64_t pVisual = read<uint64_t>(Entity + OFF_PVISUAL);

		if (Game::IsDead(Entity) == 1) return false;

		if (!GetLocalPlayerVisualState) return false;

		if (!pVisual) return false;

		Vector3 worldPosition = Game::GetCoordinate(Entity);
		Vector3 screenPosition;
		Game::WorldToScreen(worldPosition, screenPosition);

		float centerX = globals.width / 2.0f;

		float centerY = globals.height / 2.0f;

		if (screenPosition.z < 1.0f) return false;

		if (Game::AimbotKey())
		{
			if (screenPosition.x - centerX < globals.radius && centerX - screenPosition.x < globals.radius && centerY - screenPosition.y < globals.radius && screenPosition.y - centerY < globals.radius)
			{
				if (!Entity) return false;
				for (uint64_t playerId = NULL; playerId < BulletTableSize(); ++playerId) {
					//Vector3 WorldPosition = Game::GetCoordinate(Entity); //24 head //12 leg //0 body
					//int distance = Game::GetDistanceToMe(WorldPosition);
					Vector3 head = Game::BoneAim(Entity, 24);
					int distance = Game::GetDistanceToMe(head);
					SetPosition(Game::GetEntity(BulletTable(), playerId), Vector3(head.x, head.y, head.z));
				}
				return true;
			}
			return false;
		}
	}

	bool SilentAimBody(uint64_t Entity)
	{
		uint64_t pVisual = read<uint64_t>(Entity + OFF_PVISUAL);

		if (Game::IsDead(Entity) == 1) return false;

		if (!GetLocalPlayerVisualState) return false;

		if (!pVisual) return false;

		Vector3 worldPosition = Game::GetCoordinate(Entity);
		Vector3 screenPosition;
		Game::WorldToScreen(worldPosition, screenPosition);

		float centerX = globals.width / 2.0f;

		float centerY = globals.height / 2.0f;

		if (screenPosition.z < 1.0f) return false;

		if (Game::AimbotKey())
		{
			if (screenPosition.x - centerX < globals.radius && centerX - screenPosition.x < globals.radius && centerY - screenPosition.y < globals.radius && screenPosition.y - centerY < globals.radius)
			{
				if (!Entity) return false;
				for (uint64_t playerId = NULL; playerId < BulletTableSize(); ++playerId) {
					//Vector3 WorldPosition = Game::GetCoordinate(Entity); //24 head //12 leg //0 body
					//int distance = Game::GetDistanceToMe(WorldPosition);
					Vector3 head = Game::BoneAim(Entity, 20);
					int distance = Game::GetDistanceToMe(head);
					SetPosition(Game::GetEntity(BulletTable(), playerId), Vector3(head.x, head.y, head.z));
				}
				return true;
			}
			return false;
		}
	}

	bool SilentAimLegs(uint64_t Entity)
	{
		uint64_t pVisual = read<uint64_t>(Entity + OFF_PVISUAL);

		if (Game::IsDead(Entity) == 1) return false;

		if (!GetLocalPlayerVisualState) return false;

		if (!pVisual) return false;

		Vector3 worldPosition = Game::GetCoordinate(Entity);
		Vector3 screenPosition;
		Game::WorldToScreen(worldPosition, screenPosition);

		float centerX = globals.width / 2.0f;

		float centerY = globals.height / 2.0f;

		if (screenPosition.z < 1.0f) return false;

		if (Game::AimbotKey())
		{
			if (screenPosition.x - centerX < globals.radius && centerX - screenPosition.x < globals.radius && centerY - screenPosition.y < globals.radius && screenPosition.y - centerY < globals.radius)
			{
				if (!Entity) return false;
				for (uint64_t playerId = NULL; playerId < BulletTableSize(); ++playerId) {
					//Vector3 WorldPosition = Game::GetCoordinate(Entity); //24 head //12 leg //0 body
					//int distance = Game::GetDistanceToMe(WorldPosition);
					Vector3 head = Game::BoneAim(Entity, 12);
					int distance = Game::GetDistanceToMe(head);
					SetPosition(Game::GetEntity(BulletTable(), playerId), Vector3(head.x, head.y, head.z));
				}
				return true;
			}
			return false;
		}
	}

	bool SilentAimZombie(uint64_t Entity)
	{
		uint64_t pVisual = read<uint64_t>(Entity + OFF_PVISUAL);

		if (Game::IsDead(Entity) == 1) return false;

		if (!GetLocalPlayerVisualState) return false;

		if (!pVisual) return false;

		Vector3 worldPosition = Game::GetCoordinate(Entity);
		Vector3 screenPosition;
		Game::WorldToScreen(worldPosition, screenPosition);

		float centerX = globals.width / 2.0f;

		float centerY = globals.height / 2.0f;

		if (screenPosition.z < 1.0f) return false;

		if (Game::AimbotKey())
		{
			if (screenPosition.x - centerX < globals.radius && centerX - screenPosition.x < globals.radius && centerY - screenPosition.y < globals.radius && screenPosition.y - centerY < globals.radius)
			{
				if (!Entity) return false;
				for (uint64_t playerId = NULL; playerId < BulletTableSize(); ++playerId) {
					Vector3 bone = Game::BoneAimZombie(Entity, 22);
					//Vector3 WorldPosition = Game::GetCoordinate(Entity);
					//int distance = Game::GetDistanceToMe(WorldPosition);
					int distance = Game::GetDistanceToMe(bone);
					SetPosition(Game::GetEntity(BulletTable(), playerId), Vector3(bone.x, bone.y, bone.z));
				}
				return true;
			}
			return false;
		}
	}

	bool SilentAimAnimals(uint64_t Entity)
	{
		uint64_t pVisual = read<uint64_t>(Entity + OFF_PVISUAL);

		if (Game::IsDead(Entity) == 1) return false;

		if (!GetLocalPlayerVisualState) return false;

		if (!pVisual) return false;

		Vector3 worldPosition = Game::GetCoordinate(Entity);
		Vector3 screenPosition;
		Game::WorldToScreen(worldPosition, screenPosition);

		float centerX = globals.width / 2.0f;

		float centerY = globals.height / 2.0f;

		if (screenPosition.z < 1.0f) return false;

		if (Game::AimbotKey())
		{
			if (screenPosition.x - centerX < globals.radius && centerX - screenPosition.x < globals.radius && centerY - screenPosition.y < globals.radius && screenPosition.y - centerY < globals.radius)
			{
				if (!Entity) return false;
				for (uint64_t playerId = NULL; playerId < BulletTableSize(); ++playerId) {

					Vector3 bone = Game::BoneAimZombie(Entity, 0);
					//Vector3 WorldPosition = Game::GetCoordinate(Entity);
					//int distance = Game::GetDistanceToMe(WorldPosition);
					int distance = Game::GetDistanceToMe(bone);
					SetPosition(Game::GetEntity(BulletTable(), playerId), Vector3(bone.x, bone.y, bone.z));
				}
				return true;
			}
			return false;
		}
	}

	bool SilentAim(uint64_t Entity)
	{
		if (Game::AimbotKey())
		{
			if (!Entity) return false;
			for (uint64_t playerId = NULL; playerId < BulletTableSize(); ++playerId) {
				Vector3 WorldPosition = Game::GetCoordinate(Entity);
				int distance = Game::GetDistanceToMe(WorldPosition);
				SetPosition(Game::GetEntity(BulletTable(), playerId), Vector3(WorldPosition.x, WorldPosition.y + 1.0f, WorldPosition.z));
			}
			return true;
		}
	}

	bool SilentAimSit(uint64_t Entity)
	{
		if (Game::AimbotKey())
		{
			if (!Entity) return false;
			for (uint64_t playerId = NULL; playerId < BulletTableSize(); ++playerId) {
				Vector3 WorldPosition = Game::GetCoordinate(Entity);
				int distance = Game::GetDistanceToMe(WorldPosition);
				SetPosition(Game::GetEntity(BulletTable(), playerId), Vector3(WorldPosition.x, WorldPosition.y + 0.5f, WorldPosition.z));
			}
			return true;
		}
	}

	bool SilentAimLay(uint64_t Entity)
	{
		if (Game::AimbotKey())
		{
			if (!Entity) return false;
			for (uint64_t playerId = NULL; playerId < BulletTableSize(); ++playerId) {
				Vector3 WorldPosition = Game::GetCoordinate(Entity);
				int distance = Game::GetDistanceToMe(WorldPosition);
				SetPosition(Game::GetEntity(BulletTable(), playerId), Vector3(WorldPosition.x, WorldPosition.y + 0.2f, WorldPosition.z));
			}
			return true;
		}
	}

	uint64_t get_network_manager()
	{
		return (globals.dwProcess_Base + Offsets::OFFSET_NETWORK_NETWORKMANAGER);
	}

	uint64_t get_network_client()
	{
		auto p_network_manager = get_network_manager();

		if (!p_network_manager)
		{
			return {};
		}

		auto p_network_client = read<uint64_t>(p_network_manager + Offsets::OFFSET_NETWORK_NETWORKCLIENT);

		if (!p_network_client)
		{
			return {};
		}

		return p_network_client;
	}

	uint32_t get_network_id(uint64_t Entity)
	{
		if (!Entity)
		{
			return {};
		}

		auto network_id = read<uint32_t>(Entity + Offsets::OFFSET_ENTITY_NETWORKID);

		return network_id;
	}

	uint64_t get_network_client_scoreboard()
	{
		auto p_network_client = get_network_client();

		if (!p_network_client)
		{
			return {};
		}

		auto p_network_client_scoreboard = read<uint64_t>(p_network_client + Offsets::OFFSET_NETWORKCLIENT_SCOREBOARD);

		if (!p_network_client_scoreboard)
		{
			return {};
		}

		return p_network_client_scoreboard;
	}

	uint32_t get_network_client_scoreboard_size()
	{
		auto p_network_client = get_network_client();

		if (!p_network_client)
		{
			return {};
		}

		auto scoreboard_size = read<uint32_t>(p_network_client + 0x1C);

		if (!scoreboard_size)
		{
			return {};
		}

		return scoreboard_size;
	}

	std::string get_player_name(uint64_t Entity)
	{
		if (!Entity)
		{
			return {};
		}

		for (auto i = 0; i < get_network_client_scoreboard_size(); i++)
		{
			auto entity_network_id = get_network_id(Entity);

			auto player_identity = read<uint64_t>(get_network_client_scoreboard() + (i * sizeof(uint64_t)));

			if (!player_identity)
			{
				continue;
			}

			auto player_network_id = read<uint32_t>(player_identity + Offsets::OFFSET_PLAYERIDENTITY_NETWORKID);

			if (!player_network_id)
			{
				continue;
			}

			if (player_network_id == entity_network_id)
			{
				//return ReadArmaString(player_identity + 0xF0);
				return ReadArmaString(read<uint64_t>(player_identity + Offsets::OFFSET_PLAYERIDENTITY_PLAYERNAME));
			}
		}

		return std::string(xorstr("Unknown"));
	}

	/*std::string GetNetworkClientServerName() {
		return ReadArmaString(read<uint64_t>(
			get_network_client() + Offsets::OFFSET_NETWORKCLIENT_SERVER)).c_str();
	}*/

	int getCargo(uint64_t Entity, int current_posx, int current_posy)
	{
		int posy = current_posy;
		uint64_t iGrid = read<uint64_t>(Entity + Offsets::OFFSET_ENTITY_INVENTORY);
		uint64_t inventoryGrid = read<uint64_t>(iGrid + 0x148);

		if (inventoryGrid)
		{
			int size = read<uint32_t>(inventoryGrid + 0x44);
			//std::string data = ">>" + std::to_string(size) + " ";

			for (int k = 0; k < size; k++)
			{
				uint64_t tmp = read<uint64_t>(inventoryGrid + 0x38);
				uint64_t Item = read<uint64_t>(tmp + ((uint64_t)(k * 0x10) + 0x8));
				std::string itemsname = Game::GetEntityClean(Item);
				//data = data + Game::GetEntityClean(Item) + "\n\n";
				DrawString(14, current_posx, posy, &Col.white, false, true, (">" + itemsname).c_str());
				posy = getCargo(Item, current_posx + 30, posy + 12);
			}
			
			//DrawString(18, current_posx, posy, &Col.yellow, false, false, data.c_str());
		}
		return posy;
	}

	int getItems(uint64_t Entity, int current_posx, int current_posy)
	{
		int posy = current_posy;
		uint64_t inventory = read<uint64_t>(Entity + Offsets::OFFSET_ENTITY_INVENTORY);
		if (!inventory) return 0;
		uint64_t equippedItems = read<uint64_t>(inventory + 0x150);
		int size = read<uint32_t>(inventory + 0x15C);

		for (int k = 0; k < size; k++)
		{
			uint64_t Item = read<uint64_t>(equippedItems + (uint64_t)(k * 0x10) + 0x8);
			std::string itemsname = Game::GetEntityClean(Item);
			//data = data + Game::GetEntityClean(Item) + "\n\n";

			DrawString(14, current_posx, posy, &Col.white, false, true, ("+" + itemsname).c_str());
			getCargo(Item, current_posx + 150, posy + 12);
			posy = getItems(Item, current_posx + 30, posy + 12);
		}
		return posy;
	}



	/*std::vector<uint64_t> EntityList()
	{
		std::vector<uint64_t> arrayList;

		for (uint64_t playerId = NULL; playerId < NearEntityTableSize(); ++playerId)
		{
			if (playerId != 0)
			{
				uint64_t targetentity = GetEntity(NearEntityTable(), playerId);

				if (GetEntityTypeName(targetentity) == xorstr("dayzplayer"))
				{
					arrayList.push_back(targetentity);
				}

				if (GetEntityTypeName(targetentity) == xorstr("dayzinfected"))
				{
					arrayList.push_back(targetentity);
				}
			}
		}

		for (uint64_t playerId = NULL; playerId < FarEntityTableSize(); ++playerId)
		{
			uint64_t targetentity = GetEntity(FarEntityTable(), playerId);

			if (GetEntityTypeName(targetentity) == xorstr("dayzplayer"))
			{
				arrayList.push_back(targetentity);
			}
		}

		for (uint64_t playerId = NULL; playerId < SlowEntityTableSize(); ++playerId)
		{
			uint64_t targetentity = GetEntity(SlowEntityTable(), playerId);

			if (GetEntityTypeName(targetentity) == xorstr("dayzinfected"))
			{
				arrayList.push_back(targetentity);
			}
		}

		return arrayList;
	}*/

}
