/**
 * Zombie.cpp
 *
 * ゾンビ（雑魚）クラス
 */
#include "stdafx.h"
#include "Zombie.h"
#include "src/Actor/Enemy/ZombieStateMachine.h"
#include "src/Collision/CollisionManager.h"
#include "src/Core/ModelLOD.h"


namespace
{
    constexpr const char* MODEL_ASSET_PATH_LIST[] =
    {
        "Assets/ModelData/Zombie/Default/LOD1.tkm",
        "Assets/ModelData/Zombie/Default/Default.tkm"
    };

    struct AnimationClipInfo
    {
        const char* m_assetPath;
        bool m_isLoop;
        //
        AnimationClipInfo(const char* path, const bool isLoop)
            : m_assetPath(path)
            , m_isLoop(isLoop)
        {
        }
    };

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
                m_transform.m_localScale = Vector3(0.3f, 0.3f, 0.3f);
                SetDirection(Vector3(0.0f, 0.0f, -1.0f));

                //LODの初期設定
                m_modelLOD = new nsCore::ModelLOD();
                
                m_modelLOD->Initialize(500.0f, [=](int index, nsCore::ModelLOD::AnimationClipInfo* animationClipInfo)
                    {
                        const char* assetPath = MODEL_ASSET_PATH_LIST[index];
                        ModelRender* model = new ModelRender();
                        if (index == 0) {
                            model->Init(assetPath);
                        }
                        else
                        {
                            const int size = ARRAYSIZE(ANIMATION_CLIP_INFO_LIST);
                            animationClipInfo->m_animationClips = new AnimationClip[size];
                            for (int i = 0; i < size; ++i) {
                                const auto animationInfo = ANIMATION_CLIP_INFO_LIST[i];
                                animationClipInfo->m_animationClips[i].Load(animationInfo.m_assetPath);
                                animationClipInfo->m_animationClips[i].SetLoopFlag(animationInfo.m_isLoop);
                            }
                            model->Init(assetPath, animationClipInfo->m_animationClips, size);
                        }
                        return model;
                    }, 2);                

                return true;
            }
            

            void Zombie::Update()
            {
                m_transform.UpdateTransform();

                m_collisionPosition = m_transform.m_position + Vector3(0.0f, 25.0f, 0.0f);
                m_collisionObject->SetPosition(m_collisionPosition);
                m_collisionObject->Update();
                m_collisionObject->GetbtCollisionObject().setUserIndex(nsApp::enCollision_Enemy);

                //LODのいろいろ更新
                m_modelLOD->SetPosition(m_transform.m_localPosition);
                m_modelLOD->SetRotation(m_transform.m_localRotation);
                m_modelLOD->SetScale(m_transform.m_localScale);
                m_modelLOD->Update();

                m_stateMachine->Update();

                SuperClass::Update();
            }


            void Zombie::Render(RenderContext& rc)
            {
                m_modelLOD->Render(rc);
            }


            void Zombie::Initialize(const Vector3& initializePosition)
            {
                GetStatus()->ResetHP();
                SetLocalPosition(initializePosition);                

                m_collisionObject = CollisionHitManager::Get().CreateCollisionObject(ID(), this, m_collisionPosition, GetRotation(), 10.0f, 30.0f);
                m_collisionObject->GetbtCollisionObject().setUserIndex(nsApp::enCollision_Enemy);
            }


            void Zombie::Destruction()
            {
                if (!CollisionHitManager::Get().CheckCollision(this)) return;
                CollisionHitManager::Get().DeleteCollisionObject(this);

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