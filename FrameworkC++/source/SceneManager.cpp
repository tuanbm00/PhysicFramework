#include "SceneManager.h"
#include "CollisionManager.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

SceneManager* SceneManager::s_Instance = NULL;

SceneManager::SceneManager()
{
	SceneManager::m_aObject.clear();
	SceneManager::ms_iNumberObj = 0;
	m_iIdMove = -1;
	this->Init();
}

SceneManager::~SceneManager()
{
	for (int i = 0;i < ms_iNumberObj;i++) {
		delete m_aObject[i];
	}
}

SceneManager* SceneManager::GetInstance()
{
	if (!s_Instance)
		s_Instance = new SceneManager();
	return s_Instance;
}

void SceneManager::Update(float frameTime)
{
	if (frameTime != 0) {
		m_iOldDeltaX = 2 * m_iOldDeltaX / frameTime;
		m_iOldDeltaY = 2 * m_iOldDeltaY / frameTime;
	}
	for (int i = 0;i < ms_iNumberObj;i++) {
		if(m_aObject[i]->m_iObjID != 3) {
			if (m_aObject[i]->m_fVX != 0 || m_aObject[i]->m_fVY != 0) {
				m_aObject[i]->m_afPosition[0] += m_aObject[i]->m_fVX * frameTime;
				m_aObject[i]->m_afPosition[1] += m_aObject[i]->m_fVY * frameTime;	
			}
			m_aObject[i]->m_fVY += 50 * frameTime;
			float ax = m_aObject[i]->m_fVX > 0 ? -0.2f : 0.2f;
			float ay = m_aObject[i]->m_fVY > 0 ? -10.0f : 10.0f;
     		m_aObject[i]->m_fVX += ax * frameTime;
			m_aObject[i]->m_fVY += ay * frameTime;
			if (m_aObject[i]->m_fVX >= 100) {
				m_aObject[i]->m_fVY = 100 * m_aObject[i]->m_fVY / m_aObject[i]->m_fVX;
				m_aObject[i]->m_fVX = 100;
			}
			if (m_aObject[i]->m_fVX <= -100) {
				m_aObject[i]->m_fVY = -100 * m_aObject[i]->m_fVY / m_aObject[i]->m_fVX;
				m_aObject[i]->m_fVX = -100;
			}
			if (m_aObject[i]->m_fVY >= 100) {
				m_aObject[i]->m_fVX = 100 * m_aObject[i]->m_fVX / m_aObject[i]->m_fVY;
				m_aObject[i]->m_fVY = 100;
			}
			if (m_aObject[i]->m_fVY <= -100) {
				m_aObject[i]->m_fVX = -100 * m_aObject[i]->m_fVX / m_aObject[i]->m_fVY;
				m_aObject[i]->m_fVY = -100;
			}
		}
	}
	CheckCollisionInList(frameTime);
	SceneManager::Render();
}

void SceneManager::Render()
{
	for (int i = 0;i < ms_iNumberObj;i++) {
		m_aObject[i]->Render();
	}
}

void SceneManager::AddObject(Object *object)
{
	SceneManager::m_aObject.push_back(object);
	SceneManager::ms_iNumberObj++;
}

void SceneManager::Init()
{
	string sLine;
	ifstream m_readFile ("SceneManager.txt");
	if (m_readFile.is_open()) {
		try
		{
			getline(m_readFile, sLine);
			while (getline(m_readFile, sLine)) {
				int ID = stoi(sLine.substr(4));
				getline(m_readFile, sLine);
				if (sLine.substr(6) == "RECT") {
					Rectangle *m_rectangle = new Rectangle(ID);
					getline(m_readFile, sLine);
					sLine = sLine.substr(10);
					int x1 = stoi(sLine.substr(0, sLine.find(",")));
					sLine = sLine.substr(sLine.find(" ") + 1);
					int y1 = stoi(sLine.substr(0, sLine.find(",")));
					sLine = sLine.substr(sLine.find(" ") + 1);
					int width = stoi(sLine.substr(0, sLine.find(",")));
					sLine = sLine.substr(sLine.find(" ") + 1);
					int height = stoi(sLine);
					getline(m_readFile, sLine);
					m_rectangle->SetVelocity((float)stoi(sLine.substr(10)));
					m_rectangle->SetPosition(x1, y1, width, height);
					SceneManager::AddObject(m_rectangle);
				}
				else if (sLine.substr(6) == "CIRCLE") {
					Circle *m_circle = new Circle(ID);
					getline(m_readFile, sLine);
					sLine = sLine.substr(10);
					float cx = (float)stoi(sLine.substr(0, sLine.find(",")));
					sLine = sLine.substr(sLine.find(" ") + 1);
					float cy = (float)stoi(sLine.substr(0, sLine.find(",")));
					sLine = sLine.substr(sLine.find(" ") + 1);
					float radius = (float)stoi(sLine);
					getline(m_readFile, sLine);
					m_circle->SetVelocity((float)stoi(sLine.substr(10)));
					m_circle->SetPosition(cx, cy, radius);
					SceneManager::AddObject(m_circle);
				}
				else if (sLine.substr(6) == "PLANE") {
					Plane *m_plane = new Plane(ID);
					getline(m_readFile, sLine);
					sLine = sLine.substr(10);
					int x1 = stoi(sLine.substr(0, sLine.find(",")));
					sLine = sLine.substr(sLine.find(" ") + 1);
					int y1 = stoi(sLine.substr(0, sLine.find(",")));
					sLine = sLine.substr(sLine.find(" ") + 1);
					int width = stoi(sLine.substr(0, sLine.find(",")));
					sLine = sLine.substr(sLine.find(" ") + 1);
					int height = stoi(sLine);
					getline(m_readFile, sLine);
					m_plane->SetVelocity((float)stoi(sLine.substr(10)));
					m_plane->SetPosition(x1, y1, width, height);
					SceneManager::AddObject(m_plane);
				}
				getline(m_readFile, sLine);
			}
			m_readFile.close();
		}
		catch (const std::exception&)
		{
			cout << "ERROR" << endl;
			m_readFile.close();
		}
	}
}

void SceneManager::EndMove() {
	m_iIdMove = -1;
}

void SceneManager::CheckPointInList(int x, int y) {
	for (int i = 0;i < ms_iNumberObj;i++) {
		if (m_aObject[i]->CheckPointInObj(float(x), float(y))){
			m_iIdMove = i;
			m_iOldX = x;
			m_iOldY = y;
			break;
		}
	}
}

void SceneManager::SetNewState(int x, int y) {
	if(m_iIdMove != -1){
		m_aObject[m_iIdMove]->m_afPosition[0] += x - m_iOldX;
		m_aObject[m_iIdMove]->m_afPosition[1] += y - m_iOldY;
		m_iOldDeltaX = float(x - m_iOldX);
		m_iOldDeltaY = float(y - m_iOldY);
		for (int i = 0;i < ms_iNumberObj;i++) {
			if (i != m_iIdMove) {
				if (CollisionManager::GetInstance()->CheckCollision(m_aObject[m_iIdMove], m_aObject[i])) {
					m_aObject[m_iIdMove]->m_afPosition[0] -= x - m_iOldX;
					m_aObject[m_iIdMove]->m_afPosition[1] -= y - m_iOldY;
					break;
				}
			}
		}	
		m_iOldX = x;
		m_iOldY = y;
	}
}

void SceneManager::SetEndState(int x, int y) {
	if (m_iIdMove != -1) {
		m_aObject[m_iIdMove]->m_afPosition[0] += x - m_iOldX;
		m_aObject[m_iIdMove]->m_afPosition[1] += y - m_iOldY;
		while (m_iOldDeltaX >= 100 || m_iOldDeltaX <= -100 || m_iOldDeltaY >= 100 || m_iOldDeltaY <= -100) {
			m_iOldDeltaX /= 2;
			m_iOldDeltaY /= 2;
		}
		m_aObject[m_iIdMove]->m_fVX = m_iOldDeltaX;
		m_aObject[m_iIdMove]->m_fVY = m_iOldDeltaY;
	}
}

void SceneManager::CheckCollisionInList(float frameTime) {
	for (int i = 0;i < ms_iNumberObj-1;i++) {
		for (int j = i + 1;j < ms_iNumberObj;j++) {
			if (CollisionManager::GetInstance()->CheckCollision(m_aObject[i], m_aObject[j])) {
				if(m_aObject[i]->m_iObjID != 3 && m_aObject[j]->m_iObjID != 3){
				 	float m1 = m_aObject[i]->m_fVelocity;
					float m2 = m_aObject[j]->m_fVelocity;
					float v1x = m_aObject[i]->m_fVX;
					float v2x = m_aObject[j]->m_fVX;
					float v1y = m_aObject[i]->m_fVY;
					float v2y = m_aObject[j]->m_fVY;
					m_aObject[i]->m_fVX = ((m1 - m2)*v1x + 2 * m2*v2x) / (m1 + m2);
					m_aObject[j]->m_fVX = ((m2 - m1)*v2x + 2 * m1*v1x) / (m1 + m2);
					m_aObject[i]->m_fVY = ((m1 - m2)*v1y + 2 * m2*v2y) / (m1 + m2);
					m_aObject[j]->m_fVY = ((m2 - m1)*v2y + 2 * m1*v1y) / (m1 + m2);
					m_aObject[i]->m_afPosition[0] += m_aObject[i]->m_fVX * frameTime;
					m_aObject[i]->m_afPosition[1] += m_aObject[i]->m_fVY * frameTime;
					m_aObject[j]->m_afPosition[0] += m_aObject[j]->m_fVX * frameTime;
					m_aObject[j]->m_afPosition[1] += m_aObject[j]->m_fVY * frameTime;
				}
			}
		}
	}
}