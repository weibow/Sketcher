
// SketcherDoc.cpp : implementation of the CSketcherDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sketcher.h"
#endif

#include "SketcherDoc.h"
#include "PenDialog.h"
#include "ComDialog.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSketcherDoc

IMPLEMENT_DYNCREATE(CSketcherDoc, CDocument)

BEGIN_MESSAGE_MAP(CSketcherDoc, CDocument)
	ON_COMMAND(ID_COLOR_BLACK, &CSketcherDoc::OnColorBlack)
	ON_COMMAND(ID_COLOR_RED, &CSketcherDoc::OnColorRed)
	ON_COMMAND(ID_ELEMENT_LINE, &CSketcherDoc::OnElementLine)
	ON_COMMAND(ID_ELEMENT_RECTANGLE, &CSketcherDoc::OnElementRectangle)
	ON_COMMAND(ID_COLOR_GREEN, &CSketcherDoc::OnColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CSketcherDoc::OnUpdateColorBlack)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_LINE, &CSketcherDoc::OnUpdateElementLine)
	ON_COMMAND(ID_ELEMENT_CIRCLE, &CSketcherDoc::OnElementCircle)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CSketcherDoc::OnUpdateColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CSketcherDoc::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CIRCLE, &CSketcherDoc::OnUpdateElementCircle)
	ON_COMMAND(ID_COLOR_BLUE, &CSketcherDoc::OnColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CSketcherDoc::OnUpdateColorBlue)
	ON_COMMAND(ID_ELEMENT_CURVE, &CSketcherDoc::OnElementCurve)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_CURVE, &CSketcherDoc::OnUpdateElementCurve)
	ON_COMMAND(ID_ELEMENT_TEXT, &CSketcherDoc::OnElementText)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_TEXT, &CSketcherDoc::OnUpdateElementText)
	ON_COMMAND(ID_PEN_WIDTH, &CSketcherDoc::OnPenWidth)
	//ON_COMMAND(ID_COM_SERIAL, &CSketcherDoc::OnComSerial)
	ON_COMMAND(ID_PEN_COM, &CSketcherDoc::OnPenCom)
	//ON_UPDATE_COMMAND_UI(ID_COM_SERIAL, &CSketcherDoc::OnUpdateComSerial)
	//ON_COMMAND(ID_SERIAL_COM, &CSketcherDoc::OnSerialCom)
	ON_UPDATE_COMMAND_UI(ID_ELEMENT_RECTANGLE, &CSketcherDoc::OnUpdateElementRectangle)
	ON_COMMAND(ID_PEN_RS485, &CSketcherDoc::OnPenRs485)
	ON_COMMAND(ID_COM_RS232, &CSketcherDoc::OnComRs232)
	ON_COMMAND(ID_COM_RS985, &CSketcherDoc::OnComRs985)
//	ON_COMMAND(ID_COM_SERIAL, &CSketcherDoc::OnComSerial)
	ON_COMMAND(ID_COM_ADD, &CSketcherDoc::OnComAdd)
	ON_COMMAND(ID_COM_SERIAL2, &CSketcherDoc::OnComSerial2)
	ON_COMMAND(ID_COM_SERIAL0, &CSketcherDoc::OnComSerial0)
	ON_COMMAND(ID_COM_SERIAL, &CSketcherDoc::OnComSerial)
END_MESSAGE_MAP()


// CSketcherDoc construction/destruction

CSketcherDoc::CSketcherDoc()
{
	// TODO: add one-time construction code here

}

CSketcherDoc::~CSketcherDoc()
{
}

BOOL CSketcherDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CSketcherDoc serialization

void CSketcherDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar << static_cast<COLORREF>(m_Color)
			<< static_cast<int>(m_Element)
			<< m_PenWidth
			<< m_DocSize;
		ar << m_Sketch.size();		//Store the number of element in the list
		
		for (const auto &pElement : m_Sketch)
			ar << pElement.get();
	}
	else
	{
		// TODO: add loading code here

		COLORREF color{};
		int elementType{};
		ar >> color				//Retrieve the current color
			>> elementType		//the element type as an integer
			>> m_PenWidth		//and the current pen width
			>> m_DocSize;		//and the current document size
		m_Color = static_cast<ElementColor>(color);
		m_Element = static_cast<ElementType>(elementType);

		//Now retrieve all the elements and store in the list
		size_t elementCount{};
		ar >> elementCount;
		CElement* pElement;
		for (size_t i{}; i < elementCount; ++i)
		{
			ar >> pElement;
			m_Sketch.push_back(std::shared_ptr<CElement>(pElement));
		}
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSketcherDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CSketcherDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSketcherDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSketcherDoc diagnostics

#ifdef _DEBUG
void CSketcherDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSketcherDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSketcherDoc commands


void CSketcherDoc::OnColorBlack()
{
	m_Color = ElementColor::BLACK;	//Set the drawing color to black// TODO: Add your command handler code here
	SetModifiedFlag();
}


void CSketcherDoc::OnColorRed()
{
	m_Color = ElementColor::RED; // TODO: Add your command handler code here
	SetModifiedFlag();
}

void CSketcherDoc::OnColorGreen()
{
	m_Color = ElementColor::GREEN;// TODO: Add your command handler code here
	SetModifiedFlag();
}

void CSketcherDoc::OnColorBlue()
{
	// TODO: Add your command handler code here
	m_Color = ElementColor::BLUE;
	SetModifiedFlag();
}
void CSketcherDoc::OnElementLine()
{
	m_Element = ElementType::LINE;// TODO: Add your command handler code here
	SetModifiedFlag();
}

void CSketcherDoc::OnElementRectangle()
{
	// TODO: Add your command handler code here
	m_Element = ElementType::RECTANGLE;
	SetModifiedFlag();
}

void CSketcherDoc::OnElementCircle()
{
	// TODO: Add your command handler code here
	m_Element = ElementType::CIRCLE;
	SetModifiedFlag();
}

void CSketcherDoc::OnElementCurve()
{
	// TODO: Add your command handler code here
	m_Element = ElementType::CURVE;
	SetModifiedFlag();
}


void CSketcherDoc::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Color == ElementColor::BLACK);
}




void CSketcherDoc::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Color == ElementColor::RED);
}


void CSketcherDoc::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Color == ElementColor::GREEN);
}


void CSketcherDoc::OnUpdateElementCircle(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Element == ElementType::CIRCLE);
}
void CSketcherDoc::OnUpdateElementLine(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Element == ElementType::LINE);
}


void CSketcherDoc::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Color == ElementColor::BLUE);
}




void CSketcherDoc::OnUpdateElementCurve(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Element == ElementType::CURVE);
}

void CSketcherDoc::OnUpdateElementRectangle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_Element == ElementType::RECTANGLE);
}



ElementType CSketcherDoc::GetElementType() const
{
	return m_Element;
}


ElementColor  CSketcherDoc::GetElementColor() const
{
	return m_Color;
}


void CSketcherDoc::OnElementText()
{
	// TODO: Add your command handler code here
	m_Element = ElementType::TEXT;
	SetModifiedFlag();
}


void CSketcherDoc::OnUpdateElementText(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_Element == ElementType::TEXT);
}





void CSketcherDoc::SendToBack(std::shared_ptr<CElement>& pElement)
{
	if (pElement)
	{
		m_Sketch.remove(pElement);
		m_Sketch.push_back(pElement);
	}
}


//void CSketcherDoc::OnComSerial()
//{
//	// TODO: 在此添加命令处理程序代码
//	CComDialog aDlg;
//
//	if (aDlg.DoModal() == IDOK) {
//	}
//
//}
void CSketcherDoc::OnPenWidth()
{
	// TODO: 在此添加命令处理程序代码
	CPenDialog aDlg;

	aDlg.m_PenWidth = m_PenWidth;

	if (aDlg.DoModal() == IDOK)
	{
		m_PenWidth = aDlg.m_PenWidth;
		SetModifiedFlag();
	}
}

void CSketcherDoc::OnPenCom()
{
	// TODO: 在此添加命令处理程序代码
	CComDialog aDlg;

	if (aDlg.DoModal() == IDOK) {
	}
}


//void CSketcherDoc::OnUpdateComSerial(CCmdUI *pCmdUI)
//{
//
//	// TODO: 在此添加命令更新用户界面处理程序代码
//	pCmdUI->SetCheck(1);
//}


//void CSketcherDoc::OnSerialCom()
//{
//	// TODO: 在此添加命令处理程序代码
//
//
//}





void CSketcherDoc::OnPenRs485()
{
	// TODO: 在此添加命令处理程序代码
	CComDialog aDlg;

	if (aDlg.DoModal() == IDOK) {
	}
}


void CSketcherDoc::OnComRs232()
{
	// TODO: 在此添加命令处理程序代码
	CComDialog aDlg;

	if (aDlg.DoModal() == IDOK) {
	}
}


void CSketcherDoc::OnComRs985()
{
	// TODO: 在此添加命令处理程序代码
	CComDialog aDlg;

	if (aDlg.DoModal() == IDOK) {
	}
}


//void CSketcherDoc::OnComSerial()
//{
//	// TODO: 在此添加命令处理程序代码
//	CComDialog aDlg;
//
//	if (aDlg.DoModal() == IDOK) {
//	}
//}


void CSketcherDoc::OnComAdd()
{
	// TODO: 在此添加命令处理程序代码
	CComDialog aDlg;

	if (aDlg.DoModal() == IDOK) {
	}
}


void CSketcherDoc::OnComSerial2()
{
	// TODO: 在此添加命令处理程序代码
	CComDialog aDlg;

	if (aDlg.DoModal() == IDOK) {
	}
}


void CSketcherDoc::OnComSerial0()
{
	// TODO: 在此添加命令处理程序代码
	CComDialog aDlg;

	if (aDlg.DoModal() == IDOK) {
	}
}


void CSketcherDoc::OnComSerial()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	CComDialog aDlg;

	if (aDlg.DoModal() == IDOK) {
	}
}
