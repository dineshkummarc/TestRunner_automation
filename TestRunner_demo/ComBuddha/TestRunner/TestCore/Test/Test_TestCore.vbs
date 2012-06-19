'on error resume next

Dim oTestSuiteCollection
'As cvCTestSuiteCollection
Set oTestSuiteCollection = CreateObject("TestCore.cvCTestSuiteCollection")

Dim oTestSuite  
'As cvCTestSuite
Set oTestSuite = CreateObject("TestCore.cvCTestSuite")

Dim oTestSuiteItemCollection  
'As cvCTestSuiteItemCollection
Set oTestSuiteItemCollection = CreateObject("TestCore.cvCTestSuiteItemCollection")

' Initialize the test suite item collection from the registry
Call oTestSuiteItemCollection.LoadFromRegistry

' Set the test suite item collection for the test suite
oTestSuite.TestSuiteItems = oTestSuiteItemCollection

' Add the test suite to the collection of test suites
Call oTestSuiteCollection.Add(oTestSuite)


dim oTestSuite2
For Each oTestSuite2 In oTestSuiteCollection

    Dim oTestSuiteItemCollection2
    set oTestSuiteItemCollection2 = oTestSuite2.TestSuiteItems

	dim oTestSuiteItem
	for each oTestSuiteItem in oTestSuiteItemCollection2

		dim title
		title = oTestSuiteItem.ProgId

		MsgBox "Test Name = " & oTestSuiteItem.TestName, vbOKOnly, title
		MsgBox "Description = " & oTestSuiteItem.Description, vbOKOnly, title
		MsgBox "ProgId = " & title, vbOKOnly, title
		MsgBox "Run Count = " & oTestSuiteItem.RunCount, vbOKOnly, title
	
	Next 
	
	set oTestSuiteItem = nothing
	set oTestSuiteItemCollection2 = nothing

Next

dim tsc
set tsc = CreateObject("TestCore.cvCTestSuiteCollection")

tsc.RunCount = 10
MsgBox("Run Count = " & tsc.RunCount)

set tsc = nothing
set oTestSuiteItemCollection = nothing
set oTestSuite = nothing


' Test the output

dim oTestOutput
set oTestOutput = CreateObject("TestCore.cvCTestOutput")

oTestOutput.LogFileName = "c:\TestOutput.xml"
oTestOutput.TestName = "This is a big test"

'oTestOutput.LogResult("this is a result")

dim oTestComponent
set oTestComponent = CreateObject("Test1.TestComponent1")

for i = 0 to 0
	call oTestComponent.Run(oTestOutput, "Hello")
next






