// Element.cpp : implementation file
//

#include "stdafx.h"
#include "Sketcher.h"
#include "Element.h"


static const COLORREF SELECT_COLOR{ RGB(255,0,180) };

CElement::CElement(const CPoint& start, COLORREF color, int penWidth) :
	m_StartPoint{ start }, m_PenWidth{ penWidth }, m_Color{ color } 
{
}

void CElement::CreatePen(CPen& aPen, std::shared_ptr<CElement> pElement)
{
	if (!aPen.CreatePen(PS_SOLID, m_PenWidth, this == pElement.get()?  SELECT_COLOR : m_Color))
	{
		AfxMessageBox(_T("Pen creation failed."), MB_OK);
		AfxAbort();
	}
}



// CElement

CElement::CElement()
{
}

CElement::~CElement()
{
}


// CElement member functions
