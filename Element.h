#pragma once
#include <memory>
// CElement command target
static const COLORREF SELECT_COLOR{ RGB(255,0,180) };
static const UINT VERSION_NUMBER{ 1001 };                                     // Version number for serialization

class CElement : public CObject
{
DECLARE_SERIAL(CElement)
protected:
	CPoint m_StartPoint;
	int m_PenWidth;
	COLORREF m_Color;
	CRect m_EnclosingRect;
public:
	
	virtual ~CElement();
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) {}	//Virtual draw operation
	virtual void Move(const CSize& aSize) {}
													
																				//virtual void Serialize(CArchive & ar) override;
																				//Get the element enclosing rectangle
	const CRect& GetEnclosingRect() const { return m_EnclosingRect; }
protected:
	CElement();
	CElement(const CPoint& start, COLORREF color, int penWidth = 1);
	void CreatePen(CPen& aPen, std::shared_ptr<CElement> pElement);
public:
	virtual void Serialize(CArchive& ar) override;
};


