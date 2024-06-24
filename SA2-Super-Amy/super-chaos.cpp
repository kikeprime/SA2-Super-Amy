#include "pch.h"
#include "ss.h"


NJS_TEXLIST* Chaos_TexlistPtr = nullptr;
static FunctionHook<void, int>LoadChaos_t(LoadChaos);
extern std::string currentSuperMusic;

ModelIndex* ChaosasSonicMdl = nullptr;
ModelIndex* ChaosasShadowMdl = nullptr;
ModelIndex* ChaosasTailsMdl = nullptr;
ModelIndex* ChaosasKnucklesMdl = nullptr;

bool isChaosasSonic[2] = { false, false };
bool isChaosasShadow[2] = { false, false };
bool isChaosasTails[2] = { false, false };
bool isChaosasKnuckles[2] = { false, false };

bool CanChaostoSonic[2] = { false, false };
bool CanChaostoShadow[2] = { false, false };
bool CanChaostoTails[2] = { false, false };
bool CanChaostoKnuckles[2] = { false, false };

void __cdecl LoadSChaosEff_Textures() {
	njReleaseTexture(&SCHAura_Texlist);
	LoadTextureList("ssaura_efftex", &SCHAura_Texlist);
	return;
}

void __cdecl LoadHChaosEff_Textures() {
	njReleaseTexture(&SCHAura_Texlist);
	LoadTextureList("haura_efftex", &SCHAura_Texlist);
	return;
}

void __cdecl LoadSuperChaosCharTextures(KnucklesCharObj2* kco2) {
	LoadSChaosEff_Textures();
	njReleaseTexture(kco2->TextureList);
	kco2->TextureList = 0;
	if (ModelSwap1)
	{
		if (!AltCostume[kco2->base.PlayerNum])
		{
			kco2->TextureList = LoadCharTextures("SSCHAOS0TEX");
		}
		else
		{
			kco2->TextureList = LoadCharTextures("SSCHAOS01TEX");
		}
	}
	else
	{
		if (!AltCostume[kco2->base.PlayerNum])
		{
			kco2->TextureList = LoadCharTextures("SCHAOS0TEX");
		}
		else
		{
			kco2->TextureList = LoadCharTextures("SCHAOS01TEX");
		}
	}

	//used for upgrade textures.
//	Chaos_TexlistPtr = LoadCharTextures("CHAOS0TEX");

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

void __cdecl LoadHyperChaosCharTextures(KnucklesCharObj2* kco2) {
	LoadHChaosEff_Textures();
	njReleaseTexture(kco2->TextureList);
	kco2->TextureList = 0;
	if (ModelSwap2)
	{
		if (!AltCostume[kco2->base.PlayerNum])
		{
			kco2->TextureList = LoadCharTextures("HSHSCHAOS0TEX");
		}
		else
		{
			kco2->TextureList = LoadCharTextures("HSHSCHAOS01TEX");
		}
	}
	else if (ModelSwap1)
	{
		if (!AltCostume[kco2->base.PlayerNum])
		{
			kco2->TextureList = LoadCharTextures("HSSCHAOS0TEX");
		}
		else
		{
			kco2->TextureList = LoadCharTextures("HSSCHAOS01TEX");
		}
	}
	else
	{
		if (!AltCostume[kco2->base.PlayerNum])
		{
			kco2->TextureList = LoadCharTextures("HSCHAOS0TEX");
		}
		else
		{
			kco2->TextureList = LoadCharTextures("HSCHAOS01TEX");
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

AnimationInfo ChaosAnimCopy[272];

void __cdecl TransfoSuperChaos(EntityData1* data, int playerID, KnucklesCharObj2* kco2) {
	if (!isSuper[playerID])
	{
		if (SuperMusicVersion != None) {
			StopMusic();
			Play_SuperSonicMusic();
			ResetMusic();
		}

//		kco2->base.Speed.x = 0;

		memcpy(&ChaosAnimCopy, kco2->base.AnimInfo.Animations, sizeof(ChaosAnimCopy));
//		ControllerEnabled[playerID] = 0;

		if (CurrentLevel != LevelIDs_ChaoWorld)
			kco2->base.Powerups |= Powerups_Invincibility;

//		kco2->base.AnimInfo.Next = 0;
		LoadSuperChaosCharTextures(kco2);

//		PlayAnimationThing(&kco2->base.AnimInfo);
		Load_SuperPhysics(data);

		kco2->base.Upgrades |= Upgrades_SuperSonic;

		isSuper[playerID] = true;
	}
	else
	{
		MainCharacter[playerID]->DisplaySub_Delayed4 = nullptr;
		LoadHyperChaosCharTextures(kco2);
		kco2->base.Powerups |= Powerups_HyperSonic;
		isHyper[playerID] = true;
	}
}

void unSuperChaos(unsigned char player) {
	if (AlwaysSuperChaos)
		return;

	EntityData1* data = MainCharObj1[player];
	CharObj2Base* co2 = MainCharObj2[player];

	if (!data || !isSuper[player])
		return;

	KnucklesCharObj2* kco2 = (KnucklesCharObj2*)MainCharacter[player]->Data2.Character;

	if (co2->CharID == Characters_Chaos)
		co2->PhysData = PhysicsArray[Characters_Chaos];

	CharacterThrowObject(data, co2);
	ResetChaosControl(player);
	data->Status = 0;
	co2->Upgrades &= ~Upgrades_SuperSonic;
	co2->Powerups &= ~Powerups_HyperSonic;
	co2->Powerups &= ~Powerups_Invincibility;
//	kco2->base.AnimInfo.Next = 15;
//	kco2->base.AnimInfo.Animations = ChaosAnimCopy;
	njReleaseTexture(kco2->TextureList);
	kco2->TextureList = 0;
	if (!AltCostume[player])
	{
		kco2->TextureList = LoadCharTextures("CHAOS0TEX");
	}
	else
	{
		kco2->TextureList = LoadCharTextures("CHAOS01TEX");
	}

	MainCharacter[player]->DisplaySub_Delayed4 = nullptr;
	isHyper[player] = false;
	isSuper[player] = false;

	if (IsIngame())
	{
//		PlayAnimationThing(&kco2->base.AnimInfo);
		RestoreMusic();
	}
	else {
		njReleaseTexture(Chaos_TexlistPtr);
		Chaos_TexlistPtr = nullptr;
	}

	return;
}

void SuperChaos_ManagerDelete(ObjectMaster* obj)
{
	currentSuperMusic = "";
	char pnum = obj->Data1.Entity->Index;
	unSuperChaos(pnum);
	isHyper[pnum] = false;
	isSuper[pnum] = false;
	ResetChaosControl(pnum);
}

void ChaosasSonic_ManagerDelete(ObjectMaster* obj)
{
	char pnum = obj->Data1.Entity->Index;
	BacktoChaos(pnum);
	isChaosasSonic[pnum] = false;
 	ReleaseMDLFile(ChaosasSonicMdl);
	isChaosasShadow[pnum] = false;
 	ReleaseMDLFile(ChaosasShadowMdl);
	isChaosasTails[pnum] = false;
 	ReleaseMDLFile(ChaosasTailsMdl);
	isChaosasKnuckles[pnum] = false;
 	ReleaseMDLFile(ChaosasKnucklesMdl);
}

void SuperChaos_Manager(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	EntityData1* player = MainCharObj1[data->Index];

	if (!player)
		return;

	KnucklesCharObj2* kco2 = (KnucklesCharObj2*)MainCharacter[data->Index]->Data2.Character;

	if (kco2->base.CharID2 != Characters_Chaos || (player->field_2 == 3 && data->Index == 1))
	{
		DeleteObject_(obj);
		return;
	}

	//if player dies, remove transformation and reset manager action.
	if (GameState == GameStates_LoadFinished && !AlwaysSuperChaos && data->Action > playerInputCheck) {
		unSuperChaos(data->Index);
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
		obj->DeleteSub = SuperChaos_ManagerDelete;
		data->Action++;
		break;
	case playerInputCheck:

		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || AlwaysSuperChaos || CurrentLevel == LevelIDs_FinalHazard)
				data->Action++;
		}
		else
		{
			DeleteObject_(obj);
			return;
		}

		break;
	case superSonicTransfo:
//		data->Scale.y = ControllerEnabled[playerID];
		TransfoSuperChaos(player, playerID, kco2);
		data->Action++;
		break;
	case superSonicTransition:
//		kco2->base.AnimInfo.Next = superChaosIntro;
		data->Action++;
		break;
	case superSonicWait:

//		if (++data->Timer == 100 || AlwaysSuperChaos)
		{
			Load_SSWaterTask(playerID);
			LoadSuperAura(playerID);
//			ControllerEnabled[playerID] = data->Scale.y;
			DoNextAction_r(playerID, 15, 0);
			data->Action++;
//			data->Timer = 0;
		}
		break;
	case superSonicOnFrames:
		if (isHunterFlyAllowed || CurrentLevel == LevelIDs_FinalHazard)
		{
			if (player->Action == Action_Glide)
			{
				kco2->base.Speed.y = 2;
			}
		}
		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || AlwaysSuperChaos || CurrentLevel == LevelIDs_FinalHazard && FHZHyperForm)
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

		Reload_SS_WaterTask(kco2->base.CharID2, playerID);
		SubRings(playerID, data);

		break;
	case superSonicUntransfo:
		SuperSonic_DisableFly(player, &kco2->base);
		unSuperChaos(playerID);

		data->Action = playerInputCheck;
		break;
	}
}

enum ImpostorForm
{
	SonicForm,
	ShadowForm,
	TailsForm,
	KnucklesForm,
	MetalSonicForm,
	EggmanForm,
};

void __cdecl ChaostoSonic(EntityData1* data, int playerID, KnucklesCharObj2* kco2) {

	ControllerEnabled[playerID] = 0;

	for (int i = 0; i < sizeof(ChaosAnimCopy); i++)
	{
		kco2->base.AnimInfo.Animations[i].ModelNum = 0;
	}
//	kco2->base.AnimInfo.Animations = SonicAnimList;

//	njReleaseTexture(kco2->TextureList);
//	kco2->TextureList = 0;
//	kco2->TextureList = LoadCharTextures("SONICTEX");

	isChaosasSonic[playerID] = true;
	isChaosasShadow[playerID] = false;
	isChaosasTails[playerID] = false;
	isChaosasKnuckles[playerID] = false;
}

void __cdecl ChaostoShadow(EntityData1* data, int playerID, KnucklesCharObj2* kco2) {

	ControllerEnabled[playerID] = 0;

	for (int i = 0; i < sizeof(ChaosAnimCopy); i++)
	{
		kco2->base.AnimInfo.Animations[i].ModelNum = 65;
	}
//	kco2->base.AnimInfo.Animations = SonicAnimList;

//	njReleaseTexture(kco2->TextureList);
//	kco2->TextureList = 0;
//	kco2->TextureList = LoadCharTextures("SONICTEX");

	isChaosasSonic[playerID] = false;
	isChaosasShadow[playerID] = true;
	isChaosasTails[playerID] = false;
	isChaosasKnuckles[playerID] = false;
}

void __cdecl ChaostoTails(EntityData1* data, int playerID, KnucklesCharObj2* kco2) {

	ControllerEnabled[playerID] = 0;

	for (int i = 0; i < sizeof(ChaosAnimCopy); i++)
	{
		kco2->base.AnimInfo.Animations[i].ModelNum = 208;
	}
//	kco2->base.AnimInfo.Animations = SonicAnimList;

//	njReleaseTexture(kco2->TextureList);
//	kco2->TextureList = 0;
//	kco2->TextureList = LoadCharTextures("SONICTEX");

	isChaosasSonic[playerID] = false;
	isChaosasShadow[playerID] = false;
	isChaosasTails[playerID] = true;
	isChaosasKnuckles[playerID] = false;
}

void __cdecl ChaostoKnuckles(EntityData1* data, int playerID, KnucklesCharObj2* kco2) {

	ControllerEnabled[playerID] = 0;

	for (int i = 0; i < sizeof(ChaosAnimCopy); i++)
	{
		kco2->base.AnimInfo.Animations[i].ModelNum = 142;
	}
//	kco2->base.AnimInfo.Animations = SonicAnimList;

//	njReleaseTexture(kco2->TextureList);
//	kco2->TextureList = 0;
//	kco2->TextureList = LoadCharTextures("SONICTEX");

	isChaosasSonic[playerID] = false;
	isChaosasShadow[playerID] = false;
	isChaosasTails[playerID] = false;
	isChaosasKnuckles[playerID] = true;
}

void BacktoChaos(unsigned char player) {

	EntityData1* data = MainCharObj1[player];
	CharObj2Base* co2 = MainCharObj2[player];

	if (!data)
		return;

	KnucklesCharObj2* kco2 = (KnucklesCharObj2*)MainCharacter[player]->Data2.Character;

	data->Status = 0;
	for (int i = 0; i < sizeof(ChaosAnimCopy); i++)
	{
		kco2->base.AnimInfo.Animations[i].ModelNum = 507;
	}
//	njReleaseTexture(kco2->TextureList);
//	kco2->TextureList = 0;
//	kco2->TextureList = LoadCharTextures("CHAOS0TEX");

	isChaosasSonic[player] = false;
	isChaosasShadow[player] = false;
	isChaosasTails[player] = false;
	isChaosasKnuckles[player] = false;

	if (!IsIngame())
	{
		njReleaseTexture(Chaos_TexlistPtr);
		Chaos_TexlistPtr = nullptr;
	}

	return;
}

bool CheckBacktoChaos_Input(unsigned char playerID) {
	EntityData1* player = MainCharObj1[playerID];

	if (player->NextAction != 0 || player->Status & Status_DoNextAction)
	{
		return false;
	}

	if (Controllers[playerID].on & Buttons_Y &&
		((Controllers[playerID].press & Buttons_Up && isChaosasSonic[playerID]) ||
		(Controllers[playerID].press & Buttons_Down && isChaosasShadow[playerID]) ||
		(Controllers[playerID].press & Buttons_Left && isChaosasTails[playerID]) ||
		(Controllers[playerID].press & Buttons_Right && isChaosasKnuckles[playerID])))
	{
		BacktoChaos(playerID);
		return true;
	}

	return false;
}

bool CheckImpostor_Input(char playerID, EntityData1* player)
{
	if (Controllers[playerID].on & Buttons_Y && Controllers[playerID].press & Buttons_Up && !isChaosasSonic[playerID])
	{
		CanChaostoSonic[playerID] = true;
		return true;
	}
	if (Controllers[playerID].on & Buttons_Y && Controllers[playerID].press & Buttons_Down && !isChaosasShadow[playerID])
	{
		CanChaostoShadow[playerID] = true;
		return true;
	}
	if (Controllers[playerID].on & Buttons_Y && Controllers[playerID].press & Buttons_Left && !isChaosasTails[playerID])
	{
		CanChaostoTails[playerID] = true;
		return true;
	}
	if (Controllers[playerID].on & Buttons_Y && Controllers[playerID].press & Buttons_Right && !isChaosasKnuckles[playerID])
	{
		CanChaostoKnuckles[playerID] = true;
		return true;
	}

	return false;
}

void ChaostheImpostor_Manager(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	EntityData1* player = MainCharObj1[data->Index];

	if (!player)
		return;

	KnucklesCharObj2* kco2 = (KnucklesCharObj2*)MainCharacter[data->Index]->Data2.Character;

	if (kco2->base.CharID2 != Characters_Chaos || (player->field_2 == 3 && data->Index == 1))
	{
		DeleteObject_(obj);
		return;
	}

	//if player dies, remove transformation and reset manager action.
	if (GameState == GameStates_LoadFinished && data->Action > playerInputCheck) {
		BacktoChaos(data->Index);
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
		obj->DeleteSub = ChaosasSonic_ManagerDelete;
		data->Action++;
		break;
	case playerInputCheck:

		if (CheckImpostor_Input(playerID, player))
			data->Action++;
		
		break;
	case superSonicTransfo:
		data->Scale.y = ControllerEnabled[playerID];
		if (CanChaostoSonic[playerID])
		{
			CanChaostoSonic[playerID] = false;
			ChaostoSonic(player, playerID, kco2);
			data->Action++;
		}
		if (CanChaostoShadow[playerID])
		{
			CanChaostoShadow[playerID] = false;
			ChaostoShadow(player, playerID, kco2);
			data->Action++;
		}
		if (CanChaostoTails[playerID])
		{
			CanChaostoTails[playerID] = false;
			ChaostoTails(player, playerID, kco2);
			data->Action++;
		}
		if (CanChaostoKnuckles[playerID])
		{
			CanChaostoKnuckles[playerID] = false;
			ChaostoKnuckles(player, playerID, kco2);
			data->Action++;
		}
		break;
	case superSonicTransition:
//		kco2->base.AnimInfo.Next = superChaosIntro;
		data->Action++;
		break;
	case superSonicWait:
		ControllerEnabled[playerID] = data->Scale.y;
//		DoNextAction_r(playerID, 15, 0);
		data->Action++;
//		data->Timer = 0;
		break;
	case superSonicOnFrames:
		if (CheckBacktoChaos_Input(playerID))
		{
			data->Action = playerInputCheck;
		}
		else if (CheckImpostor_Input(playerID, player))
		{
			data->Action = superSonicTransfo;
		}
		break;
	case superSonicUntransfo:
		BacktoChaos(playerID);
		data->Action = playerInputCheck;
		break;
	}
}

void LoadSuperChaosManager(char playNum) {
	int id2 = MainCharObj2[playNum]->CharID2;

	if (id2 == Characters_Chaos) {
		ObjectMaster* superChaosManagerPtr = LoadObject(1, "SuperChaos_Manager", SuperChaos_Manager, LoadObj_Data1);

		if (superChaosManagerPtr)
		{
//			Load_NewSuperChaosAnim();
			superChaosManagerPtr->Data1.Entity->Index = playNum;
		}

		if (!TwoPlayerMode)
		{
			ObjectMaster* ChaosasSonicManagerPtr = LoadObject(1, "ChaostheImpostor_Manager", ChaostheImpostor_Manager, LoadObj_Data1);

			if (ChaosasSonicManagerPtr)
			{
				if (!AltCostume[playNum])
				{
					ChaosasSonicMdl = LoadMDLFile((char*)"SSONICMDL.PRS");
					ChaosasShadowMdl = LoadMDLFile((char*)"SSHADOWMDL.PRS");
					ChaosasTailsMdl = LoadMDLFile((char*)"MILESMDL.PRS");
					ChaosasKnucklesMdl = LoadMDLFile((char*)"KNUCKMDL.PRS");
				}
				else
				{
					ChaosasSonicMdl = LoadMDLFile((char*)"SONIC1MDL.PRS");
					ChaosasShadowMdl = LoadMDLFile((char*)"SHADOW1MDL.PRS");
					ChaosasTailsMdl = LoadMDLFile((char*)"MILES1MDL.PRS");
					ChaosasKnucklesMdl = LoadMDLFile((char*)"BKNUCKMDL.PRS");
				}
				ChaosasSonicManagerPtr->Data1.Entity->Index = playNum;
			}
		}
	}
}

void LoadChaos_r(int playerNum) {
	if (AltCostume[playerNum])
	{
		LoadMDLFile((char*)"CHAOS01MDL.PRS");
	}
	LoadChaos_t.Original(playerNum);
	KnucklesCharObj2* kco2 = (KnucklesCharObj2*)MainCharacter[playerNum]->Data2.Character;
	if (AltCostume[playerNum])
	{
		kco2->TextureList = 0;
		kco2->TextureList = LoadCharTextures("CHAOS01TEX");
	}

//	if (CurrentLevel != LevelIDs_FinalHazard) {
		if (MainCharObj1[playerNum] && MainCharObj1[playerNum]->field_2 != 3) {
			LoadSuperChaosManager(playerNum);
			LoadSSEff_Textures();
			LoadSChaosEff_Textures();
			LoadWaterTextures(playerNum);
			LoadSADXAuraTextures(playerNum);
		}
//	}
}

void init_SuperChaos()
{
	LoadChaos_t.Hook(LoadChaos_r);
	return;
}