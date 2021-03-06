
// SketcherView.h : interface of the CSketcherView class
//

#pragma once
#include "atltypes.h" 
#include "memory"
#include "Element.h"


class CSketcherView : public CScrollView
{
protected: // create from serialization only
	CSketcherView();
	DECLARE_DYNCREATE(CSketcherView)

// Attributes  
public:
	CSketcherDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSketcherView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	// First point recorded for an element
	
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
protected:
	CPoint m_FirstPoint;
	CPoint m_SecondPoint;
	CPoint m_CursorPos;
	CPoint m_FirstPos;
	std::shared_ptr<CElement> m_pTempElement;
	bool m_MoveMode{ false };
protected:
	std::shared_ptr<CElement> CreateElement() const;
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	virtual void OnInitialUpdate();
protected:
	std::shared_ptr<CElement> m_pSelected;
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnViewScale();
protected:
	int m_Scale{ 1 };
public:
	afx_msg void OnUpdateIndicatorScale(CCmdUI *pCmdUI);
	//void OnElementDelete();
	afx_msg void OnElementMove();
protected:
	// Move an element
	void MoveElement(CClientDC& aDC, const CPoint& point);
public:
	afx_msg void OnElementSendtoback();
	afx_msg void OnElementDelete();
	afx_msg void OnComSerial();
};

#ifndef _DEBUG  // debug version in SketcherView.cpp
inline CSketcherDoc* CSketcherView::GetDocument() const
   { return reinterpret_cast<CSketcherDoc*>(m_pDocument); }
#endif

