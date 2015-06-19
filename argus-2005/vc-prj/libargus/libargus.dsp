# Microsoft Developer Studio Project File - Name="libargus" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libargus - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libargus.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libargus.mak" CFG="libargus - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libargus - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libargus - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libargus - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libargus - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "libargus - Win32 Release"
# Name "libargus - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "util"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\util\aggre.c
# End Source File
# Begin Source File

SOURCE=..\..\src\util\btype.c
# End Source File
# Begin Source File

SOURCE=..\..\src\util\expr.c
# End Source File
# Begin Source File

SOURCE=..\..\src\util\libtype.c
# End Source File
# Begin Source File

SOURCE=..\..\src\util\llist.c
# End Source File
# Begin Source File

SOURCE=..\..\src\util\osdept.c
# End Source File
# Begin Source File

SOURCE=..\..\src\util\pool.c
# End Source File
# Begin Source File

SOURCE=..\..\src\util\schema.c
# End Source File
# Begin Source File

SOURCE=..\..\src\util\type_schema.c
# End Source File
# End Group
# Begin Group "oper"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\oper\countslidewindow.c
# End Source File
# Begin Source File

SOURCE=..\..\src\oper\counttumblewindow.c
# End Source File
# Begin Source File

SOURCE=..\..\src\oper\equijoin.c
# End Source File
# Begin Source File

SOURCE=..\..\src\oper\filter.c
# End Source File
# Begin Source File

SOURCE=..\..\src\oper\group.c
# End Source File
# Begin Source File

SOURCE=..\..\src\oper\map.c
# End Source File
# Begin Source File

SOURCE=..\..\src\oper\sender.c
# End Source File
# Begin Source File

SOURCE=..\..\src\oper\timer.c
# End Source File
# Begin Source File

SOURCE=..\..\src\oper\timeslidewindow.c
# End Source File
# Begin Source File

SOURCE=..\..\src\oper\timetumblewindow.c
# End Source File
# End Group
# Begin Group "core"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\core\core.c
# End Source File
# Begin Source File

SOURCE=..\..\src\core\index.inl
# End Source File
# Begin Source File

SOURCE=..\..\src\core\stream.c
# End Source File
# End Group
# Begin Group "sql"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\sql\api.c
# End Source File
# Begin Source File

SOURCE=..\..\src\sql\lex.sql.c
# End Source File
# Begin Source File

SOURCE=..\..\src\sql\local_api.c
# End Source File
# Begin Source File

SOURCE=..\..\src\sql\opt.c
# End Source File
# Begin Source File

SOURCE=..\..\src\sql\plan.c
# End Source File
# Begin Source File

SOURCE=..\..\src\sql\sql.tab.c
# End Source File
# Begin Source File

SOURCE=..\..\src\sql\sql.tab.h
# End Source File
# Begin Source File

SOURCE=..\..\src\sql\sql_dump.c
# End Source File
# Begin Source File

SOURCE=..\..\src\sql\sql_help.c
# End Source File
# Begin Source File

SOURCE=..\..\src\sql\sql_resolve.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\include\aggre.h
# End Source File
# Begin Source File

SOURCE=..\..\include\api.h
# End Source File
# Begin Source File

SOURCE=..\..\include\argus.h
# End Source File
# Begin Source File

SOURCE=..\..\include\buffer.h
# End Source File
# Begin Source File

SOURCE=..\..\include\cmnhdr.h
# End Source File
# Begin Source File

SOURCE=..\..\include\config.h
# End Source File
# Begin Source File

SOURCE=..\..\include\core.h
# End Source File
# Begin Source File

SOURCE=..\..\include\expr.h
# End Source File
# Begin Source File

SOURCE=..\..\include\libtype.h
# End Source File
# Begin Source File

SOURCE=..\..\include\llist.h
# End Source File
# Begin Source File

SOURCE=..\..\include\osdept.h
# End Source File
# Begin Source File

SOURCE=..\..\include\plan.h
# End Source File
# Begin Source File

SOURCE=..\..\include\pool.h
# End Source File
# Begin Source File

SOURCE=..\..\include\queue.h
# End Source File
# Begin Source File

SOURCE=..\..\include\schema.h
# End Source File
# Begin Source File

SOURCE=..\..\include\sql.h
# End Source File
# Begin Source File

SOURCE=..\..\include\sqlopr.h
# End Source File
# Begin Source File

SOURCE=..\..\include\stack.h
# End Source File
# Begin Source File

SOURCE=..\..\include\stream.h
# End Source File
# Begin Source File

SOURCE=..\..\include\timer.h
# End Source File
# End Group
# Begin Group "others"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\src\sql\bison.hairy
# End Source File
# Begin Source File

SOURCE=..\..\src\sql\bison.simple
# End Source File
# Begin Source File

SOURCE=..\..\src\sql\sql.lex
# End Source File
# Begin Source File

SOURCE=..\..\src\sql\sql.y
# End Source File
# End Group
# Begin Group "tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\tools\bison.exe
# End Source File
# Begin Source File

SOURCE=..\..\tools\flex.exe
# End Source File
# End Group
# Begin Group "makefile"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Makefile\Makefile.borland
# End Source File
# Begin Source File

SOURCE=..\..\Makefile\Makefile.linux
# End Source File
# Begin Source File

SOURCE=..\..\Makefile\Makefile.vc
# End Source File
# End Group
# End Target
# End Project
