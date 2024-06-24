#include "pch.h"
#include "ss.h"


//Using LoadEggmanPtr doesn't work
UsercallFuncVoid(LoadEggman_h, (int playerNum), (playerNum), 0x73C220, rEAX);
//static FunctionHook<void, int>LoadEggman_t(LoadEggman);
extern std::string currentSuperMusic;

void __cdecl LoadSEggmanEff_Textures() {
	njReleaseTexture(&SEAura_Texlist);
	LoadTextureList("ssaura_efftex", &SEAura_Texlist);
	return;
}

void __cdecl LoadHEggmanEff_Textures() {
	njReleaseTexture(&SEAura_Texlist);
	LoadTextureList("haura_efftex", &SEAura_Texlist);
	return;
}

void __cdecl LoadSuperEggmanCharTextures(EggmanCharObj2* eco2) {
	LoadSEggmanEff_Textures();
	njReleaseTexture(eco2->TextureList);
	eco2->TextureList = 0;
	if (ModelSwap1)
	{
		if (!AltCostume[eco2->base.PlayerNum])
		{
			eco2->TextureList = LoadCharTextures("SEGGTEX");
		}
		else
		{
			eco2->TextureList = LoadCharTextures("SEGG1TEX");
		}
	}
	else
	{
		if (!AltCostume[eco2->base.PlayerNum])
		{
			eco2->TextureList = LoadCharTextures("SEGGTEX");
		}
		else
		{
			eco2->TextureList = LoadCharTextures("SEGG1TEX");
		}
	}

	//ugly way to fix Shadow eyes texture when transforming to super, thanks to the awful GBIX Texture system.
	if (TwoPlayerMode || CurrentLevel == LevelIDs_SonicVsShadow1 || CurrentLevel == LevelIDs_SonicVsShadow2)
	{
		char OtherPlayer = eco2->base.PlayerNum == 0 ? 1 : 0;

		if (MainCharObj2[OtherPlayer] && MainCharObj2[OtherPlayer]->CharID2 == Characters_Shadow && !isSuper[OtherPlayer])
		{
			SonicCharObj2* sco2 = (SonicCharObj2*)MainCharacter[OtherPlayer]->Data2.Character;

			if (AltCostume[OtherPlayer] != 0)
				sco2->TextureList = LoadCharTextures("SHADOW1TEX");
			else
				sco2->TextureList = LoadCharTextures("teriostex");
		}
	}

	return;
}

void __cdecl LoadHyperEggmanCharTextures(EggmanCharObj2* eco2) {
	LoadHEggmanEff_Textures();
	njReleaseTexture(eco2->TextureList);
	eco2->TextureList = 0;
	if (ModelSwap2)
	{
		if (!AltCostume[eco2->base.PlayerNum])
		{
			eco2->TextureList = LoadCharTextures("HSHSEGGTEX");
		}
		else
		{
			eco2->TextureList = LoadCharTextures("HSHSEGG1TEX");
		}
	}
	else if (ModelSwap1)
	{
		if (!AltCostume[eco2->base.PlayerNum])
		{
			eco2->TextureList = LoadCharTextures("HSSEGGTEX");
		}
		else
		{
			eco2->TextureList = LoadCharTextures("HSSEGG1TEX");
		}
	}
	else
	{
		if (!AltCostume[eco2->base.PlayerNum])
		{
			eco2->TextureList = LoadCharTextures("HSEGGTEX");
		}
		else
		{
			eco2->TextureList = LoadCharTextures("HSEGG1TEX");
		}
	}

	//ugly way to fix Shadow eyes texture when transforming to super, thanks to the awful GBIX Texture system.
	if (TwoPlayerMode || CurrentLevel == LevelIDs_SonicVsShadow1 || CurrentLevel == LevelIDs_SonicVsShadow2)
	{
		char OtherPlayer = eco2->base.PlayerNum == 0 ? 1 : 0;

		if (MainCharObj2[OtherPlayer] && MainCharObj2[OtherPlayer]->CharID2 == Characters_Shadow && !isSuper[OtherPlayer])
		{
			SonicCharObj2* sco2 = (SonicCharObj2*)MainCharacter[OtherPlayer]->Data2.Character;

			if (AltCostume[OtherPlayer] != 0)
				sco2->TextureList = LoadCharTextures("SHADOW1TEX");
			else
				sco2->TextureList = LoadCharTextures("teriostex");
		}
	}

	return;
}

AnimationInfo EggmanAnimCopy[258];

void __cdecl TransfoSuperEggman(EntityData1* data, int playerID, EggmanCharObj2* eco2) {
	if (!isSuper[playerID])
	{
		if (SuperMusicVersion != None) {
			StopMusic();
			Play_SuperSonicMusic();
			ResetMusic();
		}

		eco2->base.Speed.x = 0;

//		memcpy(&EggmanAnimCopy, eco2->base.AnimInfo.Animations, sizeof(EggmanAnimCopy));
		ControllerEnabled[playerID] = 0;

		if (CurrentLevel != LevelIDs_ChaoWorld)
			eco2->base.Powerups |= Powerups_Invincibility;

//		eco2->base.AnimInfo.Next = 0;
//		eco2->base.AnimInfo.Animations = SuperEggmanAnimationList_r;
		LoadSuperEggmanCharTextures(eco2);

		Load_SuperPhysics(data);

		eco2->base.Upgrades |= Upgrades_SuperSonic;

		isSuper[playerID] = true;
	}
	else
	{
		MainCharacter[playerID]->DisplaySub_Delayed4 = nullptr;
		LoadHyperEggmanCharTextures(eco2);
		eco2->base.Upgrades |= Upgrades_KnucklesAirNecklace;
		isHyper[playerID] = true;
	}

	PlayAnimationThing(&eco2->base.AnimInfo);
}

void unSuperEggman(unsigned char player) {
	if (AlwaysSuperEggman)
		return;

	EntityData1* data = MainCharObj1[player];
	CharObj2Base* co2 = MainCharObj2[player];

	if (!data || !isSuper[player])
		return;

	EggmanCharObj2* eco2 = (EggmanCharObj2*)MainCharacter[player]->Data2.Undefined;

	if (co2->CharID == Characters_Eggman)
		co2->PhysData = PhysicsArray[Characters_Eggman];

	CharacterThrowObject(data, co2);
	ResetChaosControl(player);
	data->Status = 0;
	if (co2->Upgrades & Upgrades_KnucklesAirNecklace)
	{
		co2->Upgrades &= ~Upgrades_KnucklesAirNecklace;
	}
	co2->Upgrades &= ~Upgrades_SuperSonic;
	co2->Powerups &= ~Powerups_Invincibility;
//	eco2->base.AnimInfo.Next = 15;
//	eco2->base.AnimInfo.Animations = EggmanAnimCopy;
	njReleaseTexture(eco2->TextureList);
	eco2->TextureList = 0;
	eco2->TextureList = LoadCharTextures("EGGTEX");

	MainCharacter[player]->DisplaySub_Delayed4 = nullptr;
	isHyper[player] = false;
	isSuper[player] = false;

	if (IsIngame())
	{
		PlayAnimationThing(&eco2->base.AnimInfo);
		RestoreMusic();
	}

	return;
}

void SuperEggman_ManagerDelete(ObjectMaster* obj)
{
	currentSuperMusic = "";
	char pnum = obj->Data1.Entity->Index;
	unSuperEggman(pnum);
	isSuper[pnum] = false;
	ResetChaosControl(pnum);
//	Delete_SEAnim();
}

void SuperEggman_Manager(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	EntityData1* player = MainCharObj1[data->Index];

	if (!player)
		return;

	CharObj2Base* co2 = obj->Data2.Character;
	EggmanCharObj2* eco2 = (EggmanCharObj2*)MainCharObj2[data->Index];
	//	EggmanCharObj2* eco2 = (EggmanCharObj2*)MainCharacter[data->Index]->Data2.Character;

	if (eco2->base.CharID2 != Characters_Eggman || (player->field_2 == 3 && data->Index == 1))
	{
		DeleteObject_(obj);
		return;
	}

	//if player dies, remove transformation and reset manager action.
	if (GameState == GameStates_LoadFinished && !AlwaysSuperEggman && data->Action > playerInputCheck) {
		unSuperEggman(data->Index);
		data->Action = playerInputCheck;
		return;
	}

	if (!player || !IsIngame() || GameMode == GameMode_Event || miniEventPtr && miniEventPtr->MainSub != nullptr) {
		return;
	}

	unsigned char playerID = data->Index;

	switch (data->Action)
	{
	case superSonicInit:
		obj->DeleteSub = SuperEggman_ManagerDelete;
		data->Action++;
		break;
	case playerInputCheck:
		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || AlwaysSuperEggman || CurrentLevel == LevelIDs_FinalHazard)
				data->Action++;
		}
		else
		{
			DeleteObject_(obj);
			return;
		}

		break;
	case superSonicTransfo:
		data->Scale.y = ControllerEnabled[playerID];
		TransfoSuperEggman(player, playerID, eco2);
		data->Action++;
		break;
	case superSonicTransition:
		//		sonicCO2->base.AnimInfo.Next = superEggmanIntro;
		data->Action++;
		break;
	case superSonicWait:

		//		if (++data->Timer == 100 || AlwaysSuperEggman)
	{
		Load_SSWaterTask(playerID);
		LoadSuperAura(playerID);
		ControllerEnabled[playerID] = data->Scale.y;
		DoNextAction_r(playerID, 15, 0);
		data->Action++;
		//			data->Timer = 0;
	}
	break;
	case superSonicOnFrames:
		if (ControllerPointers[playerID]->on & Buttons_A)
		{
			eco2->base.Speed.y = 2;
		}
		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || AlwaysSuperEggman || CurrentLevel == LevelIDs_FinalHazard)
			{
				data->Action = superSonicTransfo;
			}
			else
			{
				if (CheckUntransform_Input(playerID)) {
					data->Action = playerInputCheck;
				}
			}
		}
		Reload_SS_WaterTask(eco2->base.CharID2, playerID);
		SubRings(playerID, data);
		break;
	case superSonicUntransfo:
		//		SuperSonic_DisableFly(player, &sonicCO2->base);
		unSuperEggman(playerID);

		data->Action = playerInputCheck;
		break;
	}
}

void LoadSuperEggmanManager(char playNum) {
	int id2 = MainCharObj2[playNum]->CharID2;

	if (id2 == Characters_Eggman)
	{
		ObjectMaster* superEggmanManagerPtr = LoadObject(1, "SuperEggman_Manager", SuperEggman_Manager, LoadObj_Data1);

		if (superEggmanManagerPtr)
		{
			//			Load_NewSuperEggmanAnim();
			superEggmanManagerPtr->Data1.Entity->Index = playNum;
		}
	}
}

void LoadEggman_r(int playerNum) {
	LoadEggman_h.Original(playerNum);

	//	if (CurrentLevel != LevelIDs_FinalHazard) {
	if (MainCharObj1[playerNum] && MainCharObj1[playerNum]->field_2 != 3)
	{
		LoadSuperEggmanManager(playerNum);
		LoadSSEff_Textures();
		LoadSEggmanEff_Textures();
		LoadWaterTextures(playerNum);
		LoadSADXAuraTextures(playerNum);
	}
	//	}
}

void init_SuperEggman()
{
	LoadEggman_h.Hook(LoadEggman_r);
	return;
}