#pragma once

//void ReadConfig(const char* path);
void ReadConfig(std::string path);

enum FHCharSel : int
{
	VSuperSonic = 0,
	Sonic,
	Amy,
	Tails,
	Knuckles,
	MechTails,
	Tikal,
	ChaoWalker,
	AltSonic,
	AltAmy,
	AltTails,
	AltKnuckles,
	AltMechTails,
	AltTikal,
	AltChaoWalker
};

extern bool FHZHyperForm;

extern std::string modpath;
extern ModelIndex* SuperMetalSonicMdl;
extern Buttons TransformButton;
extern Buttons FlightButton;
extern Buttons boostBtn;
extern FHCharSel FHChar;
extern bool RemoveLimitations;
extern bool AlwaysSuperSonic;
extern bool AlwaysSuperShadow;
extern bool AlwaysSuperAmy;
extern bool AlwaysSuperMetalSonic;
extern bool AlwaysSuperTails;
extern bool AlwaysSuperEggman;
extern bool AlwaysSuperKnux;
extern bool AlwaysSuperRouge;
extern bool AlwaysSuperTikal;
extern bool AlwaysSuperChaos;
extern bool AlwaysSuperMechTails;
extern bool AlwaysSuperMechEggman;
extern bool AlwaysSuperChaoWalker;
extern bool AlwaysSuperDarkChaoWalker;
extern int SuperMusicVersion;
extern int superAuraState;
extern bool isPhysics;
extern bool isFlyAllowed;
extern bool isMechFlyAllowed;
extern bool isHunterFlyAllowed;
extern bool unTransform;
extern bool AllowSuperAttacks;
extern bool isJiggle;
extern bool SADXAura;
extern bool isBoostAllowed;
extern bool LastStory;
extern bool MetalJumpBall;
extern bool GammaAsMechEggmanMod;
extern bool BigAsDarkChao;
extern HMODULE DCCharsDLL;
extern HMODULE DisableUpgradeModelsDLL;
extern HMODULE BetterMilesDLL;
extern HMODULE AmyNewTricksDLL;
extern std::string DCCharsPath;
extern std::string DisableUpgradeModelsPath;
extern std::string BetterMilesPath;
extern std::string AmyNewTricksPath;

extern bool hammerRotFix;

extern bool isUpgradeSonic;
extern bool isUpgradeShadow;
extern bool isUpgradeAmy;
extern bool isUpgradeMetal;
extern bool SSLS;
extern bool SSFR;
extern bool SSBB;
extern bool SSMG;
extern bool ShAS;
extern bool ShFR;
extern bool ShBB;
extern bool ShMG;
extern bool SALS;
extern bool SAFR;
extern bool SABB;
extern bool SAMG;
extern bool MetalAS;
extern bool MetalFR;
extern bool MetalBB;
extern bool MetalMG;

extern int P1TransformKey;
extern int P2TransformKey;
extern char LeftK;
extern char RightK;

extern bool keswitch1;
extern bool keswitch2;
extern int P1ESwitchKey;
extern int P2ESwitchKey;

extern bool FHZAuraHack;

extern AnimationInfo SuperSonicAnimationList_r[];
extern AnimationInfo SuperShadowAnimationList_r[];
extern AnimationInfo SuperAmyAnimationList_r[];
extern AnimationInfo SuperMetalSonicAnimationList_r[];

extern HelperFunctions HelperFunctionsGlobal;

extern HMODULE SA2SS;
extern HMODULE SA2Anim;
extern HMODULE SA1Char;
extern HMODULE SonkTrick;

extern NJS_TEXLIST* Sonic_TexlistPtr;
extern NJS_TEXLIST* Shadow_Texlist;

extern NJS_TEXLIST SSEff_Texlist;
extern NJS_TEXLIST SSHEff_Texlist;
extern NJS_TEXLIST SSAura_Texlist;
extern NJS_TEXLIST SMAura_Texlist;
extern NJS_TEXLIST STAura_Texlist;
extern NJS_TEXLIST SEAura_Texlist;
extern NJS_TEXLIST SKAura_Texlist;
extern NJS_TEXLIST SRAura_Texlist;
extern NJS_TEXLIST STKAura_Texlist;
extern NJS_TEXLIST SCHAura_Texlist;
extern NJS_TEXLIST SMTAura_Texlist;
extern NJS_TEXLIST SMEAura_Texlist;
extern NJS_TEXLIST SCWAura_Texlist;
extern NJS_TEXLIST SDCWAura_Texlist;

#define CURRENT_MATRIX _nj_current_matrix_ptr_
#define TaskHook static FunctionHook<void, ObjectMaster*>
constexpr char PMax = 2;

#pragma pack(push, 8)
union ModelPointers
{
	NJS_MODEL* basic;
	NJS_CNK_MODEL* chunk;
	SA2B_Model* sa2b;
};
#pragma pack(pop)

struct auraStruct {
	char idk;
	char charID;
	NJS_VECTOR pos;
	NJS_OBJECT* Model;
	NJS_TEXNAME* Tex;
	int idk3[40];
};

enum SuperSonicM {
	superSonicInit,
	playerInputCheck,
	superSonicTransfo,
	superSonicTransition,
	superSonicWait,
	superSonicOnFrames,
	superSonicUntransfo,
};

enum SuperSonicAnim {
	superSonicStanding,

	superSonicIntro = 203,
	superSonicVictory = 204,
	superSonicFlying1,
	superSonicFlying2,
	ssBeginAscent,
	ssAscending,
	ssBeginDescent,
	ssDescend,
	ssBeginDash,
	ssDash,
	ssBeginDash2,
	ssDash2
};

enum SuperAmyAnim {
	superAmyStanding,

	superAmyIntro = 258,
	superAmyVictory = 259,
	superAmyFlying1,
	superAmyFlying2,
	saBeginAscent,
	saAscending,
	saBeginDescent,
	saDescend,
	saBeginDash,
	saDash,
	saBeginDash2,
	saDash2
};

enum SuperSonicMusic {
	None,
	Sonic2,
	Sonic3,
	SonicAndKnuckles,
	SADX,
	SA2Event,
	SA2LiveAndLearn,
	Mania,
	Random
};

extern bool isSuper[PMax];
extern bool isHyper[PMax];
extern bool isChaosasSonic[PMax];

extern bool ktrans1;
extern bool ktrans2;

extern bool ModelSwap1;
extern bool ModelSwap2;
extern bool AllowSuperAmyModel;
extern bool AllowHyperAmyModel;
extern bool AllowSuperMetalModel;
extern bool AllowHyperMetalModel;
extern bool AllowSuperTailsModel;
extern bool AllowHyperTailsModel;
extern bool AllowSuperEggmanModel;
extern bool AllowHyperEggmanModel;
extern bool AllowSuperKnuxModel;
extern bool AllowHyperKnuxModel;
extern bool AllowSuperTikalModel;
extern bool AllowHyperTikalModel;
extern bool AllowSuperRougeModel;
extern bool AllowHyperRougeModel;
extern bool AllowSuperChaosModel;
extern bool AllowHyperChaosModel;
extern bool AllowSuperMechTailsModel;
extern bool AllowHyperMechTailsModel;
extern bool AllowSuperMechEggmanModel;
extern bool AllowHyperMechEggmanModel;
extern bool AllowSuperChaoWModel;
extern bool AllowHyperChaoWModel;
extern bool AllowSuperDChaoWModel;
extern bool AllowHyperDChaoWModel;
extern int spinTimer;

void init_SuperSonic();
void init_SuperAmy();
void init_SuperMetalSonic();
void init_SuperTails();
void init_SuperEggman();
void init_SuperKnuckles();
void init_SuperRouge();
void init_SuperTikal();
void init_SuperChaos();
void init_SuperMechTails();
void init_AltSuperMechTails();
void init_SuperMechEggman();
void init_SuperChaoWalker();
void init_SuperDarkChaoWalker();
void init_AuraHack();
void init_MusicHack();
void init_PhysicsHack();
void init_FinalHazardHack();
NJS_TEXLIST* getSonicTexlist();
NJS_TEXLIST* getShadowTexlist();
NJS_TEXLIST* getAmyTexlist();
NJS_TEXLIST* getMetalSonicTexlist();
NJS_TEXLIST* getKnuxTexlist();
NJS_TEXLIST* getRougeTexlist();
NJS_TEXLIST* getTikalTexlist();
NJS_TEXLIST* getChaosTexlist();
void init_SuperShadow();
void init_WaterHack();
bool isBoosting(char pnum);
bool isLastStoryBeaten();
