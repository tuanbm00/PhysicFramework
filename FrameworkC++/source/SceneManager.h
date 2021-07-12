#ifndef _SCENE_MANAGER_
#define _SCENE_MANAGER_

#include "Object.h"
#include <vector>

class SceneManager 
{
private:
	static SceneManager* s_Instance;
	int ms_iNumberObj;
	int m_iIdMove;
	int m_iOldX;
	int m_iOldY;
	float m_iOldDeltaX;
	float m_iOldDeltaY;
	std::vector<Object*> m_aObject;
public:	
	SceneManager();
	~SceneManager();
	void Update(float frameTime);
	void Render();
	void AddObject(Object *object);
	void Init();
	void EndMove();
	void CheckPointInList(int x, int y);
	void SetNewState(int x, int y);
	void SetEndState(int x, int y);
	void CheckCollisionInList(float frameTime);
	static SceneManager* GetInstance();
};

#endif
