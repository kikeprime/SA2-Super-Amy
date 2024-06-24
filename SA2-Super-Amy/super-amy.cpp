#include "pch.h"
#include "ss.h"

NJS_TEXLIST* Amy_TexlistPtr = nullptr;
static FunctionHook<void, int>LoadAmy_t(LoadAmy);
ModelIndex* SuperAmyMdl = nullptr;
extern std::string currentSuperMusic;
bool ModelSwap1 = false;
bool ModelSwap2 = false;

NJS_TEXLIST* getAmyTexlist()
{
	return Amy_TexlistPtr;
}

void __cdecl LoadSAmyEff_Textures() {
	njReleaseTexture(&SSAura_Texlist);
	LoadTextureList("ssaura_efftex", &SSAura_Texlist);
	return;
}

void __cdecl LoadHAmyEff_Textures() {
	njReleaseTexture(&SSAura_Texlist);
	LoadTextureList("haura_efftex", &SSAura_Texlist);
	return;
}

void __cdecl LoadSuperAmyCharTextures(SonicCharObj2* sco2) {
	LoadSAmyEff_Textures();
	njReleaseTexture(sco2->TextureList);
	sco2->TextureList = 0;
	if (ModelSwap1)
	{
		if (!AltCostume[sco2->base.PlayerNum])
		{
			sco2->TextureList = LoadCharTextures("SSAMYTEX");
		}
		else
		{
			sco2->TextureList = LoadCharTextures("SSAMY1TEX");
		}
	}
	else
	{
		if (!AltCostume[sco2->base.PlayerNum])
		{
			sco2->TextureList = LoadCharTextures("SAMYTEX");
		}
		else
		{
			sco2->TextureList = LoadCharTextures("SAMY1TEX");
		}
	}

	//used for upgrade textures.
	Sonic_TexlistPtr = LoadCharTextures("SONICTEX");

	//ugly way to fix Shadow eyes texture when transforming to super, thanks to the awful GBIX Texture system.
	if (TwoPlayerMode || CurrentLevel == LevelIDs_SonicVsShadow1 || CurrentLevel == LevelIDs_SonicVsShadow2)
	{
		char OtherPlayer = sco2->base.PlayerNum == 0 ? 1 : 0;

		if (MainCharObj2[OtherPlayer] && MainCharObj2[OtherPlayer]->CharID2 == Characters_Shadow && !isSuper[OtherPlayer])
		{
			SonicCharObj2* sco2H = (SonicCharObj2*)MainCharacter[OtherPlayer]->Data2.Character;

			if (AltCostume[OtherPlayer] != 0)
				sco2H->TextureList = LoadCharTextures("SHADOW1TEX");
			else
				sco2H->TextureList = LoadCharTextures("teriostex");
		}
	}

	return;
}

void __cdecl LoadHyperAmyCharTextures(SonicCharObj2* sco2) {
	LoadHAmyEff_Textures();
	njReleaseTexture(sco2->TextureList);
	sco2->TextureList = 0;
	if (ModelSwap2)
	{
		if (!AltCostume[sco2->base.PlayerNum])
		{
			sco2->TextureList = LoadCharTextures("HSHSAMYTEX");
		}
		else
		{
			sco2->TextureList = LoadCharTextures("HSHSAMY1TEX");
		}
	}
	else if (ModelSwap1)
	{
		if (!AltCostume[sco2->base.PlayerNum])
		{
			sco2->TextureList = LoadCharTextures("HSSAMYTEX");
		}
		else
		{
			sco2->TextureList = LoadCharTextures("HSSAMY1TEX");
		}
	}
	if (!AltCostume[sco2->base.PlayerNum])
	{
		sco2->TextureList = LoadCharTextures("HSAMYTEX");
	}
	else
	{
		sco2->TextureList = LoadCharTextures("HSAMY1TEX");
	}

	//used for upgrade textures.
//	Sonic_TexlistPtr = LoadCharTextures("SONICTEX");

	//ugly way to fix Shadow eyes texture when transforming to super, thanks to the awful GBIX Texture system.
	if (TwoPlayerMode || CurrentLevel == LevelIDs_SonicVsShadow1 || CurrentLevel == LevelIDs_SonicVsShadow2)
	{
		char OtherPlayer = sco2->base.PlayerNum == 0 ? 1 : 0;

		if (MainCharObj2[OtherPlayer] && MainCharObj2[OtherPlayer]->CharID2 == Characters_Shadow && !isSuper[OtherPlayer])
		{
			SonicCharObj2* sco2H = (SonicCharObj2*)MainCharacter[OtherPlayer]->Data2.Character;

			if (AltCostume[OtherPlayer] != 0)
				sco2H->TextureList = LoadCharTextures("SHADOW1TEX");
			else
				sco2H->TextureList = LoadCharTextures("teriostex");
		}
	}

	return;
}

AnimationInfo AmyAnimCopy[258];

void __cdecl TransfoSuperAmy(EntityData1* data, int playerID, SonicCharObj2* sco2) {
	if (!isSuper[playerID])
	{
		if (SuperMusicVersion != None) {
			StopMusic();
			Play_SuperSonicMusic();
			ResetMusic();
		}

//		SuperAmyMdl = LoadMDLFile((char*)"SONICMDL.PRS");
		if (AllowSuperAmyModel)
		{
			ReleaseMDLFile(sco2->ModelList);
			sco2->ModelList = AltCostume[playerID] ? LoadMDLFile((char*)"SAMY1MDL.PRS") : LoadMDLFile((char*)"SAMYMDL.PRS");
			ModelSwap1 = true;
		}
		sco2->base.Speed.x = 0;

		memcpy(&AmyAnimCopy, sco2->base.AnimInfo.Animations, sizeof(AmyAnimCopy));
		ControllerEnabled[playerID] = 0;

		if (CurrentLevel != LevelIDs_ChaoWorld)
			sco2->base.Powerups |= Powerups_Invincibility;

		sco2->base.AnimInfo.Next = 0;
		sco2->base.AnimInfo.Animations = SuperAmyAnimationList_r;
		LoadSuperAmyCharTextures(sco2);
		sco2->base.Upgrades |= Upgrades_SuperSonic;

		Load_SuperPhysics(data);

		isSuper[playerID] = true;
	}
	else
	{
		MainCharacter[playerID]->DisplaySub_Delayed4 = nullptr;
		if (AllowHyperAmyModel)
		{
			ReleaseMDLFile(sco2->ModelList);
			sco2->ModelList = AltCostume[playerID] ? LoadMDLFile((char*)"HSAMY1MDL.PRS") : LoadMDLFile((char*)"HSAMYMDL.PRS");
			ModelSwap2 = true;
		}
		LoadHyperAmyCharTextures(sco2);
		sco2->base.Powerups |= Powerups_HyperSonic;
		sco2->base.Upgrades |= Upgrades_KnucklesAirNecklace;
		isHyper[playerID] = true;
	}

	PlayAnimationThing(&sco2->base.AnimInfo);
}

void unSuperAmy(unsigned char player) {
	if (AlwaysSuperAmy)
		return;

	EntityData1* data = MainCharObj1[player];
	CharObj2Base* co2 = MainCharObj2[player];

	if (!data || !isSuper[player])
		return;

	SonicCharObj2* sco2 = (SonicCharObj2*)MainCharacter[player]->Data2.Character;

	if (co2->CharID == Characters_Amy)
		co2->PhysData = PhysicsArray[Characters_Amy];

//	ReleaseMDLFile(SuperAmyMdl);
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
	sco2->base.AnimInfo.Next = 15;
	sco2->base.AnimInfo.Animations = AmyAnimCopy;
	njReleaseTexture(sco2->TextureList);
	sco2->TextureList = 0;
	if (!AltCostume[player])
	{
		sco2->TextureList = LoadCharTextures("AMYTEX");
	}
	else
	{
		sco2->TextureList = LoadCharTextures("AMY1TEX");
	}

	MainCharacter[player]->DisplaySub_Delayed4 = nullptr;
	isHyper[player] = false;
	isSuper[player] = false;

	if (IsIngame())
	{
		PlayAnimationThing(&sco2->base.AnimInfo);
		RestoreMusic();
	}
	else {
		njReleaseTexture(Amy_TexlistPtr);
		Amy_TexlistPtr = nullptr;
	}

	if (ModelSwap1 || ModelSwap2)
	{
		ReleaseMDLFile(sco2->ModelList);
		sco2->ModelList = AltCostume[player] ? LoadMDLFile((char*)"AMY1MDL.PRS") : LoadMDLFile((char*)"AMYMDL.PRS");
		ModelSwap1 = false;
		ModelSwap2 = false;
	}

	return;
}

void SuperAmy_ManagerDelete(ObjectMaster* obj)
{
	currentSuperMusic = "";
	char pnum = obj->Data1.Entity->Index;
	unSuperAmy(pnum);
	isHyper[pnum] = false;
	isSuper[pnum] = false;
	ResetChaosControl(pnum);
//	ReleaseMDLFile(SuperAmyMdl);
	Delete_SAAnim();
}

void SuperAmy_Manager(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	EntityData1* player = MainCharObj1[data->Index];

	if (!player)
		return;

	SonicCharObj2* sonicCO2 = (SonicCharObj2*)MainCharacter[data->Index]->Data2.Character;

	if (sonicCO2->base.CharID2 != Characters_Amy || (player->field_2 == 3 && data->Index == 1))
	{
		DeleteObject_(obj);
		return;
	}
	//if player dies, remove transformation and reset manager action.
	if (GameState == GameStates_LoadFinished && !AlwaysSuperAmy && data->Action > playerInputCheck) {
		unSuperAmy(data->Index);
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
		obj->DeleteSub = SuperAmy_ManagerDelete;
		data->Action++;
		break;
	case playerInputCheck:

		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || AlwaysSuperAmy || CurrentLevel == LevelIDs_FinalHazard)
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
		TransfoSuperAmy(player, playerID, sonicCO2);
		data->Action++;
		break;
	case superSonicTransition:
		sonicCO2->base.AnimInfo.Next = superAmyIntro;
		data->Action++;
		break;
	case superSonicWait:
		if (++data->Timer == 100 || AlwaysSuperAmy)
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
		if (isLastStoryBeaten())
		{
			if (CheckTransform_Input(playerID, player) || AlwaysSuperAmy || CurrentLevel == LevelIDs_FinalHazard && FHZHyperForm)
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
		unSuperAmy(playerID);

		data->Action = playerInputCheck;
		break;
	}
}

void LoadSuperAmyManager(char playNum) {
	int id2 = MainCharObj2[playNum]->CharID2;

	if (id2 == Characters_Amy) {
		ObjectMaster* superAmyManagerPtr = LoadObject(1, "SuperAmy_Manager", SuperAmy_Manager, LoadObj_Data1);

		if (superAmyManagerPtr)
		{
			Load_NewSuperAmyAnim();
			superAmyManagerPtr->Data1.Entity->Index = playNum;
		}
	}
}

void LoadAmy_r(int playerNum) {
	if (AltCostume[playerNum])
	{
		LoadMDLFile((char*)"AMY1MDL.PRS");
	}
	LoadAmy_t.Original(playerNum);
	SonicCharObj2* sco2 = (SonicCharObj2*)MainCharacter[playerNum]->Data2.Character;
	if (AltCostume[playerNum])
	{
		sco2->TextureList = 0;
		sco2->TextureList = LoadCharTextures("AMY1TEX");
	}

	if (MainCharObj1[playerNum] && MainCharObj1[playerNum]->field_2 != 3)
	{
		SuperAmyMdl = LoadMDLFile((char*)"SONICMDL.PRS");
		LoadSuperAmyManager(playerNum);
		LoadSSEff_Textures();
		LoadSAmyEff_Textures();
		LoadWaterTextures(playerNum);
		LoadSADXAuraTextures(playerNum);
	}
}

void init_SuperAmy() {

	LoadAmy_t.Hook(LoadAmy_r);
	return;
}