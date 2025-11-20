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


namespace nsApp
{
    namespace nsScene {

        SceneManager* SceneManager::m_instance = nullptr;


        SceneManager::SceneManager()
        {
            //各シーン追加
            AddSceneMap<TitleScene>();
            AddSceneMap<InGameScene>();
            AddSceneMap<ResultScene>();
        }


        SceneManager::~SceneManager()
        {           
        }


        void SceneManager::Update()
        {           
            if (m_currentScene) {
                uint32_t nextSceneId;
                m_currentScene->Update();
                if (m_currentScene->RequestScene(nextSceneId)) {
                    delete m_currentScene;
                    CreateScene(nextSceneId);
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
            //最初のシーンを生成
            SceneManager::GetInstance()->CreateScene(TitleScene::ID());

            return true;
        }


        void SceneManagerObject::Update()
        {
            SceneManager::GetInstance()->Update();
        }
    }
}