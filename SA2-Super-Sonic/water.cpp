#include "pch.h"
#include "UsercallFunctionHandler.h"

//Allow to hover on water with the SA1 effect!

Trampoline* SplashEffect_t = nullptr;

static ModelInfo* WaterMdl[2] = { nullptr, nullptr }; //water effect model
static ModelInfo* gridCol = nullptr; //used to make Sonic able to float on water

static NJS_TEXNAME watertexid0 = { (char*)"ss_waterl01", 0, 0 };
static NJS_TEXNAME watertexid1 = { (char*)"ss_waterl03", 0, 0 };
static NJS_TEXNAME watertexid2 = { (char*)"ss_waterl05", 0, 0 };
static NJS_TEXNAME watertexid3 = { (char*)"ss_waterl07", 0, 0 };
static NJS_TEXNAME watertexid4 = { (char*)"ss_waterl09", 0, 0 };
static NJS_TEXNAME watertexid5 = { (char*)"ss_waterl11", 0, 0 };
static NJS_TEXNAME watertexid6 = { (char*)"ss_waterl13", 0, 0 };
static NJS_TEXNAME watertexid7 = { (char*)"ss_waterl15", 0, 0 };

extern NJS_TEXLIST SSEff_Texlist;
extern NJS_TEXLIST SSHEff_Texlist;

static NJS_TEXLIST waterTexList[8] = {
	&watertexid0, 2,
	&watertexid1, 2,
	&watertexid2, 2,
	&watertexid3, 2,
	&watertexid4, 2,
	&watertexid5, 2,
	&watertexid6, 2,
	&watertexid7, 2
};

//some levels don't have a water collision, it's just a part of the background and don't act like water
bool isFakeWaterLevel()
{
	return CurrentLevel == LevelIDs_GreenForest || CurrentLevel == LevelIDs_MetalHarbor || CurrentLevel == LevelIDs_GreenHill;
}

DataPointer(float, MH_WaterPosY, 0xEF68B8);

//we check if character is on water with hardcoded position instead
float getWaterposY(char pnum)
{
	if (!MainCharObj1[pnum])
		return 0.0f;

	switch (CurrentLevel)
	{
	case LevelIDs_MetalHarbor:
	case LevelIDs_MetalHarbor2P:
		return MH_WaterPosY + 5.0f;
	case LevelIDs_GreenForest:
		return -1356.91f;
	case LevelIDs_GreenHill:
		break;
	}

	return MainCharObj1[pnum]->Position.y;
}

void UpdateWaterColPos(ObjectMaster* obj, EntityData1* player)
{
	NJS_OBJECT* dyncol = (NJS_OBJECT*)obj->EntityData2;
	EntityData1* data = obj->Data1.Entity;

	data->Position = { player->Position.x, getWaterposY(data->Index), player->Position.z };
	*(NJS_VECTOR*)dyncol->pos = data->Position; //update dyncol pos
}

bool isPlayerOnWater(CharObj2Base* co2, EntityData1* player)
{
	if (!co2)
		return false;

	if (co2->SurfaceInfo.TopSurface & (SurfaceFlag_Water | SurfaceFlag_WaterNoAlpha) || isFakeWaterLevel() && player->Position.y <= getWaterposY(co2->PlayerNum) + 5.0f)
		return true;

	return false;
}


NJS_OBJECT* DynCol_AddFromObject(ObjectMaster* obj, NJS_OBJECT* object, NJS_VECTOR* position, Angle rotY, int flags)
{
	NJS_OBJECT* dynobj = GetFreeDyncolObjectEntry();

	if (dynobj)
	{
		memcpy(dynobj, object, sizeof(NJS_OBJECT));

		dynobj->evalflags &= 0xFFFFFFFC;

		dynobj->ang[1] = rotY;
		dynobj->pos[0] = position->x;
		dynobj->pos[1] = position->y;
		dynobj->pos[2] = position->z;

		DynCol_Add((SurfaceFlags)flags, obj, dynobj);
		obj->EntityData2 = (UnknownData2*)dynobj;
	}

	return dynobj;
}

void __cdecl SS_Water_Display(ObjectMaster* obj)
{
	float XScale;
	float XScalea;
	float YScale;
	float ZScale;

	EntityData1* data = obj->Data1.Entity;

	char pnum = data->Index;
	EntityData1* playerData = MainCharObj1[pnum];
	CharObj2Base* co2 = MainCharObj2[pnum];

	if ((data->Action >= 2))
	{
		njSetTexture(&waterTexList[((unsigned __int8)data->Timer >> 1) & 6]);

		njPushMatrix(CURRENT_MATRIX);
		njTranslateV(0, &playerData->Position);

		njRotateZ_(CURRENT_MATRIX, (unsigned __int16)playerData->Rotation.z);
		njRotateX_(CURRENT_MATRIX, (unsigned __int16)playerData->Rotation.x);
		njRotateY_(CURRENT_MATRIX, (unsigned __int16)-(playerData->Rotation.y));

		if (data->Scale.x != 0.0)   // draw water effect
		{
			njPushMatrix(0);
			XScale = data->Scale.x * -1.0;
			njScale(0, XScale, data->Scale.x, data->Scale.x);
			DrawObject(WaterMdl[0]->getmodel());
			DrawObject(WaterMdl[1]->getmodel());
			njPopMatrix(1u);
		}
		if (data->Scale.y != 0.0)
		{
			njPushMatrix(CURRENT_MATRIX);
			ZScale = data->Scale.y * 1.3;
			YScale = data->Scale.y * 0.80000001;
			XScalea = data->Scale.y * -0.80000001;
			njScale(0, XScalea, YScale, ZScale);
			DrawObject(WaterMdl[0]->getmodel());
			DrawObject(WaterMdl[1]->getmodel());
			njPopMatrix(1u);
		}

		njPopMatrix(1u);
	}
}

//we create a dynamic collision when the player is on water, so he can hover on it 
void __cdecl SS_Water_Main(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1.Entity;

	char pnum = data->Index;

	if (!MainCharObj1[pnum])
		return;

	EntityData1* player = MainCharObj1[pnum];
	float spd;

	CharObj2Base* co2 = MainCharObj2[pnum];

	if (co2 && (co2->Upgrades & Upgrades_SuperSonic) == 0)
	{
		DeleteObject_(obj);
		return;
	}

	switch (data->Action)
	{
	case 0:

		obj->DisplaySub_Delayed1 = SS_Water_Display;
		obj->field_4C = gridCol->getmodel();
		obj->DeleteSub = DeleteFunc_DynCol;
		DynCol_AddFromObject(obj, (NJS_OBJECT*)obj->field_4C, &data->Position, data->Rotation.y, SurfaceFlag_Solid | SurfaceFlag_Dynamic);
		data->Action++;
		break;
	case 1:

		if (isPlayerOnWater(co2, MainCharObj1[pnum])) {
			player->Position.y += 1.0f;
			data->Action++;
		}

		break;
	case 2:
	{
		UpdateWaterColPos(obj, player);

		spd = fabs(co2->Speed.x);
		data->Scale.x = sqrt(spd) * 0.40000001;

		if (data->Timer >= SHRT_MAX)
			data->Timer = 0;

		data->Timer++;

		if (!isPlayerOnWater(MainCharObj2[pnum], MainCharObj1[pnum]) || player->Action == Action_Jump) {
			data->Position = { 0, -10000, 0 };
			data->Action = 1;
			data->Timer = 0;
			return;
		}
	}

	break;
	}
}

void Load_SSWaterTask(char pid)
{
	ObjectMaster* water = LoadObject(2, "SS_Water_Eff", SS_Water_Main, LoadObj_Data1 | LoadObj_Data2);
	water->Data1.Entity->Index = pid;
	return;
}

void LoadWaterTextures(char charID) {

	if (isFakeWaterLevel())
	{
		LoadSplashEffect(charID);
	}

	char count = 0;

	if (charID == Characters_Sonic) {

		for (uint8_t i = 0; i < LengthOfArray(waterTexList); i++) {

			waterTexList[i].textures[0] = SSEff_Texlist.textures[1 + count];
			count += 2;
		}
	}
	else
	{
		for (uint8_t i = 0; i < LengthOfArray(waterTexList); i++) {

			waterTexList[i].textures[0] = SSHEff_Texlist.textures[1 + count];
			count += 2;
		}
	}
}

void LoadWaterMDL()
{
	WaterMdl[0] = LoadMDL("WaterMDL0", ModelFormat_Chunk);
	WaterMdl[1] = LoadMDL("WaterMDL1", ModelFormat_Chunk);
	gridCol = LoadMDL("gridCol", ModelFormat_Basic);
	return;
}

void FreeWaterMDL()
{
	for (uint8_t i = 0; i < LengthOfArray(WaterMdl); i++)
	{
		FreeMDL(WaterMdl[i]);
	}

	FreeMDL(gridCol);
}

using ExecFuncPtr = void(__cdecl*)(NJS_VECTOR*, Rotation*, float, float);
DataPointer(ExecFuncPtr, ExecFunc_ptr_, 0x1A5A2B0);

void DoBigSplashEffect(NJS_VECTOR* a1, int a2)
{
	void(__cdecl * v2)(NJS_VECTOR*, Rotation*, float, float);
	CharObj2Base* co2;
	BOOL spd;
	double v6;
	float v7;
	float v8;

	if (!ExecFunc_ptr)
		return;

	v2 = ExecFunc_ptr_;

	co2 = MainCharObj2[a2];
	v6 = 1.0;
	spd = njScalor(&co2->Speed) > 1.0;

	v7 = 1.0f;
	v8 = 1.27f;
	v2(a1, 0, v7, v8);
	Play3DSound_Pos(28673, a1, 0, 0, 0);
}


FunctionPointer(void, sub_6ED400, (NJS_VECTOR* a1, NJS_VECTOR* a2, float a3, float a4, int a5), 0x6ED400);
DataPointer(float, flt_1666F30, 0x1666F30);

void __cdecl SplashEffect_r(ObjectMaster* a1)
{
	EntityData1* data = a1->Data1.Entity;
	long double veloY;
	char pNum = (unsigned __int8)data->Index;
	EntityData1* playerData = MainCharObj1[pNum];
	CharObj2Base* co2 = MainCharObj2[pNum];
	EntityData2* playerData2 = MainCharData2[pNum];

	if (co2->Upgrades & Upgrades_SuperSonic && isPlayerOnWater(co2, playerData))
	{
		if (data->Timer > 12u && co2->Speed.x > 3.0f)
		{
			NJS_VECTOR Velo = playerData2->Velocity;
			NJS_VECTOR playerPos = playerData->Position;
			
			if (!isFakeWaterLevel())
				playerPos.y = co2->SurfaceInfo.TopSurfaceDist;
			else
				playerPos.y -= 2.0f;

			Velo.x *= 0.300000011920929;
			Velo.y = data->Scale.y * 0.1500000059604645;
			Velo.z *= 0.300000011920929;
			float result = 0.300000011920929 * data->Scale.y + 1.399999976158142;
			if (Velo.y > 0.25)
			{
				Velo.y = 0.25;
			}

			sub_6ED400(&playerPos, &Velo, result, flt_1666F30, 12);
			data->Timer = 0;
			Play3DSound_Pos(28672, &playerData->Position, 0, 0, 0);
		}


		if (TimeTotal % 60 * 2 == 0) {

			NJS_VECTOR pos = playerData->Position;

			if (!isFakeWaterLevel())
				pos.y = co2->SurfaceInfo.TopSurfaceDist;
			else
				pos.y -= 2.0f;

			if (WaterRippleFunc_ptr)
			{
				sub_476CC0(pNum, &pos);
			}

			DoBigSplashEffect(&pos, pNum);
		}

		data->Status = playerData->Status;
		veloY = MainCharData2[pNum]->Velocity.y;
		++data->Timer;
		data->Scale.y = fabs(veloY);
		data->Scale.x = co2->AnimInfo.field_10;
		return;
	}

	ObjectFunc(origin, SplashEffect_t->Target());
	origin(a1);
}

void init_WaterHack()
{
	SplashEffect_t = new Trampoline((int)0x6ED6E0, (int)0x6ED6E6, SplashEffect_r);
	WriteData<5>((int*)0x495218, 0x90);
}