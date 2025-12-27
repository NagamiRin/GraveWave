/**
 * SceneManager.cpp
 *
 * ゲーム全体のシーンの進行を管理するクラス
 */
#include "stdafx.h"
#include "SceneManager.h"
#include "src/Scene/IScene.h"
#include "src/Scene/TitleScene.h"
#include "src/Scene/InGameScene.h"
#include "src/Scene/ResultScene.h"
#include "src/Scene/LoadingScreen.h"

#ifdef K2_DEBUG
#include "src/Scene/DebugScene.h"
#endif


namespace {
    constexpr float SWITCH_SCENE_TIME = 0.1f;
}


namespace nsApp
{
    namespace nsScene {

        SceneManager* SceneManager::m_instance = nullptr;


        SceneManager::SceneManager()
        {
            //ロード画面生成
            m_loadingScreen = NewGO<LoadingScreen>(enGameObjectPriority_Loading, "LoadingScreen");

            //各シーン追加
            AddSceneMap<TitleScene>();
            AddSceneMap<InGameScene>();
            AddSceneMap<ResultScene>();
#ifdef K2_DEBUG
            AddSceneMap<DebugScene>();
#endif
        }


        SceneManager::~SceneManager()
        {           
            //ロード画面削除
            DeleteGO(m_loadingScreen);
        }


        void SceneManager::Update()
        {
            if (m_currentScene) {  
                m_currentScene->Update();
                if (m_currentScene->RequestScene(m_requestSceneID)) {
                    //ロード画面描画
                    m_loadingScreen->SetDraw(true);

                    //シーン切り替えのフラグを立てる
                    m_isSwitchScene = true;                   
                }
            }

            if (m_isSwitchScene) {
                //次のシーン生成にディレイをかける
                //NOTO:そのままだと、ロード画面が描画される前に、シーンの生成処理が走ってしまう
                m_elapsedTime += g_gameTime->GetFrameDeltaTime();

                if (m_elapsedTime >= SWITCH_SCENE_TIME) {
                    //次のシーンへ
                    delete m_currentScene;
                    CreateScene(m_requestSceneID);

                    //ロード画面を消す
                    m_loadingScreen->SetDraw(false);

                    //経過時間リセット
                    m_elapsedTime = 0.0f;

                    //シーン切り替えのフラグをさげる
                    m_isSwitchScene = false;                    
                }
            }
        }


        void SceneManager::CreateScene(const uint32_t id)
        {
            auto it = m_sceneMap.find(id);
            if (it == m_sceneMap.end()) {
                K2_ASSERT(false, "新規シーンが追加されていません。\n");
            }
            auto& createSceneFunc = it->second; 
            m_currentScene = createSceneFunc();
            m_currentScene->Start();
        }


        /**************************************************************/


        SceneManagerObject::SceneManagerObject()
        {
            SceneManager::CreateInstance();
        }


        SceneManagerObject::~SceneManagerObject()
        {
            SceneManager::DeleteInstance();
        }


        bool SceneManagerObject::Start()
        {
#if 0
            SceneManager::GetInstance()->CreateScene(DebugScene::ID());
#endif
#if 1
            //最初のシーンを生成
            SceneManager::GetInstance()->CreateScene(TitleScene::ID());
#endif
            return true;
        }


        void SceneManagerObject::Update()
        {
            SceneManager::GetInstance()->Update();
        }
    }
}