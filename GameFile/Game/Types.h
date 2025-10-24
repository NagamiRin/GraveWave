#pragma once


enum EnGameObjectPriority
{
	enGameObjectPriority_Default = 0,
	enGameObjectPriority_BackGround,
	enGameObjectPriority_Bullet,
	enGameObjectPriority_Camera,
	enGameObjectPriority_Enemy,
	enGameObjectPriority_Gun,
	enGameObjectPriority_Player,
	enGameObjectPriority_UI,
};


/** ゲームオブジェクトにIDを割り振る */
#define appGameObject(name)\
public:\
	static constexpr uint32_t ID() { return appHash32(#name); }

/** IDが不正 */
static constexpr uint32_t INVALID_ID = 0xffffffff;