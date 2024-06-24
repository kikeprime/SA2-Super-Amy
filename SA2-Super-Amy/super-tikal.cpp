#include "pch.h"
#include "ss.h"

static FunctionHook<void, int>LoadTikal_t(LoadTikal);
extern std::string currentSuperMusic;

void __cdecl LoadSTikalEff_Textures() {
	njReleaseTexture(&STKAura_Texlist);
	LoadTextureList("skaura_efftex", &STKAura_Texlist);
	return;
}

void __cdecl LoadHTikalEff_Textures() {
	njReleaseTexture(&STKAura_Texlist);
	LoadTextureList("haura_efftex", &STKAura_Texlist);
	return;
}

void __cdecl LoadSuperTikalCharTextures(KnucklesCharObj2* kco2) {
	LoadSTikalEff_Textures();
	njReleaseTexture(kco2->TextureList);
	kco2->TextureList = 0;
	if (ModelSwap1)
	{
		if (!AltCostume[kco2->base.PlayerNum])
		{
			kco2->TextureList = LoadCharTextures("SSTIKALTEX");
		}
		else
		{
			kco2->TextureList = LoadCharTextures("SSTIKAL1TEX");
		}
	}
	else
	{
		if (!AltCostume[kco2->base.PlayerNum])
		{
			kco2->TextureList = LoadCharTextures("STIKALTEX");
		}
		else
		{
			kco2->TextureList = LoadCharTextures("STIKAL1TEX");
		}
	}

	//ugly way to fix Shadow eyes texture when transforming to super, thanks to the awful GBIX Texture system.
	if (TwoPlayerMode || CurrentLevel == LevelIDs_SonicVsShadow1 || CurrentLevel == LevelIDs_SonicVsShadow2)
	{
		char OtherPlayer = kco2->base.PlayerNum == 0 ? 1 : 0;

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

void __cdecl LoadHyperTikalCharTextures(KnucklesCharObj2* kco2) {
	LoadHTikalEff_Textures();
	njReleaseTexture(kco2->TextureList);
	kco2->TextureList = 0;
	if (ModelSwap2)
	{
		if (!AltCostume[kco2->base.PlayerNum])
		{
			kco2->TextureList = LoadCharTextures("HSHSTIKALTEX");
		}
		else
		{
			kco2->TextureList = LoadCharTextures("HSHSTIKAL1TEX");
		}
	}
	else if (ModelSwap1)
	{
		if (!AltCostume[kco2->base.PlayerNum])
		{
			kco2->TextureList = LoadCharTextures("HSSTIKALTEX");
		}
		else
		{
			kco2->TextureList = LoadCharTextures("HSSTIKAL1TEX");
		}
	}
	else
	{
		if (!AltCostume[kco2->base.PlayerNum])
		{
			kco2->TextureList = LoadCharTextures("HSTIKALTEX");
		}
		else
		{
			kco2->TextureList = LoadCharTextures("HSTIKAL1TEX");
		}
	}

	//ugly way to fix Shadow eyes texture when transforming to super, thanks to the awful GBIX Texture system.
	if (TwoPlayerMode || CurrentLevel == LevelIDs_SonicVsShadow1 || CurrentLevel == LevelIDs_SonicVsShadow2)
	{
		char OtherPlayer = kco2->base.PlayerNum == 0 ? 1 : 0;

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

AnimationInfo TikalAnimCopy[258];

void __cdecl TransfoSuperTikal(EntityData1* data, int playerID, KnucklesCharObj2* kco2) {
	if (!isSuper[playerID])
	{
		if (SuperMusicVersion != None) {
			StopMusic();
			Play_SuperSonicMusic();
			ResetMusic();
		}

		if (AllowSuperTikalModel)
		{
			ReleaseMDLFile(kco2->ModelList);
			kco2->ModelList = AltCostume[playerID] ? LoadMDLFile((char*)"STIKAL1MDL.PRS") : LoadMDLFile((char*)"STIKALMDL.PRS");
			ModelSwap1 = true;
		}

		ControllerEnabled[playerID] = 0;

		if (CurrentLevel != LevelIDs_ChaoWorld)
			kco2->base.Powerups |= Powerups_Invincibility;

//		kco2->base.AnimInfo.Next = 0;
//		kco2->base.AnimInfo.Animations = SuperTikalAnimationList_r;
		LoadSuperTikalCharTextures(kco2);

//		PlayAnimationThing(&kco2->base.AnimInfo);
		Load_SuperPhysics(data);

		kco2->base.Upgrades |= Upgrades_SuperSonic;

		isSuper[playerID] = true;
	}
	else
	{
		MainCharacter[playerID]->DisplaySub_Delayed4 = nullptr;
		if (AllowHyperTikalModel)
		{
			ReleaseMDLFile(kco2->ModelList);
			kco2->ModelList = AltCostume[playerID] ? LoadMDLFile((char*)"HSTIKAL1MDL.PRS") : LoadMDLFile((char*)"HSTIKALMDL.PRS");
			ModelSwap2 = true;
		}
		LoadHyperTikalCharTextures(kco2);
		kco2->base.Powerups |= Powerups_HyperSonic;
		isHyper[playerID] = true;
	}
}

void unSuperTikal(unsigned char player) {
	if (AlwaysSuperTikal)
		return;

	EntityData1* data = MainCharObj1[player];
	CharObj2Base* co2 = MainCharObj2[player];

	if (!data || !isSuper[player])
		return;

	KnucklesCharObj2* kco2 = (KnucklesCharObj2*)MainCharacter[player]->Data2.Character;

	if (co2->CharID == Characters_Tikal)
		co2->PhysData = PhysicsArray[Characters_Tikal];

	CharacterThrowObject(data, co2);
	ResetChaosControl(player);
	data->Status = 0;
	co2->Upgrades &= ~Upgrades_SuperSonic;
	co2->Powerups &= ~Powerups_HyperSonic;
	co2->Powerups &= ~Powerups_Invincibility;
//	kco2->base.AnimInfo.Next = 15;
//	kco2->base.AnimInfo.Animations = TikalAnimCopy;
	njReleaseTexture(kco2->TextureList);
	kco2->TextureList = 0;
	if (!AltCostume[player])
	{
		kco2->TextureList = LoadCharTextures("TICALTEX");
	}
	else
	{
		kco2->TextureList = LoadCharTextures("TIKAL1TEX");
	}

	MainCharacter[player]->DisplaySub_Delayed4 = nullptr;
	isHyper[player] = false;
	isSuper[player] = false;

	if (IsIngame())
	{
//		PlayAnimationThing(&kco2->base.AnimInfo);
		RestoreMusic();
	}

	if (ModelSwap1 || ModelSwap2)
	{
		ReleaseMDLFile(kco2->ModelList);
		kco2->ModelList = AltCostume[player] ? LoadMDLFile((char*)"TIKAL1MDL.PRS") : LoadMDLFile((char*)"TICALMDL.PRS");
		ModelSwap1 = false;
		ModelSwap2 = false;
	}

	return;
}

void SuperTikal_ManagerDelete(ObjectMaster* obj)
{
	currentSuperMusic = "";
	char pnum = obj->Data1.Entity->Index;
	unSuperTikal(pnum);
	isHyper[pnum] = false;
	isSuper[pnum] = false;
	ResetChaosControl(pnum);
//	Delete_STAnim();
}

void SuperTikal_Manager(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	EntityData1* player = MainCharObj1[data->Index];

	if (!player)
		return;

	KnucklesCharObj2* sonicCO2 = (KnucklesCharObj2*)MainCharacter[data->Index]->Data2.Character;

	if (sonicCO2->base.CharID2 != Characters_Tikal || (player->field_2 == 3 && data->Index == 1))
	{
		DeleteObject_(obj);
		return;
	}

	//if player dies, remove transformation and reset manager action.
	if (GameState == GameStates_LoadFinished && !AlwaysSuperTikal && data->Action > playerInputCheck) {
		unSuperTikal(data->Index);
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
		obj->DeleteSub = SuperTikal_ManagerDelete;
		data->Action++;
		break;
	case playerInputCheck:

		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || AlwaysSuperTikal || CurrentLevel == LevelIDs_FinalHazard)
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
		TransfoSuperTikal(player, playerID, sonicCO2);
		data->Action++;
		break;
	case superSonicTransition:
//		sonicCO2->base.AnimInfo.Next = superTikalIntro;
		data->Action++;
		break;
	case superSonicWait:

//		if (++data->Timer == 100 || AlwaysSuperTikal)
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
		if (isHunterFlyAllowed || CurrentLevel == LevelIDs_FinalHazard)
		{
			if (player->Action == Action_Glide && isSuper[playerID])
			{
				sonicCO2->base.Speed.y = 2;
			}
		}

		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || AlwaysSuperTikal || CurrentLevel == LevelIDs_FinalHazard && FHZHyperForm)
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

		Reload_SS_WaterTask(sonicCO2->base.CharID2, playerID);
		SubRings(playerID, data);

		break;
	case superSonicUntransfo:
//		SuperSonic_DisableFly(player, &sonicCO2->base);
		unSuperTikal(playerID);

		data->Action = playerInputCheck;
		break;
	}
}

void LoadSuperTikalManager(char playNum) {
	int id2 = MainCharObj2[playNum]->CharID2;

	if (id2 == Characters_Tikal) {
		ObjectMaster* superTikalManagerPtr = LoadObject(0, "SuperTikal_Manager", SuperTikal_Manager, LoadObj_Data1);

		if (superTikalManagerPtr)
		{
//			Load_NewSuperTikalAnim();
			superTikalManagerPtr->Data1.Entity->Index = playNum;
		}
	}
}

void LoadTikal_r(int playerNum) {
	if (AltCostume[playerNum])
	{
		LoadMDLFile((char*)"TIKAL1MDL.PRS");
	}
	LoadTikal_t.Original(playerNum);
	KnucklesCharObj2* kco2 = (KnucklesCharObj2*)MainCharacter[playerNum]->Data2.Character;
	if (AltCostume[playerNum])
	{
		kco2->TextureList = 0;
		kco2->TextureList = LoadCharTextures("TIKAL1TEX");
	}

//	if (CurrentLevel != LevelIDs_FinalHazard) {
		if (MainCharObj1[playerNum] && MainCharObj1[playerNum]->field_2 != 3) {
			LoadSuperTikalManager(playerNum);
			LoadSTikalEff_Textures();
			LoadWaterTextures(playerNum);
			LoadSADXAuraTextures(playerNum);
		}
//	}
}

void init_SuperTikal()
{
	LoadTikal_t.Hook(LoadTikal_r);
	return;
}