// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// Description:
// 	Implements the class cvCSrvrItem
// 
// $Log: 
//  1    CliniVision1.0         11/9/99 11:22:51 AM  Doug C. Eveland 
// $
// $Revision: 1$
// $Date: 11/9/99 11:22:51 AM$
// $Author: Doug C. Eveland$
// 

#include "stdafx.h"
#include "cvCTestApp.h"

#include "cvCTestDoc.h"
#include "cvCSrvrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(cvCSrvrItem, COleServerItem)

cvCSrvrItem::cvCSrvrItem(cvCTestDoc* pContainerDoc)
	: COleServerItem(pContainerDoc, TRUE)
{
}

cvCSrvrItem::~cvCSrvrItem()
{
}

void cvCSrvrItem::Serialize(CArchive& ar)
{
	if (!IsLinkedItem())
	{
		cvCTestDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pDoc->Serialize(ar);
	}
}

BOOL cvCSrvrItem::OnGetExtent(DVASPECT dwDrawAspect, CSize& rSize)
{
	if (dwDrawAspect != DVASPECT_CONTENT)
		return COleServerItem::OnGetExtent(dwDrawAspect, rSize);

	cvCTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	rSize = CSize(3000, 3000);   // 3000 x 3000 HIMETRIC units

	return TRUE;
}

BOOL cvCSrvrItem::OnDraw(CDC* pDC, CSize& rSize)
{
	UNREFERENCED_PARAMETER(rSize);

	cvCTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowOrg(0,0);
	pDC->SetWindowExt(3000, 3000);

	return TRUE;
}


#ifdef _DEBUG
void cvCSrvrItem::AssertValid() const
{
	COleServerItem::AssertValid();
}

void cvCSrvrItem::Dump(CDumpContext& dc) const
{
	COleServerItem::Dump(dc);
}
#endif

