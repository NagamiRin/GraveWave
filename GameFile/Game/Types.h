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
	enGameObjectPriority_SkyCube,
};


enum EnSpwnerType
{
	enSpwnerType_Left = 0,
	enSpwnerType_Center,
	enSpwnerType_Right,
	enSpwnerType_Num
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
		enCollirionEnemy = enCollisionAttr_User,
		enCollirionStone,
		// ここに追加していく
		enCollisionMax,
	};
}



/** ゲームオブジェクトにIDを割り振る */
#define appGameObject(name)\
public:\
	static constexpr uint32_t ID() { return appHash32(#name); }

/** IDが不正 */
static constexpr uint32_t INVALID_ID = 0xffffffff;