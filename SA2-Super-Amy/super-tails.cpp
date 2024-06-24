#include "pch.h"
#include "ss.h"

//Using LoadTailsPtr doesn't work
UsercallFuncVoid(LoadTails_h, (int playerNum), (playerNum), 0x74CF00, rEAX);
TaskHook Tails_Main_t(Tails_Main);
extern std::string currentSuperMusic;

NJS_TEXNAME MilesBallTex[2];
NJS_TEXLIST MilesBall_Texlist = { arrayptrandlength(MilesBallTex) };
extern bool ModelSwap1;
extern bool ModelSwap2;

ModelInfo* JumpBallMdl = nullptr;
int spinTimer = 0;

void Tails_Main_r(ObjectMaster* obj)
{
	if (!obj || !obj->Data1.Entity)
		return;

	Tails_Main_t.Original(obj);

	EntityData1* data1 = obj->Data1.Entity;
	if (data1->Status & Status_Ball)
	{
		spinTimer++;
	}
}

void DrawMiles_JumpBall(NJS_MOTION* motion, NJS_OBJECT* mdl, float frame) {

	if (MilesCO2Extern) {

		char pID = MilesCO2Extern->base.PlayerNum;
		EntityData1* data1 = MainCharObj1[pID];
		TailsCharObj2* mCO2 = MilesCO2Extern;
		NJS_VECTOR scale = { 0.9f, 0.9f, 0.9f };

		AnimationIndex* sa2anim = getCharAnim_r();

		int curAnim = mCO2->base.AnimInfo.Current;

		if ((data1->Status & Status_Ball) != 0 && (spinTimer & 0x11) != 0 && mCO2->base.AnimInfo.mtnmode != 2)
		{
			mdl = CharacterModels[230].Model;

			if (!isSA1Char(Characters_Tails)) {
				njSetTexture(&MilesBall_Texlist);
			}

			njScaleV_(&scale);
			curAnim = 30;

			if (sa2anim)
			{
				motion = sa2anim[mCO2->base.AnimInfo.Animations[curAnim].AnimNum].Animation;
			}
			else {
				motion = CharacterAnimations[mCO2->base.AnimInfo.Animations[mCO2->base.AnimInfo.Animations[curAnim].AnimNum].AnimNum].Animation;
			}
		}
	}

	return DrawMotionAndObject(motion, mdl, frame);
}

static void __declspec(naked) DrawMotionAndObject_Hack()
{
	__asm
	{
		push[esp + 08h] // frame
		push[esp + 08h] // obj
		push ecx // mtn

		call DrawMiles_JumpBall

		pop ecx // mtn
		add esp, 4 // obj
		add esp, 4 // frame
		retn
	}
}

void __cdecl LoadSTailsEff_Textures() {
	njReleaseTexture(&STAura_Texlist);
	LoadTextureList("ssaura_efftex", &STAura_Texlist);
	return;
}

void __cdecl LoadHTailsEff_Textures() {
	njReleaseTexture(&STAura_Texlist);
	LoadTextureList("haura_efftex", &STAura_Texlist);
	return;
}

void __cdecl LoadSuperTailsCharTextures(TailsCharObj2* tco2) {
	LoadSTailsEff_Textures();
	njReleaseTexture(tco2->TextureList);
	tco2->TextureList = 0;
	if (!AltCostume[tco2->base.PlayerNum])
	{
		LoadTextureList("SballTex", &MilesBall_Texlist);
		tco2->TextureList = LoadCharTextures("SMILESTEX");
	}
	else
	{
		LoadTextureList("Sball1Tex", &MilesBall_Texlist);
		tco2->TextureList = LoadCharTextures("SMILES1TEX");
	}

	//ugly way to fix Shadow eyes texture when transforming to super, thanks to the awful GBIX Texture system.
	if (TwoPlayerMode || CurrentLevel == LevelIDs_SonicVsShadow1 || CurrentLevel == LevelIDs_SonicVsShadow2)
	{
		char OtherPlayer = tco2->base.PlayerNum == 0 ? 1 : 0;

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

void __cdecl LoadHyperTailsCharTextures(TailsCharObj2* tco2) {
	LoadHTailsEff_Textures();
	njReleaseTexture(tco2->TextureList);
	tco2->TextureList = 0;
	if (!AltCostume[tco2->base.PlayerNum])
	{
		LoadTextureList("HballTex", &MilesBall_Texlist);
		tco2->TextureList = LoadCharTextures("HSMILESTEX");
	}
	else
	{
		LoadTextureList("Hball1Tex", &MilesBall_Texlist);
		tco2->TextureList = LoadCharTextures("HSMILES1TEX");
	}

	//ugly way to fix Shadow eyes texture when transforming to super, thanks to the awful GBIX Texture system.
	if (TwoPlayerMode || CurrentLevel == LevelIDs_SonicVsShadow1 || CurrentLevel == LevelIDs_SonicVsShadow2)
	{
		char OtherPlayer = tco2->base.PlayerNum == 0 ? 1 : 0;

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

AnimationInfo TailsAnimCopy[258];

void __cdecl TransfoSuperTails(EntityData1* data, int playerID, TailsCharObj2* tco2) {
	if (!isSuper[playerID])
	{
		if (SuperMusicVersion != None) {
			StopMusic();
			Play_SuperSonicMusic();
			ResetMusic();
		}

		if (AllowSuperTailsModel)
		{
			ReleaseMDLFile(tco2->ModelList);
			tco2->ModelList = AltCostume[playerID] ? LoadMDLFile((char*)"SMILES1MDL.PRS") : LoadMDLFile((char*)"SMILESMDL.PRS");
			ModelSwap1 = true;
		}

		ControllerEnabled[playerID] = 0;

		if (CurrentLevel != LevelIDs_ChaoWorld)
			tco2->base.Powerups |= Powerups_Invincibility;

//		tco2->base.AnimInfo.Next = 0;
//		tco2->base.AnimInfo.Animations = SuperTailsAnimationList_r;
		LoadSuperTailsCharTextures(tco2);

		Load_SuperPhysics(data);

		if (CurrentLevel != LevelIDs_ChaoWorld)
			tco2->base.Upgrades |= Upgrades_SuperSonic;

		isSuper[playerID] = true;
	}
	else
	{
		MainCharacter[playerID]->DisplaySub_Delayed4 = nullptr;
		LoadHyperTailsCharTextures(tco2);
		tco2->base.Upgrades |= Upgrades_KnucklesAirNecklace;
		tco2->base.Powerups |= Powerups_HyperSonic;
		isHyper[playerID] = true;
	}

	PlayAnimationThing(&tco2->base.AnimInfo);
}

void unSuperTails(unsigned char player) {
	if (AlwaysSuperTails)
		return;

	EntityData1* data = MainCharObj1[player];
	CharObj2Base* co2 = MainCharObj2[player];

	if (!data || !isSuper[player])
		return;

	TailsCharObj2* tco2 = (TailsCharObj2*)MainCharacter[player]->Data2.Undefined;

	if (co2->CharID == Characters_Tails)
		co2->PhysData = PhysicsArray[Characters_Tails];

	CharacterThrowObject(data, co2);
	ResetChaosControl(player);
	if (co2->Upgrades & Upgrades_KnucklesAirNecklace)
	{
		co2->Upgrades &= ~Upgrades_KnucklesAirNecklace;
	}
	co2->Upgrades &= ~Upgrades_SuperSonic;
	co2->Powerups &= ~Powerups_HyperSonic;
	co2->Powerups &= ~Powerups_Invincibility;
	//	tco2->base.AnimInfo.Next = 15;
//	tco2->base.AnimInfo.Animations = TailsAnimCopy;
	njReleaseTexture(tco2->TextureList);
	LoadTextureList("ballTex", &MilesBall_Texlist);
	tco2->TextureList = 0;
	if (!AltCostume[player])
	{
		tco2->TextureList = LoadCharTextures("MILESTEX");
	}
	else
	{
		tco2->TextureList = LoadCharTextures("MILES1TEX");
	}

	MainCharacter[player]->DisplaySub_Delayed4 = nullptr;
	isHyper[player] = false;
	isSuper[player] = false;

	if (IsIngame())
	{
//		PlayAnimationThing(&tco2->base.AnimInfo);
		RestoreMusic();
	}

	if (ModelSwap1 || ModelSwap2)
	{
		ReleaseMDLFile(tco2->ModelList);
		tco2->ModelList = AltCostume[player] ? LoadMDLFile((char*)"MILES1MDL.PRS") : LoadMDLFile((char*)"MILESMDL.PRS");
		ModelSwap1 = false;
		ModelSwap2 = false;
	}

	return;
}

void SuperTails_ManagerDelete(ObjectMaster* obj)
{
	currentSuperMusic = "";
	char pnum = obj->Data1.Entity->Index;
	unSuperTails(pnum);
	isHyper[pnum] = false;
	isSuper[pnum] = false;
	ResetChaosControl(pnum);
//	Delete_STAnim();
}

void SuperTails_Manager(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	EntityData1* player = MainCharObj1[data->Index];

	if (!player)
		return;

	CharObj2Base* co2 = obj->Data2.Character;
//	TailsCharObj2* tco2 = (TailsCharObj2*)MainCharObj2[data->Index];
	TailsCharObj2* tco2 = (TailsCharObj2*)MainCharacter[data->Index]->Data2.Character;

	if (tco2->base.CharID2 != Characters_Tails || (player->field_2 == 3 && data->Index == 1))
	{
		DeleteObject_(obj);
		return;
	}

	//if player dies, remove transformation and reset manager action.
	if (GameState == GameStates_LoadFinished && !AlwaysSuperTails && data->Action > playerInputCheck) {
		unSuperTails(data->Index);
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
		obj->DeleteSub = SuperTails_ManagerDelete;
		data->Action++;
		break;
	case playerInputCheck:
		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || AlwaysSuperTails || CurrentLevel == LevelIDs_FinalHazard)
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
		TransfoSuperTails(player, playerID, tco2);
		data->Action++;
		break;
	case superSonicTransition:
//		sonicCO2->base.AnimInfo.Next = superTailsIntro;
		data->Action++;
		break;
	case superSonicWait:

//		if (++data->Timer == 100 || AlwaysSuperTails)
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
		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || CurrentLevel == LevelIDs_FinalHazard && FHZHyperForm)
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

		Reload_SS_WaterTask(tco2->base.CharID2, playerID);
		SubRings(playerID, data);

		break;
	case superSonicUntransfo:
//		SuperSonic_DisableFly(player, &sonicCO2->base);
		unSuperTails(playerID);

		data->Action = playerInputCheck;
		break;
	}
}

void LoadSuperTailsManager(char playNum) {
	int id2 = MainCharObj2[playNum]->CharID2;

	if (id2 == Characters_Tails)
	{
		ObjectMaster* superTailsManagerPtr = LoadObject(1, "SuperTails_Manager", SuperTails_Manager, LoadObj_Data1);

		if (superTailsManagerPtr)
		{
//			Load_NewSuperTailsAnim();
			superTailsManagerPtr->Data1.Entity->Index = playNum;
		}
	}
}

void LoadTails_r(int playerNum) {
	if (AltCostume[playerNum])
	{
		LoadMDLFile((char*)"MILES1MDL.PRS");
	}
	LoadTails_h.Original(playerNum);
	TailsCharObj2* tco2 = (TailsCharObj2*)MainCharObj2[playerNum];
	if (AltCostume[playerNum])
	{
		tco2->TextureList = 0;
		tco2->TextureList = LoadCharTextures("MILES1TEX");
		LoadTextureList("ball1Tex", &MilesBall_Texlist);
	}
	else
	{
		LoadTextureList("ballTex", &MilesBall_Texlist);
	}

//	if (CurrentLevel != LevelIDs_FinalHazard) {
		if (MainCharObj1[playerNum] && MainCharObj1[playerNum]->field_2 != 3)
		{
			LoadSuperTailsManager(playerNum);
			LoadSSEff_Textures();
			LoadSTailsEff_Textures();
			LoadWaterTextures(playerNum);
			LoadSADXAuraTextures(playerNum);
		}
//	}
}

void init_SuperTails()
{
	WriteCall((void*)0x750ABF, DrawMotionAndObject_Hack);
	Tails_Main_t.Hook(Tails_Main_r);
	LoadTails_h.Hook(LoadTails_r);
	return;
}