#include "pch.h"
#include <fstream>
#include "ss.h"

HelperFunctions HelperFunctionsGlobal;
const char* error = "[SA2 Super Sonic]: WARNING: Your version of the Mod Loader is old, the mod won't work properly.\nPlease update your Mod Loader for the best experience.";
time_t t;
HMODULE SA2SS = NULL;
HMODULE SA2Anim = NULL;
HMODULE SA1Char = NULL;
HMODULE SonkTrick = NULL;
HMODULE DCCharsDLL = NULL;
HMODULE DisableUpgradeModelsDLL = NULL;
HMODULE BetterMilesDLL = NULL;
HMODULE AmyNewTricksDLL = NULL;
std::string modpath;
std::string DCCharsPath;
std::string DisableUpgradeModelsPath;
std::string BetterMilesPath;
std::string AmyNewTricksPath;

bool GammaAsMechEggmanMod = false;
bool BigAsDarkChao = false;

bool SSLS = true;
bool SSFR = true;
bool SSBB = true;
bool SSMG = true;
bool ShAS = true;
bool ShFR = true;

NJS_VECTOR SavePos = { 0, 0, 0 };
Rotation SaveRot = { 0, 0, 0 };

extern "C" {
	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		Sleep(10);

		srand((unsigned)time(&t));
		HelperFunctionsGlobal = helperFunctions;

		if (HelperFunctionsGlobal.Version < 8) {
			PrintDebug(error);
			MessageBoxA(MainWindowHandle, error, "SA2 Super Sonic", MB_ICONWARNING);
		}

		SA2SS = GetModuleHandle(L"SA2-Super-Sonic");
		SA2Anim = GetModuleHandle(L"SA2-Anim-Break");
		SA1Char = GetModuleHandle(L"SA2-SA1-Chars");
		SonkTrick = GetModuleHandle(L"SA2-Sonic-Tricks");
		DCCharsDLL = GetModuleHandle(L"DCCharacters");
		DisableUpgradeModelsDLL = GetModuleHandle(L"SA2DisableUpgradeModels");
		BetterMilesDLL = GetModuleHandle(L"SA2-Better-Miles");
		AmyNewTricksDLL = GetModuleHandle(L"SA2-Amy-New-Tricks");

		modpath = std::string(path);
		auto GammaMod = helperFunctions.Mods->find_by_name("E-102 Gamma");
		auto DCChars = helperFunctions.Mods->find_by_dll(DCCharsDLL);
		DCCharsPath = DCChars->Folder;
		auto DisableUpgradeModels = helperFunctions.Mods->find_by_dll(DisableUpgradeModelsDLL);
		DisableUpgradeModelsPath = DisableUpgradeModels->Folder;
		auto BetterMiles = helperFunctions.Mods->find_by_dll(BetterMilesDLL);
		BetterMilesPath = BetterMiles->Folder;
		auto AmyNewTricks = helperFunctions.Mods->find_by_dll(AmyNewTricksDLL);
		AmyNewTricksPath = AmyNewTricks->Folder;
		
		//Gamma mod
		if (GammaMod)
		{
			GammaAsMechEggmanMod = true;
		}

//		ReadButtons(path); //get mod settings by the user

		ReadConfig(modpath); //get mod settings by the user
		if(SA2SS)
		{
			init_SuperSonic();
//			init_SuperShadow();
			init_SuperAmy();
			init_SuperMetalSonic();
			init_SuperTails();
			init_SuperEggman();
			init_SuperKnuckles();
			init_SuperRouge();
			init_SuperTikal();
			init_SuperChaos();
			init_SuperMechTails();
			init_SuperMechEggman();
			init_SuperChaoWalker();
			init_SuperDarkChaoWalker();

			init_MusicHack();
			init_PhysicsHack();
			init_AuraHack();
			init_WaterHack();

			init_FinalHazardHack();
		}
	}

	__declspec(dllexport) void __cdecl OnFrame() {
		DisplayTimed_Message_OnFrames();
	}
	
	void UltimateCharSel()
	{
		//Eggman switch
		if (!TwoPlayerMode && IsIngame())
		{
			if (CurrentCharacter == Characters_Eggman || CurrentCharacter == Characters_MechEggman)
			{
				if (GetAsyncKeyState(P1ESwitchKey) & 0x0001 && keswitch1 || ControllerPointers[0]->press & Buttons_Down && !keswitch1)
				{
					SavePos = MainCharObj1[0]->Position;
					SaveRot = MainCharObj1[0]->Rotation;
					if (CurrentCharacter == Characters_MechEggman)
					{
						unSuperMechEggman(0);
						DeleteObject_(MainCharacter[0]);
						CurrentCharacter = Characters_Eggman;
						LoadEggman(0);
					}
					else if (CurrentCharacter == Characters_Eggman)
					{
						unSuperEggman(0);
						DeleteObject_(MainCharacter[0]);
						CurrentCharacter = Characters_MechEggman;
						LoadMechEggman(0);
					}
					MainCharObj1[0]->Position = SavePos;
					MainCharObj1[0]->Rotation = SaveRot;
					InitCharacterSound();
				}
			}
		}

		if (!TwoPlayerMode && IsIngame())
		{
			if (GetKeyState(9) & 0x8000)
			{
				if (isSuper[0])
				{
					switch (MainCharObj2[0]->CharID2)
					{
					case Characters_Sonic:
					{
						unSuper(0);
						break;
					}
					case Characters_Shadow:
					{
						unSuperShadow(0);
						break;
					}
					case Characters_Amy:
					{
						unSuperAmy(0);
						break;
					}
					case Characters_MetalSonic:
					{
						unSuperMetalSonic(0);
						break;
					}
					case Characters_Tails:
					{
						unSuperTails(0);
						break;
					}
					case Characters_MechTails:
					{
						unSuperMechTails(0);
						break;
					}
					case Characters_Eggman:
					{
						unSuperEggman(0);
						break;
					}
					case Characters_MechEggman:
					{
						unSuperMechEggman(0);
						break;
					}
					case Characters_Knuckles:
					{
						unSuperKnux(0);
						break;
					}
					case Characters_Rouge:
					{
						unSuperRouge(0);
						break;
					}
					case Characters_Tikal:
					{
						unSuperTikal(0);
						break;
					}
					case Characters_Chaos:
					{
						unSuperChaos(0);
						break;
					}
					case Characters_ChaoWalker:
					{
						unSuperChaoWalker(0);
						break;
					}
					case Characters_DarkChaoWalker:
					{
						unSuperDarkChaoWalker(0);
						break;
					}
					default:
						break;
					}
				}

				SavePos = MainCharObj1[0]->Position;
				SaveRot = MainCharObj1[0]->Rotation;

				if (ControllerPointers[0]->press & Buttons_Up)
				{
					AltCharacter[0] = 0;
					AltCostume[0] = 0;
					if (ControllerPointers[0]->on & Buttons_L)
					{
						AltCharacter[0] = 1;
					}
					if (ControllerPointers[0]->on & Buttons_R)
					{
						AltCostume[0] = 1;
					}
					DeleteObject_(MainCharacter[0]);
					if (!AltCharacter[0])
					{
						CurrentCharacter = Characters_Sonic;
					}
					else
					{
						CurrentCharacter = Characters_Amy;
					}
					LoadSonic(0);
					InitPlayer(0);
				}
				else if (ControllerPointers[0]->press & Buttons_Down)
				{
					AltCharacter[0] = 0;
					AltCostume[0] = 0;
					if (ControllerPointers[0]->on & Buttons_L)
					{
						AltCharacter[0] = 1;
					}
					if (ControllerPointers[0]->on & Buttons_R)
					{
						AltCostume[0] = 1;
					}
					DeleteObject_(MainCharacter[0]);
					if (!AltCharacter[0])
					{
						CurrentCharacter = Characters_Shadow;
					}
					else
					{
						CurrentCharacter = Characters_MetalSonic;
					}
					LoadShadow(0);
					InitPlayer(0);
				}
				else if (ControllerPointers[0]->press & Buttons_Left)
				{
					AltCharacter[0] = 0;
					AltCostume[0] = 0;
					if (ControllerPointers[0]->on & Buttons_L)
					{
						AltCharacter[0] = 1;
					}
					if (ControllerPointers[0]->on & Buttons_R)
					{
						AltCostume[0] = 1;
					}
					DeleteObject_(MainCharacter[0]);
					if (!AltCharacter[0])
					{
						CurrentCharacter = Characters_Knuckles;
					}
					else
					{
						CurrentCharacter = Characters_Tikal;
					}
					LoadKnuckles(0);
					InitPlayer(0);
				}
				else if (ControllerPointers[0]->press & Buttons_Right)
				{
					AltCharacter[0] = 0;
					AltCostume[0] = 0;
					if (ControllerPointers[0]->on & Buttons_L)
					{
						AltCharacter[0] = 1;
					}
					if (ControllerPointers[0]->on & Buttons_R)
					{
						AltCostume[0] = 1;
					}
					DeleteObject_(MainCharacter[0]);
					if (!AltCharacter[0])
					{
						CurrentCharacter = Characters_Rouge;
					}
					else
					{
						CurrentCharacter = Characters_Chaos;
					}
					LoadRouge(0);
					InitPlayer(0);
				}
				else if (ControllerPointers[0]->press & Buttons_Y)
				{
					AltCharacter[0] = 0;
					AltCostume[0] = 0;
					if (ControllerPointers[0]->on & Buttons_L)
					{
						AltCharacter[0] = 1;
					}
					if (ControllerPointers[0]->on & Buttons_R)
					{
						AltCostume[0] = 1;
					}
					DeleteObject_(MainCharacter[0]);
					if (!AltCharacter[0])
					{
						CurrentCharacter = Characters_MechTails;
					}
					else
					{
						CurrentCharacter = Characters_ChaoWalker;
					}
					LoadMechTails(0);
					InitPlayer(0);
				}
				else if (ControllerPointers[0]->press & Buttons_X)
				{
					AltCharacter[0] = 0;
					AltCostume[0] = 0;
					if (ControllerPointers[0]->on & Buttons_L)
					{
						AltCharacter[0] = 1;
					}
					if (ControllerPointers[0]->on & Buttons_R)
					{
						AltCostume[0] = 1;
					}
					DeleteObject_(MainCharacter[0]);
					CurrentCharacter = Characters_Eggman;
					LoadEggman(0);
					InitPlayer(0);
				}
				else if (ControllerPointers[0]->press & Buttons_B)
				{
					AltCharacter[0] = 0;
					AltCostume[0] = 0;
					if (ControllerPointers[0]->on & Buttons_L)
					{
						AltCharacter[0] = 1;
					}
					if (ControllerPointers[0]->on & Buttons_R)
					{
						AltCostume[0] = 1;
					}
					DeleteObject_(MainCharacter[0]);
					if (!AltCharacter[0])
					{
						CurrentCharacter = Characters_MechEggman;
					}
					else
					{
						CurrentCharacter = Characters_DarkChaoWalker;
					}
					LoadMechEggman(0);
					InitPlayer(0);
				}
				else if (ControllerPointers[0]->press & Buttons_A)
				{
					AltCharacter[0] = 1;
					AltCostume[0] = 1;
					DeleteObject_(MainCharacter[0]);
					if (!AltCharacter[0])
					{
						CurrentCharacter = Characters_MechEggman;
					}
					else
					{
						CurrentCharacter = Characters_DarkChaoWalker;
					}
					LoadMechEggman(0);
					InitPlayer(0);
				}

				MainCharObj1[0]->Position = SavePos;
				MainCharObj1[0]->Rotation = SaveRot;
				InitCharacterSound();
			}
		}
	}

	__declspec(dllexport) void __cdecl OnControl() {
		if (GetKeyState(VK_F12) & 0x8000)
		{
			ReadConfig(modpath); //get mod settings by the user
		}

//		UltimateCharSel();
	}

	__declspec(dllexport) void __cdecl OnExit()
	{
		FreeWaterMDL();
		Free_AuraModels();
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}