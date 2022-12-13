@echo off

pushd ..
REM SET ASSIMP_SRC="vendor\assimp"
REM SET ASSIMP_BIN="vendor\assimp"
REM mkdir %ASSIMP_BIN%
REM cmake %ASSIMP_SRC% -G "Visual Studio 17 2022" -DBUILD_SHARED_LIBS=OFF -A x64 -S %ASSIMP_SRC% -B %ASSIMP_BIN% 
vendor\bin\premake5.exe vs2022
popd
pause