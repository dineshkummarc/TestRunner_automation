// cvSrvrItem.h : interface of the cvCSrvrItem class
//

#if !defined(AFX_CVSRVRITEM_H__42C45BC8_818D_11D3_ABBD_0008C7FB2802__INCLUDED_)
#define AFX_CVSRVRITEM_H__42C45BC8_818D_11D3_ABBD_0008C7FB2802__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class cvCSrvrItem : public COleServerItem
{
	DECLARE_DYNAMIC(cvCSrvrItem)

// Constructors
public:
	cvCSrvrItem(cvCTestDoc* pContainerDoc);

// Attributes
	cvCTestDoc* GetDocument() const
		{ return (cvCTestDoc*)COleServerItem::GetDocument(); }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cvCSrvrItem)
	public:
	virtual BOOL OnDraw(CDC* pDC, CSize& rSize);
	virtual BOOL OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize);
	//}}AFX_VIRTUAL

// Implementation
public:
	~cvCSrvrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CVSRVRITEM_H__42C45BC8_818D_11D3_ABBD_0008C7FB2802__INCLUDED_)
