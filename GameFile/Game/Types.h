#pragma once


enum EnGameObjectPriority
{
	enGameObjectPriority_Default = 0,
	enGameObjectPriority_BackGround,
	enGameObjectPriority_Bullet,
	enGameObjectPriority_Camera,
	enGameObjectPriority_Enemy,
	enGameObjectPriority_Stone,
	enGameObjectPriority_Gun,
	enGameObjectPriority_Player,
	enGameObjectPriority_Wall,
	enGameObjectPriority_UI,
	enGameObjectPriority_SceneManager,
	enGameObjectPriority_EffectManager,
	enGameObjectPriority_HitManager,
	enGameObjectPriority_SkyCube,
};


enum EnSpwnerType
{
	enSpwnerType_Left = 0,
	enSpwnerType_Center,
	enSpwnerType_Right,
	enSpwnerType_None = enSpwnerType_Right ,
};

enum EnWaveType {
	enWaveType_Normal,
	enWaveType_Boss,
	enWaveType_None,
};


enum EnResultType
{
	enResultType_Clear,
	enResultType_Over,
	enResultType_None,
};

/** アプリ側用の処理にしたいのでnamespaceをつける */
namespace nsApp
{
	enum EnCollisionAttr
	{
		enCollision_Enemy = enCollisionAttr_User,
		// ここに追加していく
		enCollision_Stone,
		enCollision_Wall,
		enCollision_Max,
	};
}



/** ゲームオブジェクトにIDを割り振る */
#define appGameObject(name)\
public:\
	static constexpr uint32_t ID() { return appHash32(#name); }

/** IDが不正 */
static constexpr uint32_t INVALID_ID = 0xffffffff;