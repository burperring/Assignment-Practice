class pt
{
private:
	int x;
	int y;
public:
	void Set(int x, int y)
	{
		//x = x;  //�����߻� compile error�� ������. Ambiguity : ��ȣ��
		//y = y;
		this->x = x;
		this->y = y;
	}
	
	POINT Get()
	{
		POINT p;
		p.x = x;
		p.y = y;
		return p;
	}
};

class mypoints : public pt  //���
{
	//public:   
private:
	pt p[1000]; //pt Ŭ������ (instance, object) �迭
	int iCount;
public:
	void Add(int x, int y)
	{
		if (iCount < 1000)	// integrity
		{
			//p[iCount].x = x;
			//p[iCount].y = y;
			p[iCount].Set(x, y);
			iCount++;
		}

	}
	void Draw(HDC hdc)
	{
		HBRUSH hBrush;
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, hBrush);
		for (int i = 0; i < iCount; i++)
		{
			Rectangle(hdc, p[i].Get().x - 10, p[i].Get().y - 10,
				p[i].Get().x + 10, p[i].Get().y + 10);
		}
	}
};