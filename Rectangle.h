#pragma once
#include "Element.h"
class CRectangle :
	public CElement
{
DECLARE_SERIAL(CRectangle)
public:
	//CRectangle();
	virtual ~CRectangle();
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr)override; //Function to display a rectangle
	CRectangle(const CPoint& start, const CPoint& end, COLORREF color, int penWidth);
protected:
	CPoint m_BottomRight;	//Bottom-right point for the rectangle
	CRectangle();

public:
	virtual void Serialize(CArchive& ar) override;
};

