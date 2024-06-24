#include "pch.h"
#include "ss.h"

static FunctionHook<void, int>LoadMechTails_t(LoadMechTails);
extern std::string currentSuperMusic;
extern bool ModelSwap1;
extern bool ModelSwap2;

void __cdecl LoadSMTailsEff_Textures() {
	njReleaseTexture(&STAura_Texlist);
	LoadTextureList("ssaura_efftex", &STAura_Texlist);
	return;
}

void __cdecl LoadHMTailsEff_Textures() {
	njReleaseTexture(&STAura_Texlist);
	LoadTextureList("haura_efftex", &STAura_Texlist);
	return;
}

void __cdecl LoadSuperMechTailsCharTextures(MechEggmanCharObj2* mco2) {
	LoadSMTailsEff_Textures();
	njReleaseTexture(mco2->TextureList);
	mco2->TextureList = 0;
	if (ModelSwap1)
	{
		if (AltCostume[mco2->base.PlayerNum] != 0)
			mco2->TextureList = LoadCharTextures("SSTWALK1TEX");
		else
			mco2->TextureList = LoadCharTextures("SSTWALKTEX");
	}
	else
	{
		if (AltCostume[mco2->base.PlayerNum] != 0)
			mco2->TextureList = LoadCharTextures("STWALK1TEX");
		else
			mco2->TextureList = LoadCharTextures("STWALKTEX");
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

void __cdecl LoadHyperMechTailsCharTextures(MechEggmanCharObj2* mco2) {
	LoadHMTailsEff_Textures();
	njReleaseTexture(mco2->TextureList);
	mco2->TextureList = 0;
	if (ModelSwap2)
	{
		if (AltCostume[mco2->base.PlayerNum] != 0)
			mco2->TextureList = LoadCharTextures("HSHSTWALK1TEX");
		else
			mco2->TextureList = LoadCharTextures("HSHSTWALKTEX");
	}
	else if (ModelSwap1)
	{
		if (AltCostume[mco2->base.PlayerNum] != 0)
			mco2->TextureList = LoadCharTextures("HSSTWALK1TEX");
		else
			mco2->TextureList = LoadCharTextures("HSSTWALKTEX");
	}
	else
	{
		if (AltCostume[mco2->base.PlayerNum] != 0)
			mco2->TextureList = LoadCharTextures("HSTWALK1TEX");
		else
			mco2->TextureList = LoadCharTextures("HSTWALKTEX");
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

AnimationInfo MechTailsAnimCopy[258];

void __cdecl TransfoSuperMechTails(EntityData1* data, int playerID, MechEggmanCharObj2* mco2) {
	if (!isSuper[playerID])
	{
		if (SuperMusicVersion != None) {
			StopMusic();
			Play_SuperSonicMusic();
			ResetMusic();
		}
		if (AllowSuperMechTailsModel)
		{
			ReleaseMDLFile(mco2->ModelList);
			mco2->ModelList = AltCostume[playerID] ? LoadMDLFile((char*)"STWALK1MDL.PRS") : LoadMDLFile((char*)"STWALKMDL.PRS");
			ModelSwap1 = true;
		}

		ControllerEnabled[playerID] = 0;

		if (CurrentLevel != LevelIDs_ChaoWorld)
			mco2->base.Powerups |= Powerups_Invincibility;

		LoadSuperMechTailsCharTextures(mco2);

//		Load_SuperPhysics(data);

		mco2->base.Upgrades |= Upgrades_SuperSonic;

		isSuper[playerID] = true;
	}
	else
	{
		MainCharacter[playerID]->DisplaySub_Delayed3 = nullptr;
		if (AllowHyperMechTailsModel)
		{
			ReleaseMDLFile(mco2->ModelList);
			mco2->ModelList = AltCostume[playerID] ? LoadMDLFile((char*)"HSTWALK1MDL.PRS") : LoadMDLFile((char*)"HSTWALKMDL.PRS");
			ModelSwap2 = true;
		}
		LoadHyperMechTailsCharTextures(mco2);
		mco2->base.Powerups |= Powerups_HyperSonic;
		mco2->base.Upgrades |= Upgrades_KnucklesAirNecklace;
		isHyper[playerID] = true;
	}
}

void unSuperMechTails(unsigned char player) {
	if (AlwaysSuperMechTails)
		return;

	EntityData1* data = MainCharObj1[player];
	CharObj2Base* co2 = MainCharObj2[player];

	if (!data || !isSuper[player])
		return;

	MechEggmanCharObj2* mco2 = (MechEggmanCharObj2*)MainCharacter[player]->Data2.Character;

	if (co2->CharID == Characters_MechTails)
		co2->PhysData = PhysicsArray[Characters_MechTails];

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

	njReleaseTexture(mco2->TextureList);
	mco2->TextureList = 0;

	if (AltCostume[player] != 0)
		mco2->TextureList = LoadCharTextures("TWALK1TEX");
	else
		mco2->TextureList = LoadCharTextures("TWALKTEX");

	MainCharacter[player]->DisplaySub_Delayed3 = nullptr;
	isHyper[player] = false;
	isSuper[player] = false;

	if (IsIngame())
	{
//		PlayAnimationThing(&mco2->base.AnimInfo);
		RestoreMusic();
	}

	if (ModelSwap1 || ModelSwap2)
	{
		ReleaseMDLFile(mco2->ModelList);
		mco2->ModelList = AltCostume[player] ? LoadMDLFile((char*)"TWALK1MDL.PRS") : LoadMDLFile((char*)"TWALKMDL.PRS");
		ModelSwap1 = false;
		ModelSwap2 = false;
	}
	return;
}

void SuperMechTails_ManagerDelete(ObjectMaster* obj)
{
	currentSuperMusic = "";
	char pnum = obj->Data1.Entity->Index;
	unSuperMechTails(pnum);
	isHyper[pnum] = false;
	isSuper[pnum] = false;
//	ResetChaosControl(pnum);
//	Delete_STAnim();
}

void SuperMechTails_Manager(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	EntityData1* player = MainCharObj1[data->Index];
	unsigned char playerID = data->Index;

	if (!player)
		return;

	MechEggmanCharObj2* mco2 = (MechEggmanCharObj2*)MainCharacter[data->Index]->Data2.Character;

	if (mco2->base.CharID2 != Characters_MechTails || (player->field_2 == 3 && data->Index == 1))
	{
		DeleteObject_(obj);
		return;
	}

	//if player dies, remove transformation and reset manager action.
	if (GameState == GameStates_LoadFinished && !AlwaysSuperMechTails && data->Action > playerInputCheck) {
		unSuperMechTails(data->Index);
		data->Action = playerInputCheck;
		return;
	}

	if (!player || !IsIngame() || GameMode == GameMode_Event || miniEventPtr && miniEventPtr->MainSub != nullptr) {
		return;
	}

	switch (data->Action)
	{
	case superSonicInit:
		obj->DeleteSub = SuperMechTails_ManagerDelete;
		data->Action++;
		break;
	case playerInputCheck:

		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || AlwaysSuperMechTails || CurrentLevel == LevelIDs_FinalHazard)
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
		TransfoSuperMechTails(player, playerID, mco2);
		data->Action++;
		break;
	case superSonicTransition:
//		mco2->base.AnimInfo.Next = superTailsIntro;
		data->Action++;
		break;
	case superSonicWait:

//		if (++data->Timer == 100 || AlwaysSuperMechTails)
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
				mco2->base.Speed.y = 2;
			}
		}
		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || CurrentLevel == LevelIDs_FinalHazard)
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
		Reload_SS_WaterTask(mco2->base.CharID2, playerID);
		SubRings(playerID, data);
		break;
	case superSonicUntransfo:
		unSuperMechTails(playerID);
		data->Action = playerInputCheck;
		break;
	}

	return;
}

void LoadSuperMechTailsManager(char playNum) {
	int id2 = MainCharObj2[playNum]->CharID2;

	if (id2 == Characters_MechTails) {
		ObjectMaster* superMechTailsManagerPtr = LoadObject(0, "SuperMechTails_Manager", SuperMechTails_Manager, LoadObj_Data1);

		if (superMechTailsManagerPtr)
		{
//			Load_NewSuperMTailsAnim();
			superMechTailsManagerPtr->Data1.Entity->Index = playNum;
		}
	}
}

void LoadMechTails_r(int playerNum) {
	LoadMechTails_t.Original(playerNum);

//	if (CurrentLevel != LevelIDs_FinalHazard) {
		if (MainCharObj1[playerNum] && MainCharObj1[playerNum]->field_2 != 3) {
			LoadSuperMechTailsManager(playerNum);
			LoadSMTailsEff_Textures();
			LoadSSEff_Textures();
			LoadWaterTextures(playerNum);
			LoadSADXAuraTextures(playerNum);
		}
//	}
}

void init_SuperMechTails()
{
	LoadMechTails_t.Hook(LoadMechTails_r);
	return;
}