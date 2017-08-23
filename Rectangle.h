#pragma once
#include "Element.h"
class CRectangle :
	public CElement
{
public:
	//CRectangle();
	virtual ~CRectangle();
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement>)override; //Function to display a rectangle
	CRectangle(const CPoint& start, const CPoint& end, COLORREF color);
protected:
	CPoint m_BottomRight;	//Bottom-right point for the rectangle
	CRectangle();

};

