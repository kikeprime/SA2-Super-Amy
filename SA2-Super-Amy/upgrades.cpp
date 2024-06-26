#include "pch.h"

enum SonicModel {
	SRoot = 0,
	SRoot2,
	SRoot3,
	SHead,
	SHead2 = 8,
	SRightFootToe,
	SLeftFootToe,
	SRightFootHeel,
	SLeftFootHeel,
	SRightHandParent = 15,
	SLeftHandParent,
	SRightArm,
	SLeftArm,
	SRightHandParent2 = 23,
	SLeftHandParent2,
};

enum SuperSonicModel {
	SSRoot = 328,
	SSRoot2,
	SSRoot3,
	SSHead,
	SSHead2 = 336,
	SSRightFootToe,
	SSLeftFootToe,
	SSRightFootHeel,
	SSLeftFootHeel,
	SSRightHandParent = 343,
	SSLeftHandParent,
	SSRightArm,
	SSLeftArm,
	SSRightHandParent2 = 351,
	SSLeftHandParent2,
};

static NJS_MATRIX SS_RightHandMatrice;
static NJS_MATRIX SS_LeftHandMatrice;
static NJS_MATRIX SS_LeftFootMatrice;
static NJS_MATRIX SS_RightFootMatrice;

void SS_SetMatrixPosition(NJS_OBJECT* mdl)
{
	if (mdl == CharacterModels[SSRightHandParent2].Model)
	{
		njSetMatrix(SS_RightHandMatrice, CURRENT_MATRIX);
	}
	if (mdl == CharacterModels[SSLeftHandParent2].Model)
	{
		njSetMatrix(SS_LeftHandMatrice, CURRENT_MATRIX);
	}
	if (mdl == CharacterModels[SSRightFootHeel].Model)
	{
		njSetMatrix(SS_RightFootMatrice, CURRENT_MATRIX);
	}
	else if (mdl == CharacterModels[SSLeftFootHeel].Model)
	{
		njSetMatrix(SS_LeftFootMatrice, CURRENT_MATRIX);
	}
}

void SuperSonic_Callback_r(NJS_OBJECT* mdl) {
	NJS_MATRIX_PTR m = _nj_current_matrix_ptr_;
	SonicCharObj2* wk = SonicCO2PtrExtern;

	char pNum = wk->base.PlayerNum;
	char char2 = wk->base.CharID2;

	if (char2 != Characters_Sonic && char2 != Characters_SuperSonic)
	{
		return;
	}

	if (mdl == CharacterModels[SRoot2].Model || mdl == CharacterModels[SSRoot2].Model || mdl == CharacterModels[6].Model->child)
	{
		NJS_VECTOR pt{};
		njCalcPoint_(m, &pt, &pt, FALSE);
		njCalcPoint_(MATRIX_1A51A00, (NJS_VECTOR*)&wk->head2_pos, &pt, 0);
		pt = { 1.0f, 0.0f, 0.0f };
		njCalcVector_(&pt, &pt, m);
		njCalcVector_(&pt, &wk->head2_vec, MATRIX_1A51A00);
		SS_SetMatrixPosition(mdl);
		return;
	}
	if (mdl == CharacterModels[SRoot3].Model || mdl == CharacterModels[SSRoot3].Model)
	{
		if (MainCharObj1[wk->base.PlayerNum]->Action == 1)
		{
			njRotateX(m, wk->base.TiltAngle);
		}
	}
	else
	{
		if (mdl != CharacterModels[SRightArm].Model && mdl != CharacterModels[SSRightArm].Model)
		{
			if (mdl == CharacterModels[SLeftArm].Model || mdl == CharacterModels[SSLeftArm].Model)
			{
				if ((MainCharObj1[wk->base.PlayerNum]->Status & Status_HoldObject) != 0)
				{
					njRotateX(m, *((uint32_t*)wk->base.HeldObject->EntityData2 + 12));
				}
			}
			else if (mdl == CharacterModels[SHead].Model || mdl == CharacterModels[SSHead].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint_(m, &pt, &pt, FALSE);
				njCalcPoint_(MATRIX_1A51A00, (NJS_VECTOR*)&wk->head0_pos, &pt, 0);
				pt = { 1.0f, 0.0f, 0.0f };
				njCalcVector_(&pt, &pt, m);
				njCalcVector_(&pt, &wk->head0_vec, MATRIX_1A51A00);
			}
			else if (mdl == CharacterModels[SHead2].Model || mdl == CharacterModels[SSHead2].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint_(m, &pt, &pt, FALSE);
				njCalcPoint_(MATRIX_1A51A00, (NJS_VECTOR*)&wk->head1_pos, &pt, 0);
				pt = { 1.0f, 0.0f, 0.0f };
				njCalcVector_(&pt, &pt, m);
				njCalcVector_(&pt, &wk->head1_vec, MATRIX_1A51A00);
			}
			else if (mdl == CharacterModels[SRightHandParent].Model || mdl == CharacterModels[SSRightHandParent].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint_(m, &pt, &pt, FALSE);
				njCalcPoint_(MATRIX_1A51A00, (NJS_VECTOR*)&wk->righthand_pos, &pt, 0);
				pt = { 0.0f, 0.0f, 1.0f };
				njCalcVector_(&pt, &pt, m);
				njCalcVector_(&pt, &wk->righthand_vec0, MATRIX_1A51A00);
				pt = { 0.0f, -1.0f, 0.0f };
				njCalcVector_(&pt, &pt, m);
				njCalcVector_(&pt, &wk->righthand_vec1, MATRIX_1A51A00);
			}
			else if (mdl == CharacterModels[SLeftHandParent].Model || mdl == CharacterModels[SSLeftHandParent].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint_(m, &pt, &pt, FALSE);
				njCalcPoint_(MATRIX_1A51A00, (NJS_VECTOR*)&wk->lefthand_pos, &pt, 0);
				pt = { 0.0f, 0.0f, -1.0f };
				njCalcVector_(&pt, &pt, m);
				njCalcVector_(&pt, &wk->lefthand_vec0, MATRIX_1A51A00);
				pt = { 0.0f, -1.0f, 0.0f };
				njCalcVector_(&pt, &pt, m);
				njCalcVector_(&pt, &wk->lefthand_vec1, MATRIX_1A51A00);
			}
			else if (mdl == CharacterModels[SRightFootToe].Model || mdl == CharacterModels[SSRightFootToe].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint_(m, &pt, &pt, FALSE);
				njCalcPoint_(MATRIX_1A51A00, (NJS_VECTOR*)&wk->rightfoot_pos, &pt, 0);
				pt = { -1.0f, 0.0f, 0.0f };
				njCalcVector_(&pt, &pt, m);
				njCalcVector_(&pt, &wk->rightfoot_vec, MATRIX_1A51A00);
			}
			else if (mdl == CharacterModels[SLeftFootToe].Model || mdl == CharacterModels[SSLeftFootToe].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint_(m, &pt, &pt, FALSE);
				njCalcPoint_(MATRIX_1A51A00, (NJS_VECTOR*)&wk->leftfoot_pos, &pt, 0);
				pt = { -1.0f, 0.0f, 0.0f };
				njCalcVector_(&pt, &pt, m);
				njCalcVector_(&pt, &wk->leftfoot_vec, MATRIX_1A51A00);
			}
			SS_SetMatrixPosition(mdl);
			return;
		}
		if ((MainCharObj1[wk->base.PlayerNum]->Status & Status_HoldObject) == 0)
		{
			SS_SetMatrixPosition(mdl);
			return;
		}
	}
}

void DisplaySuperSonic_Upgrade(EntityData1* data1, SonicCharObj2* sonicCO2) {
	if (!sonicCO2 || !isUpgradeSonic)
		return;

	if (AltCostume[sonicCO2->base.PlayerNum] != 0)
		return;

	int curAnim = sonicCO2->base.AnimInfo.Current;

	if (data1->Status & Status_Ball || curAnim == 30 || curAnim == 11 || curAnim == 12 || curAnim == 100)
		return;

	njSetTexture(getSonicTexlist());
	njPushMatrixEx();

	NJS_OBJECT* FlameRingMDL = CharacterModels[25].Model;

	int upgrade = sonicCO2->base.Upgrades;

	if ((upgrade & (Upgrades_SonicFlameRing)) != 0 && SSFR)
	{
		if (FlameRingMDL)
		{
			NJS_VECTOR FRPos = { FlameRingMDL->child->pos[0], FlameRingMDL->child->pos[1], FlameRingMDL->child->pos[2] };
			memcpy(CURRENT_MATRIX, &SS_LeftHandMatrice, 0x30u);
			DrawChunkModel(FlameRingMDL->getchunkmodel());// Display FlameRing Model on Sonic
			signed int v30 = dword_25F02D8;
			signed int v31 = *(DWORD*)&sonicCO2->field_36A[6];
			dword_1DEB6A4 = dword_25F02D8;

			SetMaterial(1, njCos(v31) * -1.0, 0, 0);
			njTranslateEx(&FRPos);
			DrawChunkModel(FlameRingMDL->child->getchunkmodel());// Display FlameRing animation on Sonic
			ResetMaterial();
			dword_25F02D8 = dword_1DEB6A4;
			sub_426420(8, 0);
			*(DWORD*)(*(DWORD*)Has_texlist_batadvPlayerChara_in_it.gap0 + 12) = *(DWORD*)(*(DWORD*)Has_texlist_batadvPlayerChara_in_it.gap0 + 12) & 0xF7FFFFFF | 0x14000000;
		}
	}
	if ((upgrade & Upgrades_SonicBounceBracelet) != 0 && SSBB)
	{
		NJS_OBJECT* BounceMDL = CharacterModels[26].Model;

		if (BounceMDL)
		{
			memcpy(CURRENT_MATRIX, &SS_RightHandMatrice, 0x30u);
			DrawChunkModel(BounceMDL->getchunkmodel());
			signed int v36 = *(DWORD*)&sonicCO2->field_36A[10];
			SetMaterial(1, njCos(v36) * -1.0, 0, 0);
			NJS_OBJECT* BounceChild = CharacterModels[26].Model->child;
			njTranslateEx((NJS_VECTOR*)BounceChild->pos);

			njRotateZ_r(BounceChild->ang[2]);
			njRotateY_r(BounceChild->ang[1]);
			njRotateX_r(BounceChild->ang[0]);

			DrawChunkModel(BounceChild->getchunkmodel());
			ResetMaterial();
		}
	}
	if ((upgrade & Upgrades_SonicMagicGloves) != 0 && CharacterModels[27].Model && SSMG)
	{
		NJS_OBJECT* GloveMDL = CharacterModels[27].Model;
		if (GloveMDL) {
			memcpy(CURRENT_MATRIX, &SS_RightHandMatrice, 0x30u);
			DrawObjWithCallBack(GloveMDL);
		}
	}
	if ((upgrade & Upgrades_SonicLightShoes) != 0 && CharacterModels[14].Model && SSLS)
	{
		NJS_OBJECT* ShoesMDL = CharacterModels[14].Model;
		if (ShoesMDL) {
			memcpy(CURRENT_MATRIX, &SS_LeftFootMatrice, 0x30u);
			DrawObjWithCallBack(ShoesMDL);
			memcpy(CURRENT_MATRIX, &SS_RightFootMatrice, 0x30u);
			DrawObjWithCallBack(CharacterModels[13].Model);
		}
	}

	njPopMatrixEx();
}