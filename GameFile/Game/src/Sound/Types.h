/**
 * Types.h
 * サウンド用の定数など必要な情報を定義するファイル
 */
#pragma once
#include <string>


/** サウンドの種類 */
enum enSoundKind
{
	enSoundKind_SE = 0,
	enSoundKind_AK_Fire = enSoundKind_SE,
	enSoundKind_HandGun_Fire,
	enSoundKind_HandGun_Reload,
	enSoundKind_LMG_Fire,
	enSoundKind_LMG_Reload,
	enSoundKind_LocketLauncher_Fire,
	enSoundKind_Recolver_Fire,
	enSoundKind_Recolver_LoadAmmo,
	enSoundKind_Recolver_Reload,
	enSoundKind_Rifle_Fire,
	enSoundKind_Rifle_Reload,
	enSoundKind_SMG_Fire,
	enSoundKind_Sniper_Fire,
	enSoundKind_OutAmmo,
	enSoundKind_SE_Max,
	enSoundKind_BGM = enSoundKind_SE_Max,
	enSoundKind_Game = enSoundKind_BGM,
	enSoundKind_Voice,
	enSoundKind_Max,
	enSoundKind_None = enSoundKind_Max,
};


/** サウンドの情報の構造体 */
struct SoundInformation
{
	std::string assetPath;
	//
	SoundInformation(const std::string& path) : assetPath(path) {}
};


/** 情報を保持 */
static SoundInformation soundInformation[enSoundKind_SE_Max] =
{
	// SE
	//銃系
	SoundInformation("Assets/Sounds/AK_Fire.wav"),
	SoundInformation("Assets/Sounds/HandGun_Fire.wav"),
	SoundInformation("Assets/Sounds/HandGun_Reload.wav"),
	SoundInformation("Assets/Sounds/LMG_Fire.wav"),
	SoundInformation("Assets/Sounds/LMG_Reload.wav"),
	SoundInformation("Assets/Sounds/LocketLauncher_Fire.wav"),
	SoundInformation("Assets/Sounds/Revolver_Fire.wav"),
	SoundInformation("Assets/Sounds/Revolver_LoadAmmo.wav"),
	SoundInformation("Assets/Sounds/Revolver_Reload.wav"),
	SoundInformation("Assets/Sounds/Rifle_Fire.wav"),
	SoundInformation("Assets/Sounds/Rifle_Reload.wav"),
	SoundInformation("Assets/Sounds/SMG_Fire.wav"),
	SoundInformation("Assets/Sounds/Sniper_Fire.wav"),
	SoundInformation("Assets/Sounds/OutAmmo.wav"),	

	////演出系
	//SoundInformation("Assets/Sounds/BattleStart.wav"),
	//SoundInformation("Assets/Sounds/Caveat.wav"),
	//SoundInformation("Assets/Sounds/Clock.wav"),
	//SoundInformation("Assets/Sounds/GameClear.wav"),
	//SoundInformation("Assets/Sounds/GameOver.wav"),
	//SoundInformation("Assets/Sounds/WaveClear.wav"),

	////被弾系
	//SoundInformation("Assets/Sounds/EliminateAllEnemy.wav"),
	//SoundInformation("Assets/Sounds/EliminateBoss.wav"),
	//SoundInformation("Assets/Sounds/HeadShot.wav"),
	//SoundInformation("Assets/Sounds/Hit.wav"),
	//SoundInformation("Assets/Sounds/StoneBreak.wav"),
	//SoundInformation("Assets/Sounds/StoneHit.wav"),
	//SoundInformation("Assets/Sounds/WallDamage.wav"),

	////システム系
	//SoundInformation("Assets/Sounds/BackMenu.wav"),
	//SoundInformation("Assets/Sounds/BuyItem.wav"),
	//SoundInformation("Assets/Sounds/Decision.wav"),
	//SoundInformation("Assets/Sounds/MoveCursor.wav"),
};

