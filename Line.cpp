#include "stdafx.h"
#include "Line.h"

IMPLEMENT_SERIAL(CLine, CElement, VERSION_NUMBER)

CLine::CLine()
{
}


CLine::~CLine()
{
}

//CLine class constructor
CLine::CLine(const CPoint& start, const CPoint& end, COLORREF color, int penWidth) :
CElement { start, color, penWidth }, m_EndPoint { end } 
{
	//Define the enclosing rectangle
	m_EnclosingRect = CRect { start, end };
	m_EnclosingRect.NormalizeRect();
	int width{ penWidth == 0 ? 1 : penWidth };
	m_EnclosingRect.InflateRect(width, width);
}

void CLine::Draw(CDC* pDC, std::shared_ptr<CElement> pElement)
{
	//Create a pen for this object and initialize it
	CPen aPen;	
	CreatePen(aPen, pElement);

	CPen* pOldPen{ pDC->SelectObject(&aPen) };
	
	// Now draw the line
	pDC->MoveTo(m_StartPoint);
	pDC->LineTo(m_EndPoint);

	pDC->SelectObject(pOldPen);
}

void CLine::Move(const CSize & aSize)
{
	m_StartPoint += aSize;
	m_EndPoint += aSize;
	m_EnclosingRect += aSize;
}

void CLine::Serialize(CArchive& ar)
{
	CElement::Serialize(ar);

	if (ar.IsStoring())
	{	// storing code'
		ar << m_EndPoint;
	}
	else
	{	// loading code
		ar >> m_EndPoint;
	}
}
