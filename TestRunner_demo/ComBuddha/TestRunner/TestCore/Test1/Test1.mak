# Microsoft Developer Studio Generated NMAKE File, Based on Test1.dsp
!IF "$(CFG)" == ""
CFG=Test1 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Test1 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Test1 - Win32 Debug" && "$(CFG)" != "Test1 - Win32 Unicode Debug" && "$(CFG)" != "Test1 - Win32 Release MinSize" && "$(CFG)" != "Test1 - Win32 Unicode Release MinSize"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Test1.mak" CFG="Test1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Test1 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Test1 - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Test1 - Win32 Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Test1 - Win32 Unicode Release MinSize" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Test1 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Test1.dll" "$(OUTDIR)\Test1.bsc" ".\Debug\regsvr32.trg"

!ELSE 

ALL : "TestCore - Win32 Debug" "$(OUTDIR)\Test1.dll" "$(OUTDIR)\Test1.bsc" ".\Debug\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"TestCore - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\Test1.obj"
	-@erase "$(INTDIR)\Test1.pch"
	-@erase "$(INTDIR)\Test1.res"
	-@erase "$(INTDIR)\Test1.sbr"
	-@erase "$(INTDIR)\TestComponent1.obj"
	-@erase "$(INTDIR)\TestComponent1.sbr"
	-@erase "$(INTDIR)\TestComponent2.obj"
	-@erase "$(INTDIR)\TestComponent2.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Test1.bsc"
	-@erase "$(OUTDIR)\Test1.dll"
	-@erase "$(OUTDIR)\Test1.exp"
	-@erase "$(OUTDIR)\Test1.ilk"
	-@erase "$(OUTDIR)\Test1.lib"
	-@erase "$(OUTDIR)\Test1.pdb"
	-@erase ".\Test1.h"
	-@erase ".\Test1.tlb"
	-@erase ".\Test1_i.c"
	-@erase ".\Debug\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_SHOW_PROPERY_NAME" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Test1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Test1.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Test1.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\Test1.sbr" \
	"$(INTDIR)\TestComponent1.sbr" \
	"$(INTDIR)\TestComponent2.sbr"

"$(OUTDIR)\Test1.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Test1.pdb" /debug /machine:I386 /def:".\Test1.def" /out:"$(OUTDIR)\Test1.dll" /implib:"$(OUTDIR)\Test1.lib" /pdbtype:sept 
DEF_FILE= \
	".\Test1.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Test1.obj" \
	"$(INTDIR)\TestComponent1.obj" \
	"$(INTDIR)\TestComponent2.obj" \
	"$(INTDIR)\Test1.res" \
	"..\Debug\TestCoreD.lib"

"$(OUTDIR)\Test1.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\Debug
TargetPath=.\Debug\Test1.dll
InputPath=.\Debug\Test1.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Test1 - Win32 Unicode Debug"

OUTDIR=.\DebugU
INTDIR=.\DebugU
# Begin Custom Macros
OutDir=.\DebugU
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Test1.dll" "$(OUTDIR)\Test1.bsc" ".\DebugU\regsvr32.trg"

!ELSE 

ALL : "TestCore - Win32 Unicode Debug" "$(OUTDIR)\Test1.dll" "$(OUTDIR)\Test1.bsc" ".\DebugU\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"TestCore - Win32 Unicode DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\Test1.obj"
	-@erase "$(INTDIR)\Test1.pch"
	-@erase "$(INTDIR)\Test1.res"
	-@erase "$(INTDIR)\Test1.sbr"
	-@erase "$(INTDIR)\TestComponent1.obj"
	-@erase "$(INTDIR)\TestComponent1.sbr"
	-@erase "$(INTDIR)\TestComponent2.obj"
	-@erase "$(INTDIR)\TestComponent2.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Test1.bsc"
	-@erase "$(OUTDIR)\Test1.dll"
	-@erase "$(OUTDIR)\Test1.exp"
	-@erase "$(OUTDIR)\Test1.ilk"
	-@erase "$(OUTDIR)\Test1.lib"
	-@erase "$(OUTDIR)\Test1.pdb"
	-@erase ".\Test1.h"
	-@erase ".\Test1.tlb"
	-@erase ".\Test1_i.c"
	-@erase ".\DebugU\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Test1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/I "..\\" 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Test1.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Test1.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\Test1.sbr" \
	"$(INTDIR)\TestComponent1.sbr" \
	"$(INTDIR)\TestComponent2.sbr"

"$(OUTDIR)\Test1.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Test1.pdb" /debug /machine:I386 /def:".\Test1.def" /out:"$(OUTDIR)\Test1.dll" /implib:"$(OUTDIR)\Test1.lib" /pdbtype:sept 
DEF_FILE= \
	".\Test1.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Test1.obj" \
	"$(INTDIR)\TestComponent1.obj" \
	"$(INTDIR)\TestComponent2.obj" \
	"$(INTDIR)\Test1.res" \
	"..\DebugU\TestCoreDU.lib"

"$(OUTDIR)\Test1.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\DebugU
TargetPath=.\DebugU\Test1.dll
InputPath=.\DebugU\Test1.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ELSEIF  "$(CFG)" == "Test1 - Win32 Release MinSize"

OUTDIR=.\ReleaseMinSize
INTDIR=.\ReleaseMinSize
# Begin Custom Macros
OutDir=.\ReleaseMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Test1.dll" ".\ReleaseMinSize\regsvr32.trg"

!ELSE 

ALL : "TestCore - Win32 Release MinSize" "$(OUTDIR)\Test1.dll" ".\ReleaseMinSize\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"TestCore - Win32 Release MinSizeCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Test1.obj"
	-@erase "$(INTDIR)\Test1.pch"
	-@erase "$(INTDIR)\Test1.res"
	-@erase "$(INTDIR)\TestComponent1.obj"
	-@erase "$(INTDIR)\TestComponent2.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Test1.dll"
	-@erase "$(OUTDIR)\Test1.exp"
	-@erase "$(OUTDIR)\Test1.lib"
	-@erase ".\Test1.h"
	-@erase ".\Test1.tlb"
	-@erase ".\Test1_i.c"
	-@erase ".\ReleaseMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ATL_DLL" /Fp"$(INTDIR)\Test1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Test1.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Test1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Test1.pdb" /machine:I386 /def:".\Test1.def" /out:"$(OUTDIR)\Test1.dll" /implib:"$(OUTDIR)\Test1.lib" 
DEF_FILE= \
	".\Test1.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Test1.obj" \
	"$(INTDIR)\TestComponent1.obj" \
	"$(INTDIR)\TestComponent2.obj" \
	"$(INTDIR)\Test1.res" \
	"..\ReleaseMinSize\TestCore.lib"

"$(OUTDIR)\Test1.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\Test1.dll
InputPath=.\ReleaseMinSize\Test1.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
<< 
	

!ELSEIF  "$(CFG)" == "Test1 - Win32 Unicode Release MinSize"

OUTDIR=.\ReleaseUMinSize
INTDIR=.\ReleaseUMinSize
# Begin Custom Macros
OutDir=.\ReleaseUMinSize
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\Test1.dll" ".\ReleaseUMinSize\regsvr32.trg"

!ELSE 

ALL : "TestCore - Win32 Unicode Release MinSize" "$(OUTDIR)\Test1.dll" ".\ReleaseUMinSize\regsvr32.trg"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"TestCore - Win32 Unicode Release MinSizeCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Test1.obj"
	-@erase "$(INTDIR)\Test1.pch"
	-@erase "$(INTDIR)\Test1.res"
	-@erase "$(INTDIR)\TestComponent1.obj"
	-@erase "$(INTDIR)\TestComponent2.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Test1.dll"
	-@erase "$(OUTDIR)\Test1.exp"
	-@erase "$(OUTDIR)\Test1.lib"
	-@erase ".\Test1.h"
	-@erase ".\Test1.tlb"
	-@erase ".\Test1_i.c"
	-@erase ".\ReleaseUMinSize\regsvr32.trg"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\Test1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Test1.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Test1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Test1.pdb" /machine:I386 /def:".\Test1.def" /out:"$(OUTDIR)\Test1.dll" /implib:"$(OUTDIR)\Test1.lib" 
DEF_FILE= \
	".\Test1.def"
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Test1.obj" \
	"$(INTDIR)\TestComponent1.obj" \
	"$(INTDIR)\TestComponent2.obj" \
	"$(INTDIR)\Test1.res" \
	"..\ReleaseUMinSize\TestCoreU.lib"

"$(OUTDIR)\Test1.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\Test1.dll
InputPath=.\ReleaseUMinSize\Test1.dll
SOURCE="$(InputPath)"

"$(OUTDIR)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	<<tempfile.bat 
	@echo off 
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode DLL on Windows 95 
	:end 
<< 
	

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Test1.dep")
!INCLUDE "Test1.dep"
!ELSE 
!MESSAGE Warning: cannot find "Test1.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Test1 - Win32 Debug" || "$(CFG)" == "Test1 - Win32 Unicode Debug" || "$(CFG)" == "Test1 - Win32 Release MinSize" || "$(CFG)" == "Test1 - Win32 Unicode Release MinSize"
SOURCE=.\dlldatax.c
SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Test1 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_SHOW_PROPERY_NAME" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Test1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Test1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Test1 - Win32 Unicode Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Test1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Test1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Test1 - Win32 Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "ATL_DLL" /Fp"$(INTDIR)\Test1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Test1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Test1 - Win32 Unicode Release MinSize"

CPP_SWITCHES=/nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_UNICODE" /D "_ATL_DLL" /Fp"$(INTDIR)\Test1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Test1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Test1.cpp

!IF  "$(CFG)" == "Test1 - Win32 Debug"


"$(INTDIR)\Test1.obj"	"$(INTDIR)\Test1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Test1.pch" ".\Test1.h" ".\Test1_i.c"


!ELSEIF  "$(CFG)" == "Test1 - Win32 Unicode Debug"


"$(INTDIR)\Test1.obj"	"$(INTDIR)\Test1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Test1.pch" ".\Test1_i.c" ".\Test1.h"


!ELSEIF  "$(CFG)" == "Test1 - Win32 Release MinSize"


"$(INTDIR)\Test1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Test1.pch" ".\Test1_i.c" ".\Test1.h"


!ELSEIF  "$(CFG)" == "Test1 - Win32 Unicode Release MinSize"


"$(INTDIR)\Test1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Test1.pch" ".\Test1_i.c" ".\Test1.h"


!ENDIF 

SOURCE=.\Test1.idl

!IF  "$(CFG)" == "Test1 - Win32 Debug"

MTL_SWITCHES=/tlb ".\Test1.tlb" /h "Test1.h" /iid "Test1_i.c" /Oicf 

".\Test1.tlb"	".\Test1.h"	".\Test1_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Test1 - Win32 Unicode Debug"

MTL_SWITCHES=/I "..\\" /tlb ".\Test1.tlb" /h "Test1.h" /iid "Test1_i.c" /Oicf 

".\Test1.tlb"	".\Test1.h"	".\Test1_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Test1 - Win32 Release MinSize"

MTL_SWITCHES=/tlb ".\Test1.tlb" /h "Test1.h" /iid "Test1_i.c" /Oicf 

".\Test1.tlb"	".\Test1.h"	".\Test1_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Test1 - Win32 Unicode Release MinSize"

MTL_SWITCHES=/tlb ".\Test1.tlb" /h "Test1.h" /iid "Test1_i.c" /Oicf 

".\Test1.tlb"	".\Test1.h"	".\Test1_i.c" : $(SOURCE) "$(INTDIR)"
	$(MTL) @<<
  $(MTL_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Test1.rc

"$(INTDIR)\Test1.res" : $(SOURCE) "$(INTDIR)" ".\Test1.tlb"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\TestComponent1.cpp

!IF  "$(CFG)" == "Test1 - Win32 Debug"


"$(INTDIR)\TestComponent1.obj"	"$(INTDIR)\TestComponent1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Test1.pch" ".\Test1.h"


!ELSEIF  "$(CFG)" == "Test1 - Win32 Unicode Debug"


"$(INTDIR)\TestComponent1.obj"	"$(INTDIR)\TestComponent1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Test1.pch" ".\Test1.h"


!ELSEIF  "$(CFG)" == "Test1 - Win32 Release MinSize"


"$(INTDIR)\TestComponent1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Test1.pch" ".\Test1.h"


!ELSEIF  "$(CFG)" == "Test1 - Win32 Unicode Release MinSize"


"$(INTDIR)\TestComponent1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Test1.pch" ".\Test1.h"


!ENDIF 

SOURCE=.\TestComponent2.cpp

!IF  "$(CFG)" == "Test1 - Win32 Debug"


"$(INTDIR)\TestComponent2.obj"	"$(INTDIR)\TestComponent2.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Test1.pch" ".\Test1.h"


!ELSEIF  "$(CFG)" == "Test1 - Win32 Unicode Debug"


"$(INTDIR)\TestComponent2.obj"	"$(INTDIR)\TestComponent2.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Test1.pch" ".\Test1.h"


!ELSEIF  "$(CFG)" == "Test1 - Win32 Release MinSize"


"$(INTDIR)\TestComponent2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Test1.pch" ".\Test1.h"


!ELSEIF  "$(CFG)" == "Test1 - Win32 Unicode Release MinSize"


"$(INTDIR)\TestComponent2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Test1.pch" ".\Test1.h"


!ENDIF 

!IF  "$(CFG)" == "Test1 - Win32 Debug"

"TestCore - Win32 Debug" : 
   cd "\CliniVision\Development\Code\TestCore"
   $(MAKE) /$(MAKEFLAGS) /F .\TestCore.mak CFG="TestCore - Win32 Debug" 
   cd ".\Test1"

"TestCore - Win32 DebugCLEAN" : 
   cd "\CliniVision\Development\Code\TestCore"
   $(MAKE) /$(MAKEFLAGS) /F .\TestCore.mak CFG="TestCore - Win32 Debug" RECURSE=1 CLEAN 
   cd ".\Test1"

!ELSEIF  "$(CFG)" == "Test1 - Win32 Unicode Debug"

"TestCore - Win32 Unicode Debug" : 
   cd "\CliniVision\Development\Code\TestCore"
   $(MAKE) /$(MAKEFLAGS) /F .\TestCore.mak CFG="TestCore - Win32 Unicode Debug" 
   cd ".\Test1"

"TestCore - Win32 Unicode DebugCLEAN" : 
   cd "\CliniVision\Development\Code\TestCore"
   $(MAKE) /$(MAKEFLAGS) /F .\TestCore.mak CFG="TestCore - Win32 Unicode Debug" RECURSE=1 CLEAN 
   cd ".\Test1"

!ELSEIF  "$(CFG)" == "Test1 - Win32 Release MinSize"

"TestCore - Win32 Release MinSize" : 
   cd "\CliniVision\Development\Code\TestCore"
   $(MAKE) /$(MAKEFLAGS) /F .\TestCore.mak CFG="TestCore - Win32 Release MinSize" 
   cd ".\Test1"

"TestCore - Win32 Release MinSizeCLEAN" : 
   cd "\CliniVision\Development\Code\TestCore"
   $(MAKE) /$(MAKEFLAGS) /F .\TestCore.mak CFG="TestCore - Win32 Release MinSize" RECURSE=1 CLEAN 
   cd ".\Test1"

!ELSEIF  "$(CFG)" == "Test1 - Win32 Unicode Release MinSize"

"TestCore - Win32 Unicode Release MinSize" : 
   cd "\CliniVision\Development\Code\TestCore"
   $(MAKE) /$(MAKEFLAGS) /F .\TestCore.mak CFG="TestCore - Win32 Unicode Release MinSize" 
   cd ".\Test1"

"TestCore - Win32 Unicode Release MinSizeCLEAN" : 
   cd "\CliniVision\Development\Code\TestCore"
   $(MAKE) /$(MAKEFLAGS) /F .\TestCore.mak CFG="TestCore - Win32 Unicode Release MinSize" RECURSE=1 CLEAN 
   cd ".\Test1"

!ENDIF 


!ENDIF 

