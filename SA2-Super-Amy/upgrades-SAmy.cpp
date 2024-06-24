#include "pch.h"

enum AmyModel {
	AmyRoot = 395,
	AmyRoot2,
	AmyRoot3,
	AmyHead,
	AmyHead2 = 403,
	AmyRightFootToe,
	AmyLeftFootToe,
	AmyRightFootHeel,
	AmyLeftFootHeel,
	AmyRightHandParent = 410,
	AmyLeftHandParent,
	AmyRightArm,
	AmyLeftArm,
	AmyRightHandParent2 = 416,
	AmyLeftHandParent2,
};

static NJS_MATRIX Amy_HeadMatrix;
static NJS_MATRIX Amy_RightHandMatrix;
static NJS_MATRIX Amy_LeftHandMatrix;
static NJS_MATRIX Amy_LeftFootMatrix;
static NJS_MATRIX Amy_RightFootMatrix;

enum AmyAnim {
	HammerJumpStartAnim = 249,
	HammerJumpAnim,
	HammerJumpLoopAnim,
	HammerAttackStartAnim,
	HammerAttackAnim,
	HammerAirAnim,
	HammerSpinSetAnim,
	HammerSpinAnim,
	DoubleJumpAnim
};

float hammerScale = 1.0f;
void AmySetHammerScale(CharObj2Base* a1) {

	switch (a1->AnimInfo.Current)
	{
	default:

		if (hammerScale > 1.0f)
			hammerScale -= 0.1f;

		break;
	case HammerAttackAnim:
	case HammerAirAnim:
	case HammerSpinSetAnim:

		if (hammerScale < 1.2f)
			hammerScale += 0.1f;
		break;
	case HammerSpinAnim:

		if (hammerScale < 1.5f)
			hammerScale += 0.1f;
		break;
	}
}

void DisplayHammer()
{
	NJS_OBJECT* hammer = CharacterModels[506].Model;

	char pnum = SonicCO2PtrExtern->base.PlayerNum;
	short curAnim = MainCharObj2[pnum]->AnimInfo.Current;
	SonicCharObj2* sco2 = SonicCO2PtrExtern;
	njSetTexture(SonicCO2PtrExtern->TextureList);
	if (hammer)
	{
		hammer->scl[0] = hammerScale;
		hammer->scl[1] = hammerScale;
		hammer->scl[2] = hammerScale;

		NJS_OBJECT* hammerChild = CharacterModels[506].Model->child;

		if (!hammerChild)
			return;

		hammerChild->scl[0] = hammerScale;
		hammerChild->scl[1] = hammerScale;
		hammerChild->scl[2] = hammerScale;

		if (curAnim == HammerSpinSetAnim) {

			hammer->ang[2] = MainCharObj1[pnum]->Rotation.z + hammerRotFix ? 0x500 : 0x4000;
			hammerChild->ang[2] = hammer->ang[2];
		}
		else if (curAnim == HammerSpinAnim) {

			hammer->ang[0] = hammerRotFix ? 0x4000 : 0x8000;
			hammer->ang[2] = MainCharObj1[pnum]->Rotation.z + hammerRotFix ? 0x3000 : -0x1000;
			hammerChild->ang[0] = hammer->ang[0];
			hammerChild->ang[2] = hammer->ang[2];
		}
		else {
			if (!hammerRotFix) {
				hammer->ang[0] = 0;
				hammer->ang[2] = 0;
				hammerChild->ang[0] = 0;
				hammerChild->ang[2] = 0x4000;
			}
			else
			{
				hammer->ang[0] = 0xFFFFFFD6;
				hammer->ang[2] = 161;
				hammerChild->ang[0] = 0;
				hammerChild->ang[2] = 0x0;
			}
		}

		if (MainCharObj2[pnum]->Speed.x >= 2.0f && MainCharObj1[pnum]->Action < 3 || curAnim == HammerJumpStartAnim || curAnim >= HammerAttackAnim && curAnim <= HammerSpinAnim) {
			njPushMatrixEx();
			memcpy(CURRENT_MATRIX, &Amy_RightHandMatrix, 0x30u);

			njTranslate(nullptr, -0.5f, 0.1f, 0.0f);
			DrawObject(hammer);
			njPopMatrixEx();
		}

		float a3 = 0;
		float v49 = 0;
		double v25 = 0;
		double v26 = 0;
		double v27 = 0;
		float v50 = 0;
		float v54 = 0;
		float v55 = 0;
		switch (sco2->base.AnimInfo.Animations[curAnim].AnimNum)
		{
			//		case 259:
		case 206:
		case 0xE4:
		case 0xE8:
			memcpy(CURRENT_MATRIX, &sonic_RightHandMatrix, 0x30u);
			v49 = sco2->base.AnimInfo.nframe;
			if (v49 >= 1.0)
			{
				v25 = v49 - 1.0;
				v26 = 1.0;
			}
			else
			{
				v26 = 1.0;
				v25 = 0.0;
			}
			v50 = v25;
			v54 = (float)CharacterAnimations[sco2->base.AnimInfo.Animations[sco2->base.AnimInfo.Animations[curAnim].AnimNum].AnimNum].Animation->nbFrame;
			v27 = v54;
			if (v54 > 2.0)
			{
				v55 = v27 - 2.0;
				v27 = v55;
			}
			a3 = v50 / v27;
			if (sco2->base.AnimInfo.Animations[curAnim].AnimNum == 259)
			{
				a3 = v26 - a3;
			}
			sub_7802B0(0, a3, a3, a3);
			goto LABEL_96;
		case 0xE6:
		case 0xF0:
		case 0xF1:
		case 0xF2:
		case 0xF5:
		case 259:
			memcpy(CURRENT_MATRIX, &sonic_RightHandMatrix, 0x30u);
		LABEL_96:
			DrawObject(hammer);
			break;
		default:
			break;
		}

	}

	if (hammerRotFix) {
		NJS_OBJECT* warrior = CharacterModels[500].Model;

		if (warrior) {
			njPushMatrixEx();
			memcpy(_nj_current_matrix_ptr_, &Amy_HeadMatrix, 0x30u);
			njTranslate(nullptr, -0.5f, 0.1f, 0.0f);
			DrawObject(warrior);
			njPopMatrixEx();
		}
	}
	return;
}

void Amy_SetMatrixPosition(NJS_OBJECT* mdl)
{
	if (mdl == CharacterModels[AmyHead].Model)
	{
		njSetMatrix(Amy_HeadMatrix, CURRENT_MATRIX);
	}
	if (mdl == CharacterModels[AmyRightHandParent2].Model)
	{
		njSetMatrix(Amy_RightHandMatrix, CURRENT_MATRIX);
	}
	if (mdl == CharacterModels[AmyLeftHandParent2].Model)
	{
		njSetMatrix(Amy_LeftHandMatrix, CURRENT_MATRIX);
	}
	if (mdl == CharacterModels[AmyRightFootHeel].Model)
	{
		njSetMatrix(Amy_RightFootMatrix, CURRENT_MATRIX);
	}
	else if (mdl == CharacterModels[AmyLeftFootHeel].Model)
	{
		njSetMatrix(Amy_LeftFootMatrix, CURRENT_MATRIX);
	}
}

void SuperAmy_Callback_r(NJS_OBJECT* mdl) {
	NJS_MATRIX_PTR m = _nj_current_matrix_ptr_;
	SonicCharObj2* wk = SonicCO2PtrExtern;

	char pNum = wk->base.PlayerNum;
	char char2 = wk->base.CharID2;

//	if (!isSuper[pNum] || char2 != Characters_Amy)
//	if (char2 != Characters_Amy)
//	{
		AmySetHammerScale(MainCharObj2[pNum]);
		sub_71F040(mdl);
//	}

	if (mdl == CharacterModels[AmyRoot2].Model || mdl == CharacterModels[401].Model->child)
	{
		NJS_VECTOR pt{};
		njCalcPoint_(m, &pt, &pt, FALSE);
		njCalcPoint_(MATRIX_1A51A00, (NJS_VECTOR*)&wk->head2_pos, &pt, 0);
		pt = { 1.0f, 0.0f, 0.0f };
		njCalcVector_(&pt, &pt, m);
		njCalcVector_(&pt, &wk->head2_vec, MATRIX_1A51A00);
		Amy_SetMatrixPosition(mdl);
		return;
	}
	if (mdl == CharacterModels[AmyRoot3].Model)
	{
		if (MainCharObj1[wk->base.PlayerNum]->Action == 1)
		{
			njRotateX(m, wk->base.TiltAngle);
		}
	}
	else
	{
		if (mdl != CharacterModels[AmyRightArm].Model)
		{
			if (mdl == CharacterModels[AmyLeftArm].Model)
			{
				if ((MainCharObj1[wk->base.PlayerNum]->Status & Status_HoldObject) != 0)
				{
					njRotateX(m, *((uint32_t*)wk->base.HeldObject->EntityData2 + 12));
				}
			}
			else if (mdl == CharacterModels[AmyHead].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint_(m, &pt, &pt, FALSE);
				njCalcPoint_(MATRIX_1A51A00, (NJS_VECTOR*)&wk->head0_pos, &pt, 0);
				pt = { 1.0f, 0.0f, 0.0f };
				njCalcVector_(&pt, &pt, m);
				njCalcVector_(&pt, &wk->head0_vec, MATRIX_1A51A00);
			}
			else if (mdl == CharacterModels[AmyHead2].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint_(m, &pt, &pt, FALSE);
				njCalcPoint_(MATRIX_1A51A00, (NJS_VECTOR*)&wk->head1_pos, &pt, 0);
				pt = { 1.0f, 0.0f, 0.0f };
				njCalcVector_(&pt, &pt, m);
				njCalcVector_(&pt, &wk->head1_vec, MATRIX_1A51A00);
			}
			else if (mdl == CharacterModels[AmyRightHandParent].Model)
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
			else if (mdl == CharacterModels[AmyLeftHandParent].Model)
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
			else if (mdl == CharacterModels[AmyRightFootToe].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint_(m, &pt, &pt, FALSE);
				njCalcPoint_(MATRIX_1A51A00, (NJS_VECTOR*)&wk->rightfoot_pos, &pt, 0);
				pt = { -1.0f, 0.0f, 0.0f };
				njCalcVector_(&pt, &pt, m);
				njCalcVector_(&pt, &wk->rightfoot_vec, MATRIX_1A51A00);
			}
			else if (mdl == CharacterModels[AmyLeftFootToe].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint_(m, &pt, &pt, FALSE);
				njCalcPoint_(MATRIX_1A51A00, (NJS_VECTOR*)&wk->leftfoot_pos, &pt, 0);
				pt = { -1.0f, 0.0f, 0.0f };
				njCalcVector_(&pt, &pt, m);
				njCalcVector_(&pt, &wk->leftfoot_vec, MATRIX_1A51A00);
			}
			Amy_SetMatrixPosition(mdl);
			return;
		}
		if ((MainCharObj1[wk->base.PlayerNum]->Status & Status_HoldObject) == 0)
		{
			Amy_SetMatrixPosition(mdl);
			return;
		}
	}
}

void DisplaySuperAmy_Upgrade(EntityData1* data1, SonicCharObj2* sco2) {
//	if (!sco2 || !isUpgradeAmy)
//		return;

//	if (AltCostume[sco2->base.PlayerNum] != 0)
//		return;

	int curAnim = sco2->base.AnimInfo.Current;

	if (data1->Status & Status_Ball || curAnim == 30)// || curAnim == 11 || curAnim == 12 || curAnim == 100)
		return;

	DisplayHammer();

	njSetTexture(getSonicTexlist());
	njPushMatrixEx();

	NJS_OBJECT* FlameRingMDL = CharacterModels[25].Model;

	int upgrade = sco2->base.Upgrades;

	if ((upgrade & (Upgrades_SonicFlameRing)) != 0 && SAFR)
	{
		if (FlameRingMDL)
		{
			NJS_VECTOR FRPos = { FlameRingMDL->child->pos[0], FlameRingMDL->child->pos[1], FlameRingMDL->child->pos[2] };
			memcpy(CURRENT_MATRIX, &Amy_LeftHandMatrix, 0x30u);
			DrawChunkModel(FlameRingMDL->getchunkmodel());// Display FlameRing Model on Sonic
			signed int v30 = dword_25F02D8;
			signed int v31 = *(DWORD*)&sco2->field_36A[6];
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
	if ((upgrade & Upgrades_SonicBounceBracelet) != 0 && SABB)
	{
		NJS_OBJECT* BounceMDL = CharacterModels[26].Model;

		if (BounceMDL)
		{
			memcpy(CURRENT_MATRIX, &Amy_RightHandMatrix, 0x30u);
			DrawChunkModel(BounceMDL->getchunkmodel());
			signed int v36 = *(DWORD*)&sco2->field_36A[10];
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
	if ((upgrade & Upgrades_SonicMagicGloves) != 0 && CharacterModels[27].Model && SAMG)
	{
		NJS_OBJECT* GloveMDL = CharacterModels[27].Model;
		if (GloveMDL) {
			memcpy(CURRENT_MATRIX, &Amy_RightHandMatrix, 0x30u);
			DrawObjWithCallBack(GloveMDL);
		}
	}
	if ((upgrade & Upgrades_SonicLightShoes) != 0 && CharacterModels[14].Model && SALS)
	{
		NJS_OBJECT* ShoesMDL = CharacterModels[14].Model;
		if (ShoesMDL) {
			memcpy(CURRENT_MATRIX, &Amy_LeftFootMatrix, 0x30u);
			DrawObjWithCallBack(ShoesMDL);
			memcpy(CURRENT_MATRIX, &Amy_RightFootMatrix, 0x30u);
			DrawObjWithCallBack(CharacterModels[13].Model);
		}
	}

	njPopMatrixEx();
}