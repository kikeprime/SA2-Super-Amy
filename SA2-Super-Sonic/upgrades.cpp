#include "pch.h"

extern NJS_TEXLIST Sonic_Texlist;
Trampoline* Sonic_CallBack_t;

enum SuperSonicModel {
    SSRoot = 328,
    SSRoot2,
    SSRoot3,
    SSHead = 331,
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

void SuperSonic_Callback_r(NJS_OBJECT* mdl) {
    

    SonicCharObj2* co2; // esi
    NJS_VECTOR v3; // ecx
    NJS_VECTOR v4; // eax
    NJS_VECTOR v6; // ecx
    NJS_VECTOR v7; // eax
    NJS_VECTOR v9; // ecx
    NJS_VECTOR v10; // eax
    NJS_VECTOR v12; // ecx
    NJS_VECTOR v13; // eax
    NJS_VECTOR v14; // eax
    NJS_VECTOR v15; // eax
    NJS_VECTOR v17; // ecx
    NJS_VECTOR v18; // eax
    NJS_VECTOR v19; // eax
    NJS_VECTOR v20; // eax
    NJS_VECTOR v22; // ecx
    NJS_VECTOR v23; // eax
    NJS_VECTOR v25; // ecx
    NJS_VECTOR v26; // eax
    ObjectMaster* heldObj; // edx
    float heldObjSomething; // eax
    NJS_MATRIX_PTR* ModelMatrice; // edi
    NJS_VECTOR result; // [esp+4h] [ebp-18h] BYREF
    NJS_VECTOR posResult; // [esp+10h] [ebp-Ch] BYREF

    char pNum = SonicCO2PtrExtern->base.PlayerNum;
    char char2 = SonicCO2PtrExtern->base.CharID2;

    if (!isSuper || char2 != Characters_Sonic)
    {
        FunctionPointer(void, original, (NJS_OBJECT * mdl), Sonic_CallBack_t->Target());
        return original(mdl);
    }

    posResult.z = 0.0;
    posResult.y = 0.0;
    posResult.x = 0.0;
    if (mdl == CharacterModels[SSRoot2].Model || mdl == CharacterModels[6].Model->child)
    {
        result.x = 1.0;
        result.z = 0.0;
        result.y = 0.0;
        njCalcPoint_(CURRENT_MATRIX, &v3, &posResult, 0);
        co2 = SonicCO2PtrExtern;  
        njCalcPoint_(flt_1A51A00, (NJS_VECTOR*)&SonicCO2PtrExtern->gap224[12], &v3, 0);
        njCalcVector_(&result, &v4, CURRENT_MATRIX);
        njCalcVector_(&v4, (NJS_VECTOR*)&co2->gap224[168], flt_1A51A00);
        goto LABEL_48;
    }
    if (mdl == CharacterModels[SSRoot3].Model)
    {
        if (MainCharObj1[SonicCO2PtrExtern->base.PlayerNum]->Action != 1)
        {
            goto LABEL_48;
        }
        heldObjSomething = *(float*)&SonicCO2PtrExtern->base.field_2C;
    }
    else
    {
        if (mdl != CharacterModels[SSRightArm].Model)
        {
            if (mdl == CharacterModels[SSLeftArm].Model)
            {
                if ((MainCharObj1[SonicCO2PtrExtern->base.PlayerNum]->Status & Status_HoldObject) != 0)
                {
                    heldObj = SonicCO2PtrExtern->base.HeldObject;
                    if (heldObj->EntityData2->field_30)
                    {
                        njRotateX(CURRENT_MATRIX, -(heldObj->EntityData2->field_30));
                    }
                }
            }
            else if (mdl == CharacterModels[SSHead].Model)
            {
                result.x = 1.0;
                result.z = 0.0;
                result.y = 0.0;
                njCalcPoint_(CURRENT_MATRIX, &v25, &posResult, 0);
                co2 = SonicCO2PtrExtern;
                njCalcPoint_(flt_1A51A00, &SonicCO2PtrExtern->HeadNodePos, &v25, 0);
                njCalcVector_(&result, &v26, CURRENT_MATRIX);
                njCalcVector_(&v26, (NJS_VECTOR*)&co2->gap224[144], flt_1A51A00);
            }
            else if (mdl == CharacterModels[SSHead2].Model)
            {
                result.x = 1.0;
                result.z = 0.0;
                result.y = 0.0;
                njCalcPoint_(CURRENT_MATRIX, &v22, &posResult, 0);
                co2 = SonicCO2PtrExtern;
                njCalcPoint_(flt_1A51A00, (NJS_VECTOR*)SonicCO2PtrExtern->gap224, &v22, 0);
                njCalcVector_(&result, &v23, CURRENT_MATRIX);
                njCalcVector_(&v23, (NJS_VECTOR*)&co2->gap224[156], flt_1A51A00);
            }
            else if (mdl == CharacterModels[SSRightHandParent].Model)
            {
                njCalcPoint_(CURRENT_MATRIX, &v17, &posResult, 0);
                co2 = SonicCO2PtrExtern;
                njCalcPoint_(flt_1A51A00, (NJS_VECTOR*)&SonicCO2PtrExtern->gap1BC[40], &v17, 0);
                result.z = 1.0;
                result.y = 0.0;
                result.x = 0.0;
                njCalcVector_(&result, &v18, CURRENT_MATRIX);
                njCalcVector_(&v18, (NJS_VECTOR*)&co2->gap224[72], flt_1A51A00);
                result.y = -1.0;
                result.x = 0.0;
                result.z = 0.0;
                njCalcVector_(&v19, &v19, CURRENT_MATRIX);
                njCalcVector_(&v20, (NJS_VECTOR*)&co2->gap224[96], flt_1A51A00);
            }
            else if (mdl == CharacterModels[SSLeftHandParent].Model)
            {
                njCalcPoint_(CURRENT_MATRIX, &v12, &posResult, 0);
                njCalcPoint_(flt_1A51A00, (NJS_VECTOR*)&SonicCO2PtrExtern->gap1BC[52], &v12, 0);
                result.z = -1.0;
                result.y = 0.0;
                result.x = 0.0;
                co2 = SonicCO2PtrExtern;
                njCalcVector_(&result, &v13, CURRENT_MATRIX);
                njCalcVector_(&v13, (NJS_VECTOR*)&co2->gap224[84], flt_1A51A00);
                result.y = -1.0;
                result.x = 0.0;
                result.z = 0.0;
                njCalcVector_(&v14, &v14, CURRENT_MATRIX);
                njCalcVector_(&v15, (NJS_VECTOR*)&co2->gap224[108], flt_1A51A00);
            }
            else if (mdl == CharacterModels[SSRightFootToe].Model)
            {
                result.x = -1.0;
                result.z = 0.0;
                result.y = 0.0;
                njCalcPoint_(CURRENT_MATRIX, &v9, &posResult, 0);
                co2 = SonicCO2PtrExtern;
                njCalcPoint_(flt_1A51A00, (NJS_VECTOR*)&SonicCO2PtrExtern->gap1BC[64], &v9, 0);
                njCalcVector_(&result, &v10, CURRENT_MATRIX);
                njCalcVector_(&v10, (NJS_VECTOR*)&co2->gap224[120], flt_1A51A00);
            }
            else if (mdl == CharacterModels[SSLeftFootToe].Model)
            {
                result.x = -1.0;
                result.z = 0.0;
                result.y = 0.0;
                njCalcPoint_(CURRENT_MATRIX, &v6, &posResult, 0);
                co2 = SonicCO2PtrExtern;
                njCalcPoint_(flt_1A51A00, (NJS_VECTOR*)&SonicCO2PtrExtern->gap1BC[76], &v6, 0);
                njCalcVector_(&result, &v7, CURRENT_MATRIX);
                njCalcVector_(&v7, (NJS_VECTOR*)&co2->gap224[132], flt_1A51A00);
            }
            goto LABEL_48;
        }
        if ((MainCharObj1[SonicCO2PtrExtern->base.PlayerNum]->Status & Status_HoldObject) == 0)
        {
            goto LABEL_48;
        }
        heldObjSomething = SonicCO2PtrExtern->base.HeldObject->EntityData2->field_30;
    }
    if (heldObjSomething != 0.0)
    {
        njRotateX(CURRENT_MATRIX, (heldObjSomething));
    }
LABEL_48:
    if (mdl == CharacterModels[SSRightHandParent2].Model)
    {
        ModelMatrice = (NJS_MATRIX_PTR*)&SS_RightHandMatrice;
        goto LABEL_56;
    }
    if (mdl == CharacterModels[SSLeftHandParent2].Model)
    {
        ModelMatrice = (NJS_MATRIX_PTR*)&SS_LeftHandMatrice;
    LABEL_56:
        memcpy(ModelMatrice, CURRENT_MATRIX, 0x30u);
    }
    if (mdl == CharacterModels[SSRightFootHeel].Model)
    {
        memcpy(&SS_RightFootMatrice, CURRENT_MATRIX, 0x30u);
    }
    else if (mdl == CharacterModels[SSLeftFootHeel].Model)
    {
        memcpy(&SS_LeftFootMatrice, CURRENT_MATRIX, 0x30u);
    }
}


void DisplaySuperSonic_Upgrade(SonicCharObj2* sonicCO2) {

    if (!sonicCO2)
        return;

    int curAnim = sonicCO2->base.AnimInfo.Current;

    if (curAnim == 30 || curAnim == 11 || curAnim == 12 || curAnim == 100)
        return;

    njSetTexture(&Sonic_Texlist);
    njPushMatrixEx();

    NJS_OBJECT* FlameRingMDL = CharacterModels[25].Model;
    NJS_VECTOR FRPos = { FlameRingMDL->child->pos[0], FlameRingMDL->child->pos[1], FlameRingMDL->child->pos[2] };
    int upgrade = sonicCO2->base.Upgrades;

    if ((upgrade & (Upgrades_SonicFlameRing)) != 0)
    {
        if (FlameRingMDL)
        {
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
    if ((upgrade & Upgrades_SonicBounceBracelet) != 0)
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
    
            if (BounceChild->ang[2])
            {
                njRotateZ((float*)_nj_current_matrix_ptr_, BounceChild->ang[2]);
            }
            if (BounceChild->ang[1])
            {
                njRotateY(CURRENT_MATRIX, BounceChild->ang[1]);
            }
            if (BounceChild->ang[0])
            {
                njRotateX(CURRENT_MATRIX, BounceChild->ang[0]);
            }
            DrawChunkModel(BounceChild->getchunkmodel());
            ResetMaterial();
        }
    }
    if ((upgrade & Upgrades_SonicMagicGloves) != 0 && CharacterModels[27].Model)
    {
        NJS_OBJECT* GloveMDL = CharacterModels[27].Model;
        memcpy(CURRENT_MATRIX, &SS_RightHandMatrice, 0x30u);
        DrawObjWithCallBack(GloveMDL);
    }
    if ((upgrade & Upgrades_SonicLightShoes) != 0 && CharacterModels[14].Model)
    {
        NJS_OBJECT* ShoesMDL = CharacterModels[14].Model;
        memcpy(CURRENT_MATRIX, &SS_LeftFootMatrice, 0x30u);
        DrawObjWithCallBack(ShoesMDL);
        memcpy(CURRENT_MATRIX, &SS_RightFootMatrice, 0x30u);
        DrawObjWithCallBack(CharacterModels[13].Model);
    }

    njPopMatrixEx();
}


void init_UpgradesHack() {
    Sonic_CallBack_t = new Trampoline((int)0x71EAA0, (int)0x71EAA9, SuperSonic_Callback_r);
}