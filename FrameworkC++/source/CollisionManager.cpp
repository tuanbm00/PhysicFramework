#include "CollisionManager.h"
#include <iostream>
#include "Object.h"

CollisionManager* CollisionManager::s_Instance = NULL;


CollisionManager::CollisionManager() {

}

CollisionManager::~CollisionManager() {

}

CollisionManager* CollisionManager::GetInstance()
{
	if (!s_Instance)
		s_Instance = new CollisionManager();
	return s_Instance;
}

bool CollisionManager::CheckCollision(Object *object1, Object *object2) {
	if (object1->m_iObjID * object2->m_iObjID == 1) {
		if (CheckCollision((Rectangle*)object1, (Rectangle*)object2)) {
			std::cout << "object collision detected" << std::endl;
			return true;
		}
	}
	if (object1->m_iObjID * object2->m_iObjID == 4) {
		if (CheckCollision((Circle*)object1, (Circle*)object2)) {
			std::cout << "object collision detected" << std::endl;
			return true;
		}
	}
	if (object1->m_iObjID * object2->m_iObjID == 2) {
		if(object1->m_iObjID == 1) {
			if (CheckCollision((Rectangle*)object1, (Circle*)object2)) {
				std::cout << "object collision detected" << std::endl;
				return true;
			}
		}
		else {
			if (CheckCollision((Rectangle*)object2, (Circle*)object1)) {
				std::cout << "object collision detected" << std::endl;
				return true;
			}
		}
	}
	if (object1->m_iObjID * object2->m_iObjID == 3) {
		if (object1->m_iObjID == 1) {
			if (CheckCollision((Rectangle*)object1, (Plane*)object2)) {
				std::cout << "edge collision detected" << std::endl;
				return true;
			}
		}
		else {
			if (CheckCollision((Rectangle*)object2, (Plane*)object1)) {
				std::cout << "edge collision detected" << std::endl;
				return true;
			}
		}
	}
	if (object1->m_iObjID * object2->m_iObjID == 6) {
		if (object1->m_iObjID == 2) {
			if (CheckCollision((Circle*)object1, (Plane*)object2)) {
				std::cout << "edge collision detected" << std::endl;
				return true;
			}
		}
		else {
			if (CheckCollision((Circle*)object2, (Plane*)object1)) {
				std::cout << "edge collision detected" << std::endl;
				return true;
			}
		}
	}
	return false;
}

bool CollisionManager::CheckCollision(Rectangle *m_rectangle1, Rectangle *m_rectangle2){
	float r1x1 = m_rectangle1->m_afPosition[0];
	float r1y1 = m_rectangle1->m_afPosition[1];
	float r1x2 = m_rectangle1->m_afPosition[0] + m_rectangle1->m_afPosition[2];
	float r1y2 = m_rectangle1->m_afPosition[1] + m_rectangle1->m_afPosition[3];
	float r2x1 = m_rectangle2->m_afPosition[0];
	float r2y1 = m_rectangle2->m_afPosition[1];
	float r2x2 = m_rectangle2->m_afPosition[0] + m_rectangle2->m_afPosition[2];
	float r2y2 = m_rectangle2->m_afPosition[1] + m_rectangle2->m_afPosition[3];
	if (m_rectangle1->CheckPointInObj(r2x1, r2y1))
		return true;
	if (m_rectangle1->CheckPointInObj(r2x1, r2y2))
		return true;
	if (m_rectangle1->CheckPointInObj(r2x2, r2y1))
		return true;
	if (m_rectangle1->CheckPointInObj(r2x2, r2y2))
		return true;
	if (m_rectangle2->CheckPointInObj(r1x1, r1y1))
		return true;
	if (m_rectangle2->CheckPointInObj(r1x1, r1y2))
		return true;
	if (m_rectangle2->CheckPointInObj(r1x2, r1y1))
		return true;
	if (m_rectangle2->CheckPointInObj(r1x2, r1y2))
		return true;
	return false;
}

bool CollisionManager::CheckCollision(Circle *m_circle1, Circle *m_circle2) {
	float d = (m_circle1->m_afPosition[0] - m_circle2->m_afPosition[0]) * (m_circle1->m_afPosition[0] - m_circle2->m_afPosition[0]) 
			+ (m_circle1->m_afPosition[1] - m_circle2->m_afPosition[1]) * (m_circle1->m_afPosition[1] - m_circle2->m_afPosition[1]);
	if (d < (m_circle1->m_afPosition[2] + m_circle2->m_afPosition[2]) *  (m_circle1->m_afPosition[2] + m_circle2->m_afPosition[2])) {
		return true;
	}
	return false;
}

bool CollisionManager::CheckCollision(Rectangle *m_rectangle, Circle *m_circle) {
	float x1 = m_rectangle->m_afPosition[0];
	float y1 = m_rectangle->m_afPosition[1];
	float x2 = m_rectangle->m_afPosition[0] + m_rectangle->m_afPosition[2];
	float y2 = m_rectangle->m_afPosition[1] + m_rectangle->m_afPosition[3];
	float cx = m_circle->m_afPosition[0];
	float cy = m_circle->m_afPosition[1];
	float r = m_circle->m_afPosition[2];
	if (m_circle->CheckPointInObj(x1, y1))
		return true;
	if (m_circle->CheckPointInObj(x1, y2))
		return true;
	if (m_circle->CheckPointInObj(x2, y1))
		return true;
	if (m_circle->CheckPointInObj(x2, y2))
		return true;
	if (m_rectangle->CheckPointInObj(cx, cy))
		return true;
	if (m_rectangle->CheckPointInObj(cx, cy + r))
		return true;
	if (m_rectangle->CheckPointInObj(cx, cy - r))
		return true;
	if (m_rectangle->CheckPointInObj(cx + r, cy))
		return true;
	if (m_rectangle->CheckPointInObj(cx - r, cy))
		return true;
	if (cx > x1 && cx < x2) {
		if(cy < y1 && cy + r > y2)
			return true;
		if(cy > y2 && cy - r < y1)
			return true;
	}
	if (cy > y1 && cy < y2) {
		if (cx < x1 && cx + r > x2)
			return true;
		if (cx > x2 && cx - r < x1)
			return true;
	}
	return false;
}

bool CollisionManager::CheckCollision(Rectangle *m_rectangle, Plane *m_plane) {
	float x1 = m_rectangle->m_afPosition[0];
	float y1 = m_rectangle->m_afPosition[1];
	float x2 = m_rectangle->m_afPosition[0] + m_rectangle->m_afPosition[2];
	float y2 = m_rectangle->m_afPosition[1] + m_rectangle->m_afPosition[3];
	float px1 = m_plane->m_afPosition[0];
	float py1 = m_plane->m_afPosition[1];
	float px2 = m_plane->m_afPosition[0] + m_plane->m_afPosition[2];
	float py2 = m_plane->m_afPosition[1] + m_plane->m_afPosition[3];

	if (x1 <= px1 && x2 >= px1) {
		if ((y1 >= py1 && y1 <= py2) || (y2 >= py1 && y2 <= py2)){
			m_rectangle->m_afPosition[0] = px1;
			m_rectangle->m_fVX = -m_rectangle->m_fVX;
			return true;
		}
	}
	if (x1 <= px2 && x2 >= px2) {
		if ((y1 >= py1 && y1 <= py2) || (y2 >= py1 && y2 <= py2)) {
			m_rectangle->m_afPosition[0] = px2 - x2 + x1;
			m_rectangle->m_fVX = -m_rectangle->m_fVX;
			return true;
		}
	}
	if (y1 <= py1 && y2 >= py1) {
		if ((x1 >= px1 && x1 <= px2) || (x2 >= px1 && x2 <= px2)) {
			m_rectangle->m_afPosition[1] = py1;
			m_rectangle->m_fVY = -m_rectangle->m_fVY;
			return true;
		}
	}
	if (y1 <= py2 && y2 >= py2) {
		if ((x1 >= px1 && x1 <= px2) || (x2 >= px1 && x2 <= px2)) {
			m_rectangle->m_afPosition[1] = py2 - y2 + y1;
			m_rectangle->m_fVY = -m_rectangle->m_fVY;
			if (m_rectangle->m_fVX*m_rectangle->m_fVX + m_rectangle->m_fVY*m_rectangle->m_fVY < 1000) {
				m_rectangle->m_fVX = 0;
				m_rectangle->m_fVY = 0;
			}
			return true;
		}
	}
	return false;
}

bool CollisionManager::CheckCollision(Circle *m_circle, Plane *m_plane) {
	float cx = m_circle->m_afPosition[0];
	float cy = m_circle->m_afPosition[1];
	float r = m_circle->m_afPosition[2];
	float x1 = m_plane->m_afPosition[0];
	float y1 = m_plane->m_afPosition[1];
	float x2 = m_plane->m_afPosition[0] + m_plane->m_afPosition[2];
	float y2 = m_plane->m_afPosition[1] + m_plane->m_afPosition[3];
	if (cx >= x1 && cx <= x2) {
		if (cy <= y2 && cy + r >= y2) {
			m_circle->m_afPosition[1] = y2 - r;
			m_circle->m_fVY = -m_circle->m_fVY;
			if (m_circle->m_fVX*m_circle->m_fVX + m_circle->m_fVY*m_circle->m_fVY < 500) {
				m_circle->m_fVX = 0;
				m_circle->m_fVY = 0;
			}
			return true;
		}
		if (cy >= y1 && cy - r <= y1){
			m_circle->m_afPosition[1] = y1 + r;
			m_circle->m_fVY = -m_circle->m_fVY;
			return true;
		}
	}
	if (cy >= y1 && cy <= y2) {
		if (cx <= x2 && cx + r >= x2){
			m_circle->m_afPosition[0] = x2 - r;
			m_circle->m_fVX = -m_circle->m_fVX;
			return true;
		}
		if (cx >= x1 && cx - r <= x1) {
			m_circle->m_afPosition[0] = x1 + r;
			m_circle->m_fVX = -m_circle->m_fVX;
			return true;
		}
	}
	return false;
}