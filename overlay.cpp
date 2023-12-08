#include <iostream>
#include <thread>
#include "overlay.h"
#include "xorstr.h"

IDirect3D9Ex* p_Object = NULL;
IDirect3DDevice9Ex* p_Device = NULL;
D3DPRESENT_PARAMETERS p_Params = { NULL };


std::string RandomString(int len)
{
	srand(time(NULL));
	std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string newstr;
	int pos;
	while (newstr.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}

void ov::create_window(bool console)
{
	if (!console)
		ShowWindow(GetConsoleWindow(), SW_SHOW);

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		0,
		WndProc,
		0,
		0,
		nullptr,
		LoadIcon(0, IDI_APPLICATION),
		LoadCursor(0, IDC_ARROW),
		nullptr,
		nullptr,
		globals.lWindowName = RandomString(10).c_str(),
		LoadIcon(nullptr, IDI_APPLICATION)
	};

	if (!RegisterClassEx(&wcex))
		return;

	globals.TargetWnd = FindWindowA(NULL, "DayZ");

	if (globals.TargetWnd)
	{
		RECT tSize;

		GetWindowRect(globals.TargetWnd, &tSize);
		globals.width = tSize.right - tSize.left;
		globals.height = tSize.bottom - tSize.top;

		globals.OverlayWnd = CreateWindowEx(
			NULL,
			globals.lWindowName = RandomString(10).c_str(),
			globals.lWindowName = RandomString(10).c_str(),
			WS_POPUP | WS_VISIBLE,
			tSize.left,
			tSize.top,
			globals.width,
			globals.height,
			NULL,
			NULL,
			0,
			NULL
		);

		const MARGINS Margin = { 0, 0, globals.width, globals.height };

		DwmExtendFrameIntoClientArea(globals.OverlayWnd, &Margin);
		SetWindowLong(globals.OverlayWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE);
		//SetWindowPos(globals.OverlayWnd, HWND_TOPMOST, tSize.left, tSize.top, globals.width, globals.height, SWP_SHOWWINDOW);
		ShowWindow(globals.OverlayWnd, SW_SHOW);

	}

#ifdef _DEBUG
	std::cout << "Success create window.." << std::endl;
#endif

	setup_directx(globals.OverlayWnd);
}

void ov::setup_directx(HWND hWnd)
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		exit(3);

	ZeroMemory(&p_Params, sizeof(p_Params));
	p_Params.Windowed = TRUE;
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
	p_Params.hDeviceWindow = hWnd;
	p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
	p_Params.BackBufferWidth = globals.width;
	p_Params.BackBufferHeight = globals.height;
	p_Params.EnableAutoDepthStencil = TRUE;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16;
	p_Params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device)))
	{
		p_Object->Release();
		exit(4);
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Arial.ttf", 16.0f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(p_Device);

	//io.Fonts->AddFontFromMemoryCompressedTTF(Cousine_compressed_data, Cousine_compressed_size, 16.0f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
	p_Object->Release();
}



void ov::update_overlay()
{
	HWND hwnd_active = GetForegroundWindow();
	if (hwnd_active == globals.TargetWnd)
	{
		HWND temp_hwnd = GetWindow(hwnd_active, GW_HWNDPREV);
		SetWindowPos(globals.OverlayWnd, temp_hwnd, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	}
}

auto TabButton(const char* label, int* index, int val, bool sameline) -> VOID
{
	if (*index == val)
	{
		if (ImGui::Button(label, ImVec2(80, 25)))
			*index = val;
		if (sameline)
			ImGui::SameLine();
	}
	else
	{
		if (ImGui::Button(label, ImVec2(80, 25)))
			*index = val;
		if (sameline)
			ImGui::SameLine();
	}
}

void InputHandler() {
	for (int i = 0; i < 5; i++) ImGui::GetIO().MouseDown[i] = false;
	int button = -1;
	if (GetAsyncKeyState(VK_LBUTTON)) button = 0;
	if (button != -1) ImGui::GetIO().MouseDown[button] = true;
}


bool MenuKey()
{
	return GetAsyncKeyState(globals.MENUkeys[globals.MENUKey]) & 1;
}

void RenderMenu()
{
	if (MenuKey())
		globals.menu = !globals.menu;

	// Set custom colors
	ImGuiStyle& style = ImGui::GetStyle();

	style.WindowMinSize = ImVec2(256, 300);
	style.WindowTitleAlign = ImVec2(0.5, 0.5);
	style.FrameBorderSize = 1;
	style.ChildBorderSize = 1;
	style.WindowBorderSize = 1;
	style.WindowRounding = 0;
	style.FrameRounding = 0;
	style.ChildRounding = 0;
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 0.85f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.10f, 0.09f, 0.12f, 0.85f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10f, 0.09f, 0.12f, 0.85f);
	style.Colors[ImGuiCol_WindowBg] = ImColor(25, 25, 25, 250);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.40f, 0.90f, 0.43f, 0.80f);
	style.Colors[ImGuiCol_Border] = ImColor(70, 70, 70);
	style.Colors[ImGuiCol_Button] = ImColor(32, 32, 32);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(42, 42, 42);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(42, 42, 42);
	style.Colors[ImGuiCol_ChildBg] = ImColor(45, 45, 45);
	style.Colors[ImGuiCol_FrameBg] = ImColor(32, 32, 32);
	style.Colors[ImGuiCol_FrameBgActive] = ImColor(42, 42, 42);
	style.Colors[ImGuiCol_FrameBgHovered] = ImColor(42, 42, 42);
	style.Colors[ImGuiCol_SliderGrab] = ImColor(255, 255, 255);
	style.Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 255, 255);

	if (globals.menu)
	{
		InputHandler();
		ImGui::SetNextWindowSize(ImVec2(475, 440)); // 450,426

		if (globals.tab_index == 0)
		{
			ImGui::SetNextWindowSize(ImVec2(675, 440)); // 450,426
		}

		if (globals.tab_index == 0 && globals.LegitSilentAim && globals.AnimalsAim)
		{
			ImGui::SetNextWindowSize(ImVec2(675, 480)); // 450,426
		}

		if (globals.tab_index == 1)
		{
			ImGui::SetNextWindowSize(ImVec2(675, 380)); // 450,426
		}

		if (globals.tab_index == 1 && globals.playertracer && globals.box)
		{
			ImGui::SetNextWindowSize(ImVec2(675, 410)); // 450,426
		}

		if (globals.tab_index == 2 && globals.weapon != globals.clothing)
		{
			ImGui::SetNextWindowSize(ImVec2(475, 600));
		}

		else if (globals.tab_index == 2 && globals.clothing && globals.clothing)
		{
			ImGui::SetNextWindowSize(ImVec2(475, 740));
		}

		if (globals.tab_index == 3 && globals.military && globals.City_Esp)
		{
			ImGui::SetNextWindowSize(ImVec2(475, 590));
		}

		if (globals.tab_index == 3 && globals.City_Esp != globals.military)
		{
			ImGui::SetNextWindowSize(ImVec2(475, 500));
		}

		if (globals.tab_index == 3 && globals.military && globals.NightVision)
		{
			ImGui::SetNextWindowSize(ImVec2(475, 600));
		}

		ImGui::Begin(xorstr("P U S S Y C A T"), 0, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);
		{
			ImGui::BeginGroup();

			ImGui::Text(xorstr(""));
			ImGui::Spacing();
			TabButton(xorstr("Aimbot"), &globals.tab_index, 0, false);
			ImGui::Spacing();
			TabButton(xorstr("Entities"), &globals.tab_index, 1, false);
			ImGui::Spacing();
			TabButton(xorstr("Items"), &globals.tab_index, 2, false);
			ImGui::Spacing();
			TabButton(xorstr("Misc"), &globals.tab_index, 3, false);

			ImGui::EndGroup();
			ImGui::SameLine();

			ImGui::BeginGroup();

			if (globals.tab_index == 0)
			{
				ImGui::Text(xorstr(""));
				ImGui::Spacing();
				ImGui::Columns(2, nullptr, false); // Start three columns

				// Column 1 (Silent Aim)
				ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
				ImGui::Checkbox(xorstr("Silent Aim"), &globals.SilentAim);
				if (globals.SilentAim)
				{
					ImGui::Checkbox(xorstr("Players"), &globals.PlayerAim);
					if (globals.PlayerAim)
					{
						ImGui::Text(xorstr("Target Bone"));
						ImGui::Combo(xorstr("   "), &globals.bone, globals.bonepos, 3);
						ImGui::Spacing();
					}
					ImGui::Checkbox(xorstr("Zombies"), &globals.ZombieAim);
					ImGui::Checkbox(xorstr("Animals / Mutants"), &globals.AnimalsAim);
				}
				ImGui::PopStyleVar();

				ImGui::NextColumn(); // Move to the next column

				// Column 2 (Legit Silent Aim)
				ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
				ImGui::Checkbox(xorstr("Legit Silent Aim"), &globals.LegitSilentAim);
				if (globals.LegitSilentAim)
				{
					ImGui::Checkbox(xorstr("Players"), &globals.PlayerAim);
					if (globals.PlayerAim)
					{
						ImGui::Text(xorstr("Target State"));
						ImGui::Combo("   ", &globals.legitcheck, globals.legit, 3);
						ImGui::Spacing();
					}
					ImGui::Checkbox(xorstr("Zombies"), &globals.ZombieAim);
					ImGui::Checkbox(xorstr("Animals / Mutants"), &globals.AnimalsAim);
					if (globals.AnimalsAim)
					{
						ImGui::Text(xorstr("Target Size"));
						ImGui::Combo(xorstr("    "), &globals.sizecheck, globals.size, 3);
						ImGui::Spacing();
					}
				}
				ImGui::PopStyleVar();

				ImGui::Columns(1); // End the columns

				// Column 3 (Additional Settings)
				ImGui::NewLine();
				ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);
				ImGui::Text(xorstr("Aimbot Key"));
				ImGui::Combo(xorstr("       "), &globals.AimKey, globals.keyItems, 7);
				ImGui::Text(xorstr("Distance"));
				ImGui::SliderInt(xorstr(" "), &globals.distancesilent, 1, 1000);
				ImGui::NewLine();
				ImGui::Checkbox(xorstr("Draw FOV"), &globals.DrawFov);
				ImGui::Text(xorstr("Radius FOV"));
				ImGui::SliderInt(xorstr(""), &globals.radius, 1, 960);
				ImGui::PopStyleVar();
			}




			else if (globals.tab_index == 1)
			{
				ImGui::Text(xorstr(""));
				ImGui::Spacing();

				ImGui::Columns(2, nullptr, false); // Start three columns
				ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);

				ImGui::Checkbox(xorstr("Players"), &globals.PlayerEsp);
				ImGui::Text(xorstr("Players Distance"));
				ImGui::SliderInt(xorstr(" "), &globals.playerdistance, 1, 1000); 
				ImGui::Checkbox(xorstr("Skeleton Players"), &globals.PlayerEspSkeleton);
				ImGui::Checkbox(xorstr("Dead Players"), &globals.deadplayer);
				ImGui::Checkbox(xorstr("Players Tracers"), &globals.playertracer); 
				if (globals.playertracer)
				{
					ImGui::Text(xorstr("Tracers Type"));
					ImGui::Combo(xorstr("               "), &globals.tracercheck, globals.tracer, 3);
				}
				ImGui::Checkbox(xorstr("Item in hands"), &globals.iteminhands);
				ImGui::Checkbox(xorstr("Players Inventory"), &globals.playersinventory);
				ImGui::Checkbox(xorstr("Players Names"), &globals.playernames);
				ImGui::Checkbox(xorstr("Players Box"), &globals.drawbox);
				if (globals.drawbox)
				{
					ImGui::Text(xorstr("Box Type"));
					ImGui::Combo(xorstr("             "), &globals.boxcheck, globals.box, 3);
				}

				ImGui::NextColumn(); // Move to the next column

				// Column 2 (Legit Silent Aim)
				ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);

				ImGui::Checkbox(xorstr("Zombie"), &globals.ZombieEsp);
				ImGui::Text(xorstr("Zombie Distance"));
				ImGui::SliderInt(xorstr(""), &globals.zombiedistance, 1, 100);
				ImGui::Checkbox(xorstr("Skeleton Zombie"), &globals.ZombieEspSkeleton);
				ImGui::Checkbox(xorstr("Zombie Box"), &globals.drawboxz);
				if(globals.drawboxz)
				{
					ImGui::Text(xorstr("Box Type"));
					ImGui::Combo(xorstr("            "), &globals.boxcheckZ, globals.boxZ, 3);
				}
				ImGui::NewLine();
				ImGui::Checkbox(xorstr("Animals / Mutants"), &globals.AnimalsEsp);
				ImGui::Checkbox(xorstr("Vehicle"), &globals.CarEsp);
				ImGui::Checkbox(xorstr("Vehicle Attachments"), &globals.carattachments);
				ImGui::Checkbox(xorstr("Vehicle Inventory"), &globals.carinventory);

				ImGui::Columns(1); // End the columns

				ImGui::PopStyleVar();
				
			}
			else if (globals.tab_index == 2)
			{
				ImGui::Text("");
				ImGui::Spacing();
				ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);

				ImGui::Checkbox(xorstr("Items Quality"), &globals.getquality);
				ImGui::Text("Items Distance");
				ImGui::SliderInt(xorstr(""), &globals.itemsdistance, 1, 1000);
				ImGui::Spacing();
				ImGui::Checkbox(xorstr("Weapons"), &globals.weapon);
				if (globals.weapon)
				{
					ImGui::Separator();
					ImGui::Spacing();

					// Begin a new column layout with three columns
					ImGui::Columns(3, nullptr, false);

					ImGui::Checkbox(xorstr("Firearms"), &globals.guns);
					ImGui::NextColumn();

					ImGui::Checkbox(xorstr("Shotguns"), &globals.shotguns);
					ImGui::NextColumn();

					ImGui::Checkbox(xorstr("Pistols"), &globals.pistols);
					ImGui::NextColumn();

					ImGui::Checkbox(xorstr("Magazines"), &globals.magazines);
					ImGui::NextColumn();

					ImGui::Checkbox(xorstr("Ammo"), &globals.ammo);
					ImGui::NextColumn();

					ImGui::Checkbox(xorstr("Optics"), &globals.optics);
					ImGui::NextColumn();

					ImGui::Checkbox(xorstr("Bayonet"), &globals.bayonet);
					ImGui::NextColumn();

					ImGui::Checkbox(xorstr("Buttstock"), &globals.buttstock);
					ImGui::NextColumn();

					ImGui::Checkbox(xorstr("Melee"), &globals.melee);
					ImGui::NextColumn();

					ImGui::Checkbox(xorstr("Explosives"), &globals.explosives);
					ImGui::NextColumn();

					// End the column layout
					ImGui::Columns(1);

					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Checkbox(xorstr("All Attachments"), &globals.allattachments);
					ImGui::NextColumn();
					ImGui::Checkbox(xorstr("Weapon Inventory"), &globals.weaponinventory);
					ImGui::NewLine();
					ImGui::Spacing();

				}
				ImGui::Checkbox(xorstr("Clothing"), &globals.clothing);
				if (globals.clothing)
				{
					ImGui::Separator();
					ImGui::Spacing();

					// Begin a new column layout with three columns
					ImGui::Columns(3, nullptr, false);

					ImGui::Checkbox(xorstr("Headgear"), &globals.headgear);
					ImGui::NextColumn();

					ImGui::Checkbox(xorstr("Belts"), &globals.belts);
					ImGui::NextColumn();

					ImGui::Checkbox(xorstr("Masks"), &globals.masks);
					ImGui::NextColumn();

					ImGui::Checkbox(xorstr("Tops"), &globals.tops);
					ImGui::NextColumn();

					ImGui::Checkbox(xorstr("Backpacks"), &globals.backpacks);
					ImGui::NextColumn();

					ImGui::Checkbox(xorstr("Vests"), &globals.vests);
					ImGui::NextColumn();

					ImGui::Checkbox(xorstr("Gloves"), &globals.gloves);
					ImGui::NextColumn();

					ImGui::Checkbox(xorstr("Pants"), &globals.pants);
					ImGui::NextColumn();

					ImGui::Checkbox(xorstr("Shoes"), &globals.shoes);
					ImGui::NextColumn();

					// End the column layout
					ImGui::Columns(1);

					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Checkbox(xorstr("All Clothing"), &globals.allclothings);
					ImGui::NewLine();
					ImGui::Spacing();

				}

				ImGui::Checkbox(xorstr("Food"), &globals.food);
				ImGui::Checkbox(xorstr("Medical"), &globals.medical);
				ImGui::Checkbox(xorstr("Inventory Items"), &globals.inventoryItem);
				ImGui::Checkbox(xorstr("Building Items"), &globals.builditems);
				ImGui::Checkbox(xorstr("Car Items"), &globals.caritems);
				ImGui::Checkbox(xorstr("Storage"), &globals.storage); 
				if(globals.storage)
				{
					ImGui::Checkbox(xorstr("Storage Inventory"), &globals.showstorage);
				}
				ImGui::Spacing();
				ImGui::Checkbox(xorstr("All Items"), &globals.allitems);

				ImGui::PopStyleVar();
			}
			else if (globals.tab_index == 3)
			{
				ImGui::Text("");
				ImGui::Spacing();
				ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);

				ImGui::Checkbox(xorstr("Disable Grass"), &globals.GrassDisable);
				ImGui::Checkbox(xorstr("Time Set"), &globals.SetDay);
				if (globals.SetDay) {
					ImGui::SliderInt(xorstr(""), &globals.timeset, 0, 12);
				}
				ImGui::Checkbox(xorstr("Night Vision"), &globals.NightVision);
				ImGui::Checkbox(xorstr("Compass"), &globals.compass);
				ImGui::Checkbox(xorstr("Crosshair"), &globals.crosshair);
				ImGui::Checkbox(xorstr("City"), &globals.City_Esp);
				if (globals.City_Esp)
				{
					if (globals.city || globals.military || globals.others)
					{
						ImGui::Text(xorstr("[Prees MiddleButton]"));
					}
					ImGui::Separator();
					ImGui::Checkbox(xorstr("Main City"), &globals.city);
					ImGui::Checkbox(xorstr("Military"), &globals.military);
					if (globals.military && globals.City_Esp)
					{
						ImGui::Spacing();
						ImGui::Checkbox(xorstr("Tier 2"), &globals.tier2);
						ImGui::Checkbox(xorstr("Tier 3"), &globals.tier3);
						ImGui::Checkbox(xorstr("Tier 4"), &globals.tier4);
						ImGui::Spacing();
					}
					ImGui::Checkbox(xorstr("Others"), &globals.others);
					ImGui::Separator();
					ImGui::NewLine();
				}
				//ImGui::Checkbox(xorstr("Server Name"), &globals.servername);
				//ImGui::Checkbox(xorstr("Count Players"), &globals.playerscount);

				ImGui::NewLine();
				ImGui::NewLine();
				ImGui::NewLine();

				ImGui::Text(xorstr("Menu Key"));
				ImGui::Combo(xorstr("        "), &globals.MENUKey, globals.keyMENU, 7);

				ImGui::PopStyleVar();
			}
			ImGui::EndGroup();
		}
		ImGui::PopStyleVar(0);
		ImGui::End();
	}
}

void ov::render()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	update_overlay();
	RenderMenu();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0)); // Invisible 
	ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
	ImGui::Begin(("##scene"), nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);

	int tWidth = globals.width;	int tHeight = globals.height;

	Hack();

	Items();

	SlowItems();

	ImGui::GetWindowDrawList()->PushClipRectFullScreen();
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(2);

	ImGui::EndFrame();
	p_Device->SetRenderState(D3DRS_ZENABLE, false);
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	p_Device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	p_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (p_Device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		p_Device->EndScene();
	}
	HRESULT result = p_Device->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && p_Device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		p_Device->Reset(&p_Params);
		ImGui_ImplDX9_CreateDeviceObjects();
	}

}

WPARAM ov::loop()
{
	MSG msg;

	while (true)
	{
		ZeroMemory(&msg, sizeof(MSG));
		if (::PeekMessage(&msg, globals.OverlayWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT || GetAsyncKeyState(VK_DELETE) || FindWindowA(NULL, xorstr("DayZ")) == NULL)
			exit(0);

		ov::render();
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	clean_directx();
	DestroyWindow(globals.OverlayWnd);

	return msg.wParam;
}

void ov::clean_directx()
{
	if (p_Device != NULL)
	{
		p_Device->EndScene();
		p_Device->Release();
	}
	if (p_Object != NULL)
	{
		p_Object->Release();
	}
}