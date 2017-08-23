#include "stdafx.h"
#include "Text.h"


CText::CText()
{
}

// CText constructor
CText::CText(const CPoint& start, const CPoint& end,
	const CString& aString, COLORREF color) :
	CElement{ start, color }
{
	m_String = aString; // Store the string
	m_EnclosingRect = CRect{ start, end };
	m_EnclosingRect.NormalizeRect();
	m_EnclosingRect.InflateRect(m_PenWidth, m_PenWidth);
}