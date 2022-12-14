#ifndef ___SCENEMANAGER___
#define ___SCENEMANAGER___

#include "stdafx.h"
#include "Scene.h"

class SceneManager {
private:
	static bool isEnd;

	Scene* nowScene = nullptr;
	Scene* AfterScene = nullptr;

	SceneManager() {}
	SceneManager(const SceneManager& ref) {}

	static SceneManager* m_Instance;

public:
	~SceneManager();
	static SceneManager& GetInstance();
	
	void Update();
	static void Release();
	static void StopEngine();
	inline static bool isRunning();

	template<typename T, enable_if_t<is_base_of_v<Scene, T>, bool> = true>
	inline void ChangeScene();
	Scene* GetNowScene();
};

inline void SceneManager::StopEngine() {
	isEnd = true;
}
inline bool SceneManager::isRunning() {
	return !isEnd;
}

template<typename T, enable_if_t<is_base_of_v<Scene, T>, bool>>
inline void SceneManager::ChangeScene() {
	if (nowScene) {
		AfterScene = new T;
		AfterScene->Awake();
		nowScene->isEnd = true;
	}
	else {
		nowScene = new T;
		nowScene->Awake();
	}
}

#endif // !___SCENEMANAGER___
