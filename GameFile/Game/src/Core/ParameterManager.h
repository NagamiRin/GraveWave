#pragma once
#include "src/Json/json.hpp"
#include <iostream>
#include <fstream>


/**
 * NOTE: すべてのパラメーターに付ける
 */
#define appParameter(name)\
public:\
 static constexpr uint32_t ID() { return appHash32(#name); }


 /** 基底クラス。必ず継承すること！ */
struct IMasterParameter {};

/** プレイヤーのステータス */
struct MasterPlayerStatus : public IMasterParameter
{
    appParameter(MasterPlayerStatus);
    //
    float m_moveSpeed;
};


//エネミーのステータス
struct MasterEnemyStatus : public IMasterParameter
{
    appParameter(MasterEnemyStatus);
    //
    uint16_t m_hp;
    uint16_t m_attackPower;
    float m_attackFrequency;
    float m_attackRange;
    float m_moveSpeed;
};

//ボスステータス
struct MasterBossStatus : public IMasterParameter
{
    appParameter(MasterBossStatus);
    //
    uint16_t m_hp;
    uint16_t m_attackPower;
    float m_attackFrequency;
    float m_attackRange;
    float m_moveSpeed;
};


// 銃のステータス
struct MasterGunParameter :public IMasterParameter
{
    appParameter(MasterGunParameter);
    //
    uint8_t m_damage;
    uint8_t m_maxAmmo;
    float m_bulletSpeed;
    float m_fireCoolTime;
    float m_reloadTime;
    float m_switchTime;
    float m_newPositionX;
    float m_newPositionY;
    float m_newPositionZ;
};


//ボスが投げる岩のステータス
struct MasterStoneParameter : public IMasterParameter
{
    appParameter(MasterStoneParameter);
    //
    float m_altitude;
    float m_landingTime;
    float m_rotSpeed;
    uint16_t m_maxDurability;
};


//弾丸のステータス
struct MasterBulletStatus : public IMasterParameter
{
    appParameter(MasterBulletStatus);
    //
    int m_damage;
    int m_maxAmmo;
    float m_bulletSpeed;    
};


//防壁のステータス
struct MasterWallParameter : public IMasterParameter
{
    appParameter(MasterWallParameter);
    //
    uint16_t m_maxDurability;
};


//カメラのパラメーター
struct MasterCameraParameter :public IMasterParameter
{
    appParameter(MasterCameraParameter);
    //
    float m_cameraNear;
    float m_cameraFar;
    float m_initialCameraPositionX;
    float m_initialCameraPositionY;
    float m_initialCameraPositionZ;
    float m_initialTargetPositionX;
    float m_initialTargetPositionY;
    float m_initialTargetPositionZ;
    float m_cameraSensitivity;
};


//インゲーム共通のパラメーター
struct MasterBattleParameter :public IMasterParameter
{
    appParameter(MasterBattleParameter);

    uint8_t m_maxEnemyNum;
    float m_baseSpawnTime;
    float m_spawnPositionZ;
    float m_besideLimitPosition;
    float m_verticalLimitAngle;
    float m_horizontalLimitAngle;
    float m_gravityAmount;
    float m_enemyStopPosition;
};


//スポナーのパラメーター
struct MasterSpawnerParameter :public IMasterParameter
{
    appParameter(MasterSpawnerParameter);

    float m_spawnPositionZ;
    float m_minPos;
    float m_maxPos;
};


//ウェーブのパラメーター
struct MasterWaveParameter :public IMasterParameter
{
    appParameter(MasterWaveParameter);

    uint16_t m_leftCount;
    uint16_t m_centerCount;
    uint16_t m_rightCount;
    uint8_t m_bossCount;
    float m_spawnInterval;
};


//準備フェーズのパラメーター
struct MasterPreparationParameter :public IMasterParameter
{
    appParameter(MasterPreparationParameter);

    float m_toCountDownTime;
    float m_specifiedSeconds;
};


//スコアのパラメーター
struct MasterScoreParameter :public IMasterParameter
{
    appParameter(MasterScoreParameter);

    uint8_t m_eliminateZombieScore;
};


//ショップUIのパラメーター
struct MasterShopUIParameter :public IMasterParameter
{
    appParameter(MasterShopUIParameter);

    float m_backWidth;
    float m_backHeight;
    float m_iconWidth;
    float m_iconHeight;
    float m_positionX;
    float m_positionY;
    float m_stringPositionX;
    float m_stringPositionY;
    uint16_t m_price;
    std::string m_weaponName;
};


/** defineの使用終了 */
#undef appParameter


/**
 * パラメーター管理クラス
 */
class ParameterManager
{
private:
    // 複数パラメーターがあっても良いように
    using ParameterVector = std::vector<IMasterParameter*>;
    // 各パラメーターごとに保持する
    using ParameterMap = std::map<uint32_t, ParameterVector>;


private:
    ParameterMap m_parameterMap;  // パラメーターを保持

private:
    ParameterManager();
    ~ParameterManager();

public:
    /// <summary>
    /// パラメーター読み込み
    /// NOTE: Unloadも呼ぶことを忘れないように
    ///       第2引数のラムダ式でテンプレートで指定する型の情報に変換する
    /// </summary>
    template <typename T>
    void LoadParameter(const char* path, const std::function<void(const nlohmann::json& j, T& p)>& func)
    {
        std::ifstream file(path);
        if (!file.is_open()) {
            return;
        }

        nlohmann::json jsonRoot;
        file >> jsonRoot;

        std::vector<IMasterParameter*> parameters;
        for (const auto& j : jsonRoot) {
            T* parameter = new T();
            func(j, *parameter);
            parameters.push_back(static_cast<IMasterParameter*>(parameter));
        }

        m_parameterMap.emplace(T::ID(), parameters);
    }


    /// <summary>
    /// パラメーター解放
    /// </summary>
    template <typename T>
    void UnloadParameter()
    {
        auto it = m_parameterMap.find(T::ID());
        if (it != m_parameterMap.end()) {
            auto& parameters = it->second;
            for (auto* p : parameters) {
                delete p;
            }
            m_parameterMap.erase(it);
        }
    }

    /// <summary>
    /// 1つだけパラメーターを取得する
    /// </summary>
    template <typename T>
    const T* GetParameter(const int index = 0) const
    {
        const auto parameters = GetParameters<T>();
        if (parameters.size() == 0) { return nullptr; }
        if (parameters.size() <= index) { return nullptr; }
        return parameters[index];
    }
    /// <summary>
    /// 複数パラメーターを取得する
    /// </summary>
    template <typename T>
    inline const std::vector<T*> GetParameters() const
    {
        std::vector<T*> parameters;
        auto it = m_parameterMap.find(T::ID());
        if (it != m_parameterMap.end()) {
            for (auto* parameter : it->second) {
                parameters.push_back(static_cast<T*>(parameter));
            }
        }
        return parameters;
    }
    /// <summary>
    /// パラメーターをラムダ式で回すForEach
    /// </summary>
    template <typename T>
    void ForEach(std::function<void(const T&)> func) const
    {
        const std::vector<T*> parameters = GetParameters<T>();
        for (const T* paramter : parameters) {
            func(*paramter);
        }
    }




    /**
     * シングルトン用
     */
public:
    /// <summary>
    /// インスタンスを作る
    /// </summary>
    static void CreateInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new ParameterManager();
        }
    }

    /// <summary>
    /// インスタンスを取得
    /// </summary>
    static ParameterManager& Get()
    {
        return *m_instance;
    }

    /// <summary>
    /// インスタンスを破棄
    /// </summary>
    static void DestroyInstance()
    {
        if (m_instance != nullptr)
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }

private:
    static ParameterManager* m_instance; //シングルトンインスタンス
};

