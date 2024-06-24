#include "pch.h"
#include "Trampoline.h"

//serie of hacks to display a yellow aura when using Super Sonic, done by using shadow texlist.
//Also add the super aura from Finalhazard fight

static UsercallFuncVoid(DoSpinDashAura_t, (ObjectMaster* a1), (a1), 0x7562A0, rEDI);
static UsercallFuncVoid(DoJumpAura_t, (ObjectMaster* a1), (a1), 0x756AE0, rEDI);
static UsercallFuncVoid(DoHomingAura_t, (ObjectMaster* a1), (a1), 0x7566C0, rEDI);
TaskHook HomingDashAura_Display_t(0x757040);

ModelInfo* SADXSuperAuraModel[3];

bool isNotSuperSonic(CharObj2Base* co2)
{
	char charID2 = co2->CharID2;

	if (charID2 == Characters_Amy || charID2 == Characters_MetalSonic || co2->CharID == Characters_Shadow || !isSuper[co2->PlayerNum] && !(co2->Upgrades & Upgrades_SuperSonic))
	{
		return true;
	}

	return false;
}

void DoSpinDashAura_r(ObjectMaster* obj)
{
	NJS_VECTOR a1;
	double v2; 
	double v3; 
	float* v4; 
	double v5; 
	CharObj2Base* co2;
	int v7; // ecx

	auto aura = (auraStruct*)obj->Data2.Undefined;

	if (!aura || !MainCharObj1[aura->charID])
		return;

	if (isNotSuperSonic(MainCharObj2[aura->charID]))
	{
		return DoSpinDashAura_t.Original(obj);
	}

	if (MainCharObj1[aura->charID])
	{
		a1.z = 0.0;
		a1.x = 0.0;
		a1.y = (double)rand() * 0.000030517578125 + 0.2000000029802322;
		njPushUnitMatrix();
		v2 = (double)rand() * 0.000030517578125 * 65536.0;
		if ((int)v2)
		{
			njRotateZ((float*)_nj_current_matrix_ptr_, (int)v2);
		}
		v3 = (double)rand() * 0.000030517578125 * 65536.0;

		njRotateX_r((int)v3);

		v5 = (double)rand() * 0.000030517578125 * 65536.0;
		v4 = (float*)_nj_current_matrix_ptr_;
		if ((int)v5)
		{
			njRotateY(_nj_current_matrix_ptr_, (int)v5);
		}
		njCalcVector_(&a1, &aura->pos, v4);
		njPopMatrix(1u);
	}
	v7 = aura->charID;
	*(float*)&aura->idk3[1] = flt_B18F54;
	aura->idk3[0] = 1;
	co2 = MainCharObj2[v7];
	char charID2 = co2->CharID2;

	if (CharacterModels[19].Model)
		aura->Model = CharacterModels[19].Model;
	else
		return;

	if ((double)rand() * 0.000030517578125 <= 0.5)
	{
		aura->Tex = Texlist_ShadEff.textures + 1;
	}
	else
	{
		aura->Tex = Texlist_ShadEff.textures;
	}

	obj->DisplaySub_Delayed1 = SpinDashAura_Display;

	return;
}

void DoJumpAura_r(ObjectMaster* obj)
{
	auraStruct* aura = (auraStruct*)obj->Data2.Undefined;

	if (!aura || !MainCharObj1[aura->charID])
		return;

	if (isNotSuperSonic(MainCharObj2[aura->charID]))
	{
		return DoJumpAura_t.Original(obj);
	}

	char charID = aura->charID;

	EntityData1* playerData = MainCharObj1[charID];

	if (playerData)
	{
		CollisionInfo* col = playerData->Collision;
		if (col)
		{
			CollisionData* colArray = col->CollisionArray;
			aura->pos.x = colArray->center.x;
			aura->pos.y = colArray->center.y;
			aura->pos.z = colArray->center.z;
		}
	}

	aura->idk3[0] = 1;
	*(float*)&aura->idk3[1] = 1.2;

	if (CharacterModels[19].Model)
		aura->Model = CharacterModels[19].Model;
	else
		return;

	if ((double)rand() * 0.000030517578125 <= 0.5)
	{
		aura->Tex = Texlist_ShadEff.textures + 1;
	}
	else
	{
		aura->Tex = Texlist_ShadEff.textures;
	}
	obj->DisplaySub_Delayed1 = JumpAura_Display;
	return;
}

void DoHomingAura_r(ObjectMaster* obj)
{
	auraStruct* aura = (auraStruct*)obj->Data2.Undefined;

	if (!aura || !MainCharObj1[aura->charID])
		return;

	if (isNotSuperSonic(MainCharObj2[aura->charID]))
	{
		return DoHomingAura_t.Original(obj);
	}

	EntityData1* pData = MainCharObj1[aura->charID];
	int rng = 0;
	double v4;
	double v5;
	NJS_VECTOR result = { 0 };
	aura = (auraStruct*)obj->Data2.Undefined;

	if (pData)
	{
		result.z = 0.0;
		result.x = 0.0;
		rng = rand();
		result.y = (double)rng * 0.000030517578125 + (double)rng * 0.000030517578125 + 1.0;
		njPushUnitMatrix();
		v4 = (double)rand() * 0.000030517578125 * 65536.0;
		if ((int)v4)
		{
			njRotateZ((float*)_nj_current_matrix_ptr_, (int)v4);
		}
		v5 = (double)rand() * 0.000030517578125 * 65536.0;

		njRotateX_r((int)v5);
		njRotateY_r(pData->Rotation.y);

		njCalcVector_(&result, &aura->pos, CURRENT_MATRIX); //njCalcVector
		njPopMatrix(1u);
	}

	char charID = aura->charID;
	*(float*)&aura->idk3[1] = 1.2;
	aura->idk3[0] = 1;
	CharObj2Base* co2 = MainCharObj2[charID];
	char charID2 = co2->CharID2;

	if (CharacterModels[19].Model)
		aura->Model = CharacterModels[19].Model;
	else
		return;

	if ((double)rand() * 0.000030517578125 <= 0.5)
	{
		aura->Tex = Texlist_ShadEff.textures + 1;
	}
	else
	{
		aura->Tex = Texlist_ShadEff.textures;
	}

	obj->DisplaySub_Delayed1 = HomingAura_Display;

	return;
}

void __cdecl HomingDashAura_Display_r(ObjectMaster* a1)
{
	int v4; // edx
	void** v5; // eax
	void** v8; // ecx
	int v10; // eax
	NJS_OBJECT* auraMdl;

	auraStruct* aura = (auraStruct*)a1->Data2.Undefined;

	if (!aura)
		return;

	auto co2 = MainCharObj2[aura->charID];

	if (isNotSuperSonic(co2))
	{
		return HomingDashAura_Display_t.Original(a1);
	}

	char charID2 = co2->CharID2;

	if (aura->idk == 2)
	{
		v4 = *(__int16*)(&aura->charID + 1);

		v5 = &off_A0B1C8 + 2 * v4;
		*(DWORD*)(*(DWORD*)Has_texlist_batadvPlayerChara_in_it.gap0 + 32) = (DWORD)v5;
	}
	else
	{
		v10 = *(__int16*)(&aura->charID + 1);
		v8 = &off_A0B128 + 2 * v10;
		*(DWORD*)(*(DWORD*)Has_texlist_batadvPlayerChara_in_it.gap0 + 32) = (DWORD)v8;
	}

	byte_25EFFCC = 0;
	if (!dword_1A55808)
	{
		sub_420510(0, flt_19341C4, flt_19341C8, dword_19341C0);
	}
	auraMdl = aura->Model;
	sub_42D340();
	ProcessChunkModelsWithCallback(auraMdl, ProcessChunkModel);
	byte_25EFFCC = 1;
	if (!dword_1A55808)
	{
		sub_420510(dword_193411C, flt_19341C4, flt_19341C8, dword_19341C0);
	}
}

char superAuraArray[6] = { 3, 4, 5, 6, 7, 8 };
char superAuraArrayShadow[6] = { 9, 10, 11, 12, 13, 14 };
char auraCount = 0;

void DisplaySuperAura(char character) {

	*(DWORD*)(*(DWORD*)Has_texlist_batadvPlayerChara_in_it.gap0 + 32) = (DWORD)&SSONEFFTEX_TEXLIST;

	if (GameState != GameStates_Pause) {

		//animate Aura using a loop doesn't work for some reason
		if (auraCount == LengthOfArray(superAuraArray) - 1)
			auraCount = 0;
		else
			auraCount++;
	}

	animate_AuraThing = character == Characters_Sonic ? superAuraArray[auraCount] : superAuraArrayShadow[auraCount];
}

void SuperAura_r(ObjectMaster* obj) {

	SonicCharObj2* co2 = (SonicCharObj2*)obj->Data2.Undefined;
	EntityData1* data = obj->Data1.Entity;
	NJS_OBJECT* v24;

	if (co2->base.AnimInfo.Current == 54 || co2->base.AnimInfo.Next == 54 || !isSuper[co2->base.PlayerNum])
	{
		obj->DisplaySub_Delayed4 = nullptr;
		return;
	}

	if (superAuraState == 1)
	{
		if (co2->base.Speed.x >= -5.0 && co2->base.Speed.x < 5.0f && co2->base.Speed.y >= -6.0f && co2->base.Speed.y < 6.0)
			return;
	}

	njSetTexture(co2->TextureList);

	njPushMatrix(CURRENT_MATRIX);

	njTranslate(CURRENT_MATRIX, data->Position.x, data->Position.y, data->Position.z);
	sub_42D340();

	njRotateZ_r(data->Rotation.z);

	njRotateX_r(data->Rotation.x);

	njRotateY_r(0x8000 - data->Rotation.y);

	njScale(CURRENT_MATRIX, data->Scale.x, data->Scale.y, data->Scale.z);

	DisplaySuperAura(co2->base.CharID2);

	njPushMatrix(CURRENT_MATRIX);
	njTranslate(CURRENT_MATRIX, 0.0f, -3.0f, 0.0f);
	sub_42D340();
	ProcessChunkModelsWithCallback((NJS_OBJECT*)0x170B47C, ProcessChunkModel);// Draw Aura
	njPopMatrix(2u);
}

static NJS_TEXNAME SADXAuratexid0 = { (char*)"S1sonic01", 0, 0 };
static NJS_TEXNAME SADXAuratexid1 = { (char*)"S1sonic02", 0, 0 };
static NJS_TEXNAME SADXAuratexid2 = { (char*)"S1sonic03", 0, 0 };
static NJS_TEXNAME SADXAuratexid3 = { (char*)"S1sonic04", 0, 0 };
static NJS_TEXNAME SADXAuratexid4 = { (char*)"S1sonic05", 0, 0 };
static NJS_TEXNAME SADXAuratexid5 = { (char*)"S1sonic06", 0, 0 };
static NJS_TEXNAME SADXAuratexid6 = { (char*)"S1sonic07", 0, 0 };
static NJS_TEXNAME SADXAuratexid7 = { (char*)"S1sonic08", 0, 0 };

static NJS_TEXNAME SADXAuratexid8 = { (char*)"S2sonic01", 0, 0 };
static NJS_TEXNAME SADXAuratexid9 = { (char*)"S2sonic02", 0, 0 };
static NJS_TEXNAME SADXAuratexid10 = { (char*)"S2sonic03", 0, 0 };
static NJS_TEXNAME SADXAuratexid11 = { (char*)"S2sonic04", 0, 0 };
static NJS_TEXNAME SADXAuratexid12 = { (char*)"S2sonic05", 0, 0 };
static NJS_TEXNAME SADXAuratexid13 = { (char*)"S2sonic06", 0, 0 };
static NJS_TEXNAME SADXAuratexid14 = { (char*)"S2sonic07", 0, 0 };
static NJS_TEXNAME SADXAuratexid15 = { (char*)"S2sonic08", 0, 0 };

static NJS_TEXNAME SADXTikalAuratexid0 = { (char*)"S1knux01", 0, 0 };
static NJS_TEXNAME SADXTikalAuratexid1 = { (char*)"S1knux02", 0, 0 };
static NJS_TEXNAME SADXTikalAuratexid2 = { (char*)"S1knux03", 0, 0 };
static NJS_TEXNAME SADXTikalAuratexid3 = { (char*)"S1knux04", 0, 0 };
static NJS_TEXNAME SADXTikalAuratexid4 = { (char*)"S1knux05", 0, 0 };
static NJS_TEXNAME SADXTikalAuratexid5 = { (char*)"S1knux06", 0, 0 };
static NJS_TEXNAME SADXTikalAuratexid6 = { (char*)"S1knux07", 0, 0 };
static NJS_TEXNAME SADXTikalAuratexid7 = { (char*)"S1knux08", 0, 0 };

static NJS_TEXNAME SADXTikalAuratexid8 = { (char*)"S2knux01", 0, 0 };
static NJS_TEXNAME SADXTikalAuratexid9 = { (char*)"S2knux02", 0, 0 };
static NJS_TEXNAME SADXTikalAuratexid10 = { (char*)"S2knux03", 0, 0 };
static NJS_TEXNAME SADXTikalAuratexid11 = { (char*)"S2knux04", 0, 0 };
static NJS_TEXNAME SADXTikalAuratexid12 = { (char*)"S2knux05", 0, 0 };
static NJS_TEXNAME SADXTikalAuratexid13 = { (char*)"S2knux06", 0, 0 };
static NJS_TEXNAME SADXTikalAuratexid14 = { (char*)"S2knux07", 0, 0 };
static NJS_TEXNAME SADXTikalAuratexid15 = { (char*)"S2knux08", 0, 0 };

static NJS_TEXLIST SADXSuperAuraTexList[8] = {
	&SADXAuratexid0, 1,
	&SADXAuratexid1, 1,
	&SADXAuratexid2, 1,
	&SADXAuratexid3, 1,
	&SADXAuratexid4, 1,
	&SADXAuratexid5, 1,
	&SADXAuratexid6, 1,
	&SADXAuratexid7, 1
};

static NJS_TEXLIST SADXSuperAuraTexList2[8] = {
	&SADXAuratexid8, 1,
	&SADXAuratexid9, 1,
	&SADXAuratexid10, 1,
	&SADXAuratexid11, 1,
	&SADXAuratexid12, 1,
	&SADXAuratexid13, 1,
	&SADXAuratexid14, 1,
	&SADXAuratexid15, 1
};


static NJS_TEXLIST SADXShadowSuperAuraTexList[8] = {
	&SADXAuratexid0, 1,
	&SADXAuratexid1, 1,
	&SADXAuratexid2, 1,
	&SADXAuratexid3, 1,
	&SADXAuratexid4, 1,
	&SADXAuratexid5, 1,
	&SADXAuratexid6, 1,
	&SADXAuratexid7, 1
};

static NJS_TEXLIST SADXShadowSuperAuraTexList2[8] = {
	&SADXAuratexid8, 1,
	&SADXAuratexid9, 1,
	&SADXAuratexid10, 1,
	&SADXAuratexid11, 1,
	&SADXAuratexid12, 1,
	&SADXAuratexid13, 1,
	&SADXAuratexid14, 1,
	&SADXAuratexid15, 1
};


static NJS_TEXLIST SADXAmySuperAuraTexList[8] = {
	&SADXAuratexid0, 1,
	&SADXAuratexid1, 1,
	&SADXAuratexid2, 1,
	&SADXAuratexid3, 1,
	&SADXAuratexid4, 1,
	&SADXAuratexid5, 1,
	&SADXAuratexid6, 1,
	&SADXAuratexid7, 1
};

static NJS_TEXLIST SADXAmySuperAuraTexList2[8] = {
	&SADXAuratexid8, 1,
	&SADXAuratexid9, 1,
	&SADXAuratexid10, 1,
	&SADXAuratexid11, 1,
	&SADXAuratexid12, 1,
	&SADXAuratexid13, 1,
	&SADXAuratexid14, 1,
	&SADXAuratexid15, 1
};


static NJS_TEXLIST SADXMetalSuperAuraTexList[8] = {
	&SADXTikalAuratexid0, 1,
	&SADXTikalAuratexid1, 1,
	&SADXTikalAuratexid2, 1,
	&SADXTikalAuratexid3, 1,
	&SADXTikalAuratexid4, 1,
	&SADXTikalAuratexid5, 1,
	&SADXTikalAuratexid6, 1,
	&SADXTikalAuratexid7, 1
};

static NJS_TEXLIST SADXMetalSuperAuraTexList2[8] = {
	&SADXTikalAuratexid8, 1,
	&SADXTikalAuratexid9, 1,
	&SADXTikalAuratexid10, 1,
	&SADXTikalAuratexid11, 1,
	&SADXTikalAuratexid12, 1,
	&SADXTikalAuratexid13, 1,
	&SADXTikalAuratexid14, 1,
	&SADXTikalAuratexid15, 1
};


static NJS_TEXLIST SADXTailsSuperAuraTexList[8] = {
	&SADXAuratexid0, 1,
	&SADXAuratexid1, 1,
	&SADXAuratexid2, 1,
	&SADXAuratexid3, 1,
	&SADXAuratexid4, 1,
	&SADXAuratexid5, 1,
	&SADXAuratexid6, 1,
	&SADXAuratexid7, 1
};

static NJS_TEXLIST SADXTailsSuperAuraTexList2[8] = {
	&SADXAuratexid8, 1,
	&SADXAuratexid9, 1,
	&SADXAuratexid10, 1,
	&SADXAuratexid11, 1,
	&SADXAuratexid12, 1,
	&SADXAuratexid13, 1,
	&SADXAuratexid14, 1,
	&SADXAuratexid15, 1
};


static NJS_TEXLIST SADXEggmanSuperAuraTexList[8] = {
	&SADXAuratexid0, 1,
	&SADXAuratexid1, 1,
	&SADXAuratexid2, 1,
	&SADXAuratexid3, 1,
	&SADXAuratexid4, 1,
	&SADXAuratexid5, 1,
	&SADXAuratexid6, 1,
	&SADXAuratexid7, 1
};

static NJS_TEXLIST SADXEggmanSuperAuraTexList2[8] = {
	&SADXAuratexid8, 1,
	&SADXAuratexid9, 1,
	&SADXAuratexid10, 1,
	&SADXAuratexid11, 1,
	&SADXAuratexid12, 1,
	&SADXAuratexid13, 1,
	&SADXAuratexid14, 1,
	&SADXAuratexid15, 1
};


static NJS_TEXLIST SADXKnucklesSuperAuraTexList[8] = {
	&SADXTikalAuratexid0, 1,
	&SADXTikalAuratexid1, 1,
	&SADXTikalAuratexid2, 1,
	&SADXTikalAuratexid3, 1,
	&SADXTikalAuratexid4, 1,
	&SADXTikalAuratexid5, 1,
	&SADXTikalAuratexid6, 1,
	&SADXTikalAuratexid7, 1
};

static NJS_TEXLIST SADXKnucklesSuperAuraTexList2[8] = {
	&SADXTikalAuratexid8, 1,
	&SADXTikalAuratexid9, 1,
	&SADXTikalAuratexid10, 1,
	&SADXTikalAuratexid11, 1,
	&SADXTikalAuratexid12, 1,
	&SADXTikalAuratexid13, 1,
	&SADXTikalAuratexid14, 1,
	&SADXTikalAuratexid15, 1
};


static NJS_TEXLIST SADXTikalSuperAuraTexList[8] = {
	&SADXTikalAuratexid0, 1,
	&SADXTikalAuratexid1, 1,
	&SADXTikalAuratexid2, 1,
	&SADXTikalAuratexid3, 1,
	&SADXTikalAuratexid4, 1,
	&SADXTikalAuratexid5, 1,
	&SADXTikalAuratexid6, 1,
	&SADXTikalAuratexid7, 1
};

static NJS_TEXLIST SADXTikalSuperAuraTexList2[8] = {
	&SADXTikalAuratexid8, 1,
	&SADXTikalAuratexid9, 1,
	&SADXTikalAuratexid10, 1,
	&SADXTikalAuratexid11, 1,
	&SADXTikalAuratexid12, 1,
	&SADXTikalAuratexid13, 1,
	&SADXTikalAuratexid14, 1,
	&SADXTikalAuratexid15, 1
};


static NJS_TEXLIST SADXRougeSuperAuraTexList[8] = {
	&SADXAuratexid0, 1,
	&SADXAuratexid1, 1,
	&SADXAuratexid2, 1,
	&SADXAuratexid3, 1,
	&SADXAuratexid4, 1,
	&SADXAuratexid5, 1,
	&SADXAuratexid6, 1,
	&SADXAuratexid7, 1
};

static NJS_TEXLIST SADXRougeSuperAuraTexList2[8] = {
	&SADXAuratexid8, 1,
	&SADXAuratexid9, 1,
	&SADXAuratexid10, 1,
	&SADXAuratexid11, 1,
	&SADXAuratexid12, 1,
	&SADXAuratexid13, 1,
	&SADXAuratexid14, 1,
	&SADXAuratexid15, 1
};


static NJS_TEXLIST SADXChaosSuperAuraTexList[8] = {
	&SADXAuratexid0, 1,
	&SADXAuratexid1, 1,
	&SADXAuratexid2, 1,
	&SADXAuratexid3, 1,
	&SADXAuratexid4, 1,
	&SADXAuratexid5, 1,
	&SADXAuratexid6, 1,
	&SADXAuratexid7, 1
};

static NJS_TEXLIST SADXChaosSuperAuraTexList2[8] = {
	&SADXAuratexid8, 1,
	&SADXAuratexid9, 1,
	&SADXAuratexid10, 1,
	&SADXAuratexid11, 1,
	&SADXAuratexid12, 1,
	&SADXAuratexid13, 1,
	&SADXAuratexid14, 1,
	&SADXAuratexid15, 1
};

static NJS_TEXLIST SADXChaoWalkerSuperAuraTexList[8] = {
	&SADXAuratexid0, 1,
	&SADXAuratexid1, 1,
	&SADXAuratexid2, 1,
	&SADXAuratexid3, 1,
	&SADXAuratexid4, 1,
	&SADXAuratexid5, 1,
	&SADXAuratexid6, 1,
	&SADXAuratexid7, 1
};

static NJS_TEXLIST SADXChaoWalkerSuperAuraTexList2[8] = {
	&SADXAuratexid8, 1,
	&SADXAuratexid9, 1,
	&SADXAuratexid10, 1,
	&SADXAuratexid11, 1,
	&SADXAuratexid12, 1,
	&SADXAuratexid13, 1,
	&SADXAuratexid14, 1,
	&SADXAuratexid15, 1
};

static NJS_TEXLIST SADXDarkChaoWalkerSuperAuraTexList[8] = {
	&SADXAuratexid0, 1,
	&SADXAuratexid1, 1,
	&SADXAuratexid2, 1,
	&SADXAuratexid3, 1,
	&SADXAuratexid4, 1,
	&SADXAuratexid5, 1,
	&SADXAuratexid6, 1,
	&SADXAuratexid7, 1
};

static NJS_TEXLIST SADXDarkChaoWalkerSuperAuraTexList2[8] = {
	&SADXAuratexid8, 1,
	&SADXAuratexid9, 1,
	&SADXAuratexid10, 1,
	&SADXAuratexid11, 1,
	&SADXAuratexid12, 1,
	&SADXAuratexid13, 1,
	&SADXAuratexid14, 1,
	&SADXAuratexid15, 1
};

int timerSuperAura[2] = { 0, 0 };

void SADX_SuperAura(ObjectMaster* obj) {

	SonicCharObj2* Sco2 = (SonicCharObj2*)obj->Data2.Undefined;
	CharObj2Base* co2 = &Sco2->base;
	EntityData1* data = obj->Data1.Entity;

	if (!co2)
		return;

	EntityData1* playerData = MainCharObj1[co2->PlayerNum];
	char pnum = co2->PlayerNum;

	bool isShadow = co2->CharID2 == Characters_Shadow;

	if (co2->AnimInfo.Current == 54 || co2->AnimInfo.Next == 54 || !isSuper[pnum])
	{
		obj->DisplaySub_Delayed4 = nullptr;
		return;
	}

	if (superAuraState == 1)
	{
		if (co2->Speed.x >= -5.0 && co2->Speed.x < 5.0f && co2->Speed.y >= -6.0f && co2->Speed.y < 6.0)
			return;
	}

	if (GameState != GameStates_Pause) {
		timerSuperAura[pnum]++;
	}

//	njSetTexture(isShadow ? &SADXShadowSuperAuraTexList[timerSuperAura[pnum] & 7] : &SADXSuperAuraTexList[timerSuperAura[pnum] & 7]);
	if (co2->CharID2 == Characters_Sonic)
	{
		njSetTexture(&SADXSuperAuraTexList[timerSuperAura[pnum] & 7]);
	}
	else if (co2->CharID2 == Characters_Amy)
	{
		njSetTexture(&SADXAmySuperAuraTexList[timerSuperAura[pnum] & 7]);
	}
	else if (co2->CharID2 == Characters_MetalSonic)
	{
		njSetTexture(&SADXMetalSuperAuraTexList[timerSuperAura[pnum] & 7]);
	}
	else if (co2->CharID2 == Characters_Tails || co2->CharID2 == Characters_MechTails)
	{
		njSetTexture(&SADXTailsSuperAuraTexList[timerSuperAura[pnum] & 7]);
	}
	else if (co2->CharID2 == Characters_Eggman || co2->CharID2 == Characters_MechEggman)
	{
		njSetTexture(&SADXEggmanSuperAuraTexList[timerSuperAura[pnum] & 7]);
	}
	else if (co2->CharID2 == Characters_Knuckles)
	{
		njSetTexture(&SADXKnucklesSuperAuraTexList[timerSuperAura[pnum] & 7]);
	}
	else if (co2->CharID2 == Characters_Tikal)
	{
		njSetTexture(&SADXTikalSuperAuraTexList[timerSuperAura[pnum] & 7]);
	}
	else if (co2->CharID2 == Characters_Rouge)
	{
		njSetTexture(&SADXRougeSuperAuraTexList[timerSuperAura[pnum] & 7]);
	}
	else if (co2->CharID2 == Characters_Chaos)
	{
		njSetTexture(&SADXChaosSuperAuraTexList[timerSuperAura[pnum] & 7]);
	}
	else if (co2->CharID2 == Characters_ChaoWalker)
	{
		njSetTexture(&SADXChaoWalkerSuperAuraTexList[timerSuperAura[pnum] & 7]);
	}
	else if (co2->CharID2 == Characters_DarkChaoWalker)
	{
		njSetTexture(&SADXDarkChaoWalkerSuperAuraTexList[timerSuperAura[pnum] & 7]);
	}
	else
	{
		njSetTexture(&SADXShadowSuperAuraTexList[timerSuperAura[pnum] & 7]);
	}

	SaveControl3D();
	OnControl3D(NJD_CONTROL_3D_CONSTANT_MATERIAL);
	SetMaterial(1.0, 1.0, 1.0, 1.0);
	njPushMatrix(CURRENT_MATRIX);
	njTranslateV(0, &playerData->Collision->CollisionArray->center);

	njRotateZ_r((unsigned __int16)playerData->Rotation.z);
	njRotateX_r((unsigned __int16)playerData->Rotation.x);
	njRotateY_r((unsigned __int16)-(playerData->Rotation.y));

	njScale(0, -1.0, 1.0, 1.0);

	if (!isBoosting(co2->PlayerNum))
	{
		if (co2->Speed.x <= 7.0)
		{
			DrawObject(SADXSuperAuraModel[0]->getmodel());
		}
		else
		{
//			njSetTexture(isShadow ? &SADXShadowSuperAuraTexList[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7] : &SADXSuperAuraTexList[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
			if (co2->CharID2 == Characters_Sonic)
			{
				njSetTexture(&SADXSuperAuraTexList[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
			}
			else if (co2->CharID2 == Characters_Amy)
			{
				njSetTexture(&SADXAmySuperAuraTexList[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
			}
			else if (co2->CharID2 == Characters_MetalSonic)
			{
				njSetTexture(&SADXMetalSuperAuraTexList[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
			}
			else if (co2->CharID2 == Characters_Tails || co2->CharID2 == Characters_MechTails)
			{
				njSetTexture(&SADXTailsSuperAuraTexList[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
			}
			else if (co2->CharID2 == Characters_Eggman || co2->CharID2 == Characters_MechEggman)
			{
				njSetTexture(&SADXEggmanSuperAuraTexList[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
			}
			else if (co2->CharID2 == Characters_Knuckles)
			{
				njSetTexture(&SADXKnucklesSuperAuraTexList[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
			}
			else if (co2->CharID2 == Characters_Tikal)
			{
				njSetTexture(&SADXTikalSuperAuraTexList[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
			}
			else if (co2->CharID2 == Characters_Rouge)
			{
				njSetTexture(&SADXRougeSuperAuraTexList[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
			}
			else if (co2->CharID2 == Characters_Chaos)
			{
				njSetTexture(&SADXChaosSuperAuraTexList[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
			}
			else if (co2->CharID2 == Characters_ChaoWalker)
			{
				njSetTexture(&SADXChaoWalkerSuperAuraTexList[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
			}
			else if (co2->CharID2 == Characters_DarkChaoWalker)
			{
				njSetTexture(&SADXDarkChaoWalkerSuperAuraTexList[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
			}
			else
			{
				njSetTexture(&SADXShadowSuperAuraTexList[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
			}
			DrawObject(SADXSuperAuraModel[1]->getmodel());
		}
	}
	else
	{
//		njSetTexture(isShadow ? &SADXShadowSuperAuraTexList2[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7] : &SADXSuperAuraTexList2[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
		if (co2->CharID2 == Characters_Sonic)
		{
			njSetTexture(&SADXSuperAuraTexList2[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
		}
		else if (co2->CharID2 == Characters_Amy)
		{
			njSetTexture(&SADXAmySuperAuraTexList2[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
		}
		else if (co2->CharID2 == Characters_MetalSonic)
		{
			njSetTexture(&SADXMetalSuperAuraTexList2[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
		}
		else if (co2->CharID2 == Characters_Tails || co2->CharID2 == Characters_MechTails)
		{
			njSetTexture(&SADXTailsSuperAuraTexList2[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
		}
		else if (co2->CharID2 == Characters_Eggman || co2->CharID2 == Characters_MechEggman)
		{
			njSetTexture(&SADXEggmanSuperAuraTexList2[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
		}
		else if (co2->CharID2 == Characters_Knuckles)
		{
			njSetTexture(&SADXKnucklesSuperAuraTexList2[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
		}
		else if (co2->CharID2 == Characters_Tikal)
		{
			njSetTexture(&SADXTikalSuperAuraTexList2[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
		}
		else if (co2->CharID2 == Characters_Rouge)
		{
			njSetTexture(&SADXRougeSuperAuraTexList2[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
		}
		else if (co2->CharID2 == Characters_Chaos)
		{
			njSetTexture(&SADXChaosSuperAuraTexList2[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
		}
		else if (co2->CharID2 == Characters_ChaoWalker)
		{
			njSetTexture(&SADXChaoWalkerSuperAuraTexList2[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
		}
		else if (co2->CharID2 == Characters_DarkChaoWalker)
		{
			njSetTexture(&SADXDarkChaoWalkerSuperAuraTexList2[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
		}
		else
		{
			njSetTexture(&SADXShadowSuperAuraTexList2[((unsigned __int8)timerSuperAura[pnum] >> 1) & 7]);
		}
		DrawObject(SADXSuperAuraModel[2]->getmodel());
	}

	njPopMatrix(1u);
	ResetMaterial();
	LoadControl3D();
}


void LoadSuperAura(char pID)
{
	if (!superAuraState)
		return;
	if (MainCharacter[pID]->Data2.Character->CharID2 != Characters_MechTails && MainCharacter[pID]->Data2.Character->CharID2 != Characters_MechEggman && MainCharacter[pID]->Data2.Character->CharID2 != Characters_ChaoWalker && MainCharacter[pID]->Data2.Character->CharID2 != Characters_DarkChaoWalker)
	{
		MainCharacter[pID]->DisplaySub_Delayed4 = SADXAura ? SADX_SuperAura : SuperAura_r;
	}
	else
	{
		MainCharacter[pID]->DisplaySub_Delayed3 = SADXAura ? SADX_SuperAura : SuperAura_r;
	}
	return;
}

void LoadSADXAuraTextures(char pnum) {

	if (!SADXAura)
	{
		return;
	}

	timerSuperAura[pnum] = 0;

	CharObj2Base* co2 = MainCharObj2[pnum];

	if (co2) {
		if (co2->CharID2 == Characters_Sonic)
		{
			for (uint8_t i = 0; i < LengthOfArray(SADXSuperAuraTexList); i++)
			{

				SADXSuperAuraTexList[i].textures[0] = SSEff_Texlist.textures[i + 17];
				SADXSuperAuraTexList2[i].textures[0] = SSEff_Texlist.textures[i + 25];
			}
		}
		else if (co2->CharID2 == Characters_Amy)
		{
			for (uint8_t i = 0; i < LengthOfArray(SADXAmySuperAuraTexList); i++) {

				SADXAmySuperAuraTexList[i].textures[0] = SSAura_Texlist.textures[i];
				SADXAmySuperAuraTexList2[i].textures[0] = SSAura_Texlist.textures[i + 8];
			}
		}
		else if (co2->CharID2 == Characters_MetalSonic)
		{
			for (uint8_t i = 0; i < LengthOfArray(SADXMetalSuperAuraTexList); i++) {

				SADXMetalSuperAuraTexList[i].textures[0] = SMAura_Texlist.textures[i];
				SADXMetalSuperAuraTexList2[i].textures[0] = SMAura_Texlist.textures[i + 8];
			}
		}
		else if (co2->CharID2 == Characters_Tails || co2->CharID2 == Characters_MechTails)
		{
			for (uint8_t i = 0; i < LengthOfArray(SADXTailsSuperAuraTexList); i++) {

				SADXTailsSuperAuraTexList[i].textures[0] = STAura_Texlist.textures[i];
				SADXTailsSuperAuraTexList2[i].textures[0] = STAura_Texlist.textures[i + 8];
			}
		}
		else if (co2->CharID2 == Characters_Eggman || co2->CharID2 == Characters_MechEggman)
		{
			for (uint8_t i = 0; i < LengthOfArray(SADXEggmanSuperAuraTexList); i++) {

				SADXEggmanSuperAuraTexList[i].textures[0] = SEAura_Texlist.textures[i];
				SADXEggmanSuperAuraTexList2[i].textures[0] = SEAura_Texlist.textures[i + 8];
			}
		}
		else if (co2->CharID2 == Characters_Knuckles)
		{
			for (uint8_t i = 0; i < LengthOfArray(SADXKnucklesSuperAuraTexList); i++) {

				SADXKnucklesSuperAuraTexList[i].textures[0] = SKAura_Texlist.textures[i];
				SADXKnucklesSuperAuraTexList2[i].textures[0] = SKAura_Texlist.textures[i + 8];
			}
		}
		else if (co2->CharID2 == Characters_Rouge) {

			for (uint8_t i = 0; i < LengthOfArray(SADXRougeSuperAuraTexList); i++) {

				SADXRougeSuperAuraTexList[i].textures[0] = SRAura_Texlist.textures[i];
				SADXRougeSuperAuraTexList2[i].textures[0] = SRAura_Texlist.textures[i + 8];
			}
		}
		else if (co2->CharID2 == Characters_Tikal) {

			for (uint8_t i = 0; i < LengthOfArray(SADXTikalSuperAuraTexList); i++) {

				SADXTikalSuperAuraTexList[i].textures[0] = STKAura_Texlist.textures[i];
				SADXTikalSuperAuraTexList2[i].textures[0] = STKAura_Texlist.textures[i + 8];
			}
		}
		else if (co2->CharID2 == Characters_Chaos) {

			for (uint8_t i = 0; i < LengthOfArray(SADXChaosSuperAuraTexList); i++) {

				SADXChaosSuperAuraTexList[i].textures[0] = SCHAura_Texlist.textures[i];
				SADXChaosSuperAuraTexList2[i].textures[0] = SCHAura_Texlist.textures[i + 8];
			}
		}
		else if (co2->CharID2 == Characters_ChaoWalker) {

			for (uint8_t i = 0; i < LengthOfArray(SADXChaoWalkerSuperAuraTexList); i++) {

				SADXChaoWalkerSuperAuraTexList[i].textures[0] = SCWAura_Texlist.textures[i];
				SADXChaoWalkerSuperAuraTexList2[i].textures[0] = SCWAura_Texlist.textures[i + 8];
			}
		}
		else if (co2->CharID2 == Characters_DarkChaoWalker) {

			for (uint8_t i = 0; i < LengthOfArray(SADXDarkChaoWalkerSuperAuraTexList); i++) {

				SADXDarkChaoWalkerSuperAuraTexList[i].textures[0] = SDCWAura_Texlist.textures[i];
				SADXDarkChaoWalkerSuperAuraTexList2[i].textures[0] = SDCWAura_Texlist.textures[i + 8];
			}
		}
		else
		{
			for (uint8_t i = 0; i < LengthOfArray(SADXSuperAuraTexList); i++) {

				SADXShadowSuperAuraTexList[i].textures[0] = SSHEff_Texlist.textures[i + 17];
				SADXShadowSuperAuraTexList2[i].textures[0] = SSHEff_Texlist.textures[i + 25];
			}
		}
	}
}

void Free_AuraModels()
{
	for (uint8_t i = 0; i < LengthOfArray(SADXSuperAuraModel); i++)
	{
		FreeMDL(SADXSuperAuraModel[i]);
	}
}

//Serie of hack to make every aura display a yellow texture when Super Sonic. (Using Shadow texlist)
void init_AuraHack() {

	//regular sonic aura
	DoSpinDashAura_t.Hook(DoSpinDashAura_r);
	DoJumpAura_t.Hook(DoJumpAura_r);
	DoHomingAura_t.Hook(DoHomingAura_r);
	HomingDashAura_Display_t.Hook(HomingDashAura_Display_r);

	if (SADXAura)
	{
		SADXSuperAuraModel[0] = LoadMDL("SADXAura0", ModelFormat_Chunk);
		SADXSuperAuraModel[1] = LoadMDL("SADXAura1", ModelFormat_Chunk);
		SADXSuperAuraModel[2] = LoadMDL("SADXAura2", ModelFormat_Chunk);
	}

	return;
}