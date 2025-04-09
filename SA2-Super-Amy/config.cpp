#include "pch.h"
#include <fstream>

Buttons TransformButton = Buttons_B;
Buttons UntransformButton = Buttons_B;
Buttons FlightButton = Buttons_Y;
bool RemoveLimitations = false;
bool AlwaysSuperSonic = false;
int SuperMusicVersion = SA2LiveAndLearn;
int superAuraState = 1;
bool SADXAura = false;
bool isPhysics = true;
bool isFlyAllowed = true;
bool isMechFlyAllowed = true;
bool isHunterFlyAllowed = true;
bool unTransform = true;
bool isBoostAllowed = true;

bool AlwaysSuperShadow = false;
bool AllowSuperAttacks = true;
bool LastStory = false;
bool isJiggle = false;

bool AllowSuperAmy = true;
bool AllowSuperMetalSonic = true;
bool AllowSuperTails = true;
bool AllowSuperEggman = true;
bool AllowSuperKnux = true;
bool AllowSuperRouge = true;
bool AllowSuperTikal = true;
bool AllowSuperChaos = true;
bool AllowSuperMechTails = true;
bool AllowSuperMechEggman = true;
bool AllowSuperChaoWalker = true;
bool AllowSuperDarkChaoWalker = true;

bool AlwaysSuperAmy = false;
bool AlwaysSuperMetalSonic = false;
bool AlwaysSuperTails = false;
bool AlwaysSuperEggman = false;
bool AlwaysSuperKnux = false;
bool AlwaysSuperRouge = false;
bool AlwaysSuperTikal = false;
bool AlwaysSuperChaos = false;
bool AlwaysSuperMechTails = false;
bool AlwaysSuperMechEggman = false;
bool AlwaysSuperChaoWalker = false;
bool AlwaysSuperDarkChaoWalker = false;

bool MetalJumpBall = false;

bool isUpgradeSonic = true;
bool isUpgradeShadow = true;
bool isUpgradeAmy = true;
bool isUpgradeMetal = true;
bool ShBB = false;
bool ShMG = false;
bool SALS = false;
bool SAFR = false;
bool SABB = false;
bool SAMG = false;
bool MetalAS = false;
bool MetalFR = false;
bool MetalBB = false;
bool MetalMG = false;

bool ktrans1 = false;
bool ktrans2 = false;
int P1TransformKey;
int P2TransformKey;
bool keswitch1 = false;
bool keswitch2 = false;
int P1ESwitchKey;
int P2ESwitchKey;
char LeftK;
char RightK;

bool FHZAuraHack = true;

FHCharSel FHChar = VSuperSonic;
bool FHZHyperForm = false;

Buttons boostBtn = Buttons_B;

static const Buttons ButtonsList[]
{
	Buttons_B,
	Buttons_Y,
	Buttons_X,
	Buttons_Up,
	Buttons_Down,
	Buttons_Left,
	Buttons_Right,
};

bool AllowSuperAmyModel = false;
bool AllowHyperAmyModel = false;
bool AllowSuperMetalModel = false;
bool AllowHyperMetalModel = false;
bool AllowSuperTailsModel = false;
bool AllowHyperTailsModel = false;
bool AllowSuperEggmanModel = false;
bool AllowHyperEggmanModel = false;
bool AllowSuperKnuxModel = false;
bool AllowHyperKnuxModel = false;
bool AllowSuperTikalModel = false;
bool AllowHyperTikalModel = false;
bool AllowSuperRougeModel = false;
bool AllowHyperRougeModel = false;
bool AllowSuperChaosModel = false;
bool AllowHyperChaosModel = false;
bool AllowSuperMechTailsModel = false;
bool AllowHyperMechTailsModel = false;
bool AllowSuperMechEggmanModel = false;
bool AllowHyperMechEggmanModel = false;
bool AllowSuperChaoWModel = false;
bool AllowHyperChaoWModel = false;
bool AllowSuperDChaoWModel = false;
bool AllowHyperDChaoWModel = false;

bool hammerRotFix = false;

bool isLastStoryBeaten()
{
	if (!LastStory)
		return true;

	return SomeStoryUnlocksOrSomething[2];
}

void ReadConfig(std::string path)
{
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

	AllowSuperAmy = config->getBool("Enabler", "AllowSuperAmy", true);
	AllowSuperMetalSonic = config->getBool("Enabler", "AllowSuperMetalSonic", true);
	AllowSuperTails = config->getBool("Enabler", "AllowSuperTails", true);
	AllowSuperEggman = config->getBool("Enabler", "AllowSuperEggman", true);
	AllowSuperKnux = config->getBool("Enabler", "AllowSuperKnux", true);
	AllowSuperRouge = config->getBool("Enabler", "AllowSuperRouge", true);
	AllowSuperTikal = config->getBool("Enabler", "AllowSuperTikal", true);
	AllowSuperChaos = config->getBool("Enabler", "AllowSuperChaos", true);

	RemoveLimitations = config->getBool("Gameplay", "RemoveLimitations", false);
	AlwaysSuperSonic = config->getBool("Gameplay", "AlwaysSuperSonic", false);
	AlwaysSuperShadow = config->getBool("Gameplay", "AlwaysSuperShadow", false);
	AlwaysSuperAmy = config->getBool("Gameplay", "AlwaysSuperAmy", false);
	AlwaysSuperMetalSonic = config->getBool("Gameplay", "AlwaysSuperMetalSonic", false);
	AlwaysSuperTails = config->getBool("Gameplay", "AlwaysSuperTails", false);
	AlwaysSuperEggman = config->getBool("Gameplay", "AlwaysSuperEggman", false);
	AlwaysSuperKnux = config->getBool("Gameplay", "AlwaysSuperKnux", false);
	AlwaysSuperRouge = config->getBool("Gameplay", "AlwaysSuperRouge", false);
	AlwaysSuperTikal = config->getBool("Gameplay", "AlwaysSuperTikal", false);
	AlwaysSuperChaos = config->getBool("Gameplay", "AlwaysSuperChaos", false);
	isPhysics = config->getBool("Gameplay", "isPhysics", true);
	isFlyAllowed = config->getBool("Gameplay", "isFly", true);
	isMechFlyAllowed = config->getBool("Gameplay", "isMechFly", true);
	isHunterFlyAllowed = config->getBool("Gameplay", "isHunterFly", true);
	unTransform = config->getBool("Gameplay", "unTransform", true);
	AllowSuperAttacks = config->getBool("Gameplay", "AllowSuperAttacks", true);
	LastStory = config->getBool("Gameplay", "LastStory", false);

	TransformButton = ButtonsList[config->getInt("Controls", "TransformButton", 1)];
	FlightButton = ButtonsList[config->getInt("Controls", "FlightButton", 2)];
	boostBtn = ButtonsList[config->getInt("Controls", "boostBtn", 0)];
	ktrans1 = config->getBool("Controls", "ktrans1", false);
	P1TransformKey = config->getInt("Controls", "P1TransformKey", 82);
	ktrans2 = config->getBool("Controls", "ktrans2", false);
	P2TransformKey = config->getInt("Controls", "P2TransformKey", 104);
	keswitch1 = config->getBool("Controls", "ktrans1", false);
	P1ESwitchKey = config->getInt("Controls", "P1ESwitchKey", 67);
	keswitch2 = config->getBool("Controls", "ktrans2", false);
	P2ESwitchKey = config->getInt("Controls", "P2ESwitchKey", 99);

	superAuraState = config->getInt("Appearance", "superAuraState", 2);
	SADXAura = config->getBool("Appearance", "SADXAura", true);
	isJiggle = config->getBool("Appearance", "isJiggle", true);
	MetalJumpBall = config->getBool("Appearance", "MetalJumpBall", true);

	isUpgradeSonic = config->getBool("Upgrades", "isUpgradeSonic", true);
	isUpgradeShadow = config->getBool("Upgrades", "isUpgradeShadow", true);
	isUpgradeAmy = config->getBool("Upgrades", "isUpgradeAmy", false);
	isUpgradeMetal = config->getBool("Upgrades", "isUpgradeMetal", false);
	ShBB = config->getBool("Upgrades", "ShBB", false);
	ShMG = config->getBool("Upgrades", "ShMG", false);
	SALS = config->getBool("Upgrades", "SALS", false);
	SAFR = config->getBool("Upgrades", "SAFR", false);
	SABB = config->getBool("Upgrades", "SABB", false);
	SAMG = config->getBool("Upgrades", "SAMG", false);
	MetalAS = config->getBool("Upgrades", "MetalAS", true);
	MetalFR = config->getBool("Upgrades", "MetalFR", true);
	MetalBB = config->getBool("Upgrades", "MetalBB", true);
	MetalMG = config->getBool("Upgrades", "MetalMG", true);

	FHChar = (FHCharSel)config->getInt("FHZ", "FHChar", 0);
	FHZAuraHack = config->getBool("FHZ", "FHZAuraHack", true);

	SuperMusicVersion = config->getInt("Audio", "SuperMusicVersion", SA2LiveAndLearn);

	AllowSuperAmyModel = config->getBool("Models", "AllowSuperAmyModel", false);
	AllowHyperAmyModel = config->getBool("Models", "AllowHyperAmyModel", false);
	AllowSuperMetalModel = config->getBool("Models", "AllowSuperMetalModel", false);
	AllowHyperMetalModel = config->getBool("Models", "AllowHyperMetalModel", false);
	AllowSuperTailsModel = config->getBool("Models", "AllowSuperTailsModel", false);
	AllowHyperTailsModel = config->getBool("Models", "AllowHyperTailsModel", false);
	AllowSuperEggmanModel = config->getBool("Models", "AllowSuperEggmanModel", false);
	AllowHyperEggmanModel = config->getBool("Models", "AllowHyperEggmanModel", false);
	AllowSuperKnuxModel = config->getBool("Models", "AllowSuperKnuxModel", false);
	AllowHyperKnuxModel = config->getBool("Models", "AllowHyperKnuxModel", false);
	AllowSuperTikalModel = config->getBool("Models", "AllowSuperTikalModel", false);
	AllowHyperTikalModel = config->getBool("Models", "AllowHyperTikalModel", false);
	AllowSuperRougeModel = config->getBool("Models", "AllowSuperRougeModel", false);
	AllowHyperRougeModel = config->getBool("Models", "AllowHyperRougeModel", false);
	AllowSuperChaosModel = config->getBool("Models", "AllowSuperChaosModel", false);
	AllowHyperChaosModel = config->getBool("Models", "AllowHyperChaosModel", false);
	AllowSuperMechTailsModel = config->getBool("Models", "AllowSuperMechTailsModel", false);
	AllowHyperMechTailsModel = config->getBool("Models", "AllowHyperMechTailsModel", false);
	AllowSuperMechEggmanModel = config->getBool("Models", "AllowSuperMechEggmanModel", false);
	AllowHyperMechEggmanModel = config->getBool("Models", "AllowHyperMechEggmanModel", false);
	AllowSuperChaoWModel = config->getBool("Models", "AllowSuperChaoWModel", false);
	AllowHyperChaoWModel = config->getBool("Models", "AllowHyperChaoWModel", false);
	AllowSuperDChaoWModel = config->getBool("Models", "AllowSuperDChaoWModel", false);
	AllowHyperDChaoWModel = config->getBool("Models", "AllowHyperDChaoWModel", false);

	delete config;

	if (AlwaysSuperSonic || AlwaysSuperShadow || AlwaysSuperAmy || AlwaysSuperMetalSonic || AlwaysSuperKnux || AlwaysSuperRouge || AlwaysSuperTikal || AlwaysSuperChaos || AlwaysSuperChaoWalker || AlwaysSuperDarkChaoWalker)
		RemoveLimitations = true;

	//DC skins
	if (DCCharsDLL)
	{
		const IniFile* DCCharsConfig = new IniFile(DCCharsPath + "\\config.ini");
		std::string BigAsDarkChaoS = "Big";
		BigAsDarkChaoS = DCCharsConfig->getString("Characters", "DarkChaoWalker", "Big");
		delete DCCharsConfig;

		if (BigAsDarkChaoS == "Big")
		{
			BigAsDarkChao = true;
		}
		if (BigAsDarkChaoS == "Dark Chao Walker")
		{
			BigAsDarkChao = false;
		}
	}
	//Disable Upgrade Models
	if (DisableUpgradeModelsDLL)
	{
		const IniFile* DisableUpgradeModelsConfig = new IniFile(std::string(DisableUpgradeModelsPath) + "\\config.ini");
		SSLS = !DisableUpgradeModelsConfig->getBool("Sonic", "DisableLightShoes", true);
		SSFR = !DisableUpgradeModelsConfig->getBool("Sonic", "DisableFlameRing", true);
		SSBB = !DisableUpgradeModelsConfig->getBool("Sonic", "DisableBounceBracelet", true);
		SSMG = !DisableUpgradeModelsConfig->getBool("Sonic", "DisableMagicGloves", true);
		ShAS = !DisableUpgradeModelsConfig->getBool("Shadow", "DisableAirShoes", true);
		ShFR = !DisableUpgradeModelsConfig->getBool("Shadow", "DisableFlameRing", true);
		delete DisableUpgradeModelsConfig;
	}

	if (BetterMilesDLL)
	{
		const IniFile* BetterMilesConfig = new IniFile(std::string(BetterMilesPath) + "\\config.ini");
		delete BetterMilesConfig;
	}

	if (AmyNewTricksDLL)
	{
		const IniFile* AmyNewTricksConfig = new IniFile(std::string(AmyNewTricksPath) + "\\config.ini");
		hammerRotFix = AmyNewTricksConfig->getBool("General", "hammerRotFix", false);
		delete AmyNewTricksConfig;
	}
}
