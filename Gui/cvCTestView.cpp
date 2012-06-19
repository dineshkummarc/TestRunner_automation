// 
// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// File:
//    cvTestView.cpp 
// 
// Description:
//    Impliments CTestView - used for listing available tests
// 
// $Log: 
//  3    CliniVision1.2         11/16/99 5:08:10 PM  Doug C. Eveland Added DocJet
//       group comment.
//       Added a catch(...) based on a code review comment by Jerry Edens.
//  2    CliniVision1.1         11/11/99 10:29:44 AM Doug C. Eveland Added function
//       headers.
//       Fixed non-Unicode compile bug
//  1    CliniVision1.0         11/9/99 11:22:54 AM  Doug C. Eveland 
// $
// $Revision: 3$
// $Date: 11/16/99 5:08:10 PM$
// $Author: Doug C. Eveland$
// 
// cvTestView.cpp : implementation of the cvCTestView class
//

#include "stdafx.h"
#include "cvCTestApp.h"

#include "cvCTestDoc.h"
#include "cvCTestView.h"
#include "cvCTestSuiteView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

IMPLEMENT_DYNCREATE(cvCTestView, CListView)

BEGIN_MESSAGE_MAP(cvCTestView, CListView)
	//{{AFX_MSG_MAP(cvCTestView)
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, OnBeginDrag)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnDeleteItem)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

cvCTestView::cvCTestView()
: m_bDragging(FALSE)
, m_nDragIndex(-1)
, m_nDropIndex(-1)
, m_pDropWnd(NULL)
, m_pDragImage(NULL)
, m_bInitialized(FALSE)
{
}

cvCTestView::~cvCTestView()
{
	if (m_pDragImage)
	{
		delete m_pDragImage;
		m_pDragImage = NULL;
	}
}

BOOL cvCTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_EDITLABELS | LVS_REPORT |
		LVS_SINGLESEL | LVS_NOCOLUMNHEADER ;//| LVS_EX_INFOTIP;

	return CListView::PreCreateWindow(cs);
}

void cvCTestView::OnDraw(CDC* pDC)
{
	cvCTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

BOOL cvCTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void cvCTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void cvCTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestView::OnInitialUpdate
// 
// Description:
// 	Called by the framework just before the view is first displayed.
//  Loads the drop/no-drop cursors and creates image lists used by the 
//  listctrl.
// 
void cvCTestView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	if (!m_bInitialized)
	{
		// Load drop/no-drop cursors
		m_hNoDropCursor = AfxGetApp()->LoadCursor(IDC_NODROP);
		ASSERT(m_hNoDropCursor != NULL);

		m_hDropCursor = AfxGetApp()->LoadCursor(IDC_POINTER);
		ASSERT(m_hDropCursor != NULL);

		// get client rec and handle to list control associated with this view
		CRect rcClient;
		GetClientRect(&rcClient);

		CListCtrl& ListCtrl = GetListCtrl();

		// Create image list

		if (m_ImageList.GetSafeHandle() == NULL)
		{
			m_ImageList.Create( IDB_TEST, 16, 1, (COLORREF)-1 ); 
			ListCtrl.SetImageList(&m_ImageList, LVSIL_SMALL );
		}

		// Insert Column
		LV_COLUMN lvc;

		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

		lvc.iSubItem = 0;
		lvc.pszText = _T("Test Name");
		lvc.cx = rcClient.Width();
		lvc.fmt = LVCFMT_LEFT;
		ListCtrl.InsertColumn(0,&lvc);

		// Load cvITest objects
		try
		{
			CComPtr<cvITestSuiteItemCollection> spTestSuiteItemCollection;
			CComPtr<cvIEnumTestSuiteItems> spEnumTestSuiteItems;
			CComPtr<cvITestSuiteItem> spTestSuiteItem;

			// get test suite item collection
			HRESULT hr = spTestSuiteItemCollection.CoCreateInstance(__uuidof(cvCTestSuiteItemCollection));
			if (FAILED(hr))
				throw _com_error(hr);

			// load test item info using category info in registry.
			spTestSuiteItemCollection->LoadFromRegistry();
			spEnumTestSuiteItems = spTestSuiteItemCollection->GetNewEnum();

			// enumerate through all items in the collection
			unsigned long ulFetched;
			int nItem = 0;

			while (spEnumTestSuiteItems->Next(1, &spTestSuiteItem, &ulFetched) == S_OK)
			{
				_bstr_t bstrDescription = spTestSuiteItem->Description;
				_bstr_t bstrName = spTestSuiteItem->TestName;
				_bstr_t bstrProgId = spTestSuiteItem->ProgId;


				CLSID clsid;
				CLSIDFromProgID(spTestSuiteItem->ProgId, &clsid);

				InsertItem(nItem++, bstrName, bstrDescription, clsid);
				spTestSuiteItem.Release();
				spTestSuiteItem = NULL;
			}

			m_bInitialized = true;
		}
		catch (...)
		{
			CString strLoadFailure(MAKEINTRESOURCE(IDS_TESTCOLLECTIONLOAD_FAILED));
			CString strCaption(MAKEINTRESOURCE(AFX_IDS_APP_TITLE));
			MessageBox(strLoadFailure, strCaption, MB_OK);
		}
	}
}

#ifdef _DEBUG
void cvCTestView::AssertValid() const
{
	CListView::AssertValid();
}

void cvCTestView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

cvCTestDoc* cvCTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(cvCTestDoc)));
	return (cvCTestDoc*)m_pDocument;
}
#endif //_DEBUG


// {group:View Classes}
// 
// Name: 
// 	cvCTestView::OnBeginDrag
// 
// Description:
// 	Called when the drag operation starts.  Creates a drag image,
//  sets the dragging flag to true, and turns on mouse capture.
// 
// Arguments:
// 	pNMHDR - A pointer to the notification message header
// 
// 	pResult - A pointer to the return value
// 
void cvCTestView::OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	ASSERT(pResult != NULL);
	if (pResult != NULL)
		*pResult = 0;

	//Record the index of the item begin dragged as m_nDragIndex
	m_nDragIndex = ((NM_LISTVIEW *)pNMHDR)->iItem;	

	//Create a drag image from the center point of the item being dragged
	POINT pt;
	pt.x = 8;
	pt.y = 8;
	m_pDragImage = GetListCtrl().CreateDragImage(m_nDragIndex, &pt);
	m_pDragImage->BeginDrag(0, CPoint (8, 8));
	m_pDragImage->DragEnter(GetDesktopWindow(), ((NM_LISTVIEW *)pNMHDR)->ptAction);	

	//Set flags indicating a drag is in progress
	m_bDragging = TRUE;
	m_nDropIndex = -1;	
	m_pDropWnd = &GetListCtrl();	

	// Capture all mouse messages while in drag mode
	SetCapture();
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestView::OnLButtonUp
// 
// Description:
// 	Called when the left button is released.  If dragging is in process an attempt is made to perform a drop operation.
// 
// Arguments:
// 	nFlags - Indicates whether various virtual keys are down (see CWnd::OnLButtonDown)
// 
// 	ptDrop - The location where the drop operation is attempted.
// 
void cvCTestView::OnLButtonUp(UINT nFlags, CPoint ptDrop) 
{
	CWaitCursor WaitCursor;
	
	if (m_bDragging)
	{
		//---- Release mouse capture and stop dragging ---//
		::ReleaseCapture();
		m_bDragging = FALSE;
		m_pDragImage->DragLeave(GetDesktopWindow());
		m_pDragImage->EndDrag();	

		//---- Delete drag image once drag is completed.----//
		if (m_pDragImage != NULL)
		{
			delete m_pDragImage;
			m_pDragImage = NULL;
		}

		//---- Get window under drag point ----//
		CPoint pt(ptDrop);
		ClientToScreen(&pt);
		m_pDropWnd = WindowFromPoint(pt);

		//---- Drop the test item within the test view -----//
		if (m_pDropWnd->IsKindOf(RUNTIME_CLASS(cvCTestView)))
		{
			DropItemOnList();
		}
		//---- Drop the test item within the test suite view ----//
		else if (m_pDropWnd->IsKindOf(RUNTIME_CLASS(cvCTestSuiteView)))
		{
			cvCDragDropItem* pDragDropItem = GetDragDropItemFromIndex(m_nDragIndex);

			cvCTestSuiteView* pTestSuiteView = dynamic_cast<cvCTestSuiteView*>(m_pDropWnd);
			ASSERT(pTestSuiteView != NULL);

			cvCDragDropItem *pNewDragDropItem = new cvCDragDropItem;
			*pNewDragDropItem = *pDragDropItem;

			TRACE2("CTestView::OnLButtonUp: Created copy of Test Item (%p to %p)\n",
				pDragDropItem, pNewDragDropItem);

			pTestSuiteView->DropNewTestOnTree(ptDrop, pNewDragDropItem);
		}
	}
	CView::OnLButtonUp(nFlags, ptDrop);
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestView::OnMouseMove
// 
// Description:
// 	Called by the framework when the mouse moves over the view
// 
// Arguments:
// 	nFlags - Indicates whether various virtual keys are down (see CWnd::OnLButtonDown)
// 
// 	ptDrop - The location where the mouse moved to
// 
void cvCTestView::OnMouseMove(UINT nFlags, CPoint ptMove) 
{
	if (m_bDragging)
	{
		m_ptDropPoint = ptMove;
		ClientToScreen(&m_ptDropPoint);		

		// Move the drag image
		m_pDragImage->DragMove(m_ptDropPoint);		

		// Temporarily unlock window updates
		m_pDragImage->DragShowNolock(FALSE);		

		// Convert the drop point to client coordinates
		m_pDropWnd = WindowFromPoint(m_ptDropPoint);
		m_pDropWnd->ScreenToClient(&m_ptDropPoint);

		// Drop the test item within the test or testsuite views //
		if (m_pDropWnd != NULL)
		{
			if (m_pDropWnd->IsKindOf(RUNTIME_CLASS(cvCTestView)))
			{
				SetCursor(m_hDropCursor);
			}
			else if (m_pDropWnd->IsKindOf(RUNTIME_CLASS(cvCTestSuiteView))) 
			{
				cvCTestSuiteView *pView = dynamic_cast<cvCTestSuiteView*>(m_pDropWnd);
				ASSERT(pView != NULL);

				HTREEITEM htiDropTarget;
				if (pView->CanDropAtPoint(m_ptDropPoint, htiDropTarget))
				{
					SetCursor(m_hDropCursor);
				}
				else 
				{
					SetCursor(m_hNoDropCursor);
				}
			}
			else 
			{
				SetCursor(m_hNoDropCursor);
			}
		}

		// Lock window updates
		m_pDragImage->DragShowNolock(TRUE);
	}
	CView::OnMouseMove(nFlags, ptMove);
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestView::InsertItem
// 
// Description:
// 	Inserts an item into the list ctrl associated with this view
// 
// Arguments:
// 	nItem - The 0-based index of the item which is to be inserted
// 
// 	bstrName - The name of the item (testname)
// 
// 	_bstr_t bstrDescription - A description of the item to be inserted
// 
// 	clsidTest - The CLSID of the test item to be inserted
// 
// Results:
// 	 Returns -1 if the item was not inserted; else the index of the
//       item which was inserted.
// 
int cvCTestView::InsertItem(int nItem, _bstr_t bstrName,
					  _bstr_t bstrDescription, CLSID clsidTest)
{
	CWaitCursor WaitCursor;

	cvCDragDropItem *pDragDropItem = new cvCDragDropItem;
	TRACE1("CTestView::InsertItem: Created new Test Item (%p)\n", pDragDropItem);

	ASSERT(pDragDropItem != NULL);

	if (pDragDropItem != NULL)
	{
		pDragDropItem->SetType(cvCDragDropItem::EDragDropType_Test);
		pDragDropItem->SetDescription(bstrDescription);
		pDragDropItem->SetName(bstrName);
		pDragDropItem->SetCLSID(clsidTest);

		return GetListCtrl().InsertItem
			(
				LVIF_TEXT | LVIF_IMAGE | LVIF_STATE | LVIF_PARAM,
				nItem,
				bstrName, 
				0,
				LVIS_DROPHILITED | LVIS_FOCUSED | LVIS_SELECTED,
				0,
				(LPARAM) pDragDropItem
			);
	}
	else
	{
		return -1;
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestView::GetDragDropItemFromIndex
// 
// Description:
// 	A convenience method used to obtain information about the item which 
//  is associated with a listctrl entry
// 
// Arguments:
// 	nIndex - A 0-based index to the item in the list
// 
// Results:
// 	A pointer to a dragdrop item
// 
cvCDragDropItem* cvCTestView::GetDragDropItemFromIndex(int nIndex)
{
	if (nIndex < 0)
	{
		return (cvCDragDropItem*) NULL;
	}
	else
	{
		LV_ITEM lvi;
		ZeroMemory(&lvi, sizeof(LV_ITEM));
		lvi.mask = LVIF_PARAM;
		lvi.iItem = nIndex;
		GetListCtrl().GetItem(&lvi);
		return (cvCDragDropItem*) lvi.lParam;
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestView::DropItemOnList
// 
// Description:
// 	Called when an item is to be dropped on the listctrl.  A new entry 
//  in the list control is made and the original item is deleted.
// 
void cvCTestView::DropItemOnList()
{
	//GET THE DROP INDEX
	m_ptDropPoint.y += 10;
	m_nDropIndex = GetListCtrl().HitTest(m_ptDropPoint);	
	if (m_nDropIndex < 0)
		m_nDropIndex = GetListCtrl().GetItemCount();

	//GET INFORMATION ON THE DRAGGED ITEM BY SETTING AN LV_ITEM STRUCTURE
	//AND THEN CALLING GetItem TO FILL IT IN
	TCHAR szLabel[256];
	LV_ITEM lvi;
	ZeroMemory(&lvi, sizeof(LV_ITEM));
	lvi.mask = LVIF_TEXT | LVIF_PARAM;
	lvi.pszText = szLabel;
	lvi.iItem = m_nDragIndex;
	lvi.cchTextMax = 255;
	GetListCtrl().GetItem(&lvi);

	_bstr_t bstrDescription;
	CLSID clsid;

	if (lvi.lParam != NULL)
	{
		bstrDescription = ((cvCDragDropItem*) lvi.lParam)->GetDescription();
		clsid = ((cvCDragDropItem*) lvi.lParam)->GetCLSID();
	}

	// Perform the insert operation here
	InsertItem(m_nDropIndex, _bstr_t(lvi.pszText), bstrDescription, clsid);

	// Fill in the attributes for the item to be inserted
	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetListCtrl().GetDlgItem(0);
	ASSERT(pHeader != NULL);

	if (pHeader != NULL)
	{
		int nColumnCount = pHeader->GetItemCount();
		lvi.mask = LVIF_TEXT;
		lvi.iItem = m_nDropIndex;

		// Increment index if we are dragging an item above itself
		if (m_nDragIndex > m_nDropIndex)
			m_nDragIndex++;

		// Delete the source item
		GetListCtrl().DeleteItem(m_nDragIndex);
	}
}


// {group:View Classes}
// 
// Name: 
// 	cvCTestView::OnDeleteItem
// 
// Description:
// 	Called by the framework before a listctrl item is deleted.  
//  The cvCDragDropItem pointed to by the list entry's itemdata is deleted 
// 
// Arguments:
// 	pNMHDR - A pointer to the notification message header
// 
// 	pResult - A pointer to the result value
// 
void cvCTestView::OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	ASSERT(pNMListView != NULL);

	if (pNMListView && pNMListView->lParam)
	{
		TRACE1("CTestView::OnDeleteItem: Delete Test Item (%p)\n", (cvCDragDropItem*) pNMListView->lParam);

		delete ((cvCDragDropItem*) pNMListView->lParam);
		pNMListView->lParam = 0;
	}	
	*pResult = 0;
}

