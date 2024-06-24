#include "pch.h"
#include "ss.h"

static FunctionHook<void, int>LoadChaoWalker_t(LoadChaoWalker);
extern std::string currentSuperMusic;

void __cdecl LoadSChaoWEff_Textures() {
	njReleaseTexture(&SCWAura_Texlist);
	LoadTextureList("ssaura_efftex", &SCWAura_Texlist);
	return;
}

void __cdecl LoadHChaoWEff_Textures() {
	njReleaseTexture(&SCWAura_Texlist);
	LoadTextureList("haura_efftex", &SCWAura_Texlist);
	return;
}

void __cdecl LoadSuperChaoWalkerCharTextures(MechEggmanCharObj2* mco2) {
	LoadSChaoWEff_Textures();
	njReleaseTexture(mco2->TextureList);
	mco2->TextureList = 0;
	if (ModelSwap1)
	{
		if (AltCostume[mco2->base.PlayerNum] != 0)
			mco2->TextureList = LoadCharTextures("SSCWALK1TEX");
		else
			mco2->TextureList = LoadCharTextures("SSCWALKTEX");
	}
	else
	{
		if (AltCostume[mco2->base.PlayerNum] != 0)
			mco2->TextureList = LoadCharTextures("SCWALK1TEX");
		else
			mco2->TextureList = LoadCharTextures("SCWALKTEX");
	}

	//ugly way to fix Shadow eyes texture when transforming to super, thanks to the awful GBIX Texture system.
	if (TwoPlayerMode || CurrentLevel == LevelIDs_SonicVsShadow1 || CurrentLevel == LevelIDs_SonicVsShadow2)
	{
		char OtherPlayer = mco2->base.PlayerNum == 0 ? 1 : 0;

		if (MainCharObj2[OtherPlayer] && MainCharObj2[OtherPlayer]->CharID2 == Characters_Shadow && !isSuper[OtherPlayer])
		{
			SonicCharObj2* mco2H = (SonicCharObj2*)MainCharacter[OtherPlayer]->Data2.Character;

			if (AltCostume[OtherPlayer] != 0)
				mco2H->TextureList = LoadCharTextures("SHADOW1TEX");
			else
				mco2H->TextureList = LoadCharTextures("teriostex");
		}
	}

	return;
}

void __cdecl LoadHyperChaoWalkerCharTextures(MechEggmanCharObj2* mco2) {
	LoadHChaoWEff_Textures();
	njReleaseTexture(mco2->TextureList);
	mco2->TextureList = 0;
	if (ModelSwap2)
	{
		if (AltCostume[mco2->base.PlayerNum] != 0)
			mco2->TextureList = LoadCharTextures("HSHSCWALK1TEX");
		else
			mco2->TextureList = LoadCharTextures("HSHSCWALKTEX");
	}
	else if (ModelSwap1)
	{
		if (AltCostume[mco2->base.PlayerNum] != 0)
			mco2->TextureList = LoadCharTextures("HSSCWALK1TEX");
		else
			mco2->TextureList = LoadCharTextures("HSSCWALKTEX");
	}
	else
	{
		if (AltCostume[mco2->base.PlayerNum] != 0)
			mco2->TextureList = LoadCharTextures("HSCWALK1TEX");
		else
			mco2->TextureList = LoadCharTextures("HSCWALKTEX");
	}

	//ugly way to fix Shadow eyes texture when transforming to super, thanks to the awful GBIX Texture system.
	if (TwoPlayerMode || CurrentLevel == LevelIDs_SonicVsShadow1 || CurrentLevel == LevelIDs_SonicVsShadow2)
	{
		char OtherPlayer = mco2->base.PlayerNum == 0 ? 1 : 0;

		if (MainCharObj2[OtherPlayer] && MainCharObj2[OtherPlayer]->CharID2 == Characters_Shadow && !isSuper[OtherPlayer])
		{
			SonicCharObj2* mco2H = (SonicCharObj2*)MainCharacter[OtherPlayer]->Data2.Character;

			if (AltCostume[OtherPlayer] != 0)
				mco2H->TextureList = LoadCharTextures("SHADOW1TEX");
			else
				mco2H->TextureList = LoadCharTextures("teriostex");
		}
	}

	return;
}

AnimationInfo ChaoWalkerAnimCopy[258];

void __cdecl TransfoSuperChaoWalker(EntityData1* data, int playerID, MechEggmanCharObj2* mco2) {
	if (!isSuper[playerID])
	{
		if (SuperMusicVersion != None) {
			StopMusic();
			Play_SuperSonicMusic();
			ResetMusic();
		}

//		mco2->base.Speed.x = 0;

		memcpy(&ChaoWalkerAnimCopy, mco2->base.AnimInfo.Animations, sizeof(ChaoWalkerAnimCopy));
		ControllerEnabled[playerID] = 0;

		if (CurrentLevel != LevelIDs_ChaoWorld)
			mco2->base.Powerups |= Powerups_Invincibility;

//		mco2->base.AnimInfo.Next = 0;
//		mco2->base.AnimInfo.Animations = SuperChaoWalkerAnimationList_r;
		LoadSuperChaoWalkerCharTextures(mco2);

//		PlayAnimationThing(&mco2->base.AnimInfo);
//		Load_SuperPhysics(data);

		mco2->base.Upgrades |= Upgrades_SuperSonic;

		isSuper[playerID] = true;
	}
	else
	{
		MainCharacter[playerID]->DisplaySub_Delayed3 = nullptr;
		LoadHyperChaoWalkerCharTextures(mco2);
		mco2->base.Powerups |= Powerups_HyperSonic;
		mco2->base.Upgrades |= Upgrades_KnucklesAirNecklace;
		isHyper[playerID] = true;
	}
}

void unSuperChaoWalker(unsigned char player) {
	if (AlwaysSuperChaoWalker)
		return;

	EntityData1* data = MainCharObj1[player];
	CharObj2Base* co2 = MainCharObj2[player];

	if (!data || !isSuper[player])
		return;

	MechEggmanCharObj2* mco2 = (MechEggmanCharObj2*)MainCharacter[player]->Data2.Character;

	if (co2->CharID == Characters_ChaoWalker)
		co2->PhysData = PhysicsArray[Characters_ChaoWalker];

	CharacterThrowObject(data, co2);
	ResetChaosControl(player);
	data->Status = 0;
	if (co2->Upgrades & Upgrades_KnucklesAirNecklace)
	{
		co2->Upgrades &= ~Upgrades_KnucklesAirNecklace;
	}
	co2->Upgrades &= ~Upgrades_SuperSonic;
	co2->Powerups &= ~Powerups_HyperSonic;
	co2->Powerups &= ~Powerups_Invincibility;
	//	mco2->base.AnimInfo.Next = 15;
//	mco2->base.AnimInfo.Animations = ChaoWalkerAnimCopy;
	njReleaseTexture(mco2->TextureList);
	mco2->TextureList = 0;
	if (!AltCostume[player])
	{
		mco2->TextureList = LoadCharTextures("CWALKTEX");
	}
	else
	{
		mco2->TextureList = LoadCharTextures("CWALK1TEX");
	}

	MainCharacter[player]->DisplaySub_Delayed3 = nullptr;
	isHyper[player] = false;
	isSuper[player] = false;

	if (IsIngame())
	{
//		PlayAnimationThing(&mco2->base.AnimInfo);
		RestoreMusic();
	}

	return;
}

void SuperChaoWalker_ManagerDelete(ObjectMaster* obj)
{
	currentSuperMusic = "";
	char pnum = obj->Data1.Entity->Index;
	unSuperChaoWalker(pnum);
	isSuper[pnum] = false;
	ResetChaosControl(pnum);
// 	ReleaseMDLFile(SuperChaoWalkerMdl);
//	Delete_SChWAnim();
}

void SuperChaoWalker_Manager(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	EntityData1* player = MainCharObj1[data->Index];

	if (!player)
		return;

	MechEggmanCharObj2* sonicCO2 = (MechEggmanCharObj2*)MainCharacter[data->Index]->Data2.Character;

	if (sonicCO2->base.CharID2 != Characters_ChaoWalker || (player->field_2 == 3 && data->Index == 1))
	{
		DeleteObject_(obj);
		return;
	}

	//if player dies, remove transformation and reset manager action.
	if (GameState == GameStates_LoadFinished && !AlwaysSuperChaoWalker && data->Action > playerInputCheck) {
		unSuperChaoWalker(data->Index);
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
		obj->DeleteSub = SuperChaoWalker_ManagerDelete;
		data->Action++;
		break;
	case playerInputCheck:

		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || AlwaysSuperChaoWalker || CurrentLevel == LevelIDs_FinalHazard)
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
		TransfoSuperChaoWalker(player, playerID, sonicCO2);
		data->Action++;
		break;
	case superSonicTransition:
//		sonicCO2->base.AnimInfo.Next = superChaoWalkerIntro;
		data->Action++;
		break;
	case superSonicWait:

//		if (++data->Timer == 100 || AlwaysSuperChaoWalker)
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
		if (isMechFlyAllowed || CurrentLevel == LevelIDs_FinalHazard)
		{
			if (player->Action == Action_MechHover && isSuper[playerID])
			{
				sonicCO2->base.Speed.y = 2;
			}
		}
		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || AlwaysSuperChaoWalker || CurrentLevel == LevelIDs_FinalHazard)
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
		unSuperChaoWalker(playerID);

		data->Action = playerInputCheck;
		break;
	}
}

void LoadSuperChaoWalkerManager(char playNum) {
	int id2 = MainCharObj2[playNum]->CharID2;

	if (id2 == Characters_ChaoWalker) {
		ObjectMaster* superChaoWalkerManagerPtr = LoadObject(0, "SuperChaoWalker_Manager", SuperChaoWalker_Manager, LoadObj_Data1);

		if (superChaoWalkerManagerPtr)
		{
//			Load_NewSuperChaoWalkerAnim();
			superChaoWalkerManagerPtr->Data1.Entity->Index = playNum;
		}
	}
}

void __cdecl LoadSChaoWalkerEff_Textures() {
	LoadTextureList("skaura_efftex", &SKAura_Texlist);
	return;
}

void LoadChaoWalker_r(int playerNum) {
	if (AltCostume[playerNum])
	{
		LoadMDLFile((char*)"CWALK1MDL.PRS");
	}
	LoadChaoWalker_t.Original(playerNum);
	MechEggmanCharObj2* mco2 = (MechEggmanCharObj2*)MainCharacter[playerNum]->Data2.Character;
	if (AltCostume[playerNum])
	{
		mco2->TextureList = 0;
		mco2->TextureList = LoadCharTextures("CWALK1TEX");
	}

//	if (CurrentLevel != LevelIDs_FinalHazard) {
		if (MainCharObj1[playerNum] && MainCharObj1[playerNum]->field_2 != 3) {
			LoadSuperChaoWalkerManager(playerNum);
			LoadSChaoWEff_Textures();
			LoadSSEff_Textures();
			LoadWaterTextures(playerNum);
			LoadSADXAuraTextures(playerNum);
		}
//	}
}

void init_SuperChaoWalker()
{
	LoadChaoWalker_t.Hook(LoadChaoWalker_r);
	return;
}