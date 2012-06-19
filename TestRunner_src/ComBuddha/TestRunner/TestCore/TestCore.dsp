# Microsoft Developer Studio Project File - Name="TestCore" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TestCore - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TestCore.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestCore.mak" CFG="TestCore - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestCore - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TestCore - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TestCore - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TestCore - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TestCore - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I ".\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD MTL /I ".\Include"
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Debug/TestCoreD.dll" /pdbtype:sept
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=.\Debug\TestCoreD.dll
InputPath=.\Debug\TestCoreD.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TestCore - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I ".\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD MTL /I ".\Include"
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"DebugU/TestCoreDU.dll" /pdbtype:sept
# Begin Custom Build - Performing registration
OutDir=.\DebugU
TargetPath=.\DebugU\TestCoreDU.dll
InputPath=.\DebugU\TestCoreDU.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TestCore - Win32 Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /I ".\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_ATL_DLL" /Yu"stdafx.h" /FD /c
# ADD MTL /I ".\Include"
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\TestCore.dll
InputPath=.\ReleaseMinSize\TestCore.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "TestCore - Win32 Unicode Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinSize"
# PROP BASE Intermediate_Dir "ReleaseUMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinSize"
# PROP Intermediate_Dir "ReleaseUMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /I ".\Include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /FR /Yu"stdafx.h" /FD /c
# ADD MTL /I ".\Include"
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"ReleaseUMinSize/TestCoreU.dll"
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\TestCoreU.dll
InputPath=.\ReleaseUMinSize\TestCoreU.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "TestCore - Win32 Debug"
# Name "TestCore - Win32 Unicode Debug"
# Name "TestCore - Win32 Release MinSize"
# Name "TestCore - Win32 Unicode Release MinSize"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CTestOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\CTestSuite.cpp
# End Source File
# Begin Source File

SOURCE=.\CTestSuiteItem.cpp
# End Source File
# Begin Source File

SOURCE=.\dlldatax.c
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TestCore.cpp
# End Source File
# Begin Source File

SOURCE=.\TestCore.idl
# ADD MTL /tlb ".\TestCore.tlb" /h "TestCore.h" /iid "TestCore_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\TestCoreXMLFormatDefs.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CDurationCounter.h

!IF  "$(CFG)" == "TestCore - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TestCore - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TestCore - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "TestCore - Win32 Unicode Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CPropertyTester.h

!IF  "$(CFG)" == "TestCore - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TestCore - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TestCore - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "TestCore - Win32 Unicode Release MinSize"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CTestOutput.h
# End Source File
# Begin Source File

SOURCE=.\CTestSuite.h
# End Source File
# Begin Source File

SOURCE=.\CTestSuiteItem.h
# End Source File
# Begin Source File

SOURCE=.\dlldatax.h
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TestCoreXMLFormatDefs.h

!IF  "$(CFG)" == "TestCore - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TestCore - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TestCore - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "TestCore - Win32 Unicode Release MinSize"

!ENDIF 

# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\CTest.rgs
# End Source File
# Begin Source File

SOURCE=.\CTestOutput.rgs
# End Source File
# Begin Source File

SOURCE=.\CTestSuite.rgs
# End Source File
# Begin Source File

SOURCE=.\CTestSuiteCollection.rgs
# End Source File
# Begin Source File

SOURCE=.\CTestSuiteItem.rgs
# End Source File
# Begin Source File

SOURCE=.\CTestSuiteItemCollection.rgs
# End Source File
# Begin Source File

SOURCE=.\TestCore.rc
# End Source File
# End Group
# Begin Group "Interfaces"

# PROP Default_Filter "idl"
# Begin Source File

SOURCE=.\Include\EnumCollectionHelper.idl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\IDirectLoad.idl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\IEnumTestSuiteItems.idl
# ADD MTL /tlb "" /h "IEnumTestSuiteItems.h" /iid "IEnumTestSuiteItems_i.c"
# End Source File
# Begin Source File

SOURCE=.\IEnumTestSuites.idl
# ADD MTL /tlb "" /h "IEnumTestSuites.h" /iid "IEnumTestSuites_i.c"
# End Source File
# Begin Source File

SOURCE=.\ITest.idl
# ADD MTL /tlb "" /h "ITest.h" /iid "ITest_i.c"
# End Source File
# Begin Source File

SOURCE=.\ITestOutput.idl
# ADD MTL /tlb "" /h "ITestOutput.h" /iid "ITestOutput_i.c"
# End Source File
# Begin Source File

SOURCE=.\ITestSuite.idl
# ADD MTL /tlb "" /h "ITestSuite.h" /iid "ITestSuite_i.c"
# End Source File
# Begin Source File

SOURCE=.\ITestSuiteCollection.idl
# ADD MTL /tlb "" /h "ITestSuiteCollection.h" /iid "ITestSuiteCollection_i.c"
# End Source File
# Begin Source File

SOURCE=.\ITestSuiteItem.idl
# ADD MTL /tlb "" /h "ItestSuiteItem.h" /iid "ItestSuiteItem_i.c"
# End Source File
# Begin Source File

SOURCE=.\ITestSuiteItemCollection.idl
# ADD MTL /tlb "" /h "ITestSuiteItemCollection.h" /iid "ITestSuiteItemCollection_i.c"
# End Source File
# End Group
# Begin Group "Collections and Enums"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CTestSuiteCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\CTestSuiteCollection.h
# End Source File
# Begin Source File

SOURCE=.\CTestSuiteItemCollection.cpp
# End Source File
# Begin Source File

SOURCE=.\CTestSuiteItemCollection.h
# End Source File
# End Group
# Begin Group "Defs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TestCore.def
# End Source File
# End Group
# Begin Group "Inlines"

# PROP Default_Filter ".inl"
# Begin Source File

SOURCE=.\SetValue.inl

!IF  "$(CFG)" == "TestCore - Win32 Debug"

!ELSEIF  "$(CFG)" == "TestCore - Win32 Unicode Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TestCore - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "TestCore - Win32 Unicode Release MinSize"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\OverView.gls

!IF  "$(CFG)" == "TestCore - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "TestCore - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "TestCore - Win32 Release MinSize"

!ELSEIF  "$(CFG)" == "TestCore - Win32 Unicode Release MinSize"

!ENDIF 

# End Source File
# End Target
# End Project
