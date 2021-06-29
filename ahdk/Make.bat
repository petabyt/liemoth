@echo off
rem Usage:
rem Make.bat activeondx G:\

set CC=tcc
set CLFAGS=-include "../platform/$1"

%CC% Build.c %CFLAGS% -o Build.exe
Build.exe minimal

del Build.exe