@ECHO OFF

SET BUILD_TYPE=%1

ECHO #
ECHO # Building %BUILD_TYPE% version...
ECHO #

REM the name of the application
SET APP_NAME=april
SET QT_VER=5_0_2

REM save current drive
SET drive=%cd:~0,2%

REM prepare Qt environment
CALL %QTDIR%\qtenv2.bat

REM make sure we're back on same drive
%drive%

REM up to parent directory
PUSHD ..\..\.. > /dev/null 2>&1

REM make a directory for our build
mkdir %APP_NAME%-%QT_VER%-%BUILD_TYPE% > /dev/null 2>&1
cd %APP_NAME%-%QT_VER%-%BUILD_TYPE%

REM generate makefiles
SET PRO_FILE=%cd%\..\%APP_NAME%\tools\Qt\%APP_NAME%.pro
%QTDIR%\qmake.exe -makefile -spec win32-g++ "%PRO_FILE%" "CONFIG+=%BUILD_TYPE%" 

REM build the project
mingw32-make -j 2 > make.log

REM back to original directory
POPD > /dev/null 2>&1

ECHO #
ECHO # Done building %BUILD_TYPE% version 
ECHO #
pause


