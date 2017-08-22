#include "stdafx.h"
#include "Circle.h"


CCircle::CCircle()
{
}


CCircle::~CCircle()
{
}


//Constructor for a circle object
CCircle::CCircle(const CPoint& start, const CPoint& end, COLORREF color) :
	CElement{ start, color}
{
	long radius{ static_cast<long>(sqrt(
						static_cast<double>((end.x - start.x)*(end.x - start.x) +
							(end.y - start.y)*(end.y - start.y)))) };
	if (radius < 1L) radius = 1L;
	m_StartPoint = CPoint{ start.x - radius, start.y - radius };
	m_BottomRight = CPoint{ start.x + radius, start.y + radius };

	//Define the enclosing rectangle
	m_EnclosingRect = CRect{ m_StartPoint.x, m_StartPoint.y,
							m_BottomRight.x, m_BottomRight.y };
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}

void CCircle::Draw(CDC* pDC)
{
	CPen aPen;
	CreatePen(aPen);
	CPen* pOldPen{ pDC->SelectObject(&aPen) };
	
	CBrush* pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };

	pDC->Ellipse(m_StartPoint.x, m_StartPoint.y,
				 m_BottomRight.x, m_BottomRight.y);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);

}