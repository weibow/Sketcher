#pragma once
#include "Element.h"
#include <vector>
class CCurve :
	public CElement
{
public:
	CCurve(const CPoint& first, const CPoint& second, COLORREF color);
	virtual ~CCurve();
	void AddSegment(const CPoint& point); 
	virtual void Draw(CDC* pDC) override;
protected:
	std::vector<CPoint> m_Points;
	CCurve();
};

