@echo off
setlocal enabledelayedexpansion

echo ========================================
echo   MATRIX LIBRARY - Build ^& Run Script
echo ========================================

:: Check for g++
where g++ >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo [ERROR] g++ compiler not found! Please install MinGW or similar.
    pause
    exit /b 1
)

:menu
echo.
echo 1. Build Static Library (libmatrix.a)
echo 2. Build Dynamic Library (matrix.dll)
echo 3. Run Gaussian Elimination (using Static Lib)
echo 4. Run LU Decomposition (using Static Lib)
echo 5. Run Gaussian Elimination (using Dynamic Lib)
echo 6. Clean Build Files
echo 7. Exit
echo.
set /p choice="Choose an option (1-7): "

if "%choice%"=="1" goto build_static
if "%choice%"=="2" goto build_dynamic
if "%choice%"=="3" goto run_main_static
if "%choice%"=="4" goto run_lu_static
if "%choice%"=="5" goto run_main_dynamic
if "%choice%"=="6" goto clean
if "%choice%"=="7" exit /b 0

echo Invalid choice, try again.
goto menu

:build_static
echo.
echo Compiling object files...
g++ -std=c++17 -Wall -IInclude -c Src/Matrix_Methods.cpp -o Src/Matrix_Methods.o
g++ -std=c++17 -Wall -IInclude -c Src/Matrix_Algorithms.cpp -o Src/Matrix_Algorithms.o
g++ -std=c++17 -Wall -IInclude -c Src/LU.cpp -o Src/LU.o
echo Creating Static Library (libmatrix.a)...
ar rcs libmatrix.a Src/Matrix_Methods.o Src/Matrix_Algorithms.o Src/LU.o
echo SUCCESS: Static Library built!
goto menu

:build_dynamic
echo.
echo Compiling object files with PIC...
g++ -std=c++17 -Wall -IInclude -fPIC -c Src/Matrix_Methods.cpp -o Src/Matrix_Methods.o
g++ -std=c++17 -Wall -IInclude -fPIC -c Src/Matrix_Algorithms.cpp -o Src/Matrix_Algorithms.o
g++ -std=c++17 -Wall -IInclude -fPIC -c Src/LU.cpp -o Src/LU.o
echo Creating Dynamic Library (matrix.dll)...
g++ -shared -o matrix.dll Src/Matrix_Methods.o Src/Matrix_Algorithms.o Src/LU.o
echo SUCCESS: Dynamic Library built!
goto menu

:run_main_static
if not exist libmatrix.a call :build_static
echo.
echo Compiling Main.cpp (Static)...
g++ Main.cpp -L. -lmatrix -std=c++17 -Wall -IInclude -o main_static.exe
echo Running...
main_static.exe
goto menu

:run_lu_static
if not exist libmatrix.a call :build_static
echo.
echo Compiling Main_LU.cpp (Static)...
g++ Main_LU.cpp -L. -lmatrix -std=c++17 -Wall -IInclude -o main_lu_static.exe
echo Running...
main_lu_static.exe
goto menu

:run_main_dynamic
if not exist matrix.dll call :build_dynamic
echo.
echo Compiling Main.cpp (Dynamic)...
g++ Main.cpp -L. -lmatrix -std=c++17 -Wall -IInclude -o main_dynamic.exe
echo Running (Ensure matrix.dll is in the same folder)...
main_dynamic.exe
goto menu

:clean
echo Cleaning...
powershell -Command "Remove-Item -ErrorAction SilentlyContinue *.exe, *.a, *.dll, Src/*.o"
echo Cleaned successfully.
goto menu
