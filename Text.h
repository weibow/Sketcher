#pragma once
#include "Element.h"
#include <memory>
class CText :
	public CElement
{
public:
	//CText(const CPoint& start, const CPoint& end, const CString& aString, COLORREF color);
	//virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement = nullptr) override;
	virtual ~CText(){}
protected:
	CString m_String;
	CText(); 
};

