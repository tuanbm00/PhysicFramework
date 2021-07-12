#include "Object.h"
#include "VideoDriver.h"
#include <iostream>

Object::Object()
{
	m_fVX = 0;
	m_fVY = 0;
}

Object::~Object()
{

}


void Object::Update(float frameTime)
{
	
}

void Object::SetVelocity(float fVelocity) {
	m_fVelocity = fVelocity;
}


// Rectangle
Rectangle::Rectangle() {
	
}

Rectangle::Rectangle(int ID) {
	m_iObjID = 1;
}

Rectangle::~Rectangle() {

}

void Rectangle::Render() {
	VideoDriver::GetInstance()->FillRect((int) m_afPosition[0], (int)m_afPosition[1], (int)m_afPosition[2], (int)m_afPosition[3]);
}

void Rectangle::SetPosition(int x1, int y1, int width, int height) {
	Rectangle::m_afPosition[0] = (float) x1;
	Rectangle::m_afPosition[1] = (float) y1;
	Rectangle::m_afPosition[2] = (float) width;
	Rectangle::m_afPosition[3] = (float) height;
}

bool Rectangle::CheckPointInObj(float x, float y) {
	if(x < m_afPosition[0])
		return false;
	if(x > m_afPosition[0] + m_afPosition[2])
		return false;
	if(y < m_afPosition[1])
		return false;
	if(y > m_afPosition[1] + m_afPosition[3])
		return false;
	return true;
}


// Circle
Circle::Circle() {
	
}

Circle::Circle(int ID) {
	m_iObjID = 2;
}

Circle::~Circle() {

}

void Circle::Render() {
	VideoDriver::GetInstance()->DrawCircle(m_afPosition[0], m_afPosition[1], m_afPosition[2]);
}

void Circle::SetPosition(float cx, float cy, float radius) {
	Circle::m_afPosition[0] = cx;
	Circle::m_afPosition[1] = cy;
	Circle::m_afPosition[2] = radius;
	Circle::m_afPosition[3] = 0;
}

bool Circle::CheckPointInObj(float x, float y) {
	float d = (m_afPosition[0] - x)*(m_afPosition[0] - x) + (m_afPosition[1] - y)*(m_afPosition[1] - y);
	if(d > m_afPosition[2]*m_afPosition[2])
		return false;
	return true;
}


// Plane
Plane::Plane() {
	
}

Plane::Plane(int ID) {
	m_iObjID = 3;
}

Plane::~Plane() {

}

void Plane::Render() {
	VideoDriver::GetInstance()->DrawRect((int)m_afPosition[0], (int)m_afPosition[1], (int)m_afPosition[2], (int)m_afPosition[3]);
}

void Plane::SetPosition(int x1, int y1, int x2, int y2) {
	Plane::m_afPosition[0] = (float) x1;
	Plane::m_afPosition[1] = (float) y1;
	Plane::m_afPosition[2] = (float) x2;
	Plane::m_afPosition[3] = (float) y2;
}

bool Plane::CheckPointInObj(float x, float y) {
	return false;
}
