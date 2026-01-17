/**
 * Zombie.cpp
 *
 * ゾンビ（通常）クラス
 */
#include "stdafx.h"
#include "Zombie.h"
#include "src/Actor/Enemy/ZombieStateMachine.h"
#include "src/Collision/CollisionManager.h"
#include "src/Core/ModelLOD.h"
#include "src/Sound/SoundManager.h"


namespace {
    const Vector3 NEW_SCALE = Vector3{ 0.3f,0.3f,0.3f };
    constexpr float LOD_SWITCH_DISTANCE = 700.0f;
    constexpr float COLLISION_YPOSITION = 25.0f;    
    constexpr float GROAN_ZPOSITION = 500.0f;   
    constexpr float GROAN_FREQUECY = 10.0f;   
    constexpr float COLLISION_RADISU = 10.0f;
    constexpr float COLLISION_HEIGHT = 30.0f;
}

namespace
{
    constexpr const char* MODEL_ASSET_PATH_LIST[] =
    {
        //"Assets/ModelData/Zombie/Default/LowModel.tkm",
        "Assets/ModelData/Zombie/Default/MidModel.tkm",
        "Assets/ModelData/Zombie/Default/HighModel.tkm"
    };

    //アニメーション情報の構造体
    struct AnimationClipInfo
    {
        //モデルのアセットパス
        const char* m_assetPath;
        //アニメーションのループフラグ
        bool m_isLoop;
        //
        AnimationClipInfo(const char* path, const bool isLoop)
            : m_assetPath(path)
            , m_isLoop(isLoop)
        {
        }
    };

    //アニメーション情報の構造体
    static const AnimationClipInfo ANIMATION_CLIP_INFO_LIST[] = {
        AnimationClipInfo("Assets/AnimData/Zombie/Attack.tka", false),  //攻撃
        AnimationClipInfo("Assets/AnimData/Zombie/Death.tka", false),   //死亡
        AnimationClipInfo("Assets/AnimData/Zombie/GetUp.tka", false),   //起き上がり
        AnimationClipInfo("Assets/AnimData/Zombie/Hit.tka", false),     //被弾
        AnimationClipInfo("Assets/AnimData/Zombie/Idle.tka", true),     //待機
        AnimationClipInfo("Assets/AnimData/Zombie/Walk.tka", true),     //歩き
    };
}


namespace nsApp
{
    namespace nsActor
    {
        namespace nsEnemy
        {
            Zombie::Zombie()
            {
                //自身のステータスを生成
                m_status = new ZombieStatus();

                //自身のステートマシンを生成
                m_stateMachine = std::make_unique<ZombieStateMachine>();
                dynamic_cast<ZombieStateMachine*>(m_stateMachine.get())->Setup(this, GetStatus());
            }


            Zombie::~Zombie()
            {
                //ステータスを削除
                delete m_status;
                m_status = nullptr;

                //LOD削除
                delete m_modelLOD;
            }


            bool Zombie::Start()
            {
                //大きさを設定
                m_transform.m_localScale = Vector3(NEW_SCALE);

                //向きを設定
                SetDirection(Vector3(0.0f, 0.0f, -1.0f));

                //LODの初期設定
                m_modelLOD = new nsCore::ModelLOD();                
                m_modelLOD->Initialize(LOD_SWITCH_DISTANCE, [=](int index, nsCore::ModelLOD::AnimationClipInfo* animationClipInfo)
                    {
                        const char* assetPath = MODEL_ASSET_PATH_LIST[index];
                        ModelRender* model = new ModelRender();
                        if (index == 0) {
                            //モデルの初期化
                            model->Init(assetPath);
                        }
                        else
                        {
                            //アニメーションの数
                            const int size = ARRAYSIZE(ANIMATION_CLIP_INFO_LIST);

                            //アニメーションの数だけアニメーションクリップを生成
                            animationClipInfo->m_animationClips = new AnimationClip[size];

                            //アニメーションクリップに情報を入れていく
                            for (int i = 0; i < size; ++i) {
                                const auto animationInfo = ANIMATION_CLIP_INFO_LIST[i];
                                animationClipInfo->m_animationClips[i].Load(animationInfo.m_assetPath);
                                animationClipInfo->m_animationClips[i].SetLoopFlag(animationInfo.m_isLoop);
                            }

                            //モデルの初期化
                            model->Init(assetPath, animationClipInfo->m_animationClips, size);
                        }

                        return model;

                    }, 2);                

                return true;
            }
            

            void Zombie::Update()
            {
                //ゾンビのうめき声を再生
                PlayGroan();

                //transformの更新
                m_transform.UpdateTransform();


                //コリジョン（胴体）の更新
                m_collisionPosition = m_transform.m_position + Vector3(0.0f, COLLISION_YPOSITION, 0.0f);
                m_collisionObject->SetPosition(m_collisionPosition);
                m_collisionObject->Update();

                //コリジョン（頭部）の更新
                m_headCollision->SetPosition(m_collisionPosition);
                m_headCollision->Update();

                //LODの更新
                m_modelLOD->SetPosition(m_transform.m_localPosition);
                m_modelLOD->SetRotation(m_transform.m_localRotation);
                m_modelLOD->SetScale(m_transform.m_localScale);
                m_modelLOD->Update();

                //ステートマシンの更新
                m_stateMachine->Update();

                //親クラスの更新
                SuperClass::Update();
            }


            void Zombie::Render(RenderContext& rc)
            {
                //モデルを描画
                m_modelLOD->Render(rc);
            }


            void Zombie::PlayGroan()
            {
                //一定以上近づいたら実行
                if (m_transform.m_localPosition.z >= GROAN_ZPOSITION) return;

                //時間を数える
                m_groanTime += g_gameTime->GetFrameDeltaTime();

                //一定時間ごとにうめき声を再生
                if (m_groanTime >= GROAN_FREQUECY) {
                    //SoundManager::Get().PlaySE(enSoundKind_ZombieGroan);
                    m_groanTime = 0.0f;
                }
            }


            void Zombie::Initialize(const Vector3& initializePosition)
            {
                //HPをリセット
                GetStatus()->ResetHP();

                //位置をリセット
                SetLocalPosition(initializePosition);                

                //コリジョン（胴体）を作る
                m_collisionObject = CollisionHitManager::Get().CreateCollisionObject(ID(), this, m_collisionPosition, GetRotation(), COLLISION_RADISU, COLLISION_HEIGHT);
                m_collisionObject->GetbtCollisionObject().setUserIndex(nsApp::enCollision_Enemy);

                //コリジョン（頭部）を作る）
                m_headCollision = CollisionHitManager::Get().CreateCollisionObject(ID(), this, m_collisionPosition, GetRotation(), 20.0f);
                m_headCollision->GetbtCollisionObject().setUserIndex(nsApp::enCollision_Head);               
            }


            void Zombie::Destruction()
            {
                //コリジョンを消す
                //（一応コリジョンがあるか確認）
                if (!CollisionHitManager::Get().CheckCollision(this)) return;
                CollisionHitManager::Get().DeleteCollisionObject(this);

                //攻撃をしない状態に
                SetAttackState(false);

                //LODをリセット
                m_modelLOD->ResetLOD();
            }


            nsCore::ModelLOD* Zombie::GetModel()
            {
                return m_modelLOD;
            }
        }
    }
}