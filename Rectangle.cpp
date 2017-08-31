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

CRectangle::CRectangle(const CPoint& start, const CPoint& end, COLORREF color, int penWidth) :
	CElement{ start, color, penWidth }
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
	int width{ penWidth == 0 ? 1 : penWidth }; //Inflate rect by at least 1
	m_EnclosingRect.InflateRect(width, width);
}


//Draw a CRectangle object
void CRectangle::Draw(CDC* pDC, std::shared_ptr<CElement> pElement)
{
	CPen aPen;

	CreatePen(aPen, pElement);

	//Select the pen and the null brush
	CPen* pOldPen { pDC->SelectObject(&aPen) };
	CBrush* pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };

	pDC->Rectangle(m_StartPoint.x, m_StartPoint.y,
					m_BottomRight.x, m_BottomRight.y);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);


}