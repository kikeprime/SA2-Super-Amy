#include "pch.h"
#include "ss.h"

TaskHook Sonic_Main_t(Sonic_Main);
TaskHook Sonic_Display_t(Sonic_Display);
static FunctionHook<void, int>LoadSonic_t(LoadSonic);
static FunctionHook<void, EntityData1*, EntityData2*, CharObj2Base*, SonicCharObj2*> Sonic_runsActions_t(Sonic_runsActions);

bool isSuper[2] = { false, false };
bool isHyper[2] = { false, false };

NJS_TEXNAME SSEffTex[33];
NJS_TEXNAME SKAuraEffTex[16];
NJS_TEXLIST SSEff_Texlist = { arrayptrandlength(SSEffTex) };
NJS_TEXLIST SSAura_Texlist = { arrayptrandlength(SKAuraEffTex) };
NJS_TEXLIST SMAura_Texlist = { arrayptrandlength(SKAuraEffTex) };
NJS_TEXLIST STAura_Texlist = { arrayptrandlength(SKAuraEffTex) };
NJS_TEXLIST SEAura_Texlist = { arrayptrandlength(SKAuraEffTex) };
NJS_TEXLIST SKAura_Texlist = { arrayptrandlength(SKAuraEffTex) };
NJS_TEXLIST SRAura_Texlist = { arrayptrandlength(SKAuraEffTex) };
NJS_TEXLIST STKAura_Texlist = { arrayptrandlength(SKAuraEffTex) };
NJS_TEXLIST SCHAura_Texlist = { arrayptrandlength(SKAuraEffTex) };
NJS_TEXLIST SMTAura_Texlist = { arrayptrandlength(SKAuraEffTex) };
NJS_TEXLIST SMEAura_Texlist = { arrayptrandlength(SKAuraEffTex) };
NJS_TEXLIST SCWAura_Texlist = { arrayptrandlength(SKAuraEffTex) };
NJS_TEXLIST SDCWAura_Texlist = { arrayptrandlength(SKAuraEffTex) };

NJS_TEXLIST* Sonic_TexlistPtr = nullptr;

ModelIndex* SuperSonicMdl = nullptr;
extern std::string currentSuperMusic;
extern NJS_TEXLIST SSHEff_Texlist;

NJS_TEXLIST* getSonicTexlist()
{
	return Sonic_TexlistPtr;
}

//add super sonic model to sonic model pointer
void __cdecl SetSuperSonicModels(SonicCharObj2* sco2) {
	sco2->ModelList[328].Index = SuperSonicMdl[328].Index;
	sco2->ModelList[328].Model = SuperSonicMdl[328].Model;
	return;
}

void __cdecl LoadSuperSonicCharTextures(SonicCharObj2* sco2) {
	njReleaseTexture(sco2->TextureList);
	sco2->TextureList = 0;
	sco2->TextureList = LoadCharTextures("SSONICTEX");

	//used for upgrade textures.
	if (AltCostume[sco2->base.PlayerNum] != 0)
		Sonic_TexlistPtr = LoadCharTextures("SONIC1TEX");
	else
		Sonic_TexlistPtr = LoadCharTextures("SONICTEX");

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

void __cdecl LoadSSEff_Textures() {
	LoadTextureList("ss_efftex", &SSEff_Texlist);
	LoadTextureList("SSONEFFTEX", &SSONEFFTEX_TEXLIST);
	LoadTextureList("sh_efftex", &Texlist_ShadEff);
	LoadTextureList("ssh_efftex", &SSHEff_Texlist);
	return;
}

AnimationInfo SonicAnimCopy[203];

void __cdecl TransfoSuperSonic(EntityData1* data, int playerID, SonicCharObj2* sco2) {
	if (SuperMusicVersion != None) {
		StopMusic();
		Play_SuperSonicMusic();
		ResetMusic();
	}

	sco2->base.Speed.x = 0;

	memcpy(&SonicAnimCopy, sco2->base.AnimInfo.Animations, sizeof(SonicAnimCopy));
	ControllerEnabled[playerID] = 0;

	if (CurrentLevel != LevelIDs_ChaoWorld)
		sco2->base.Powerups |= Powerups_Invincibility;

	SetSuperSonicModels(sco2);
	DeleteSSJiggle(sco2);
	initJiggleSuperSonic(sco2);
	sco2->base.AnimInfo.Next = 0;
	sco2->base.AnimInfo.Animations = SuperSonicAnimationList_r;
	LoadSuperSonicCharTextures(sco2);

	PlayAnimationThing(&sco2->base.AnimInfo);
	Load_SuperPhysics(data);

	if (CurrentLevel != LevelIDs_ChaoWorld)
		sco2->base.Upgrades |= Upgrades_SuperSonic;

	isSuper[playerID] = true;
}

void SubRings(unsigned char player, EntityData1* data) {
	char charID = MainCharObj2[player]->CharID2;

	if (RemoveLimitations || charID == Characters_Amy && AlwaysSuperAmy || charID == Characters_MetalSonic && AlwaysSuperMetalSonic || charID == Characters_Knuckles && AlwaysSuperKnux || charID == Characters_Rouge && AlwaysSuperRouge || charID == Characters_Tikal && AlwaysSuperTikal || charID == Characters_Chaos && AlwaysSuperChaos || !isSuper[player] || TimerStopped != 0)
		return;

	if (FrameCountIngame % 60 == 0 && RingCount[player] > 0) {
		AddRings(player, -1);
	}

	if (RingCount[player] <= 0)
	{
		data->Action = superSonicUntransfo;
	}

	return;
}

void unSuper(unsigned char player) {
	if (AlwaysSuperSonic)
		return;

	EntityData1* data = MainCharObj1[player];
	CharObj2Base* co2 = MainCharObj2[player];

	if (!data || !isSuper[player])
		return;

	SonicCharObj2* co2S = (SonicCharObj2*)MainCharacter[player]->Data2.Character;

	if (co2->CharID == Characters_Sonic)
		co2->PhysData = PhysicsArray[Characters_Sonic];

	CharacterThrowObject(data, co2);
	ResetChaosControl(player);
	DeleteSSJiggle(co2S);
	initJiggleSuperSonic(co2S);
	data->Status = 0;
	co2->Upgrades &= ~Upgrades_SuperSonic;
	co2->Powerups &= ~Powerups_Invincibility;
	co2S->base.AnimInfo.Next = 15;
	co2S->base.AnimInfo.Animations = SonicAnimCopy;
	njReleaseTexture(co2S->TextureList);
	co2S->TextureList = 0;

	if (AltCostume[player] != 0)
		co2S->TextureList = LoadCharTextures("SONIC1TEX");
	else
		co2S->TextureList = LoadCharTextures("SONICTEX");

	MainCharacter[player]->DisplaySub_Delayed4 = nullptr;
	isSuper[player] = false;

	if (IsIngame())
	{
		PlayAnimationThing(&co2S->base.AnimInfo);
		RestoreMusic();
	}
	else {
		njReleaseTexture(Sonic_TexlistPtr);
		Sonic_TexlistPtr = nullptr;
	}

	return;
}

bool CheckUntransform_Input(unsigned char playerID) {
	EntityData1* player = MainCharObj1[playerID];

	if (!player
		|| AlwaysSuperAmy && MainCharObj2[playerID]->CharID2 == Characters_Amy || AlwaysSuperMetalSonic && MainCharObj2[playerID]->CharID2 == Characters_MetalSonic
		|| AlwaysSuperTails && MainCharObj2[playerID]->CharID2 == Characters_Tails || AlwaysSuperEggman && MainCharObj2[playerID]->CharID2 == Characters_Eggman
		|| AlwaysSuperKnux && MainCharObj2[playerID]->CharID2 == Characters_Knuckles || AlwaysSuperRouge && MainCharObj2[playerID]->CharID2 == Characters_Rouge
		|| AlwaysSuperTikal && MainCharObj2[playerID]->CharID2 == Characters_Tikal || AlwaysSuperChaos && MainCharObj2[playerID]->CharID2 == Characters_Chaos
		|| AlwaysSuperMechTails && MainCharObj2[playerID]->CharID2 == Characters_MechTails || AlwaysSuperMechEggman && MainCharObj2[playerID]->CharID2 == Characters_MechEggman
		|| AlwaysSuperChaoWalker && MainCharObj2[playerID]->CharID2 == Characters_ChaoWalker || AlwaysSuperDarkChaoWalker && MainCharObj2[playerID]->CharID2 == Characters_DarkChaoWalker
		|| !unTransform)
		return false;

	if (player->NextAction != 0 || player->Status & Status_DoNextAction)
	{
		return false;
	}

	if (ControllerPointers[playerID]->on & TransformButton && (!playerID ? !ktrans1 : !ktrans2) || (!playerID ? ktrans1 : ktrans2) && GetAsyncKeyState(!playerID ? P1TransformKey : P2TransformKey) & 0x0001)
	{
		if (player->Action == Action_HomingAttack || player->Action == Action_Glide || player->Action == Action_MechHover || player->Action == Action_Jump) {
			player->Status &= ~Status_Ball;

			if (MainCharObj2[playerID]->CharID2 == Characters_Amy)
				unSuperAmy(playerID);
			else if (MainCharObj2[playerID]->CharID2 == Characters_MetalSonic)
				unSuperMetalSonic(playerID);
			else if (MainCharObj2[playerID]->CharID2 == Characters_Tails)
				unSuperTails(playerID);
			else if (MainCharObj2[playerID]->CharID2 == Characters_Eggman)
				unSuperEggman(playerID);
			else if (MainCharObj2[playerID]->CharID2 == Characters_Knuckles)
				unSuperKnux(playerID);
			else if (MainCharObj2[playerID]->CharID2 == Characters_Rouge)
				unSuperRouge(playerID);
			else if (MainCharObj2[playerID]->CharID2 == Characters_Tikal)
				unSuperTikal(playerID);
			else if (MainCharObj2[playerID]->CharID2 == Characters_Chaos)
				unSuperChaos(playerID);
			else if (MainCharObj2[playerID]->CharID2 == Characters_MechTails)
				unSuperMechTails(playerID);
			else if (MainCharObj2[playerID]->CharID2 == Characters_MechEggman)
				unSuperMechEggman(playerID);
			else if (MainCharObj2[playerID]->CharID2 == Characters_ChaoWalker)
				unSuperChaoWalker(playerID);
			else if (MainCharObj2[playerID]->CharID2 == Characters_DarkChaoWalker)
				unSuperDarkChaoWalker(playerID);

			return true;
		}
	}

	return false;
}

bool CheckTransform_Input(char playerID, EntityData1* player)
{
	if (isHyper[playerID])
		return false;

	if (CurrentLevel == LevelIDs_FinalHazard)
		return false;

	if (RingCount[playerID] >= 50 && !isSuper[playerID] || RingCount[playerID] >= 100 && isSuper[playerID] || RemoveLimitations)
	{
		if (player->Action == Action_Jump || player->Action == Action_Glide || player->Action == Action_MechHover || player->Action == Action_BounceUp && (player->Status & Status_Ball) == 0)
		{
				if (Controllers[playerID].press & TransformButton && (!playerID ? !ktrans1 : !ktrans2) || (!playerID ? ktrans1 : ktrans2) && GetAsyncKeyState(!playerID ? P1TransformKey : P2TransformKey) & 0x0001)
				{
					player->Action = 18;
					player->Status &= ~Status_Ball;
					return true;
				}
		}
	}

	return false;
}

void SuperSonic_ManagerDelete(ObjectMaster* obj)
{
	currentSuperMusic = "";
	char pnum = obj->Data1.Entity->Index;
	unSuper(pnum);
	isSuper[pnum] = false;
	ResetChaosControl(pnum);
	ReleaseMDLFile(SuperSonicMdl);
	Delete_SSAnim();
}

void SuperSonic_Manager(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;
	EntityData1* player = MainCharObj1[data->Index];

	if (!player)
		return;

	SonicCharObj2* sco2 = (SonicCharObj2*)MainCharacter[data->Index]->Data2.Character;

	if (sco2->base.CharID2 != Characters_Sonic || (player->field_2 == 3 && data->Index == 1))
	{
		DeleteObject_(obj);
		return;
	}

	//if player dies, remove transformation and reset manager action.
	if (GameState == GameStates_LoadFinished && !AlwaysSuperSonic && data->Action > playerInputCheck) {
		unSuper(data->Index);
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
		obj->DeleteSub = SuperSonic_ManagerDelete;
		data->Action++;
		break;
	case playerInputCheck:

		if (isLastStoryBeaten()) {
			if (CheckTransform_Input(playerID, player) || AlwaysSuperSonic)
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
		TransfoSuperSonic(player, playerID, sco2);
		data->Action++;
		break;
	case superSonicTransition:
		sco2->base.AnimInfo.Next = superSonicIntro;
		data->Action++;
		break;
	case superSonicWait:

		if (++data->Timer == 100 || AlwaysSuperSonic)
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
		if (CheckUntransform_Input(playerID)) {
			data->Action = playerInputCheck;
		}

		Reload_SS_WaterTask(sco2->base.CharID2, playerID);
		SubRings(playerID, data);

		break;
	case superSonicUntransfo:
		SuperSonic_DisableFly(player, &sco2->base);
		unSuper(playerID);

		data->Action = playerInputCheck;
		break;
	}
}

void LoadSuperSonicManager(char playNum) {
	int id2 = MainCharObj2[playNum]->CharID2;

	if (id2 == Characters_Sonic) {
		ObjectMaster* superSonicManagerPtr = LoadObject(0, "SuperSonic_Manager", SuperSonic_Manager, LoadObj_Data1);

		if (superSonicManagerPtr)
		{
			SuperSonicMdl = LoadMDLFile((char*)"SSONICMDL.PRS");
			Load_NewSuperSonicAnim();
			superSonicManagerPtr->Data1.Entity->Index = playNum;
		}
	}
}

void __cdecl Sonic_HealdObjectStuff(EntityData1* data1, CharObj2Base* co2) {
	*(int*)0x25F02D8 &= 0xFFFFDBFF;
	*(int*)0x25F02D4 = *(int*)0x1DEB6A0;
	UpgradeDrawCallback = 0;
	*(int*)0x25F0268 = *(int*)0x1DEB6A8;
	sub_487060(byte_1DE4400);
	SonicHeldObjectThing(data1, co2);
	return;
}

void DrawSonicMotion(EntityData1* data1, SonicCharObj2* sco2) {
	NJS_MOTION* Motion;

	NJS_TEXLIST* texlist = sco2->TextureList;

	if (!texlist)
		return;

	bool isSonic = sco2->base.CharID2 == Characters_Sonic;
	bool isShadow = sco2->base.CharID2 == Characters_Shadow;
	bool isAmy = sco2->base.CharID2 == Characters_Amy;
	bool isMetal = sco2->base.CharID2 == Characters_MetalSonic;

	njScale(CURRENT_MATRIX, data1->Scale.x, data1->Scale.y, data1->Scale.z);

	int curAnim = sco2->base.AnimInfo.Current;
	NJS_OBJECT* SonicModel = CharacterModels[sco2->base.AnimInfo.Animations[curAnim].ModelNum].Model;

	if (sco2->base.AnimInfo.mtnmode == 2)
	{
		Motion = sco2->base.AnimInfo.Motion;
	}
	else
	{
		if ((data1->Status & Status_Ball) != 0
			&& (sco2->gap35E[2] & 0x11) != 0)
		{
			SonicModel = CharacterModels[sco2->base.AnimInfo.Animations[30].ModelNum].Model;// ball form
			curAnim = 30;
		}

		AnimationIndex* CharAnim = getCharAnim_r();

		if (!CharAnim)
			Motion = CharacterAnimations[sco2->base.AnimInfo.Animations[curAnim].AnimNum].Animation;
		else
			Motion = CharAnim[sco2->base.AnimInfo.Animations[curAnim].AnimNum].Animation;
	}

	if (curAnim == 30 && !isAmy && !isMetal && !(isShadow && sco2->base.AnimInfo.Animations[0].ModelNum != 355))
	{
		if (isSonic && !isSA1Char(Characters_SuperSonic))
			texlist = &SSEff_Texlist;
		else if (!isSonic && !isSA1Char(Characters_SuperShadow))
			texlist = &SSHEff_Texlist;
	}

	if (AltCostume[sco2->base.PlayerNum] == 0)
		njSetTexture(texlist);

	njCnkMotion(SonicModel, Motion, sco2->base.AnimInfo.nframe); //Draw Sonic animated

	if (isSonic)
		ResetSSJiggle(sco2);
	else if (isShadow)
		ResetSSHJiggle(sco2);
}

void __cdecl DoSpinDashRotationModel() {
	NJS_VECTOR spinDashThing = { 0.0f, -1.0f, 0.0f };

	njTranslateEx(&spinDashThing);
	NJS_MATRIX_PTR v14 = _nj_current_matrix_ptr_;
	njTranslate(_nj_current_matrix_ptr_, 0.0f, 5.0f, 0.0f);
	njRotateZ(v14, 0x2000);
	njTranslate(v14, 0.0f, -5.0f, 0.0f);
	spinDashThing.x = 0.69999999f;
	spinDashThing.y = 1.1f;
	spinDashThing.z = 0.80000001f;
	njScaleEx(&spinDashThing);
}

void __cdecl Sonic_Display_r(ObjectMaster* obj)
{
	SonicCharObj2* sco2 = (SonicCharObj2*)obj->Data2.Undefined;
	EntityData1* data1 = obj->Data1.Entity;
	char pID = sco2->base.PlayerNum;
	char char2 = sco2->base.CharID2;

	if (!sco2->TextureList || !sco2->MotionList)
		return;

//	if (!isSuper[pID] || char2 != Characters_Amy && char2 != Characters_MetalSonic) {
	if (char2 != Characters_Amy && char2 != Characters_MetalSonic && char2 != Characters_Sonic && char2 != Characters_Shadow || char2 == Characters_Sonic && sco2->base.AnimInfo.Animations[0].ModelNum != 328) {// || char2 == Characters_Shadow && sco2->base.AnimInfo.Animations[0].ModelNum != 355) {
		return Sonic_Display_t.Original(obj);
	}

	bool isSonic = char2 == Characters_Sonic;
	bool isShadow = char2 == Characters_Shadow;
	bool isAmy = char2 == Characters_Amy;
	bool isMetal = char2 == Characters_MetalSonic;

	//used to calc matrix for upgrades, pick/drop object and aura position.
	memcpy(MATRIX_1A51A00, CURRENT_MATRIX, 0x30u);
	SonicCO2PtrExtern = sco2;
	sub_427040(MATRIX_1A51A00, CURRENT_MATRIX);

	ModelFuncPtr UpgradeDrawCallbackB = UpgradeDrawCallback;

	//if (isSonic || isShadow)
	{
		if (AltCostume[pID] != 0)
			Sonic_TexlistPtr = LoadCharTextures("SONIC1TEX");
		else
			Sonic_TexlistPtr = LoadCharTextures("SONICTEX");

		if (AltCostume[pID] != 0)
			Shadow_Texlist = LoadCharTextures("SHADOW1TEX");
		else
			Shadow_Texlist = LoadCharTextures("TERIOSTEX");
	}

	if (isSonic)
		UpgradeDrawCallback = SuperSonic_Callback_r;
	else if (isShadow)
		UpgradeDrawCallback = SuperShadow_Callback_r;
	else if (isAmy)
		UpgradeDrawCallback = SuperAmy_Callback_r;
	else if (isMetal)
		UpgradeDrawCallback = SuperMetal_Callback_r;

	if ((data1->Timer & 2) != 0 && !Pose2PStart_PlayerNum)
	{
		Sonic_HealdObjectStuff(data1, &sco2->base);
		return;
	}

	int curAnim = sco2->base.AnimInfo.Current;

	njSetTexture(sco2->TextureList);
	njPushMatrixEx();
	njTranslateEx(&data1->Position);
	njScale(CURRENT_MATRIX, data1->Scale.x, data1->Scale.y, data1->Scale.z);

	if (isShadow)
		Set_SSHJiggle(sco2);
	else if (isSonic)
		Set_SSJiggle(sco2);

	njRotateZ_r(data1->Rotation.z);
	njRotateX_r(data1->Rotation.x);
	njRotateY_r(0x8000 - data1->Rotation.y);

	if (curAnim != 11 || (data1->Status & (Status_OnObjectColli | Status_Ground)) == 0)
	{
		DrawSonicMotion(data1, sco2);

		if (isSonic)
			DisplaySuperSonic_Upgrade(data1, sco2);
		else if (isShadow)
			DisplaySuperShadow_Upgrade(data1, sco2);
		else if (isAmy)
			DisplaySuperAmy_Upgrade(data1, sco2);
		else if (isMetal)
			DisplaySuperMetal_Upgrade(data1, sco2);

		Sonic_HealdObjectStuff(data1, &sco2->base);
		njPopMatrixEx();
		return;
	}

	DoSpinDashRotationModel();
	DrawSonicMotion(data1, sco2);
	njPopMatrixEx();
}

void LoadSonic_r(int playerNum) {
	LoadSonic_t.Original(playerNum);

	if (CurrentLevel != LevelIDs_FinalHazard) {
		if (MainCharObj1[playerNum] && MainCharObj1[playerNum]->field_2 != 3) {
			LoadSuperSonicManager(playerNum);
			LoadSSEff_Textures();
			LoadWaterTextures(playerNum);
			LoadSADXAuraTextures(playerNum);
		}
	}
}


void SuperSonic_PlayVictoryAnimation(EntityData1* data1, CharObj2Base* co2) {
	if (data1->Action == Action_ObjectControl)
	{
		if (TimerStopped != 0 && (co2->AnimInfo.Next == 54 || co2->AnimInfo.Current == 54)) { //Check if the level is finished
			{
				if(co2->CharID == Characters_Amy)
				co2->AnimInfo.Next = superAmyVictory;
				else
				co2->AnimInfo.Next = superSonicVictory;

				data1->Action = 120;
			}
		}
	}
}

void SuperSonic_RunCustomAction(EntityData1* data1, EntityData2* data2, SonicCharObj2* SonicCO2, CharObj2Base* co2)
{
	SuperSonicFly_ActionsManagement(data1, data2, SonicCO2, co2);

	if (AllowSuperAttacks && !TwoPlayerMode) {
		ChaosControl_Management(co2);
	}
}

void Sonic_Main_r(ObjectMaster* obj)
{
	CharObj2Base* co2 = MainCharObj2[obj->Data2.Character->PlayerNum];
	EntityData1* data1 = MainCharObj1[obj->Data2.Character->PlayerNum];
	EntityData2* data2 = MainCharData2[obj->Data2.Character->PlayerNum];
	SonicCharObj2* sco2 = (SonicCharObj2*)obj->Data2.Character;

	if (isSuper[co2->PlayerNum]) {
		if (sco2->base.CharID2 != Characters_Amy)
		SuperSonic_PlayVictoryAnimation(data1, co2);

		SuperSonicFly_MainManagement(data1, co2, data2);
	}

	Sonic_Main_t.Original(obj);
}

void __cdecl Sonic_runsActions_r(EntityData1* data1, EntityData2* data2, CharObj2Base* co2, SonicCharObj2* SonicCO2)
{
	if (isSuper[co2->PlayerNum]) {
		SuperSonic_RunCustomAction(data1, data2, SonicCO2, co2);
	}

	Sonic_runsActions_t.Original(data1, data2, co2, SonicCO2);
}

void init_SuperSonic() {

//	LoadSonic_t.Hook(LoadSonic_r);
	Sonic_Display_t.Hook(Sonic_Display_r);
	LoadSSEff_Textures();
	Sonic_runsActions_t.Hook(Sonic_runsActions_r);
	Sonic_Main_t.Hook(Sonic_Main_r);
	init_AfterImages();
//	initChaosControl_Hack();
	
	return;
}
