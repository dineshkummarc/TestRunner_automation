#pragma once
// 
// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// File:
//    cvDragDropItem.h 
// 
// Description:
//    Declares cvCDragDropItem class 
// 
// $Log: 
//  2    CliniVision1.1         11/16/99 4:59:41 PM  Doug C. Eveland Added copy
//       constructor
//  1    CliniVision1.0         11/9/99 11:22:49 AM  Doug C. Eveland 
// $
// $Revision: 2$
// $Date: 11/16/99 4:59:41 PM$
// $Author: Doug C. Eveland$
// 
// 

// {group:Helper Classes}
// 
// Description:
// 	Used to display a tree of test suites and tests
// 
// Author:
// 	Doug Eveland
// 
// Name:
//    cvCDragDropItem
// 
// Description:
//    Contains information about a drag-drop item
// 
// Author:
//    Doug Eveland
// 
class cvCDragDropItem
{ 
public: 
	// Group=ENUMS AND TYPEDEFS 

	// Enumeration used to indicate whether a dragdrop item is a 
	// test or a suite
	enum EDragDropType 
	{
		EDragDropType_Test = 0,
		EDragDropType_Suite
	};

	// Group=TORS
	cvCDragDropItem() {Init();}

	cvCDragDropItem(const cvCDragDropItem& rcvDragDropItem) 
	{
		Init();
		SetType(rcvDragDropItem.GetType());
		SetCLSID(rcvDragDropItem.GetCLSID());
		SetName(rcvDragDropItem.GetName());
		SetDescription(rcvDragDropItem.GetDescription()); 
		SetRunCount(rcvDragDropItem.GetRunCount());
	}
	virtual ~cvCDragDropItem() {}
    
	// Group=METHODS 

	// 
	// Name: Init
	// 
	// Description:
	// 	Initializes class variables
	// 
	void Init()
	{
		m_eDragDropType = EDragDropType_Test;
		m_nRunCount = 0;
		m_nNumTestRuns = 0;
		m_bSelected = FALSE;
	}

	// Retrieves Type property
	EDragDropType GetType() const {return m_eDragDropType;}
	// Retrieves CLSID property
	CLSID GetCLSID() const {return m_clsid;}
	// Retrieves Name property
	_bstr_t GetName() const {return m_bstrName;}
	// Retrieves Description property
	_bstr_t GetDescription() const {return m_bstrDescription;}
	// Retrieves RunCount property
	int GetRunCount() const {return m_nRunCount;}
	// Retrieves Selected property
	BOOL GetSelected() const {return m_bSelected;}
	// Retrieves NumTestRuns property
	int GetNumTestRuns() const {return m_nNumTestRuns;}

	// Increments RunCount
	void IncrementCount() {m_nRunCount++;}
	// Decrements RunCount
	void DecrementCount() {if (m_nRunCount > 0) m_nRunCount--;}

	// Sets the drag drop type property
	void SetType(EDragDropType eDragDropType) {m_eDragDropType = eDragDropType;}
	// Sets the CLSID property (only valid for test items)
	void SetCLSID(CLSID clsid) {m_clsid = clsid;}
	// Sets the name property
	void SetName(_bstr_t bstrName) {m_bstrName = bstrName;}
	// Sets the description property
	void SetDescription(_bstr_t bstrDescription) {m_bstrDescription = bstrDescription;}
	// Sets the runcount property (indicates how many times the test/suite should be run
	void SetRunCount(int nRunCount) {m_nRunCount = nRunCount;}
	// Sets the Selected property (Bool which indicates whether this test/suite should be run)
	void SetSelected(BOOL bSelected) {m_bSelected = bSelected;}
	// Sets the NumTestRuns property (tracks # number of tests that have been run so far)
	void SetNumTestRuns(int nNumTestRuns) {m_nNumTestRuns = nNumTestRuns;}
     
	// Group=OPERATORS 


	// 
	// Name: operator=
	// 
	// Description:
	// 	Assignment operator - copies each property from one instance of the object to another
	// 
	// Arguments:
	// 	rcvCDragDropItem - A reference to the item whose properties are to be copied
	// 
	// Results:
	// 	Returns a  reference to itself
	// 
	cvCDragDropItem& operator=(cvCDragDropItem& rcvCDragDropItem)
	{
		SetType(rcvCDragDropItem.GetType());
		SetCLSID(rcvCDragDropItem.GetCLSID());
		SetName(rcvCDragDropItem.GetName());
		SetDescription(rcvCDragDropItem.GetDescription()); 
		SetRunCount(rcvCDragDropItem.GetRunCount());

		return *this;
	}
	bool operator==(const cvCDragDropItem& rcvCDragDropItem);
 
	// Group=ATTRIBUTES 
     
protected: 
 
	// Group=PROTECTED METHODS 

	// Group=PROTECTED MEMBER DATA 
 
private: 
 
	// Group=PRIVATE METHODS 

	// Group=PRIVATE MEMBER DATA 
	EDragDropType m_eDragDropType;	// type of drag drop object, suite or test
	CLSID m_clsid;					// clsid of test object
	_bstr_t m_bstrName;				// name of test
	_bstr_t m_bstrDescription;		// description of test
	int m_nRunCount;				// # of times this test/suite should be run
	int m_nNumTestRuns;				// # of times this suite has been run (does not apply to tests)
	BOOL m_bSelected;				// TRUE if this test/suite will be run.
	// Group=FRIENDS 
}; 
    
