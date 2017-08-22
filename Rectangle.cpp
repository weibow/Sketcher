#include "stdafx.h"
#include "Rectangle.h"
#include "algorithm"

CRectangle::CRectangle()
{
}


CRectangle::~CRectangle()
{
}


//CRectagle constructor

CRectangle::CRectangle(const CPoint& start, const CPoint& end, COLORREF color) :
	CElement{ start, color }
{
	m_StartPoint = CPoint{(std::min)(start.x, end.x), (std::min)(start.y, end.y)};
	m_BottomRight = CPoint{ (std::max)(start.x, end.x), (std::max)(start.y, end.y) };

	//Ensure width and height between the pointes is at least 2
	if ((m_BottomRight.x - m_StartPoint.x) < 2)
		m_BottomRight.x = m_StartPoint.x + 2;
	if ((m_BottomRight.y - m_StartPoint.y) < 2)
		m_BottomRight.y = m_StartPoint.y + 2;

	//Define the enclosing rectangle
	m_EnclosingRect = CRect{ m_StartPoint, m_BottomRight };
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}


//Draw a CRectangle object
void CRectangle::Draw(CDC* pDC)
{
	CPen aPen;
	CreatePen(aPen);

	//Select the pen and the null brush
	CPen* pOldPen { pDC->SelectObject(&aPen) };
	CBrush* pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };

	pDC->Rectangle(m_StartPoint.x, m_StartPoint.y,
					m_BottomRight.x, m_BottomRight.y);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);


}