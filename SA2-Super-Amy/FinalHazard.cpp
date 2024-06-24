#include "pch.h"

static FunctionHook<void>FinalHazard_Init_t(FinalHazard_Init);

void __cdecl FinalHazard_Hack()
{
	FinalHazard_Init_t.Original();

	if (MainCharacter[0])
	{
		DeleteObject_(MainCharacter[0]);
	}
	switch (FHChar)
	{
	case VSuperSonic:
		return FinalHazard_Init_t.Original();
		break;
	case Sonic:
		AltCharacter[0] = 0;
		AltCostume[0] = 0;
		LoadSonic(0);
		break;
	case Amy:
		AltCostume[0] = 0;
		LoadAmy(0);
		break;
	case Tails:
		AltCostume[0] = 0;
		LoadTails(0);
		break;
	case Knuckles:
		AltCharacter[0] = 0;
		AltCostume[0] = 0;
		LoadKnuckles(0);
		break;
	case MechTails:
		AltCharacter[0] = 0;
		AltCostume[0] = 0;
		LoadMechTails(0);
		break;
	case Tikal:
		AltCostume[0] = 0;
		LoadTikal(0);
		break;
	case ChaoWalker:
		AltCostume[0] = 0;
		LoadChaoWalker(0);
		break;
	case AltSonic:
		AltCostume[0] = 1;
		LoadSonic(0);
		break;
	case AltAmy:
		AltCostume[0] = 1;
		LoadAmy(0);
		break;
	case AltTails:
		AltCostume[0] = 1;
		LoadTails(0);
		break;
	case AltKnuckles:
		AltCostume[0] = 1;
		LoadKnuckles(0);
		break;
	case AltMechTails:
		AltCostume[0] = 1;
		LoadMechTails(0);
		break;
	case AltTikal:
		AltCostume[0] = 1;
		LoadTikal(0);
		break;
	case AltChaoWalker:
		AltCostume[0] = 1;
		LoadChaoWalker(0);
		break;
	default:
		return FinalHazard_Init_t.Original();
		break;
	}
	InitPlayer(0);

	if (MainCharacter[1])
	{
		DeleteObject_(MainCharacter[1]);
	}
	LoadSuperShadow();
	InitPlayer(1);
}

void init_FinalHazardHack()
{
	FinalHazard_Init_t.Hook(FinalHazard_Hack);
	if (FHZAuraHack)
	{
		WriteData<6>((int*)0x49cf7f, 0x90); //Display super Aura infinitely
	}
	return;

	//Better Miles FinalHazard hacks
//	WriteData<40>((int*)0x498a9d, 0x90); //Remove the game calling super shadow and stuff since we will manually do it.
//	WriteCall((void*)0x498a98, LoadSuperFormFinalBattle); //hook "LoadSuperSonic"
//	WriteData<6>((int*)0x49cf7f, 0x90); //Display super Aura infinitely
//	WriteData<7>((int*)0x49cfc3, 0x90); //Remove super aura math thing for Tails.
}