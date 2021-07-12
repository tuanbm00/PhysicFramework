#ifndef _OBJECT_
#define _OBJECT_

class Object
{
public:
	float m_afPosition[4];
	float m_fMass;
	float m_fVelocity;
	int m_iObjID;
	float m_fVX;
	float m_fVY;

	Object();
	virtual ~Object();
	virtual void Render() = 0;
	virtual bool CheckPointInObj(float x, float y) = 0;
	void Update(float frameTime);
	void SetVelocity(float fVelocity);
};

class Rectangle : public Object
{
public:
	Rectangle();
	Rectangle(int ID);
	~Rectangle();
	void Render();
	void SetPosition(int x1, int y1, int width, int height);
	bool CheckPointInObj(float x, float y);
};

class Circle : public Object
{
public:
	Circle();
	Circle(int ID);
	~Circle();
	void Render();
	void SetPosition(float cx, float cy, float radius);
	bool CheckPointInObj(float x, float y);
};

class Plane : public Object
{
public:
	Plane();
	Plane(int ID);
	~Plane();
	void Render();
	void SetPosition(int x1, int y1, int x2, int y2);
	bool CheckPointInObj(float x, float y);
};


#endif // !_OBJECT_
