
// SketcherView.cpp : implementation of the CSketcherView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sketcher.h"
#endif

#include "SketcherDoc.h"
#include "SketcherView.h"
#include "Line.h"
#include "Rectangle.h"
#include "Curve.h"
#include "Circle.h"
#include "Text.h"
#include "TextDialog.h"
#include "ScaleDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSketcherView

IMPLEMENT_DYNCREATE(CSketcherView, CScrollView)

BEGIN_MESSAGE_MAP(CSketcherView, CScrollView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
//	ON_WM_MBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_VIEW_SCALE, &CSketcherView::OnViewScale)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_SCALE, &CSketcherView::OnUpdateIndicatorScale)
	ON_COMMAND(ID_ELEMENT_MOVE, &CSketcherView::OnElementMove)
	ON_COMMAND(ID_ELEMENT_SENDTOBACK, &CSketcherView::OnElementSendtoback)
	ON_COMMAND(ID_ELEMENT_DELETE, &CSketcherView::OnElementDelete)
	//ON_COMMAND(ID_COM_SERIAL, &CSketcherView::OnComSerial)
END_MESSAGE_MAP()

// CSketcherView construction/destruction

CSketcherView::CSketcherView()
	: m_FirstPoint{ CPoint{} }
	, m_SecondPoint(0)
{
	// TODO: add construction code here

}

CSketcherView::~CSketcherView()
{
}

BOOL CSketcherView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSketcherView drawing

void CSketcherView::OnDraw(CDC* pDC)
{
	CSketcherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
//	for (auto iter = pDoc->begin(); iter != pDoc->end(); ++iter) {
		for (const auto& pElement : *pDoc)
		{
			if (pDC->RectVisible(pElement->GetEnclosingRect()))
				pElement->Draw(pDC, m_pSelected);
		}
//	}
}


// CSketcherView printing

BOOL CSketcherView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSketcherView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSketcherView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSketcherView diagnostics

#ifdef _DEBUG
void CSketcherView::AssertValid() const
{
	CView::AssertValid();
}

void CSketcherView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSketcherDoc* CSketcherView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSketcherDoc)));
	return (CSketcherDoc*)m_pDocument;
}
#endif //_DEBUG


// CSketcherView message handlers
void CSketcherView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (this == GetCapture())
		ReleaseCapture();
	//CView::OnLButtonUp(nFlags, point);
	if (m_pTempElement)
	{
		CRect aRect{ m_pTempElement->GetEnclosingRect() };
		GetDocument()->AddElement(m_pTempElement);

		CClientDC aDC{ this };
		OnPrepareDC(&aDC);
		aDC.LPtoDP(aRect);
		InvalidateRect(aRect);

		//InvalidateRect(&m_pTempElement->GetEnclosingRect());
		m_pTempElement.reset();
	}
}

void CSketcherView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC aDC{ this };
	OnPrepareDC(&aDC);
	aDC.DPtoLP(&point);
	CSketcherDoc* pDoc{ GetDocument() };
	if (m_MoveMode)
	{
		m_MoveMode = false;
		auto pElement(m_pSelected);
		m_pSelected.reset();
		pDoc->UpdateAllViews(nullptr, 0, pElement.get());
		pDoc->SetModifiedFlag();
	} 
	else if (pDoc->GetElementType() == ElementType::TEXT)
	{
		CTextDialog aDlg;
		if (aDlg.DoModal() == IDOK)
		{
			CSize textExtent {aDC.GetOutputTextExtent(aDlg.m_TextString)};
			textExtent.cx *= 1;
			textExtent.cy *= 1;
			std::shared_ptr<CElement> pTextElement
				{std::make_shared<CText>(point, point + textExtent, aDlg.m_TextString,
					static_cast<COLORREF>(pDoc->GetElementColor()))};
			pDoc->AddElement(pTextElement);
			pDoc->UpdateAllViews(nullptr, 0, pTextElement.get());
		//	pDoc->SetModifiedFlag();			//Set the modified flag
		}
	}
	else
	{
		m_FirstPoint = point;
		SetCapture();
	}
}

void CSketcherView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//Define a Device Context object for the view
	CClientDC aDC{ this };		//DC is for this view
	
	OnPrepareDC(&aDC);
	aDC.DPtoLP(&point);

	//CView::OnMouseMove(nFlags, point);
	if (m_MoveMode)
	{
		MoveElement(aDC, point);
	}
	else if ((nFlags & MK_LBUTTON) && (this == GetCapture()))
	{
		m_SecondPoint = point;
		if (m_pTempElement)
		{
			if (ElementType::CURVE == GetDocument()->GetElementType())
			{
				std::dynamic_pointer_cast<CCurve>(m_pTempElement)->AddSegment(m_SecondPoint);
				m_pTempElement->Draw(&aDC);
				return;
			}
			else
			{
				aDC.SetROP2(R2_NOTXORPEN);
				m_pTempElement->Draw(&aDC);
			}
		}
		m_pTempElement = CreateElement();
		m_pTempElement->Draw(&aDC);
	}
	else
	{
		auto pOldSelected = m_pSelected;
		m_pSelected = GetDocument()->FindElement(point);
		if (m_pSelected != pOldSelected)
		{
			if (m_pSelected)
				GetDocument()->UpdateAllViews(nullptr, 0, m_pSelected.get());
			if (pOldSelected)
				GetDocument()->UpdateAllViews(nullptr, 0, pOldSelected.get());
		}
	}
}





std::shared_ptr<CElement> CSketcherView::CreateElement() const
{
	CSketcherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	COLORREF color{ static_cast<COLORREF>(pDoc->GetElementColor()) };

	int penWidth{ pDoc->GetPenWidth() };

	switch (pDoc->GetElementType())
	{
	case ElementType::CURVE:
		return std::make_shared<CCurve>(m_FirstPoint, m_SecondPoint, color, penWidth);
	case ElementType::CIRCLE:
		return std::make_shared<CCircle>(m_FirstPoint, m_SecondPoint, color, penWidth);		
	case ElementType::RECTANGLE:
		return std::make_shared<CRectangle>(m_FirstPoint, m_SecondPoint, color, penWidth);
	case ElementType::LINE:		
		return std::make_shared<CLine>(m_FirstPoint, m_SecondPoint, color, penWidth);
	default:
		AfxMessageBox(_T("Bad Element code"), MB_OK);
		AfxAbort();
		return nullptr;
	}

//	return std::shared_ptr<CElement>();
}



void CSketcherView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pHint)
	{
		CClientDC aDC {this};
		OnPrepareDC(&aDC);		
		CRect aRect{ dynamic_cast<CElement*>(pHint)->GetEnclosingRect() };
		aDC.LPtoDP(aRect);
		InvalidateRect(aRect);
	} 
	else
	{
		InvalidateRect(nullptr);
	}
}
;

void CSketcherView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize DocSize{ 20000, 20000 };

	SetScrollSizes(MM_TEXT, DocSize, CSize{ 500, 500 }, CSize{ 20, 20 });
}


void CSketcherView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: Add your message handler code here
	CMenu menu;
	menu.LoadMenu(IDR_CONTEXT_MENU);
	CMenu* pContext{};
	if (m_pSelected)
	{
		pContext = menu.GetSubMenu(0);
	}
	else
	{
		pContext = menu.GetSubMenu(1);
		// Check color menu items
		ElementColor color{ GetDocument()->GetElementColor() };
		menu.CheckMenuItem(ID_COLOR_BLACK,
			(ElementColor::BLACK == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOR_RED,
			(ElementColor::RED == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOR_GREEN,
			(ElementColor::GREEN == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_COLOR_BLUE,
			(ElementColor::BLUE == color ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		// Check element menu items
		ElementType type{ GetDocument()->GetElementType() };
		menu.CheckMenuItem(ID_ELEMENT_LINE,
			(ElementType::LINE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_RECTANGLE,
			(ElementType::RECTANGLE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_CIRCLE,
			(ElementType::CIRCLE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		menu.CheckMenuItem(ID_ELEMENT_CURVE,
			(ElementType::CURVE == type ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
	}

//	CMenu* pContext{ menu.GetSubMenu(m_pSelected ? 0 : 1) };
	ASSERT(pContext != nullptr);
	pContext->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTALIGN, point.x, point.y, this);
}


//void CSketcherView::OnElementDelete()
//{
//	if (m_pSelected)
//	{
//		GetDocument()->DeleteElement(m_pSelected);
//		m_pSelected.reset();
//	}
//}


void CSketcherView::OnViewScale()
{
	// TODO: 在此添加命令处理程序代码
	CScaleDialog aDlg;
	
	aDlg.m_Scale = m_Scale;
	if (aDlg.DoModal() == IDOK)
	{
		m_Scale = aDlg.m_Scale;
		InvalidateRect(nullptr);
	}
}


void CSketcherView::OnUpdateIndicatorScale(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->Enable();
	CString scaleStr;
	scaleStr.Format(_T(" View Scale : %d"), m_Scale);
	pCmdUI->SetText(scaleStr);
}


void CSketcherView::OnElementMove()
{
	// TODO: 在此添加命令处理程序代码
	CClientDC aDC{ this };
	OnPrepareDC(&aDC);
	GetCursorPos(&m_CursorPos);
	ScreenToClient(&m_CursorPos);
	aDC.DPtoLP(&m_CursorPos);
	m_FirstPos = m_CursorPos;
	m_MoveMode = true;
}


// Move an element
void CSketcherView::MoveElement(CClientDC& aDC, const CPoint& point)
{
	CSize distance{ point - m_CursorPos };
	m_CursorPos = point;

	if (m_pSelected)
	{
		CSketcherDoc* pDoc{ GetDocument() };
		pDoc->UpdateAllViews(this, 0L, m_pSelected.get());
		aDC.SetROP2(R2_NOTXORPEN);
		m_pSelected->Draw(&aDC, m_pSelected);
		m_pSelected->Move(distance);
		m_pSelected->Draw(&aDC, m_pSelected);

		pDoc->UpdateAllViews(this, 0, m_pSelected.get());
	}
}


void CSketcherView::OnElementSendtoback()
{
	// TODO: 在此添加命令处理程序代码
}


void CSketcherView::OnElementDelete()
{
	// TODO: 在此添加命令处理程序代码
		if (m_pSelected)
		{
			GetDocument()->DeleteElement(m_pSelected);
			m_pSelected.reset();
		}
}


void CSketcherView::OnComSerial()
{
	// TODO: 在此添加命令处理程序代码
}
