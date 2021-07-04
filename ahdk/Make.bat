@echo off
 
rem Usage:
rem Make.bat activeondx G:\
rem TCC download: http://download.savannah.gnu.org/releases/tinycc/

set CC=tcc

where %CC% >nul
if %ERRORLEVEL% neq 0 (
	echo !!!! %CC% Not found.
	exit /b
)

rem Host CC info
set CFLAGS=-include "../platform/%1.h" '-DHOSTCC="%CC%"'
 
%CC% Build.c %CFLAGS% -o Build.exe
Build.exe minimal test.c
 
del Build.exe