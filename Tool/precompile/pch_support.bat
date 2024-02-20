@echo off

@where pch51.py >NUL 2>&1
@if %ERRORLEVEL% EQU 0 (
    pch51.py --support "ON" --user_option "ON" --target %1 --uv_file %2 --scaler_type %3 --keil_root %4
    exit 0
)

@if exist "C:\Python27\python.exe" (
    @if exist "..\Tool\precompile\pch_support.py" (
        @set PYTHONPATH=..\Tool
        "C:\Python27\python.exe" ..\Tool\precompile\pch_support.py --support "ON" --user_option "ON" --target %1 --uv_file %2 --scaler_type %3 --keil_root %4
        exit 0
    )
)

@if exist ".\Tool\precompile\pch_support.exe" (
    .\Tool\precompile\pch_support.exe --support "OFF" --target %1 --uv_file %2 --scaler_type %3 --keil_root %4 
    exit 0
)
