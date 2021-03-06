#pragma once
#include "Element.h"
class CLine :
	public CElement
{
DECLARE_SERIAL(CLine)
public:
	//CLine();
	virtual ~CLine();
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override; //Function to display a line
	virtual void Move(const CSize& aSize) override;
	//Constructor for a line object
	CLine(const CPoint& start, const CPoint& end, COLORREF color, int penWidth);
protected:
	CPoint m_EndPoint;
protected:
	CLine();
	//void Draw(CDC* pDC);
public:
	virtual void Serialize(CArchive& ar) override;
};

