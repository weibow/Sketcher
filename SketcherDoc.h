
// SketcherDoc.h : interface of the CSketcherDoc class
//



#include "ElementType.h"
#include "ElementColor.h"
#include "Element.h"
#include <list>
#include <memory>

using SketchIterator = std::list<std::shared_ptr<CElement>>::const_iterator;


#pragma once

class CSketcherDoc : public CDocument
{
protected: // create from serialization only
	CSketcherDoc();
	DECLARE_DYNCREATE(CSketcherDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CSketcherDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	// Finds the element under the point
	std::shared_ptr<CElement> FindElement(const CPoint& point)const
	{
		for (const auto& pElement : m_Sketch)
		{
			if (pElement->GetEnclosingRect().PtInRect(point))
				return pElement;
		}
		return nullptr;
	}
	void AddElement(std::shared_ptr<CElement>& pElement)
	{
		m_Sketch.push_back(pElement);
		UpdateAllViews(nullptr, 0, pElement.get());
		SetModifiedFlag();
	}
	void DeleteElement(std::shared_ptr<CElement>& pElement)
	{
		m_Sketch.remove(pElement);
		UpdateAllViews(nullptr, 0, pElement.get());
		SetModifiedFlag();
	}
protected:
	//std::list <std::shared_ptr<CElement>> m_Sketch;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
	ElementType m_Element {ElementType::LINE };		//Current element type
	ElementColor m_Color{ ElementColor::BLACK };	//Current drawing color
	std::list<std::shared_ptr<CElement>> m_Sketch;	//A list containing the sketch
	int m_PenWidth{};		//Record the current pen width
	CSize m_DocSize{ CSize{3000, 3000} };
public:
	afx_msg void OnColorBlack();
	afx_msg void OnColorRed();
	afx_msg void OnElementLine();
	afx_msg void OnElementRectangle();
	afx_msg void OnColorGreen();
	afx_msg void OnUpdateColorBlack(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementLine(CCmdUI *pCmdUI);
	afx_msg void OnElementCircle();
	afx_msg void OnUpdateColorRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementCircle(CCmdUI *pCmdUI);
	afx_msg void OnColorBlue();
	afx_msg void OnUpdateColorBlue(CCmdUI *pCmdUI);
	afx_msg void OnElementCurve();
	afx_msg void OnUpdateElementCurve(CCmdUI *pCmdUI);
	
public:
	ElementType GetElementType() const;
	ElementColor GetElementColor() const;
	
	SketchIterator begin() const { return std::begin(m_Sketch); }
	SketchIterator end()  const { return std::end(m_Sketch); }
	afx_msg void OnElementText();
	afx_msg void OnUpdateElementText(CCmdUI *pCmdUI);
	afx_msg void OnPenWidth();
	int GetPenWidth() const { return m_PenWidth; }

	void SendToBack(std::shared_ptr<CElement>& pElement);
	afx_msg void OnComSerial();
	afx_msg void OnPenCom();
	afx_msg void OnUpdateComSerial(CCmdUI *pCmdUI);
};
