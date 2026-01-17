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
	enGameObjectPriority_Loading = 250,
};


enum EnSpwnerType
{
	enSpwnerType_Left = 0,
	enSpwnerType_Center,
	enSpwnerType_Right,
	enSpwnerType_None = enSpwnerType_Right ,
};

enum EnProductType
{
	enProductType_None = 0,

	enProductType_GZ75,
	enProductType_R8,
	enProductType_M1911,
	enProductType_TEC9,
	enProductType_SubWeaponMax,

	enProductType_ACR,
	enProductType_AK47,
	enProductType_G36,
	enProductType_HAMR,
	enProductType_L86A2,
	enProductType_M4A1,
	enProductType_SCAR,
	enProductType_MainWeaponMax,

	enProductType_NormalAmmo,
	enProductType_AmmoMax
};

enum EnMainWeaponVar {
	enMainWeaponVar_M4A1,
	enMainWeaponVar_AK47,
	enMainWeaponVar_ACR,
	enMainWeaponVar_SCAR,
	enMainWeaponVar_HAMR,
	enMainWeaponVar_G36,
	enMainWeaponVar_L86A2,
	enMainWeaponVar_None
};

enum EnSubWeaponVar {
	enSubWeaponVar_GZ75,
	enSubWeaponVar_TEC9,
	enSubWeaponVar_M1911,
	enSubWeaponVar_R8,
	enSubWeaponVar_None
};

enum EnWeaponType {
	enWeaponType_Main,
	enWeaponType_Sub,
	enWeaponType_Special,
	enWeaponType_None
};

enum EnBulletType {
	EnBulletType_Normal,
	EnBulletType_Rocket
};

enum EnScoreType {
	enScoreType_EliminateZombie = 0,
	enScoreType_None,
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
		enCollision_Head,
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