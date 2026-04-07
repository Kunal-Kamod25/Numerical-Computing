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
echo 3. Run Main Menu Solver (Main.cpp, Static)
echo 4. Run LU Solver (Main_LU.cpp, Static)
echo 5. Run Iterative Solver (Main_Iterative.cpp, Static)
echo 6. Run Gaussian Solver (Main_Gaussian.cpp, Static)
echo 7. Run Gershgorin Analysis (Main_Gershgorin.cpp, Static)
echo 8. Clean Build Files (.exe, .a, .dll, .o)
echo 9. Clean and Rebuild Fresh
echo 10. Exit
echo.
set /p choice="Choose an option (1-10): "

if "%choice%"=="1" goto build_static
if "%choice%"=="2" goto build_dynamic
if "%choice%"=="3" goto run_main_static
if "%choice%"=="4" goto run_lu_static
if "%choice%"=="5" goto run_iterative_static
if "%choice%"=="6" goto run_gaussian_static
if "%choice%"=="7" goto run_gershgorin_static
if "%choice%"=="8" goto clean
if "%choice%"=="9" goto clean_and_rebuild
if "%choice%"=="10" exit /b 0

echo Invalid choice, try again.
goto menu

:build_static
echo.
echo Compiling object files...
g++ -std=c++17 -Wall -IInclude -c Src/Matrix_Methods.cpp -o Src/Matrix_Methods.o
g++ -std=c++17 -Wall -IInclude -c Src/Matrix_Algorithms.cpp -o Src/Matrix_Algorithms.o
g++ -std=c++17 -Wall -IInclude -c Src/LU.cpp -o Src/LU.o
g++ -std=c++17 -Wall -IInclude -c Src/Iterative.cpp -o Src/Iterative.o
echo Creating Static Library (libmatrix.a)...
ar rcs libmatrix.a Src/Matrix_Methods.o Src/Matrix_Algorithms.o Src/LU.o Src/Iterative.o
echo SUCCESS: Static Library built!
goto menu

:build_dynamic
echo.
echo Compiling object files with PIC...
g++ -std=c++17 -Wall -IInclude -fPIC -c Src/Matrix_Methods.cpp -o Src/Matrix_Methods.o
g++ -std=c++17 -Wall -IInclude -fPIC -c Src/Matrix_Algorithms.cpp -o Src/Matrix_Algorithms.o
g++ -std=c++17 -Wall -IInclude -fPIC -c Src/LU.cpp -o Src/LU.o
g++ -std=c++17 -Wall -IInclude -fPIC -c Src/Iterative.cpp -o Src/Iterative.o
echo Creating Dynamic Library (matrix.dll)...
g++ -shared -o matrix.dll Src/Matrix_Methods.o Src/Matrix_Algorithms.o Src/LU.o Src/Iterative.o
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

:run_iterative_static
if not exist libmatrix.a call :build_static
echo.
echo Compiling Main_Iterative.cpp (Static)...
g++ Main_Iterative.cpp -L. -lmatrix -std=c++17 -Wall -IInclude -o main_iterative_static.exe
echo Running Iterative Solver...
main_iterative_static.exe
call :ask_open_latest_graph
goto menu

:run_gaussian_static
if not exist libmatrix.a call :build_static
echo.
echo Compiling Main_Gaussian.cpp (Static)...
g++ Main_Gaussian.cpp -L. -lmatrix -std=c++17 -Wall -IInclude -o main_gaussian_static.exe
echo Running Gaussian Solver...
main_gaussian_static.exe
goto menu

:run_gershgorin_static
if not exist libmatrix.a call :build_static
echo.
echo Compiling Main_Gershgorin.cpp (Static)...
g++ Main_Gershgorin.cpp -L. -lmatrix -std=c++17 -Wall -IInclude -o main_gershgorin_static.exe
echo Running Gershgorin Analysis...
main_gershgorin_static.exe
goto menu

:clean
echo Cleaning...
powershell -Command "Remove-Item -ErrorAction SilentlyContinue *.exe, *.a, *.dll, Src/*.o"
echo Cleaned successfully.
goto menu

:clean_and_rebuild
call :clean
echo.
echo Rebuilding static library and all split executables...
call :build_static
g++ Main.cpp -L. -lmatrix -std=c++17 -Wall -IInclude -o main_static.exe
g++ Main_LU.cpp -L. -lmatrix -std=c++17 -Wall -IInclude -o main_lu_static.exe
g++ Main_Iterative.cpp -L. -lmatrix -std=c++17 -Wall -IInclude -o main_iterative_static.exe
g++ Main_Gaussian.cpp -L. -lmatrix -std=c++17 -Wall -IInclude -o main_gaussian_static.exe
g++ Main_Gershgorin.cpp -L. -lmatrix -std=c++17 -Wall -IInclude -o main_gershgorin_static.exe
echo Fresh rebuild completed.
goto menu

:ask_open_latest_graph
set /p openGraph="Open latest generated graph image now? (y/n): "
if /I "%openGraph%"=="y" goto open_latest_graph
if /I "%openGraph%"=="yes" goto open_latest_graph
goto :eof

:open_latest_graph
for /f "usebackq delims=" %%F in (`powershell -NoProfile -Command "$f = Get-ChildItem -Path . -Filter 'graph_*.png' -File | Sort-Object LastWriteTime -Descending | Select-Object -First 1 -ExpandProperty FullName; if ($f) { $f }"`) do set "LATEST_GRAPH=%%F"

if not defined LATEST_GRAPH (
    echo No graph_*.png file found in this folder.
    goto :eof
)

echo Opening: %LATEST_GRAPH%
start "" "%LATEST_GRAPH%"
goto :eof
