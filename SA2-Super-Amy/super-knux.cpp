#include "pch.h"
#include "ss.h"


NJS_TEXLIST* Knux_TexlistPtr = nullptr;
static FunctionHook<void, int>LoadKnux_t(LoadKnuckles);
ModelIndex* SuperKnuxMdl = nullptr;
extern std::string currentSuperMusic;

NJS_TEXLIST* getKnuxTexlist()
{
	return Knux_TexlistPtr;
}

//add super Knux model to sonic model pointer
void __cdecl SetSuperKnuxModels(KnucklesCharObj2* sco2) {
	sco2->ModelList[328].Index = SuperKnuxMdl[328].Index;
	sco2->ModelList[328].Model = SuperKnuxMdl[328].Model;
	return;
}

void __cdecl LoadSuperKnuxCharTextures(KnucklesCharObj2* sco2) {
	njReleaseTexture(sco2->TextureList);
	sco2->TextureList = 0;
	sco2->TextureList = LoadCharTextures("SKNUCKLESTEX");

	//used for upgrade textures.
//	Knux_TexlistPtr = LoadCharTextures("KNUCKTEX");

	//ugly way to fix Shadow eyes texture when transforming to super, thanks to the awful GBIX Texture system.
	if (TwoPlayerMode || CurrentLevel == LevelIDs_SonicVsShadow1 || CurrentLevel == LevelIDs_SonicVsShadow2)
	{
		char OtherPlayer = sco2->base.PlayerNum == 0 ? 1 : 0;

		if (MainCharObj2[OtherPlayer] && MainCharObj2[OtherPlayer]->CharID2 == Characters_Shadow && !isSuper[OtherPlayer])
		{
			SonicCharObj2* co2SH = (SonicCharObj2*)MainCharacter[OtherPlayer]->Data2.Character;

			if (AltCostume[OtherPlayer] != 0)
				co2SH->TextureList = LoadCharTextures("SHADOW1TEX");
			else
				co2SH->TextureList = LoadCharTextures("teriostex");
		}
	}

	return;
}

AnimationInfo KnuxAnimCopy[258];

void __cdecl TransfoSuperKnux(EntityData1* data, int playerID, KnucklesCharObj2* sco2) {
	if (SuperMusicVersion != None) {
		StopMusic();
		Play_SuperSonicMusic();
		ResetMusic();
	}

	sco2->base.Speed.x = 0;

	memcpy(&KnuxAnimCopy, sco2->base.AnimInfo.Animations, sizeof(KnuxAnimCopy));
	ControllerEnabled[playerID] = 0;

	if (CurrentLevel != LevelIDs_ChaoWorld)
		sco2->base.Powerups |= Powerups_Invincibility;

//	SetSuperKnuxModels(sco2);
//	sco2->base.AnimInfo.Next = 0;
//	sco2->base.AnimInfo.Animations = SuperKnuxAnimationList_r;
	LoadSuperKnuxCharTextures(sco2);

	PlayAnimationThing(&sco2->base.AnimInfo);
	Load_SuperPhysics(data);

//	if (CurrentLevel != LevelIDs_ChaoWorld)
	sco2->base.Upgrades |= Upgrades_SuperSonic;

	isSuper[playerID] = true;
}

void unSuperKnux(unsigned char player) {
	if (AlwaysSuperKnux)
		return;

	EntityData1* data = MainCharObj1[player];
	CharObj2Base* co2 = MainCharObj2[player];

	if (!data || !isSuper[player])
		return;

	KnucklesCharObj2* co2S = (KnucklesCharObj2*)MainCharacter[player]->Data2.Character;

	if (co2->CharID == Characters_Knuckles)
		co2->PhysData = PhysicsArray[Characters_Knuckles];

	CharacterThrowObject(data, co2);
	ResetChaosControl(player);
	data->Status = 0;
	co2->Upgrades &= ~Upgrades_SuperSonic;
	co2->Powerups &= ~Powerups_Invincibility;
//	co2S->base.AnimInfo.Next = 15;
//	co2S->base.AnimInfo.Animations = KnuxAnimCopy;
	njReleaseTexture(co2S->TextureList);
	co2S->TextureList = 0;

	co2S->TextureList = LoadCharTextures("KNUCKTEX");

	MainCharacter[player]->DisplaySub_Delayed4 = nullptr;
	isSuper[player] = false;

	if (IsIngame())
	{
		//		PlayAnimationThing(&co2S->base.AnimInfo);
		RestoreMusic();
	}
	else {
		//		njReleaseTexture(Knux_TexlistPtr);
		//		Knux_TexlistPtr = nullptr;
	}

	return;
}

void SuperKnux_ManagerDelete(ObjectMaster* obj)
{
	currentSuperMusic = "";
	char pnum = obj->Data1.Entity->Index;
	unSuperKnux(pnum);
	isSuper[pnum] = false;
	ResetChaosControl(pnum);
	// 	ReleaseMDLFile(SuperKnuxMdl);
	//	Delete_SAAnim();
}

void SuperKnux_Manager(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	EntityData1* player = MainCharObj1[data->Index];

	if (!player)
		return;

	KnucklesCharObj2* sonicCO2 = (KnucklesCharObj2*)MainCharacter[data->Index]->Data2.Character;

	if (sonicCO2->base.CharID2 != Characters_Knuckles || (player->field_2 == 3 && data->Index == 1))
	{
		DeleteObject_(obj);
		return;
	}

	//if player dies, remove transformation and reset manager action.
	if (GameState == GameStates_LoadFinished && !AlwaysSuperKnux && data->Action > playerInputCheck) {
		unSuperKnux(data->Index);
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
		obj->DeleteSub = SuperKnux_ManagerDelete;
		data->Action++;
		break;
	case playerInputCheck:

		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || AlwaysSuperKnux || CurrentLevel == LevelIDs_FinalHazard)
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
		TransfoSuperKnux(player, playerID, sonicCO2);
		data->Action++;
		break;
	case superSonicTransition:
//		sonicCO2->base.AnimInfo.Next = superKnuxIntro;
		data->Action++;
		break;
	case superSonicWait:

//		if (++data->Timer == 100 || AlwaysSuperKnux)
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
			if (player->Action == Action_Glide)
			{
				sonicCO2->base.Speed.y = 2;
			}
		}

		if (CheckUntransform_Input(playerID)) {
			data->Action = playerInputCheck;
		}

		Reload_SS_WaterTask(sonicCO2->base.CharID2, playerID);
		SubRings(playerID, data);

		break;
	case superSonicUntransfo:
		SuperSonic_DisableFly(player, &sonicCO2->base);
		unSuperKnux(playerID);

		data->Action = playerInputCheck;
		break;
	}
}

void LoadSuperKnuxManager(char playNum) {
	int id2 = MainCharObj2[playNum]->CharID2;

	if (id2 == Characters_Knuckles) {
		ObjectMaster* superKnuxManagerPtr = LoadObject(1, "SuperKnux_Manager", SuperKnux_Manager, LoadObj_Data1);

		if (superKnuxManagerPtr)
		{
//			SuperKnuxMdl = LoadMDLFile((char*)"SKNUCKLESMDL.PRS");
//			Load_NewSuperKnuxAnim();
			superKnuxManagerPtr->Data1.Entity->Index = playNum;
		}
	}
}

void __cdecl LoadSKnuxEff_Textures() {
	LoadTextureList("skaura_efftex", &SKAura_Texlist);
	return;
}

void LoadKnux_r(int playerNum) {
	LoadKnux_t.Original(playerNum);

//	if (CurrentLevel != LevelIDs_FinalHazard) {
		if (MainCharObj1[playerNum] && MainCharObj1[playerNum]->field_2 != 3) {
			LoadSuperKnuxManager(playerNum);
			LoadSKnuxEff_Textures();
			LoadWaterTextures(playerNum);
			LoadSADXAuraTextures(playerNum);
		}
//	}
}

void init_SuperKnuckles()
{
	LoadKnux_t.Hook(LoadKnux_r);
	return;
}