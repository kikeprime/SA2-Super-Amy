#include "pch.h"
#include "ss.h"

static FunctionHook<void, int>LoadMechEggman_t(LoadMechEggman);
extern std::string currentSuperMusic;

void __cdecl LoadSMEggmanEff_Textures() {
	njReleaseTexture(&SEAura_Texlist);
	LoadTextureList("ssaura_efftex", &SEAura_Texlist);
	return;
}

void __cdecl LoadHMEggmanEff_Textures() {
	njReleaseTexture(&SEAura_Texlist);
	LoadTextureList("haura_efftex", &SEAura_Texlist);
	return;
}

void __cdecl LoadSuperMechEggmanCharTextures(MechEggmanCharObj2* mco2) {
	LoadSMEggmanEff_Textures();
	njReleaseTexture(mco2->TextureList);
	mco2->TextureList = 0;
	if (!GammaAsMechEggmanMod)
	{
		if (ModelSwap1)
		{
			if (AltCostume[mco2->base.PlayerNum] != 0)
				mco2->TextureList = LoadCharTextures("SSEWALK1TEX");
			else
				mco2->TextureList = LoadCharTextures("SSEWALKTEX");
		}
		else
		{
			if (AltCostume[mco2->base.PlayerNum] != 0)
				mco2->TextureList = LoadCharTextures("SEWALK2TEX");
			else
				mco2->TextureList = LoadCharTextures("SEWALKTEX");
		}
	}
	else
	{
		if (ModelSwap1)
		{
			if (AltCostume[mco2->base.PlayerNum] != 0)
				mco2->TextureList = LoadCharTextures("SEWALK1TEX");
			else
				mco2->TextureList = LoadCharTextures("SSGAMMATEX");
		}
		else
		{
			if (AltCostume[mco2->base.PlayerNum] != 0)
				mco2->TextureList = LoadCharTextures("SEWALK2TEX");
			else
				mco2->TextureList = LoadCharTextures("SGAMMATEX");
		}
	}

	//ugly way to fix Shadow eyes texture when transforming to super, thanks to the awful GBIX Texture system.
	if (TwoPlayerMode || CurrentLevel == LevelIDs_SonicVsShadow1 || CurrentLevel == LevelIDs_SonicVsShadow2)
	{
		char OtherPlayer = mco2->base.PlayerNum == 0 ? 1 : 0;

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

void __cdecl LoadHyperMechEggmanCharTextures(MechEggmanCharObj2* mco2) {
	LoadHMEggmanEff_Textures();
	njReleaseTexture(mco2->TextureList);
	mco2->TextureList = 0;
	if (!GammaAsMechEggmanMod)
	{
		if (ModelSwap2)
		{
			if (AltCostume[mco2->base.PlayerNum] != 0)
				mco2->TextureList = LoadCharTextures("HSHSEWALK2TEX");
			else
				mco2->TextureList = LoadCharTextures("HSHSEWALKTEX");
		}
		else if (ModelSwap1)
		{
			if (AltCostume[mco2->base.PlayerNum] != 0)
				mco2->TextureList = LoadCharTextures("HSSEWALK1TEX");
			else
				mco2->TextureList = LoadCharTextures("HSSEWALKTEX");
		}
		else
		{
			if (AltCostume[mco2->base.PlayerNum] != 0)
				mco2->TextureList = LoadCharTextures("HSEWALK2TEX");
			else
				mco2->TextureList = LoadCharTextures("HSEWALKTEX");
		}
	}
	else
	{
		if (ModelSwap2)
		{
			if (AltCostume[mco2->base.PlayerNum] != 0)
				mco2->TextureList = LoadCharTextures("HSHSEWALK2TEX");
			else
				mco2->TextureList = LoadCharTextures("HSHSGAMMATEX");
		}
		else if (ModelSwap1)
		{
			if (AltCostume[mco2->base.PlayerNum] != 0)
				mco2->TextureList = LoadCharTextures("HSSEWALK2TEX");
			else
				mco2->TextureList = LoadCharTextures("HSSGAMMATEX");
		}
		else
		{
			if (AltCostume[mco2->base.PlayerNum] != 0)
				mco2->TextureList = LoadCharTextures("HSEWALK2TEX");
			else
				mco2->TextureList = LoadCharTextures("HSGAMMATEX");
		}
	}

	//ugly way to fix Shadow eyes texture when transforming to super, thanks to the awful GBIX Texture system.
	if (TwoPlayerMode || CurrentLevel == LevelIDs_SonicVsShadow1 || CurrentLevel == LevelIDs_SonicVsShadow2)
	{
		char OtherPlayer = mco2->base.PlayerNum == 0 ? 1 : 0;

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

AnimationInfo MechEggmanAnimCopy[139];

void __cdecl TransfoSuperMechEggman(EntityData1* data, int playerID, MechEggmanCharObj2* mco2) {
	if (!isSuper[playerID])
	{
		if (SuperMusicVersion != None) {
			StopMusic();
			Play_SuperSonicMusic();
			ResetMusic();
		}

//		mco2->base.Speed.x = 0;

		memcpy(&MechEggmanAnimCopy, mco2->base.AnimInfo.Animations, sizeof(MechEggmanAnimCopy));
		ControllerEnabled[playerID] = 0;

		if (CurrentLevel != LevelIDs_ChaoWorld)
			mco2->base.Powerups |= Powerups_Invincibility;

//		SetSuperMechEggmanModels(mco2);
//		mco2->base.AnimInfo.Next = 0;
//		mco2->base.AnimInfo.Animations = SuperEggmanAnimationList_r;
		LoadSuperMechEggmanCharTextures(mco2);

//		PlayAnimationThing(&mco2->base.AnimInfo);
//		Load_SuperPhysics(data);

		mco2->base.Upgrades |= Upgrades_SuperSonic;

		isSuper[playerID] = true;
	}
	else
	{
		MainCharacter[playerID]->DisplaySub_Delayed3 = nullptr;
		LoadHyperMechEggmanCharTextures(mco2);
		mco2->base.Powerups |= Powerups_HyperSonic;
		mco2->base.Upgrades |= Upgrades_KnucklesAirNecklace;
		isHyper[playerID] = true;
	}
}

void unSuperMechEggman(unsigned char player) {
	if (AlwaysSuperMechEggman)
		return;

	EntityData1* data = MainCharObj1[player];
	CharObj2Base* co2 = MainCharObj2[player];

	if (!data || !isSuper[player])
		return;

	MechEggmanCharObj2* co2S = (MechEggmanCharObj2*)MainCharacter[player]->Data2.Character;

	if (co2->CharID == Characters_MechEggman)
		co2->PhysData = PhysicsArray[Characters_MechEggman];

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
//	co2S->base.AnimInfo.Next = 15;
	co2S->base.AnimInfo.Animations = MechEggmanAnimCopy;
	njReleaseTexture(co2S->TextureList);
	co2S->TextureList = 0;

	if (AltCostume[player] != 0)
		co2S->TextureList = LoadCharTextures("EWALK2TEX");
	else
		co2S->TextureList = LoadCharTextures("EWALKTEX");

	MainCharacter[player]->DisplaySub_Delayed3 = nullptr;
	isHyper[player] = false;
	isSuper[player] = false;

	if (IsIngame())
	{
//		PlayAnimationThing(&co2S->base.AnimInfo);
		RestoreMusic();
	}

	return;
}

void SuperMechEggman_ManagerDelete(ObjectMaster* obj)
{
	currentSuperMusic = "";
	char pnum = obj->Data1.Entity->Index;
	unSuperMechEggman(pnum);
	isHyper[pnum] = false;
	isSuper[pnum] = false;
	ResetChaosControl(pnum);
// 	ReleaseMDLFile(SuperEggmanMdl);
//	Delete_SAAnim();
}

void SuperMechEggman_Manager(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	EntityData1* player = MainCharObj1[data->Index];

	if (!player)
		return;

	MechEggmanCharObj2* sonicCO2 = (MechEggmanCharObj2*)MainCharacter[data->Index]->Data2.Character;

	if (sonicCO2->base.CharID2 != Characters_MechEggman || (player->field_2 == 3 && data->Index == 1))
	{
		DeleteObject_(obj);
		return;
	}

	//if player dies, remove transformation and reset manager action.
	if (GameState == GameStates_LoadFinished && !AlwaysSuperMechEggman && data->Action > playerInputCheck) {
		unSuperMechEggman(data->Index);
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
		obj->DeleteSub = SuperMechEggman_ManagerDelete;
		data->Action++;
		break;
	case playerInputCheck:

		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || AlwaysSuperMechEggman || CurrentLevel == LevelIDs_FinalHazard)
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
		TransfoSuperMechEggman(player, playerID, sonicCO2);
		data->Action++;
		break;
	case superSonicTransition:
//		sonicCO2->base.AnimInfo.Next = superEggmanIntro;
		data->Action++;
		break;
	case superSonicWait:

//		if (++data->Timer == 100 || AlwaysSuperMechEggman)
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
			if (CheckTransform_Input(playerID, player) || AlwaysSuperMechEggman || CurrentLevel == LevelIDs_FinalHazard)
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
		unSuperMechEggman(playerID);

		data->Action = playerInputCheck;
		break;
	}
}

void LoadSuperMechEggmanManager(char playNum) {
	int id2 = MainCharObj2[playNum]->CharID2;

	if (id2 == Characters_MechEggman) {
		ObjectMaster* superMechEggmanManagerPtr = LoadObject(0, "SuperMechEggman_Manager", SuperMechEggman_Manager, LoadObj_Data1);

		if (superMechEggmanManagerPtr)
		{
//			SuperEggmanMdl = LoadMDLFile((char*)"EWALK2MDL.PRS");
//			Load_NewSuperEggmanAnim();
			superMechEggmanManagerPtr->Data1.Entity->Index = playNum;
		}
	}
}

void LoadMechEggman_r(int playerNum) {
	LoadMechEggman_t.Original(playerNum);

//	if (CurrentLevel != LevelIDs_FinalHazard) {
		if (MainCharObj1[playerNum] && MainCharObj1[playerNum]->field_2 != 3) {
			LoadSuperMechEggmanManager(playerNum);
			LoadSMEggmanEff_Textures();
			LoadSSEff_Textures();
			LoadWaterTextures(playerNum);
			LoadSADXAuraTextures(playerNum);
		}
//	}
}

void init_SuperMechEggman()
{
	LoadMechEggman_t.Hook(LoadMechEggman_r);
	return;
}