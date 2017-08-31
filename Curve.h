#pragma once
#include "Element.h"
#include <vector>
class CCurve :
	public CElement
{
public:
	CCurve(const CPoint& first, const CPoint& second, COLORREF color, int penWidth);
	virtual ~CCurve();
	void AddSegment(const CPoint& point); 
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) override;
protected:
	std::vector<CPoint> m_Points;
	CCurve();
};

