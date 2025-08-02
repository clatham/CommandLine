set CWD=%cd%
set PROJECT_DIR=%~dp0.


cd %PROJECT_DIR%


if exist build\ (
    rmdir /s /q build
)


cmake -B .\build -S .
cmake --build .\build --config Debug --target ALL_BUILD


cd %CWD%
