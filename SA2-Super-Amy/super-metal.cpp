#include "pch.h"
#include "ss.h"

NJS_TEXLIST* MetalSonic_TexlistPtr = nullptr;
static FunctionHook<void, int>LoadMetalSonic_t(LoadMetalSonic);
ModelIndex* SuperMetalSonicMdl = nullptr;
ModelIndex* SuperMetalSonic2Mdl = nullptr;
extern std::string currentSuperMusic;

void __cdecl LoadSMetalEff_Textures() {
	njReleaseTexture(&SMAura_Texlist);
	LoadTextureList("skaurar_efftex", &SMAura_Texlist);
	return;
}

void __cdecl LoadHMetalEff_Textures() {
	njReleaseTexture(&SMAura_Texlist);
	LoadTextureList("haura_efftex", &SMAura_Texlist);
	return;
}

void __cdecl LoadSuperMetalSonicCharTextures(SonicCharObj2* sco2) {
	LoadSMetalEff_Textures();
	njReleaseTexture(sco2->TextureList);
	sco2->TextureList = 0;
	if (ModelSwap1)
	{
		if (!AltCostume[sco2->base.PlayerNum])
		{
			sco2->TextureList = LoadCharTextures("SSMETALSONICTEX");
		}
		else
		{
			sco2->TextureList = LoadCharTextures("SSMETALSONIC1TEX");
		}
	}
	else
	{
		if (!AltCostume[sco2->base.PlayerNum])
		{
			sco2->TextureList = LoadCharTextures("SMETALSONICTEX");
		}
		else
		{
			sco2->TextureList = LoadCharTextures("SMETALSONIC1TEX");
		}
	}

	//ugly way to fix Super Sonic's eyes texture when transforming to super, thanks to the awful GBIX Texture system.
	if (TwoPlayerMode || CurrentLevel == LevelIDs_SonicVsShadow1 || CurrentLevel == LevelIDs_SonicVsShadow2)
	{
		char OtherPlayer = sco2->base.PlayerNum == 0 ? 1 : 0;

		if (MainCharObj2[OtherPlayer] && MainCharObj2[OtherPlayer]->CharID2 == Characters_Sonic && !isSuper[OtherPlayer])
		{
			SonicCharObj2* sco2 = (SonicCharObj2*)MainCharacter[OtherPlayer]->Data2.Character;

//			if (AltCostume[OtherPlayer] != 0)
//				sco2->TextureList = LoadCharTextures("SONIC1TEX");
//			else
				sco2->TextureList = LoadCharTextures("ssonictex");
		}
	}

	return;
}

void __cdecl LoadHyperMetalSonicCharTextures(SonicCharObj2* sco2) {
	LoadHMetalEff_Textures();
	njReleaseTexture(sco2->TextureList);
	sco2->TextureList = 0;
	if (ModelSwap2)
	{
		if (!AltCostume[sco2->base.PlayerNum])
		{
			sco2->TextureList = LoadCharTextures("HSHSMETALSONICTEX");
		}
		else
		{
			sco2->TextureList = LoadCharTextures("HSHSMETALSONIC1TEX");
		}
	}
	else if (ModelSwap1)
	{
		if (!AltCostume[sco2->base.PlayerNum])
		{
			sco2->TextureList = LoadCharTextures("HSSMETALSONICTEX");
		}
		else
		{
			sco2->TextureList = LoadCharTextures("HSSMETALSONIC1TEX");
		}
	}
	if (!AltCostume[sco2->base.PlayerNum])
	{
		sco2->TextureList = LoadCharTextures("HSMETALSONICTEX");
	}
	else
	{
		sco2->TextureList = LoadCharTextures("HSMETALSONIC1TEX");
	}

	//ugly way to fix Super Sonic's eyes texture when transforming to super, thanks to the awful GBIX Texture system.
	if (TwoPlayerMode || CurrentLevel == LevelIDs_SonicVsShadow1 || CurrentLevel == LevelIDs_SonicVsShadow2)
	{
		char OtherPlayer = sco2->base.PlayerNum == 0 ? 1 : 0;

		if (MainCharObj2[OtherPlayer] && MainCharObj2[OtherPlayer]->CharID2 == Characters_Sonic && !isSuper[OtherPlayer])
		{
			SonicCharObj2* sco2 = (SonicCharObj2*)MainCharacter[OtherPlayer]->Data2.Character;

//			if (AltCostume[OtherPlayer] != 0)
//				sco2->TextureList = LoadCharTextures("SONIC1TEX");
//			else
				sco2->TextureList = LoadCharTextures("ssonictex");
		}
	}

	return;
}

AnimationInfo MetalSonicAnimCopy[249];

void __cdecl TransfoSuperMetalSonic(EntityData1* data, int playerID, SonicCharObj2* sco2) {
	if (!isSuper[playerID])
	{
		if (SuperMusicVersion != None) {
			StopMusic();
			Play_SuperSonicMusic();
			ResetMusic();
		}

		if (AllowSuperMetalModel)
		{
			ReleaseMDLFile(sco2->ModelList);
			sco2->ModelList = AltCostume[playerID] ? LoadMDLFile((char*)"SMETALSONIC1MDL.PRS") : LoadMDLFile((char*)"SMETALSONICMDL.PRS");
			ModelSwap1 = true;
		}

		sco2->base.Speed.x = 0;

		memcpy(&MetalSonicAnimCopy, sco2->base.AnimInfo.Animations, sizeof(MetalSonicAnimCopy));
		ControllerEnabled[playerID] = 0;

		if (CurrentLevel != LevelIDs_ChaoWorld)
			sco2->base.Powerups |= Powerups_Invincibility;

		sco2->base.AnimInfo.Next = 0;
		if (!MetalJumpBall)
			SuperMetalSonicAnimationList_r[30] = MetalSonicAnimCopy[30];

		sco2->base.AnimInfo.Animations = SuperMetalSonicAnimationList_r;
		LoadSuperMetalSonicCharTextures(sco2);

		Load_SuperPhysics(data);

		sco2->base.Upgrades |= Upgrades_SuperSonic;

		isSuper[playerID] = true;
	}
	else
	{
		MainCharacter[playerID]->DisplaySub_Delayed4 = nullptr;
		if (AllowHyperMetalModel)
		{
			ReleaseMDLFile(sco2->ModelList);
			sco2->ModelList = AltCostume[playerID] ? LoadMDLFile((char*)"HSMETALSONIC1MDL.PRS") : LoadMDLFile((char*)"HSMETALSONICMDL.PRS");
			ModelSwap2 = true;
		}
		LoadHyperMetalSonicCharTextures(sco2);
		sco2->base.Powerups |= Powerups_HyperSonic;
		isHyper[playerID] = true;
	}

	PlayAnimationThing(&sco2->base.AnimInfo);
}

void unSuperMetalSonic(unsigned char player) {
	if (AlwaysSuperMetalSonic)
		return;

	EntityData1* data = MainCharObj1[player];
	CharObj2Base* co2 = MainCharObj2[player];

	if (!data || !isSuper[player])
		return;

	SonicCharObj2* sco2 = (SonicCharObj2*)MainCharacter[player]->Data2.Character;

	if (co2->CharID == Characters_MetalSonic)
		co2->PhysData = PhysicsArray[Characters_MetalSonic];

	CharacterThrowObject(data, co2);
	ResetChaosControl(player);
	data->Status = 0;
	sco2->base.AnimInfo.Next = 15;
	sco2->base.AnimInfo.Animations = MetalSonicAnimCopy;
	co2->Upgrades &= ~Upgrades_SuperSonic;
	co2->Powerups &= ~Powerups_HyperSonic;
	co2->Powerups &= ~Powerups_Invincibility;
	njReleaseTexture(sco2->TextureList);
	sco2->TextureList = 0;
	if (!AltCostume[player])
	{
		sco2->TextureList = LoadCharTextures("METALSONICTEX");
	}
	else
	{
		sco2->TextureList = LoadCharTextures("METALSONIC1TEX");
	}

	MainCharacter[player]->DisplaySub_Delayed4 = nullptr;
	isHyper[player] = false;
	isSuper[player] = false;

	if (IsIngame())
	{
		PlayAnimationThing(&sco2->base.AnimInfo);
		RestoreMusic();
	}

	if (ModelSwap1 || ModelSwap2)
	{
		ReleaseMDLFile(sco2->ModelList);
		sco2->ModelList = AltCostume[player] ? LoadMDLFile((char*)"METALSONIC1MDL.PRS") : LoadMDLFile((char*)"METALSONICMDL.PRS");
		ModelSwap1 = false;
		ModelSwap2 = false;
	}

	return;
}

void SuperMetalSonic_ManagerDelete(ObjectMaster* obj)
{
	currentSuperMusic = "";
	char pnum = obj->Data1.Entity->Index;
	unSuperMetalSonic(pnum);
	isHyper[pnum] = false;
	isSuper[pnum] = false;
	ResetChaosControl(pnum);
	Delete_SMSAnim();
}

void SuperMetalSonic_Manager(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	EntityData1* player = MainCharObj1[data->Index];

	if (!player)
		return;

	SonicCharObj2* sco2 = (SonicCharObj2*)MainCharacter[data->Index]->Data2.Character;
	sco2->base.UnderwaterTime = 0;
	if (sco2->base.CharID2 != Characters_MetalSonic || (player->field_2 == 3 && data->Index == 1))
	{
		DeleteObject_(obj);
		return;
	}

	//if player dies, remove transformation and reset manager action.
	if (GameState == GameStates_LoadFinished && !AlwaysSuperMetalSonic && data->Action > playerInputCheck) {
		unSuperMetalSonic(data->Index);
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
		obj->DeleteSub = SuperMetalSonic_ManagerDelete;
		data->Action++;
		break;
	case playerInputCheck:

		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || AlwaysSuperMetalSonic || CurrentLevel == LevelIDs_FinalHazard)
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
		TransfoSuperMetalSonic(player, playerID, sco2);
		data->Action++;
		break;
	case superSonicTransition:
		sco2->base.AnimInfo.Next = superSonicIntro;
		data->Action++;
		break;
	case superSonicWait:

		if (++data->Timer == 100 || AlwaysSuperMetalSonic)
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
		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || AlwaysSuperAmy || CurrentLevel == LevelIDs_FinalHazard)
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

		Reload_SS_WaterTask(sco2->base.CharID2, playerID);
		SubRings(playerID, data);

		break;
	case superSonicUntransfo:
		SuperSonic_DisableFly(player, &sco2->base);
		unSuperMetalSonic(playerID);

		data->Action = playerInputCheck;
		break;
	}
}

void LoadSuperMetalSonicManager(char playNum) {
	int id2 = MainCharObj2[playNum]->CharID2;

	if (id2 == Characters_MetalSonic) {
		ObjectMaster* superMetalSonicManagerPtr = LoadObject(1, "SuperMetalSonic_Manager", SuperMetalSonic_Manager, LoadObj_Data1);

		if (superMetalSonicManagerPtr)
		{
			SuperMetalSonicMdl = LoadMDLFile((char*)"TERIOSMDL.PRS");
			SuperMetalSonic2Mdl = LoadMDLFile((char*)"SONICMDL.PRS");

			Load_NewSuperMetalSonicAnim();
			superMetalSonicManagerPtr->Data1.Entity->Index = playNum;
		}
	}
}

void LoadMetalSonic_r(int playerNum) {
	if (AltCostume[playerNum])
	{
		LoadMDLFile((char*)"METALSONIC1MDL.PRS");
	}
	LoadMetalSonic_t.Original(playerNum);
	SonicCharObj2* sco2 = (SonicCharObj2*)MainCharacter[playerNum]->Data2.Character;
	if (AltCostume[playerNum])
	{
		sco2->TextureList = 0;
		sco2->TextureList = LoadCharTextures("METALSONIC1TEX");
	}

	if (MetalJumpBall)
	{
		MetalSonicAnimList[30] = SuperMetalSonicAnimationList_r[30];
	}

//	if (CurrentLevel != LevelIDs_FinalHazard) {
		if (MainCharObj1[playerNum] && MainCharObj1[playerNum]->field_2 != 3) {
			LoadSuperMetalSonicManager(playerNum);
			LoadSSEff_Textures();
			LoadSMetalEff_Textures();
			LoadWaterTextures(playerNum);
			LoadSADXAuraTextures(playerNum);
		}
//	}
}

void init_SuperMetalSonic() {

	LoadMetalSonic_t.Hook(LoadMetalSonic_r);
	return;
}