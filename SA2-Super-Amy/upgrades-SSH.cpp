#include "pch.h"

enum ShadowModel {
	SHRoot = 65,
	SHRoot2,
	SHRoot3,
	SHHead,
	SHHead2 = 73,
	SHRightFootToe,
	SHLeftFootToe,
	SHRightFootHeel,
	SHLeftFootHeel,
	SHRightHandParent = 80,
	SHLeftHandParent,
	SHRightArm,
	SHLeftArm,
	SHRightHandParent2 = 88,
	SHLeftHandParent2
};

enum SuperShadowModel {
	SSHRoot = 355,
	SSHRoot2,
	SSHRoot3,
	SSHHead,
	SSHHead2 = 363,
	SSHRightFootToe,
	SSHLeftFootToe,
	SSHRightFootHeel,
	SSHLeftFootHeel,
	SSHRightHandParent = 370,
	SSHLeftHandParent,
	SSHRightArm,
	SSHLeftArm,
	SSHRightHandParent2 = 378,
	SSHLeftHandParent2,
};

static NJS_MATRIX SSH_RightHandMatrice;
static NJS_MATRIX SSH_LeftHandMatrice;
static NJS_MATRIX SSH_LeftFootMatrice;
static NJS_MATRIX SSH_RightFootMatrice;

DataArray(float, flt_1A51ADC, 0x1A51ADC, 12);
DataArray(float, flt_1A51994, 0x1A51994, 12);
DataArray(float, flt_1A51930, 0x1A51930, 12);
DataArray(float, flt_1A51900, 0x1A51900, 12);

void SSH_SetMatrixPosition(NJS_OBJECT* mdl)
{
	if (mdl == CharacterModels[SHRightHandParent2].Model || mdl == CharacterModels[SSHRightHandParent2].Model)
	{
		njSetMatrix(SSH_RightHandMatrice, CURRENT_MATRIX);
	}
	if (mdl == CharacterModels[SHLeftHandParent2].Model || mdl == CharacterModels[SSHLeftHandParent2].Model)
	{
		njSetMatrix(SSH_LeftHandMatrice, CURRENT_MATRIX);
	}
	if (mdl == CharacterModels[SHRightFootHeel].Model || mdl == CharacterModels[SSHRightFootHeel].Model)
	{
		njSetMatrix(SSH_RightFootMatrice, CURRENT_MATRIX);
	}
	else if (mdl == CharacterModels[SHLeftFootHeel].Model || mdl == CharacterModels[SSHLeftFootHeel].Model)
	{
		njSetMatrix(SSH_LeftFootMatrice, CURRENT_MATRIX);
	}
}

void SuperShadow_Callback_r(NJS_OBJECT* mdl) {
	NJS_MATRIX_PTR m = _nj_current_matrix_ptr_;
	SonicCharObj2* wk = SonicCO2PtrExtern;

	char pNum = wk->base.PlayerNum;
	char char2 = wk->base.CharID2;

	if (char2 != Characters_Shadow)
	{
		return;
	}

	if (mdl == CharacterModels[SHRoot2].Model || mdl == CharacterModels[SSHRoot2].Model || mdl == CharacterModels[71].Model->child)
	{
		NJS_VECTOR pt{};
		njCalcPoint_(m, &pt, &pt, FALSE);
		njCalcPoint_(MATRIX_1A51A00, (NJS_VECTOR*)&wk->head2_pos, &pt, 0);
		pt = { 1.0f, 0.0f, 0.0f };
		njCalcVector_(&pt, &pt, m);
		njCalcVector_(&pt, &wk->head2_vec, MATRIX_1A51A00);
		SSH_SetMatrixPosition(mdl);
		return;
	}
	if (mdl == CharacterModels[SHRoot3].Model || mdl == CharacterModels[SSHRoot3].Model)
	{
		if (MainCharObj1[wk->base.PlayerNum]->Action == 1)
		{
			njRotateX(m, wk->base.TiltAngle);
		}
	}
	else
	{
		if (mdl != CharacterModels[SHRightArm].Model && mdl != CharacterModels[SSHRightArm].Model)
		{
			if (mdl == CharacterModels[SHLeftArm].Model || mdl == CharacterModels[SSHLeftArm].Model)
			{
				if ((MainCharObj1[wk->base.PlayerNum]->Status & Status_HoldObject) != 0)
				{
					njRotateX(m, *((uint32_t*)wk->base.HeldObject->EntityData2 + 12));
				}
			}
			else if (mdl == CharacterModels[SHHead].Model || mdl == CharacterModels[SSHHead].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint_(m, &pt, &pt, FALSE);
				njCalcPoint_(MATRIX_1A51A00, (NJS_VECTOR*)&wk->head0_pos, &pt, 0);
				pt = { 1.0f, 0.0f, 0.0f };
				njCalcVector_(&pt, &pt, m);
				njCalcVector_(&pt, &wk->head0_vec, MATRIX_1A51A00);
			}
			else if (mdl == CharacterModels[SHHead2].Model || mdl == CharacterModels[SSHHead2].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint_(m, &pt, &pt, FALSE);
				njCalcPoint_(MATRIX_1A51A00, (NJS_VECTOR*)&wk->head1_pos, &pt, 0);
				pt = { 1.0f, 0.0f, 0.0f };
				njCalcVector_(&pt, &pt, m);
				njCalcVector_(&pt, &wk->head1_vec, MATRIX_1A51A00);
			}
			else if (mdl == CharacterModels[SHRightHandParent].Model || mdl == CharacterModels[SSHRightHandParent].Model)
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
			else if (mdl == CharacterModels[SHLeftHandParent].Model || mdl == CharacterModels[SSHLeftHandParent].Model)
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
			else if (mdl == CharacterModels[SHRightFootToe].Model || mdl == CharacterModels[SSHRightFootToe].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint_(m, &pt, &pt, FALSE);
				njCalcPoint_(MATRIX_1A51A00, (NJS_VECTOR*)&wk->rightfoot_pos, &pt, 0);
				pt = { -1.0f, 0.0f, 0.0f };
				njCalcVector_(&pt, &pt, m);
				njCalcVector_(&pt, &wk->rightfoot_vec, MATRIX_1A51A00);
				sub_42F770(flt_1A51ADC);
			}
			else if (mdl == CharacterModels[SHLeftFootToe].Model || mdl == CharacterModels[SSHLeftFootToe].Model)
			{
				NJS_VECTOR pt{};
				njCalcPoint_(m, &pt, &pt, FALSE);
				njCalcPoint_(MATRIX_1A51A00, (NJS_VECTOR*)&wk->leftfoot_pos, &pt, 0);
				pt = { -1.0f, 0.0f, 0.0f };
				njCalcVector_(&pt, &pt, m);
				njCalcVector_(&pt, &wk->leftfoot_vec, MATRIX_1A51A00);
				sub_42F770(flt_1A51994);
			}
			else if (mdl == CharacterModels[90].Model
				|| mdl == CharacterModels[380].Model)
			{
				sub_42F770(flt_1A51930); //used for roller light effect
			}
			else if (mdl == CharacterModels[91].Model || mdl == CharacterModels[381].Model)
			{
				sub_42F770(flt_1A51900);
			}
			SSH_SetMatrixPosition(mdl);
			return;
		}
		if ((MainCharObj1[wk->base.PlayerNum]->Status & Status_HoldObject) == 0)
		{
			SSH_SetMatrixPosition(mdl);
			return;
		}
	}
}

void DisplaySuperShadow_Upgrade(EntityData1* data1, SonicCharObj2* sonicCO2) {
	if (!isUpgradeShadow || AltCostume[sonicCO2->base.PlayerNum] != 0)
		return;

	int curAnim = sonicCO2->base.AnimInfo.Current;

	if (data1->Status & Status_Ball || curAnim == 30 || curAnim == 11 || curAnim == 12 || curAnim == 100)
		return;
	
	int otherpnum = 1;
	if (sonicCO2->base.PlayerNum == 1)
		otherpnum = 0;

	if (AltCostume[otherpnum] != 0)
		ModelIndex* SonicMdl = LoadMDLFile((char*)"SONIC1MDL.PRS");
	else
		ModelIndex* SonicMdl = LoadMDLFile((char*)"SONICMDL.PRS");


	njSetTexture(getShadowTexlist());
	njPushMatrixEx();

	NJS_OBJECT* FlameRingMDL = CharacterModels[100].Model;

	int upgrade = sonicCO2->base.Upgrades;

	if ((upgrade & (Upgrades_ShadowFlameRing)) != 0 && ShFR)
	{
		if (FlameRingMDL)
		{
			NJS_VECTOR FRPos = { FlameRingMDL->child->pos[0], FlameRingMDL->child->pos[1], FlameRingMDL->child->pos[2] };
			memcpy(CURRENT_MATRIX, &SSH_LeftHandMatrice, 0x30u);
			DrawChunkModel(FlameRingMDL->getchunkmodel());// Display FlameRing Model on Shadow
			signed int v30 = dword_25F02D8;
			signed int v31 = *(DWORD*)&sonicCO2->field_36A[6];
			dword_1DEB6A4 = dword_25F02D8;

			SetMaterial(1, njCos(v31) * -1.0, 0, 0);
			njTranslateEx(&FRPos);
			DrawChunkModel(FlameRingMDL->child->getchunkmodel());// Display FlameRing animation on Shadow
			ResetMaterial();
			dword_25F02D8 = dword_1DEB6A4;
			sub_426420(8, 0);
			*(DWORD*)(*(DWORD*)Has_texlist_batadvPlayerChara_in_it.gap0 + 12) = *(DWORD*)(*(DWORD*)Has_texlist_batadvPlayerChara_in_it.gap0 + 12) & 0xF7FFFFFF | 0x14000000;
		}
	}

	if ((upgrade & Upgrades_ShadowAirShoes) != 0 && CharacterModels[79].Model && ShAS)
	{
		NJS_OBJECT* ShoesMDL = CharacterModels[79].Model;
		if (ShoesMDL) {
			memcpy(CURRENT_MATRIX, &SSH_LeftFootMatrice, 0x30u);
			DrawObjWithCallBack(ShoesMDL);
			memcpy(CURRENT_MATRIX, &SSH_RightFootMatrice, 0x30u);
			DrawObjWithCallBack(CharacterModels[78].Model);
		}
	}

	njPopMatrixEx();

	njSetTexture(getSonicTexlist());
	njPushMatrixEx();
	if ((upgrade & Upgrades_SonicBounceBracelet) != 0 && ShBB)
	{
		NJS_OBJECT* BounceMDL = CharacterModels[26].Model;

		if (BounceMDL)
		{
			memcpy(CURRENT_MATRIX, &SSH_RightHandMatrice, 0x30u);
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
	if ((upgrade & Upgrades_SonicMagicGloves) != 0 && CharacterModels[27].Model && ShMG)
	{
		NJS_OBJECT* GloveMDL = CharacterModels[27].Model;
		if (GloveMDL) {
			memcpy(CURRENT_MATRIX, &SSH_RightHandMatrice, 0x30u);
			DrawObjWithCallBack(GloveMDL);
		}
	}

	njPopMatrixEx();

}