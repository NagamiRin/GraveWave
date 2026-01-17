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

	//銃系
	enSoundKind_AK_Fire = enSoundKind_SE,	//AKの発砲
	enSoundKind_HandGun_Fire,				//ハンドガンの発砲
	enSoundKind_HandGun_Reload,				//ハンドガンのリロード
	enSoundKind_LMG_Fire,					//LMGの発砲
	enSoundKind_LMG_Reload,					//LMGのリロード
	enSoundKind_LocketLauncher_Fire,		//ロケランの発砲
	enSoundKind_OutAmmo,					//弾切れの音
	enSoundKind_Recolver_Fire,				//リボルバーの発砲
	enSoundKind_Recolver_Reload,			//リボルバーのリロード
	enSoundKind_Rifle_Fire,					//ライフルの発砲
	enSoundKind_Rifle_Reload,				//ライフルのリロード
	enSoundKind_SMG_Fire,					//SMGの発砲
	enSoundKind_Sniper_Fire,				//スナイパーの発砲

	//演出系
	enSoundKind_BattleStart,				//戦闘フェーズ開始
	enSoundKind_Cavet,						//ゾンビ接近の警告
	enSoundKind_Clock,						//準備フェーズが終わりそう
	enSoundKind_GameClear,					//ゲームクリア
	enSoundKind_GameOver,					//ゲームオーバー
	enSoundKind_WaveClear,					//ウェーブクリア

	//ヒット系
	enSoundKind_BulletHit,					//弾がヒット
	enSoundKind_EliminateAllEnemy,			//全ての敵を倒した
	enSoundKind_EkiminateBoss,				//ボスを倒した
	enSoundKind_HeadShot,					//ヘッドショット
	enSoundKind_StoneBreak,					//岩が壊れた
	enSoundKind_StoneHit,					//岩に弾がヒット
	enSoundKind_WallDamage,					//防壁が被弾

	//エネミー系
	enSoundKind_ZombieGroan,				//ゾンビのうめき声

	//システム系
	enSoundKind_BackMenu,					//前のメニューに戻る
	enSoundKind_BuyItem,					//商品を買った
	enSoundKind_Decision,					//決定（メニュー）
	enSoundKind_MoveCursor,					//メニューのカーソル移動

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
	//BGM



	// SE
	//銃系
	SoundInformation("Assets/Sounds/Gun/AK_Fire.wav"),
	SoundInformation("Assets/Sounds/Gun/HandGun_Fire.wav"),
	SoundInformation("Assets/Sounds/Gun/HandGun_Reload.wav"),
	SoundInformation("Assets/Sounds/Gun/LMG_Fire.wav"),
	SoundInformation("Assets/Sounds/Gun/LMG_Reload.wav"),
	SoundInformation("Assets/Sounds/Gun/LocketLauncher_Fire.wav"),
	SoundInformation("Assets/Sounds/Gun/OutAmmo.wav"),
	SoundInformation("Assets/Sounds/Gun/Revolver_Fire.wav"),
	SoundInformation("Assets/Sounds/Gun/Revolver_Reload.wav"),
	SoundInformation("Assets/Sounds/Gun/Rifle_Fire.wav"),
	SoundInformation("Assets/Sounds/Gun/Rifle_Reload.wav"),
	SoundInformation("Assets/Sounds/Gun/SMG_Fire.wav"),
	SoundInformation("Assets/Sounds/Gun/Sniper_Fire.wav"),

	////演出系
	SoundInformation("Assets/Sounds/Direction/BattleStart.wav"),
	SoundInformation("Assets/Sounds/Direction/Caveat.wav"),
	SoundInformation("Assets/Sounds/Direction/Clock.wav"),
	SoundInformation("Assets/Sounds/Direction/GameClear.wav"),
	SoundInformation("Assets/Sounds/Direction/GameOver.wav"),
	SoundInformation("Assets/Sounds/Direction/WaveClear.wav"),

	//ヒット系
	SoundInformation("Assets/Sounds/Hit/BulletHit.wav"),
	SoundInformation("Assets/Sounds/Hit/EliminateAllEnemy.wav"),
	SoundInformation("Assets/Sounds/Hit/EliminateBoss.wav"),
	SoundInformation("Assets/Sounds/Hit/HeadShot.wav"),
	SoundInformation("Assets/Sounds/Hit/StoneBreak.wav"),
	SoundInformation("Assets/Sounds/Hit/StoneHit.wav"),
	SoundInformation("Assets/Sounds/Hit/WallDamage.wav"),

	//エネミー系
	SoundInformation("Assets/Sounds/Enemy/ZombieGroan.wav"),

	//システム系
	SoundInformation("Assets/Sounds/System/BackMenu.wav"),
	SoundInformation("Assets/Sounds/System/BuyItem.wav"),
	SoundInformation("Assets/Sounds/System/Decision.wav"),
	SoundInformation("Assets/Sounds/System/MoveCursor.wav"),
};

