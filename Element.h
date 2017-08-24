#pragma once
#include <memory>
// CElement command target

class CElement : public CObject
{
protected:
	CPoint m_StartPoint;
	int m_PenWidth;
	COLORREF m_Color;
	CRect m_EnclosingRect;
public:
	
	virtual ~CElement();
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) {}	//Virtual draw operation
	//Get the element enclosing rectangle
	const CRect& GetEnclosingRect() const { return m_EnclosingRect; }
protected:
	CElement();
	CElement(const CPoint& start, COLORREF color, int penWidth = 1);
	void CreatePen(CPen& aPen, std::shared_ptr<CElement> pElement);
};


