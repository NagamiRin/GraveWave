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
	enSoundKind_HandGun_Fire = enSoundKind_SE,
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
	SoundInformation("Assets/Sounds/HandGun_Fire.wav"),
};

