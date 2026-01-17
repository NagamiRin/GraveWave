#pragma once
#include "src/Json/json.hpp"
#include <iostream>
#include <fstream>


#ifdef K2_DEBUG
#define APP_PARAM_HOT_RELOAD
#endif


/**
 * NOTE: すべてのパラメーターに付ける
 */
#ifdef APP_PARAM_HOT_RELOAD

#define appParameter(name)\
public:\
static constexpr uint32_t ID() {return appHash32(#name);}\
std::function<void(const nlohmann::json& j, name& p)> load;

#else 

#define appParameter(name)\
public:\
static constexpr uint32_t ID() {return appHash32(#name);}

#endif 


 /** 基底クラス。必ず継承すること！ */
struct IMasterParameter
{
#ifdef APP_PARAM_HOT_RELOAD
    virtual void Load(const nlohmann::json& j) {};
    std::string m_path;         // パラメーターのファイルパス（ホットリロード用）
    time_t m_lastWriteTime;     // 最終更新時刻
#endif // APP_PARAM_HOT_RELOAD
};

/** プレイヤーのステータス */
struct MasterPlayerStatus : public IMasterParameter
{
    appParameter(MasterPlayerStatus);

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif // APP_PARAM_HOT_RELOAD
    //
    float m_moveSpeed;
};


//エネミーのステータス
struct MasterEnemyStatus : public IMasterParameter
{
    appParameter(MasterEnemyStatus);

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif // APP_PARAM_HOT_RELOAD
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

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif // APP_PARAM_HOT_RELOAD
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

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif // APP_PARAM_HOT_RELOAD
    //
    std::string m_gunName;
    uint8_t m_damage;
    uint8_t m_maxAmmo;
    float m_bulletSpeed;
    float m_currentFireCoolTime;
    float m_reloadTime;
    float m_switchTime;
    float m_newPositionX;
    float m_newPositionY;
    float m_newPositionZ;
};

struct MasterSubWeaponParameter :public IMasterParameter
{
    appParameter(MasterSubWeaponParameter);

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif // APP_PARAM_HOT_RELOAD
    //
    std::string m_gunName;
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

struct MasterShopParameter :public IMasterParameter
{
    appParameter(MasterShopParameter);

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif // APP_PARAM_HOT_RELOAD
    //
    uint16_t m_GZ75;
    uint16_t m_R8;
    uint16_t m_M1911;
    uint16_t m_TEC9;
    uint16_t m_ACR;
    uint16_t m_AK47;
    uint16_t m_G36;
    uint16_t m_HAMR;
    uint16_t m_L86A2;
    uint16_t m_M4A1;
    uint16_t m_SCAR;
};


//ボスが投げる岩のステータス
struct MasterStoneParameter : public IMasterParameter
{
    appParameter(MasterStoneParameter);

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif // APP_PARAM_HOT_RELOAD
    //
    float m_altitude;
    float m_landingTime;
    float m_rotSpeed;
    uint16_t m_maxDurability;
    uint8_t m_divisionNum;
};

//岩の破壊表現ステータス
struct MasterBreakStoneParameter : public IMasterParameter
{
    appParameter(MasterBreakStoneParameter);

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif // APP_PARAM_HOT_RELOAD
    //
    float m_altitude;
    float m_landingTime;
    float m_rotSpeed;
};


//弾丸のステータス
struct MasterBulletStatus : public IMasterParameter
{
    appParameter(MasterBulletStatus);

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif // APP_PARAM_HOT_RELOAD
    //
    int m_damage;
    int m_maxAmmo;
    float m_bulletSpeed;    
};


//防壁のステータス
struct MasterWallParameter : public IMasterParameter
{
    appParameter(MasterWallParameter);

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif // APP_PARAM_HOT_RELOAD
    //
    uint16_t m_maxDurability;
};


//カメラのパラメーター
struct MasterCameraParameter :public IMasterParameter
{
    appParameter(MasterCameraParameter);

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif // APP_PARAM_HOT_RELOAD
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

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif // APP_PARAM_HOT_RELOAD

    uint8_t m_maxEnemyNum;
    uint8_t m_clearWaveNum;
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

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif // APP_PARAM_HOT_RELOAD

    float m_spawnPositionZ;
    float m_minXPosition;
    float m_maxXPosition;
};


//ウェーブのパラメーター
struct MasterWaveParameter :public IMasterParameter
{
    appParameter(MasterWaveParameter);

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif // APP_PARAM_HOT_RELOAD

    uint16_t m_leftCount;
    uint16_t m_centerCount;
    uint16_t m_rightCount;
    bool m_isBossSpawn;
    float m_spawnInterval;
};


//準備フェーズのパラメーター
struct MasterPreparationParameter :public IMasterParameter
{
    appParameter(MasterPreparationParameter);

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif // APP_PARAM_HOT_RELOAD

    float m_toCountDownTime;
    float m_specifiedSeconds;
};


//スコアのパラメーター
struct MasterScoreParameter :public IMasterParameter
{
    appParameter(MasterScoreParameter);

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif // APP_PARAM_HOT_RELOAD

    uint8_t m_eliminateZombieScore;
};


//ショップUIのパラメーター
struct MasterShopUIParameter :public IMasterParameter
{
    appParameter(MasterShopUIParameter);

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif

    float m_subWeaponPositionX;
    float m_subWeaponPositionY;
    float m_subWeaponWidth;
    float m_subWeaponHeight;
    float m_mainWeaponPositionX;
    float m_mainWeaponPositionY;
    float m_mainWeaponWidth;
    float m_mainWeaponHeight;
};


//ショップUIのアイテムごとのパラメーター
struct MasterShopColumnUIParameter :public IMasterParameter
{
    appParameter(MasterShopColumnUIParameter);

#ifdef APP_PARAM_HOT_RELOAD
    void Load(const nlohmann::json& j) override
    {
        load(j, *this);
    }
#endif

    float m_columnPositionX;
    float m_columnPositionY;
    float m_columnWidth;
    float m_columnHeight;
    float m_pricePositionX;
    float m_pricePositionY;
    uint16_t m_price;
    std::string m_itemName;
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
    void Update()
    {
#ifdef APP_PARAM_HOT_RELOAD
        for (auto paramPair : m_parameterMap)
        {
            for (auto param : paramPair.second)
            {
                if (CheckFileModified(param))
                {
                    std::ifstream file(param->m_path);
                    if (!file.is_open())
                    {
                        return;
                    }

                    nlohmann::json jsonRoot;
                    file >> jsonRoot;

                    ParameterVector parameters;

                    for (const auto& j : jsonRoot)
                    {
                        param->m_lastWriteTime = GetFileLastWriteTime(param->m_path.c_str());
                        param->Load(j);
                    }
                }
            }
        }
#endif
    }

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
#ifdef APP_PARAM_HOT_RELOAD
            parameter->m_path = std::string(path);
            parameter->m_lastWriteTime = GetFileLastWriteTime(path);
            parameter->load = func;
#endif
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

#ifdef APP_PARAM_HOT_RELOAD
    /**
     * ファイル更新日時取得
     */
    static time_t GetFileLastWriteTime(const char* path)
    {
        struct stat result;
        // stat関数でファイル情報を取得 (0なら成功)
        if (stat(path, &result) == 0) {
            return result.st_mtime;
        }
        return 0;
    }


    /**
     * ファイル更新チェック
     */
    static bool CheckFileModified(const IMasterParameter* param)
    {
        if (GetFileLastWriteTime(param->m_path.c_str()) > param->m_lastWriteTime)
        {
            return true;
        }
        return false;
    }

#endif // APP_PARAM_HOT_RELOAD


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