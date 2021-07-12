#ifndef _COLLISION_MANAGER_
#define _COLLISION_MANAGER_

#include "Object.h"

class CollisionManager
{
private:
	static CollisionManager* s_Instance;
public:
	CollisionManager();
	~CollisionManager();
	bool CheckCollision(Object *object1, Object *object2);
	bool CheckCollision(Rectangle *m_rectangle1, Rectangle *m_rectangle2);
	bool CheckCollision(Circle *m_circle1, Circle *m_circle2);
	bool CheckCollision(Rectangle *m_rectangle, Circle *m_circle);
	bool CheckCollision(Rectangle *m_rectangle,Plane *m_plane);
	bool CheckCollision(Circle *m_circlee, Plane *m_plane);
	static CollisionManager* GetInstance();
};


#endif