#include "pch.h"
#include "ss.h"

static FunctionHook<void, int>LoadRouge_t(LoadRouge);
extern std::string currentSuperMusic;

void __cdecl LoadSRougeEff_Textures() {
	njReleaseTexture(&SRAura_Texlist);
	LoadTextureList("ssaura_efftex", &SRAura_Texlist);
	return;
}

void __cdecl LoadHRougeEff_Textures() {
	njReleaseTexture(&SRAura_Texlist);
	LoadTextureList("skaura_efftex", &SRAura_Texlist);
	return;
}

void __cdecl LoadSuperRougeCharTextures(KnucklesCharObj2* kco2) {
	LoadSRougeEff_Textures();
	njReleaseTexture(kco2->TextureList);
	kco2->TextureList = 0;
	if (ModelSwap1)
	{
		if (!AltCostume[kco2->base.PlayerNum])
		{
			kco2->TextureList = LoadCharTextures("SSROUGETEX");
		}
		else
		{
			kco2->TextureList = LoadCharTextures("SSBROUGETEX");
		}
	}
	else
	{
		if (!AltCostume[kco2->base.PlayerNum])
		{
			kco2->TextureList = LoadCharTextures("SROUGETEX");
		}
		else
		{
			kco2->TextureList = LoadCharTextures("SBROUGETEX");
		}
	}

	//ugly way to fix Shadow eyes texture when transforming to super, thanks to the awful GBIX Texture system.
	if (TwoPlayerMode || CurrentLevel == LevelIDs_SonicVsShadow1 || CurrentLevel == LevelIDs_SonicVsShadow2)
	{
		char OtherPlayer = kco2->base.PlayerNum == 0 ? 1 : 0;

		if (MainCharObj2[OtherPlayer] && MainCharObj2[OtherPlayer]->CharID2 == Characters_Shadow && !isSuper[OtherPlayer])
		{
			SonicCharObj2* kco2H = (SonicCharObj2*)MainCharacter[OtherPlayer]->Data2.Character;

			if (AltCostume[OtherPlayer] != 0)
				kco2H->TextureList = LoadCharTextures("SHADOW1TEX");
			else
				kco2H->TextureList = LoadCharTextures("teriostex");
		}
	}

	return;
}

void __cdecl LoadHyperRougeCharTextures(KnucklesCharObj2* kco2) {
	LoadHRougeEff_Textures();
	njReleaseTexture(kco2->TextureList);
	kco2->TextureList = 0;
	if (ModelSwap2)
	{
		if (!AltCostume[kco2->base.PlayerNum])
		{
			kco2->TextureList = LoadCharTextures("HSHSROUGETEX");
		}
		else
		{
			kco2->TextureList = LoadCharTextures("HSHSBROUGETEX");
		}
	}
	else if (ModelSwap1)
	{
		if (!AltCostume[kco2->base.PlayerNum])
		{
			kco2->TextureList = LoadCharTextures("HSSROUGETEX");
		}
		else
		{
			kco2->TextureList = LoadCharTextures("HSSBROUGETEX");
		}
	}
	else
	{
		if (!AltCostume[kco2->base.PlayerNum])
		{
			kco2->TextureList = LoadCharTextures("HSROUGETEX");
		}
		else
		{
			kco2->TextureList = LoadCharTextures("HSBROUGETEX");
		}
	}

	//ugly way to fix Shadow eyes texture when transforming to super, thanks to the awful GBIX Texture system.
	if (TwoPlayerMode || CurrentLevel == LevelIDs_SonicVsShadow1 || CurrentLevel == LevelIDs_SonicVsShadow2)
	{
		char OtherPlayer = kco2->base.PlayerNum == 0 ? 1 : 0;

		if (MainCharObj2[OtherPlayer] && MainCharObj2[OtherPlayer]->CharID2 == Characters_Shadow && !isSuper[OtherPlayer])
		{
			SonicCharObj2* kco2H = (SonicCharObj2*)MainCharacter[OtherPlayer]->Data2.Character;

			if (AltCostume[OtherPlayer] != 0)
				kco2H->TextureList = LoadCharTextures("SHADOW1TEX");
			else
				kco2H->TextureList = LoadCharTextures("teriostex");
		}
	}

	return;
}

AnimationInfo RougeAnimCopy[258];

void __cdecl TransfoSuperRouge(EntityData1* data, int playerID, KnucklesCharObj2* kco2) {
	if (!isSuper[playerID])
	{
		if (SuperMusicVersion != None) {
			StopMusic();
			Play_SuperSonicMusic();
			ResetMusic();
		}

		kco2->base.Speed.x = 0;

		memcpy(&RougeAnimCopy, kco2->base.AnimInfo.Animations, sizeof(RougeAnimCopy));
		ControllerEnabled[playerID] = 0;

		if (CurrentLevel != LevelIDs_ChaoWorld)
			kco2->base.Powerups |= Powerups_Invincibility;

//		kco2->base.AnimInfo.Next = 0;
//		kco2->base.AnimInfo.Animations = SuperRougeAnimationList_r;
		LoadSuperRougeCharTextures(kco2);

		PlayAnimationThing(&kco2->base.AnimInfo);
		Load_SuperPhysics(data);

		kco2->base.Upgrades |= Upgrades_SuperSonic;

		isSuper[playerID] = true;
	}
	else
	{
		MainCharacter[playerID]->DisplaySub_Delayed4 = nullptr;
		LoadHyperRougeCharTextures(kco2);
		kco2->base.Powerups |= Powerups_HyperSonic;
		isHyper[playerID] = true;
	}
}

void unSuperRouge(unsigned char player) {
	if (AlwaysSuperRouge)
		return;

	EntityData1* data = MainCharObj1[player];
	CharObj2Base* co2 = MainCharObj2[player];

	if (!data || !isSuper[player])
		return;

	KnucklesCharObj2* kco2 = (KnucklesCharObj2*)MainCharacter[player]->Data2.Character;

	if (co2->CharID == Characters_Rouge)
		co2->PhysData = PhysicsArray[Characters_Rouge];

	CharacterThrowObject(data, co2);
	ResetChaosControl(player);
	data->Status = 0;
	co2->Upgrades &= ~Upgrades_SuperSonic;
	co2->Powerups &= ~Powerups_HyperSonic;
	co2->Powerups &= ~Powerups_Invincibility;
	//	kco2->base.AnimInfo.Next = 15;
//	kco2->base.AnimInfo.Animations = RougeAnimCopy;
	njReleaseTexture(kco2->TextureList);
	kco2->TextureList = 0;
	if (!AltCostume[player])
	{
		kco2->TextureList = LoadCharTextures("ROUGETEX");
	}
	else
	{
		kco2->TextureList = LoadCharTextures("BROUGETEX");
	}

	MainCharacter[player]->DisplaySub_Delayed4 = nullptr;
	isHyper[player] = false;
	isSuper[player] = false;

	if (IsIngame())
	{
//		PlayAnimationThing(&kco2->base.AnimInfo);
		RestoreMusic();
	}

	return;
}

void SuperRouge_ManagerDelete(ObjectMaster* obj)
{
	currentSuperMusic = "";
	char pnum = obj->Data1.Entity->Index;
	unSuperRouge(pnum);
	isSuper[pnum] = false;
	ResetChaosControl(pnum);
//	Delete_SRAnim();
}

void SuperRouge_Manager(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	EntityData1* player = MainCharObj1[data->Index];

	if (!player)
		return;

	KnucklesCharObj2* sonicCO2 = (KnucklesCharObj2*)MainCharacter[data->Index]->Data2.Character;

	if (sonicCO2->base.CharID2 != Characters_Rouge || (player->field_2 == 3 && data->Index == 1))
	{
		DeleteObject_(obj);
		return;
	}

	//if player dies, remove transformation and reset manager action.
	if (GameState == GameStates_LoadFinished && !AlwaysSuperRouge && data->Action > playerInputCheck) {
		unSuperRouge(data->Index);
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
		obj->DeleteSub = SuperRouge_ManagerDelete;
		data->Action++;
		break;
	case playerInputCheck:

		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || AlwaysSuperRouge || CurrentLevel == LevelIDs_FinalHazard)
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
		TransfoSuperRouge(player, playerID, sonicCO2);
		data->Action++;
		break;
	case superSonicTransition:
//		sonicCO2->base.AnimInfo.Next = superRougeIntro;
		data->Action++;
		break;
	case superSonicWait:

//		if (++data->Timer == 100 || AlwaysSuperRouge)
		{
			Load_SSWaterTask(playerID);
			LoadSuperAura(playerID);
			ControllerEnabled[playerID] = data->Scale.y;
			DoNextAction_r(playerID, 15, 0);
			data->Action++;
			data->Timer = 0;
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
			if (CheckTransform_Input(playerID, player) || AlwaysSuperRouge || CurrentLevel == LevelIDs_FinalHazard && FHZHyperForm)
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
		SuperSonic_DisableFly(player, &sonicCO2->base);
		unSuperRouge(playerID);

		data->Action = playerInputCheck;
		break;
	}
}

void LoadSuperRougeManager(char playNum) {
	int id2 = MainCharObj2[playNum]->CharID2;

	if (id2 == Characters_Rouge) {
		ObjectMaster* superRougeManagerPtr = LoadObject(0, "SuperRouge_Manager", SuperRouge_Manager, LoadObj_Data1);

		if (superRougeManagerPtr)
		{
//			SuperRougeMdl = LoadMDLFile((char*)"SROUGEMDL.PRS");
//			Load_NewSuperRougeAnim();
			superRougeManagerPtr->Data1.Entity->Index = playNum;
		}
	}
}

void LoadRouge_r(int playerNum) {
	LoadRouge_t.Original(playerNum);

//	if (CurrentLevel != LevelIDs_FinalHazard) {
		if (MainCharObj1[playerNum] && MainCharObj1[playerNum]->field_2 != 3) {
			LoadSuperRougeManager(playerNum);
			LoadSSEff_Textures();
			LoadSRougeEff_Textures();
			LoadWaterTextures(playerNum);
			LoadSADXAuraTextures(playerNum);
		}
//	}
}

void init_SuperRouge()
{
	LoadRouge_t.Hook(LoadRouge_r);
	return;
}