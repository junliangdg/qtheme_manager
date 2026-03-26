@echo off
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"
set CMAKE="C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"
set NINJA="C:\Users\Joon.Ye\AppData\Local\Microsoft\WinGet\Packages\Ninja-build.Ninja_Microsoft.Winget.Source_8wekyb3d8bbwe\ninja.exe"
set QTDIR=C:\Qt\6.9.0\msvc2022_64

:: Build both QThemeLib.dll and QThemeDemo (default)
:: To build only the DLL (e.g. when used as a submodule), add: -DQTHEME_BUILD_DEMO=OFF
%CMAKE% -S "d:\repos\qtheme_manager" -B "d:\repos\qtheme_manager\build" -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=%NINJA% -DCMAKE_PREFIX_PATH=%QTDIR%
if %ERRORLEVEL% NEQ 0 goto :error

%CMAKE% --build "d:\repos\qtheme_manager\build" --config Debug
if %ERRORLEVEL% NEQ 0 goto :error

echo BUILD SUCCESS
goto :end
:error
echo BUILD FAILED with error %ERRORLEVEL%
:end
