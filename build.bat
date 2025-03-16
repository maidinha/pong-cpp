@echo off

REM Set the build directory
set BUILD_DIR=build
set PROJECT_NAME=pong

REM Build the project
cmake -G "MinGW Makefiles" -S . -B %BUILD_DIR%
cmake --build %BUILD_DIR%

REM Execute the project
cd %BUILD_DIR%
%PROJECT_NAME%.exe

REM Go back to the root folder, not sure why I can't execute using the folder/executable thing
cd ..